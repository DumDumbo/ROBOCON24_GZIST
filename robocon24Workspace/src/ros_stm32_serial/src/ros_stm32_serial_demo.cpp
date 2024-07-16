/****************************************************************************************
 * @brief:  本文件为ROS系统与下位机STM32全双工异步串行通信例程
 * 
 * @version: 1.0
 * 
 * @date：2023/12/9
 * 
 * @author: YYY
 *                     
 * @details: 本文件通过UART串口通信方式，实现ROS系统与下位机STM32F407IIH6的全双工异步串行通信。
 *                      该例程将ROS所接收到的串口通信数据发布至“serial_data”话题。
 *                      订阅/cmd/vel话题将速度（m/s）发布至下位机。
 *            
 * @note:     基于gkorbot_serial_demo.cpp 修改而来，与源文件相比，此文件将串口数据独立发布至一个话题
 *  
 ****************************************************************************************/

#include "ros_stm32_serial_demo.h"


/*******
 * @brief:	主函数，ROS初始化
 * 			 
*********/
int main(int argc, char** argv)
{
  ros::init(argc, argv, "ros_stm32_serial_demo"); //ROS initializes and sets the node name //ROS初始化 并设置节点名称 
  robot Robot_Control; //Instantiate an object //实例化一个对象

  // 为两个函数创建线程  
  std::thread data_pub_thread(&robot::serial_data_pub, &Robot_Control);
  std::thread ros2stm32_thread(&robot::serial_ros2stm32, &Robot_Control);

  // 等待两个线程完成  
  data_pub_thread.join();
  ros2stm32_thread.join();

  
  return 0;  
} 


/*******
 * @name:   void robot::robot()
 * 
 * @brief:   构造函数

*********/
robot::robot():Cmd_Vel_Sub(n.subscribe("/cmd_vel", 1, &robot::Cmd_Vel_Callback, this)),
                              Machine_Status_Sub(n.subscribe("/machine_status", 1, &robot::MachineStatusCallback, this)), linearX(0),linearY(0),angularZ(0)
{
  //Clear the data
  //清空结构体数据
  memset(&Robot_Vel, 0, sizeof(Robot_Vel));
  memset(&Send_Data, 0, sizeof(Send_Data));
  memset(&Laser_Data, 0, sizeof(Laser_Data));
  memset(&machine_status, 0, sizeof(machine_status));

  ros::NodeHandle private_nh("~"); //Create a node handle //创建节点句柄
  //The private_nh.param() entry parameter corresponds to the initial value of the name of the parameter variable on the parameter server
  //private_nh.param()入口参数分别对应：参数服务器上的名称  参数变量名  初始值
  private_nh.param<std::string>("usart_port_name",  usart_port_name,  "/dev/USBTTL"); //Fixed serial port number //固定串口号
  private_nh.param<int>        ("serial_baud_rate", serial_baud_rate, 115200); //Communicate baud rate 115200 to the lower machine //和下位机通信波特率115200
 
  serial_data_publisher =  n.advertise<ros_stm32_serial::serial_topic_msgs>("serial_data",1);
  
  //速度话题订阅(已在构造函数初始化列表写入)
  
  //Prompt message //提示信息(绿色字体)
  ROS_INFO_STREAM("\033[1;32mros_stm32_serial_demo node Initialized \033[0m"); 
  
  try
  { 
    //Attempts to initialize and open the serial port //尝试初始化与开启串口
    Stm32_Serial.setPort(usart_port_name); //Select the serial port number to enable //选择要开启的串口号
    Stm32_Serial.setBaudrate(serial_baud_rate); //Set the baud rate //设置波特率
    serial::Timeout _time = serial::Timeout::simpleTimeout(20); //Timeout //超时等待 //单位:ms
    Stm32_Serial.setTimeout(_time);
    Stm32_Serial.open(); //Open the serial port //开启串口
  }
  catch (serial::IOException& e)
  {
    ROS_ERROR_STREAM("robot can not open serial port,Please check the serial port cable! "); //If opening the serial port fails, an error message is printed //如果开启串口失败，打印错误信息
  }
  if(Stm32_Serial.isOpen())
  {
    ROS_INFO_STREAM("\033[1;32mrobot serial port opened  \033[0m"); //Serial port opened successfully //串口开启成功提示
  }
}


/*******
 * @name:   unsigned char robot::Check_Sum(unsigned char Count_Number,unsigned char mode)
 * 
 * @brief:	串口通讯校验函数（BCC校验）
 *          数据包n有个字节，第n-1个字节为校验位，第n个字节位帧尾。
 *          第1个字节到第n-2个字节数据按位异或的结果与第n-1个字节对比，即为BCC校验
 * 
 * @param:  Count_Number：数据包前几个字节加入校验          
 *          mode：对发送数据还是接收数据进行校验
 * 
 * @retval: check_sum
*********/
unsigned char robot::Check_Sum(unsigned char Count_Number,unsigned char mode)
{
  unsigned char check_sum=0,k;
  
  if(mode==0) //Receive data mode //接收数据模式
  {
   for(k=0;k<Count_Number;k++)
    {
     check_sum=check_sum^Receive_Data.rx[k]; //By bit or by bit //按位异或
     }
  }
  if(mode==1) //Send data mode //发送数据模式
  {
   for(k=0;k<Count_Number;k++)
    {
     check_sum=check_sum^Send_Data.tx[k]; //By bit or by bit //按位异或
     }
  }
  return check_sum; //Returns the bitwise XOR result //返回按位异或结果
}


/*******************************************发送数据部分******************************************/
/************************************************************************************************/

/*******
 * @name:   void robot::serial_ros2stm32()
 * 
 * @brief:	数据发送函数。将指令通过UART串口通信方式发送至Stm32进行控制
 * 
*********/
void robot::serial_ros2stm32()
{
  short  transition;  //intermediate variable //中间变量
  while(ros::ok())
  {  
    // time1 = ros::Time::now();
    Send_Data.tx[0] = FRAME_HEADER;   //frame head 0x7B //帧头0X7B
    Send_Data.tx[1] = 0;    //target_Point1; //set aside //预留位
    Send_Data.tx[2] = 0;    //set aside //预留位

    //The target velocity of the X-axis of the robot
    //机器人x轴的目标线速度
    transition = 0;
    transition = linearX;        //因速度单位为m/s，已将浮点数放大一千倍，变成mm/s，简化传输
    Send_Data.tx[3] = transition>>8;  //取数据的高8位
    Send_Data.tx[4] = transition;     //取数据的低8位
    //The target velocity of the Y-axis of the robot
    //机器人y轴的目标线速度
    transition = 0;
    transition = linearY;    
    Send_Data.tx[5] = transition>>8;
    Send_Data.tx[6] = transition;
    //The target velocity of the Y-axis of the robot
    //机器人绕自身z轴旋转的目标角速度
    transition = 0;
    transition = angularZ;
    Send_Data.tx[7] = transition>>8;
    Send_Data.tx[8] = transition;

    // 滚筒启动控制变量
    Send_Data.tx[9] = machine_status.Roller;
    // 小球入仓模式变量
    Send_Data.tx[10] = machine_status.Mode;
    //决策小球是否选择持有
    Send_Data.tx[11] =machine_status.KeepOrNot;
    //决策小球是否释放归仓	
	  Send_Data.tx[12] = machine_status.PlaceOrNot;  		

    Send_Data.tx[13] = Check_Sum(13,SEND_DATA_CHECK); //For the BCC check bits, see the Check_Sum function //BCC校验位，规则参见Check_Sum函数
    Send_Data.tx[14] = FRAME_TAIL; //frame tail 0x7D //帧尾0X7D
    try
    {
      for (int i = 0; i < 15; i++)
      {
        /* code */
        Stm32_Serial.write(&Send_Data.tx[i], 1);

      }
    // time = (ros::Time::now()-time1).toSec();
    // std::cout<<"timeSerial"<<time<< std::endl;

      // Stm32_Serial.write(Send_Data.tx, 11); //Sends data to the downloader via serial port //通过串口向下位机发送数据 
      /* code */
    }
    catch (serial::IOException& e)   
    {
      ROS_ERROR_STREAM("Unable to send data through serial port(From function serial_ros2stm32())"); //If sending data fails, an error message is printed //如果发送数据失败，打印错误信息
    }
  }
}


/*******
 * @name:   void robot::Cmd_Vel_Callback(const geometry_msgs::Twist &twist_aux)
 * 
 * @brief:	速度话题订阅回调函数Callback
 *          The speed topic subscription Callback function
 * 
*********/
void robot::Cmd_Vel_Callback(const geometry_msgs::Twist &twist_aux)
{
  //必须在这放大倍数，因为twist_aux.linear.x为float，单位为m/s，放大1000倍数后mm/s,且小数部分都为0，
  //相当于整数，此时赋值给short类型的linearX不会出现数据丢失的情况。

  //The target velocity of the X-axis of the robot
  //机器人x轴的目标线速度
  linearX = twist_aux.linear.x *1000; //将浮点数放大一千倍，简化传输

  //The target velocity of the Y-axis of the robot
  //机器人y轴的目标线速度
  linearY = twist_aux.linear.y*1000;

  //The target angular velocity of the robot's Z axis
  //机器人z轴的目标角速度
  angularZ = twist_aux.angular.z*1000;
}



/*******
 * @name:  void robot::MachineStatusCallback(const robot_control::machine_status &msg)
 * 
 * @brief:	机械状态话题订阅回调函数Callback
 *       
 * 
*********/
void robot::MachineStatusCallback(const robot_control::machine_status &msg)
{
  machine_status.Roller = msg.Roller;
  machine_status.Mode = msg.Mode;
  machine_status.KeepOrNot = msg.KeepOrNot;
  machine_status.PlaceOrNot = msg.PlaceOrNot;
  machine_status.RobotStatus = msg.RobotStatus;
}



/*******************************************接收数据部分******************************************/
/************************************************************************************************/

/*******
 * @name:   robot::Odom_Trans(uint8_t Data_High,uint8_t Data_Low)
 * 
 * @brief:	速度转换函数，将拆分成8位的数据拼接成16位，并转换成float类型返回。
 * 
 * @param： uint8_t Data_High：高八位数据
 *          uint8_t Data_Low： 低八位数据
 * 
 * @retval: data_return
*********/
float robot::Odom_Trans(uint8_t Data_High,uint8_t Data_Low)
{
  float data_return;
  short transition_16;
  transition_16 = 0;
  transition_16 |=  Data_High<<8;  //Get the high 8 bits of data   //获取数据的高8位
  transition_16 |=  Data_Low;      //Get the lowest 8 bits of data //获取数据的低8位
  data_return   =  (transition_16 / 1000)+(transition_16 % 1000)*0.001; // The speed unit is changed from mm/s to m/s //速度单位从mm/s转换为m/s
  return data_return;
}



/*******
 * @name:   robot::Laser_Trans(uint8_t Data_High,uint8_t Data_Low)
 * 
 * @brief:	速度转换函数，将拆分成8位的数据拼接成16位，并转换成unsigned short类型返回。
 * 
 * @param： uint8_t Data_High：高八位数据
 *                        uint8_t Data_Low： 低八位数据
 * 
 * @retval: data_return
*********/
unsigned short robot::Laser_Trans(uint8_t Data_High,uint8_t Data_Low)
{
  unsigned short transition_16;
  transition_16 = 0;
  transition_16 |=  Data_High<<8;  //Get the high 8 bits of data   //获取数据的高8位
  transition_16 |=  Data_Low;      //Get the lowest 8 bits of data //获取数据的低8位
  return transition_16;
}



/*******
 * @name:   void robot::pub_serial_data()
 * 
 * @brief:	stm32上传数据的话题发布函数
 *               
 * 
*********/
void robot::pub_serial_data()
{
    //实例化数据消息
    ros_stm32_serial::serial_topic_msgs serialMsg;
    //数据赋值 
    serialMsg.flag =  Receive_Data.Sensor_Str.Flag;
    serialMsg.status = Receive_Data.Sensor_Str.Status;
    serialMsg.linearX = Robot_Vel.X;
    serialMsg.linearY = Robot_Vel.Y;
    serialMsg.angularZ = Robot_Vel.Z;
    serialMsg.LaserFront =  Laser_Data.LaserFront;
    serialMsg.LaserL =  Laser_Data.LaserL;
    serialMsg.LaserR =  Laser_Data.LaserR;
    serialMsg.LaserRear =  Laser_Data.LaserRear;
    serialMsg.Roller = machine_status.Roller;
    serialMsg.Mode = machine_status.Mode;
    serialMsg.KeepOrNot = machine_status.KeepOrNot;
    serialMsg.PlaceOrNot = machine_status.PlaceOrNot;
    serialMsg.RobotStatus = machine_status.RobotStatus;
    
    //发布来自下位机的串口数据话题
    serial_data_publisher.publish(serialMsg); 
  
}


/*******
 * @name:   bool robot::serial_data_from_stm32()
 * 
 * @brief:	ROS从Stm32接收数据函数
 *          Receiving data from Stm32
 * 
*********/
bool robot::serial_data_from_stm32()
{
  short transition_16=0; //Intermediate variable //中间变量
  uint8_t check=0, error=1,Receive_Data_Pr[1]; //Temporary variable to save the data of the lower machine //临时变量，保存下位机数据
  static int count; //Static variable for counting //静态变量，用于计数


  Stm32_Serial.read(Receive_Data_Pr,sizeof(Receive_Data_Pr)); //Read the data sent by the lower computer through the serial port //通过串口读取下位机发送过来的数据

  Receive_Data.rx[count] = Receive_Data_Pr[0]; //Fill the array with serial data //串口数据填入数组

  //固定数据赋值
  Receive_Data.Sensor_Str.Frame_Header = Receive_Data.rx[0]; //The first part of the data is the frame header 0X7B //数据的第一位是帧头0X7B
  Receive_Data.Sensor_Str.Frame_Tail = Receive_Data.rx[18];  //The last bit of data is frame tail 0X7D //数据的最后一位是帧尾0X7D

  if(Receive_Data_Pr[0] == FRAME_HEADER || count>0)//Ensure that the first data in the array is FRAME_HEADER //确保数组第一个数据为FRAME_HEADER
  {
    count++;
  } 
    
  else
    count=0;

  if(count == 19) //Verify the length of the packet //验证数据包的长度
  {
    count=0;  //Prepare for the serial port data to be refill into the array //为串口数据重新填入数组做准备
    
    if(Receive_Data.Sensor_Str.Frame_Tail == FRAME_TAIL) //Verify the frame tail of the packet //验证数据包的帧尾
    {
      check=Check_Sum(17,READ_DATA_CHECK);  //BCC check passes or two packets are interlaced //BCC校验通过或者两组数据包交错
      
      if(check == Receive_Data.rx[17])  
      {
        error=0;  //XOR bit check successful //异或位校验成功
      }

      if(error == 0)
      {
        Receive_Data.Sensor_Str.Flag = Receive_Data.rx[1]; //set aside //预留位
        Receive_Data.Sensor_Str.Status = Receive_Data.rx[2]; //set aside //预留位
        // 速度数据
        Robot_Vel.X = Odom_Trans(Receive_Data.rx[3],Receive_Data.rx[4]); //Get the speed of the moving chassis in the X direction //获取运动底盘X方向速度
        Robot_Vel.Y = Odom_Trans(Receive_Data.rx[5],Receive_Data.rx[6]); //Get the speed of the moving chassis in the Y direction//获取运动底盘Y方向速度
        Robot_Vel.Z = Odom_Trans(Receive_Data.rx[7],Receive_Data.rx[8]); //Get the speed of the moving chassis in the Z direction //获取运动底盘Z方向速度   
        //  激光测距数据
        Laser_Data.LaserL = Laser_Trans(Receive_Data.rx[9], Receive_Data.rx[10]);
        Laser_Data.LaserR = Laser_Trans(Receive_Data.rx[11], Receive_Data.rx[12]);
        Laser_Data.LaserFront = Laser_Trans(Receive_Data.rx[13], Receive_Data.rx[14]);
        Laser_Data.LaserRear = Laser_Trans(Receive_Data.rx[15], Receive_Data.rx[16]);

        return true;
      } 
    }
  }
  return false;
}

/*******
 * @name:   void robot::serial_data_pub()
 * 
 * @brief:	循环获取下位机数据与发布话题
 * 
*********/
void robot::serial_data_pub()
{
  while(ros::ok())
  {
    if (true == serial_data_from_stm32()) 
    {
      pub_serial_data(); //发布接收数据话题
    }
    ros::spinOnce();   //循环等待回调函数
  }
}

