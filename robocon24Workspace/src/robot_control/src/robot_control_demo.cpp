/****************************************************************************************
 * @brief:  
 * 
 * @version: 1.0
 * 
 * @author: YYY
 *                     
 * @details:  
 *
 * @note: 
 ****************************************************************************************/


#include "robot_control_demo.h"



int main(int argc, char** argv)
{
    // 初始化节点
    ros::init(argc, argv, "robot_control_demo");
    //实例化控制器对象
    RcController Control;
    PIDController PID;
    //进行机器人相关参数初始化(实例化类后构造函数会自动启用)
    ROS_INFO_STREAM("\033[1;32mRobotControl Node Initialized\033[0m");
    
    // 创建线程 
    std::thread CallbackThread(&RcController::CallbackThread, &Control);   // 负责回调运行
    std::thread MotionContorl(&RcController::UnifiedControl, &Control);  // 归仓运动
    // 等待完成
    CallbackThread.join();
    MotionContorl.join();
    
    return 0 ;
}



/*******
 * @name:  PIDController::PIDController()
 * 
 * @brief:  构造函数, 只执行一次，用于初始化
*********/
PIDController::PIDController(): nh("~")
{
    // 全局话题名称
    pidDataPub = nh.advertise<robot_control::msg4pid>("/pid",  10);

    // 从launch文件，参数服务器中读取PID参数，默认值为0
    nh.param("kp_x", kp_x, 0.0);       // 右手坐标系X轴
    nh.param("ki_x", ki_x, 0.0);
    nh.param("kd_x", kd_x, 0.0);
    nh.param("integral_x", integral_x, 0.0);
    nh.param("prev_error_x", prev_error_x, 0.0);

    nh.param("kp_y", kp_y, 0.0);        // 右手坐标系Y轴
    nh.param("ki_y", ki_y, 0.0);
    nh.param("kd_y", kd_y, 0.0);
    nh.param("integral_y", integral_y, 0.0);
    nh.param("prev_error_y", prev_error_y, 0.0);

    nh.param("kp_z", kp_z, 0.0);        // 右手坐标系Z轴
    nh.param("ki_z", ki_z, 0.0);
    nh.param("kd_z", kd_z, 0.0);
    nh.param("integral_z", integral_z, 0.0);
    nh.param("prev_error_z", prev_error_z, 0.0);

    nh.param("kp_yaw", kp_yaw, 0.0);        // 航向角
    nh.param("ki_yaw", ki_yaw, 0.0);
    nh.param("kd_yaw", kd_yaw, 0.0);
    nh.param("integral_yaw", integral_yaw, 0.0);
    nh.param("prev_error_yaw", prev_error_yaw, 0.0);

    ros::Time now = ros::Time::now();
    _Last_Time_x = now;
    _Last_Time_y = now;
    _Last_Time_z = now;
    _Last_Time_yaw = now;
}




/*******
 * @name:  void PIDController::pidParameterPub(double kp, double ki, double kd,double  feedback, double setpoint)
 * 
 * @brief:  pid参数发布函数（用于可视化pid调参）
*********/
void PIDController::pidParameterPub(double kp, double ki, double kd,double  setpoint, double feedback)
{
    robot_control::msg4pid msg;
    msg.kp = kp; 
    msg.ki = ki;
    msg.kd = kd;
    msg.feedback = feedback;
    msg.setpoint = setpoint;
    pidDataPub.publish(msg);
}



/*******
 * @name:  double PIDController::computeCommandLocationForYaw(double setpoint, double feedback)
 * 
 * @brief:  位置式PID(供Yaw使用)
*********/
double PIDController::computeCommandLocationForYaw(double setpoint, double feedback){
    
    _Now_yaw = ros::Time::now();                // 获取当前时间
    dt_yaw = (_Now_yaw - _Last_Time_yaw).toSec();       // 计算积分时间

    double error = setpoint-feedback;     //计算误差

    // 防止逆旋转
    if(abs(error) > 180)
    {
        if(error <0){error = 360+error;}
        else if(error >0){error = error-360;}
    }


    integral_yaw +=error * dt_yaw;                  //更新积分项
    derivative_yaw = (error-prev_error_yaw) / dt_yaw;   //计算微分项

    output_yaw = kp_yaw*error + ki_yaw*integral_yaw + kd_yaw*derivative_yaw; // 计算控制输出

    prev_error_yaw = error;

    _Last_Time_yaw = _Now_yaw;
    
    // std::cout <<"dt_yaw:"<< dt_yaw<< std::endl;
    // std::cout <<"error:"<< error<< std::endl;
    
    // 用于pid可视化调参，调完参数注释即可
    // pidParameterPub(kp_yaw, ki_yaw, kd_yaw,setpoint, feedback);
    
    return output_yaw;
}



/*******
 * @name:  double PIDController::computeCommandLocationForZ(double setpoint, double feedback)
 * 
 * @brief:  位置式PID(供Z轴使用)
*********/
double PIDController::computeCommandLocationForZ(double setpoint, double feedback){
    
    _Now_z = ros::Time::now();                // 获取当前时间
    dt_z = (_Now_z - _Last_Time_z).toSec();       // 计算积分时间

    double error = setpoint-feedback;     //计算误差
    
    // 防止逆旋转
    if(abs(error) > 180)
    {
        if(error <0){error = 360+error;}
        else if(error >0){error = error-360;}
    }
    
    integral_z +=error * dt_z;                  //更新积分项
    derivative_z = (error-prev_error_z) / dt_z;   //计算微分项

    output_z = kp_z*error + ki_z*integral_z + kd_z*derivative_z; // 计算控制输出

    prev_error_z = error;

    _Last_Time_z = _Now_z;
    
    // std::cout <<"dt_z:"<< dt_z<< std::endl;
    // std::cout <<"error:"<< error<< std::endl;
    
    // 用于pid可视化调参，调完参数注释即可
    // pidParameterPub(kp_z, ki_z, kd_z,setpoint, feedback);
    
    return output_z;
}



/*******
 * @name:  double PIDController::computeCommandLocationForY(double setpoint, double feedback)
 * 
 * @brief:  位置式PID(供Y轴使用)
*********/
double PIDController::computeCommandLocationForY(double setpoint, double feedback){
    
    _Now_y = ros::Time::now();                // 获取当前时间
    dt_y = (_Now_y - _Last_Time_y).toSec();       // 计算积分时间

    double error = setpoint-feedback;     //计算误差
    integral_y +=error * dt_y;                  //更新积分项
    derivative_y = (error-prev_error_y) / dt_y;   //计算微分项

    output_y = kp_y*error + ki_y*integral_y + kd_y*derivative_y; // 计算控制输出

    prev_error_y = error;

    _Last_Time_y = _Now_y;
    
    // std::cout <<"dt_y:"<< dt_y<< std::endl;

    // 用于pid可视化调参，调完参数注释即可
    // pidParameterPub(kp_y, ki_y, kd_y,setpoint, feedback);

    return output_y;
}



/*******
 * @name:  double PIDController::computeCommandLocationForX(double setpoint, double feedback)
 * 
 * @brief:  位置式pid (供给X轴使用)
*********/
double PIDController::computeCommandLocationForX(double setpoint, double feedback){

    _Now_x = ros::Time::now();                // 获取当前时间
    dt_x = (_Now_x - _Last_Time_x).toSec();       // 计算积分时间

    double error =setpoint-feedback;     //计算误差
    integral_x +=error * dt_x;                  //更新积分项
    derivative_x = (error-prev_error_x) / dt_x;   //计算微分项

    output_x = kp_x*error + ki_x*integral_x + kd_x*derivative_x; // 计算控制输出

    prev_error_x = error;

    _Last_Time_x = _Now_x;
    
    // std::cout <<"dt_x:"<< dt_x<< std::endl;

    // 用于pid可视化调参，调完参数注释即可
    // pidParameterPub(kp_x, ki_x, kd_x,setpoint, feedback);

    return output_x;
}



/*******
 * @name:  RcController::RcController()
 * 
 * @brief:  构造函数, 只执行一次，用于初始化
*********/
RcController::RcController(): n("~"), flag1(0), initial_orientation_set(false), last_time(ros::Time::now()), RobotStatus("Initializing"),areaColor("False"), barnsIndex(0), barn_status({std::vector<std::string>(5,  "False")})
{
    // 结构体数据清零
    memset(&Imu_Data, 0, sizeof(Imu_Data));
    memset(&target_pos, 0, sizeof(target_pos));
    memset(&robot_pos, 0, sizeof(robot_pos));
    memset(&Laser_Ranging, 0 , sizeof(Laser_Ranging));
    memset(&machine_status, 5 , sizeof(machine_status));

    // 自定义变量清零
    current_orientation.getIdentity();          //小车当前姿态（四元数） 

    // 初始化谷仓位置的映射
    barnMap = {
        {0,{0.160f, 0.01f}},
        {1,{0.910f, 0.01f}},
        {2,{1.660f, 0.01f}},
        {3,{2.410f, 0.01f}},
        {4,{3.160f, 0.01f}}
    };

    barnX = -1;
    barnY = -1;
    ResetMachine = false; // 复位排球机构

    // 相关话题订阅
    imu_Sub = n.subscribe("/wit/imu", 10, &RcController::imuCallback, this);
    locked_Sub = n.subscribe("/Locked", 10, &RcController::lockedCallback, this);
    // robotOdom_Sub = n.subscribe("/robot_pose_ekf/odom_combined", 10, &RcController::robotOdomCallback, this);
    serialMsg_Sub = n.subscribe("/serial_data", 10, &RcController::serialMsgCallback, this);
    barn_sub = n.subscribe("/barn_status", 10, &RcController::barnCallback, this);
    ballColor_sub = n.subscribe("/color_detected", 10, &RcController::ballColorCallback, this);

    // 话题发布者(全局名称话题)
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
    machine_contorl_pub =  n.advertise<robot_control::machine_status>("/machine_status", 10);
}



/*******
 * @name:  double RcController::limitSpeed(double speed, double max_speed) 
 * 
 * @brief:  用于显示机器人各轴的运动速度
*********/
double RcController::limitSpeed(double speed, double max_speed){
    return (speed > max_speed) ? max_speed : (speed < -max_speed) ? -max_speed : speed;
}



/*******
 * @name:  double RcController::computeLimitedPIDOutput(char axis, double setpoint, double feedback, double max_speed) 
 * 
 * @brief:  PID计算调用接口（坐标系编号，目标值，反馈值，最大速度）
*********/
double RcController::computeLimitedPIDOutput(char axis, double setpoint, double feedback, double max_speed){
    double pid_output = 0.0;
    switch (axis) {
        case 'x': pid_output = PID.computeCommandLocationForX(setpoint, feedback); break;
        case 'y': pid_output = PID.computeCommandLocationForY(setpoint, feedback); break;
        case 'z': pid_output = PID.computeCommandLocationForZ(setpoint, feedback); break;
        case 'w': pid_output = PID.computeCommandLocationForYaw(setpoint, feedback); break;
        default: throw std::invalid_argument("Invalid axis");
    }
    return limitSpeed(pid_output, max_speed);
}




/*******
 * @name:   void RcController::barnCallback(const yolov5_ros_msgs::BoundingBoxes::ConstPtr& boxes_msg);
 * 
 * @brief:  谷仓状态话题回调函数
*********/
void RcController::barnCallback(const yolov5_ros_msgs::BoundingBoxes::ConstPtr& barn_msg)
{
    if(barn_msg->bounding_boxes.size() == 5){
        // 将bounding_boxes拷贝至sortBoxes进行排列
        std::vector<yolov5_ros_msgs::BoundingBox> sortBoxes = barn_msg->bounding_boxes;
        areaColor = "Red";
        // 开始排序
        if (areaColor == "Red") {
            std::sort(sortBoxes.begin(), sortBoxes.end(), [](const yolov5_ros_msgs::BoundingBox& a, const yolov5_ros_msgs::BoundingBox& b){
                return a.xmin < b.xmin;});  // 按照 xmin 从小到大排序
        }
        else if (areaColor == "Blue") {
            std::sort(sortBoxes.begin(), sortBoxes.end(), [](const yolov5_ros_msgs::BoundingBox& a, const yolov5_ros_msgs::BoundingBox& b){
                return a.xmin > b.xmin;}); // 按照 xmin 从小到大排序
        }

        // 结构体赋值
        for(int i =0; i<5; ++i){
            barn_status.barns[i] = sortBoxes[i].Class;
        }

        // 计算权重
        auto calculateWeight = [](const std::string& label, bool isRed) {
            if (label == "None")
                return 0.2;
            else if (label == "R")
                return isRed ? 0.4 : 0.1;
            else if (label == "RR")
                return isRed ? 0.8 : 0.6;
            else if (label == "RB" || label == "BR")
                return 1.0;
            else if (label == "B")
                return isRed ? 0.1 : 0.4;
            else if (label == "BB")
                return isRed ? 0.6 : 0.8;
            else
                return 0.0;
        };

        double maxWeight = 0.0;
        barnsIndex = 0;
        double weight = 0.0;
        // 遍历五个谷仓，选择最大权重的谷仓作为目标
        for(int i=0; i<5; ++i){
            if(areaColor == "Red"){weight = calculateWeight(barn_status.barns[i], true);}
            else if(areaColor == "Blue"){weight = calculateWeight(barn_status.barns[i], false);}
            if(weight > maxWeight){
                maxWeight = weight;
                barnsIndex = i;}
        }

        // 检查 barnsIndex 是否在 barnMap 中
        if (barnMap.find(barnsIndex) != barnMap.end()) {
            // 获取对应的 BarnInfo
            BARN_POSITION_INDEX info = barnMap.at(barnsIndex);
            barnX = info.Rear;
            barnY = info.sideFace;
            // std::cout << "BarnsIndex: " << barnsIndex << ", sideFace: " << info.sideFace << ", Rear: " << info.Rear << std::endl;
            }

    }
    else{ROS_WARN("No enough barn received!");}
    // ROS_INFO_STREAM("\033[1;32mBarn1: \033[0m" << barn_status.barns[0]);
    // ROS_INFO_STREAM("\033[1;32mBarn2: \033[0m" << barn_status.barns[1]);
    // ROS_INFO_STREAM("\033[1;32mBarn3: \033[0m" << barn_status.barns[2]);
    // ROS_INFO_STREAM("\033[1;32mBarn4: \033[0m" << barn_status.barns[3]);
    // ROS_INFO_STREAM("\033[1;32mBarn5: \033[0m" << barn_status.barns[4]);
    // ROS_INFO_STREAM("\033[1;32mareaColor: \033[0m" << areaColor);

}



/*******
 * @name:   void RcController::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg)
 * 
 * @brief:  imu话题回调函数
*********/
void RcController::imuCallback(const sensor_msgs::Imu::ConstPtr& imu_msg)
{
    // 从imu话题获取小车当前姿态
    current_orientation.setX(imu_msg->orientation.x);
    current_orientation.setY(imu_msg->orientation.y);
    current_orientation.setZ(imu_msg->orientation.z);
    current_orientation.setW(imu_msg->orientation.w);

    // 将四元数姿态解算欧拉角，范围-180°~180°
    tf2::Matrix3x3(current_orientation).getRPY(roll, pitch, yaw);
    Imu_Data.Euler.roll =  std::floor((roll * 180.0 / M_PI)*10)/10;
    Imu_Data.Euler.pitch =  std::floor((pitch * 180.0 / M_PI)*10)/10;
    Imu_Data.Euler.yaw = std::floor((yaw * 180.0 / M_PI)*10)/10;
 

    // 如果imu上电时尚未设置初始目标值，则设置初始目标值并停止记录
    if (!initial_orientation_set) {
        // 设置初始目标值
        initial_orientation_set = true;
        initial_roll = std::floor(Imu_Data.Euler.roll*10)/10;
        initial_pitch = std::floor(Imu_Data.Euler.pitch*10)/10;
        initial_yaw = std::floor(Imu_Data.Euler.yaw*10)/10;
        search_yaw = initial_yaw;
        RobotStatus = "Initialized";
        // 输出初始目标值
        ROS_INFO_STREAM("\033[1;32mInitial Roll: \033[0m" << initial_roll);
        ROS_INFO_STREAM("\033[1;32mInitial Pitch: \033[0m" << initial_pitch);
        ROS_INFO_STREAM("\033[1;32mInitial Yaw: \033[0m" << initial_yaw);
        ROS_INFO_STREAM("\033[1;32mRobot Status: \033[0m" << RobotStatus);
    }
}



/*******
 * @name:  void lockedCallback(const target_detection::Locked::ConstPtr& locked_msg);
 * 
 * @brief:  目标小球数据回调函数
*********/
void RcController::lockedCallback(const target_detection::Locked::ConstPtr& locked_msg)
{
    pos = locked_msg->pos[0];
    target_pos.Class = pos.Class;
    // 目标小球三维坐标
    if((pos.Class == "BlueBall" || pos.Class == "RedBall") && 
        (pos.centerX_3 == 0.15 || pos.centerX_3 == 0.015)){
        target_pos.x3 = 0.0;
        target_pos.y3 = 0.0;
        target_pos.z3 = 0.0;}
    else{ 
        target_pos.x3 = pos.centerX_3;   //单位m
        target_pos.y3 = pos.centerY_3; 
        target_pos.z3 = pos.centerZ_3;}
    // 依据视场获取的角度，单位degree
    target_pos.angleX = pos.angleX;         
    target_pos.angleY =  pos.angleY;
    // 目标框像素点
    target_pos.centerX = pos.centerX;
    target_pos.centerY = pos.centerY;
}



/*******
 * @name:   
 * 
 * @brief:
*********/
void RcController::ballColorCallback(const std_msgs::String& ballColormsg)
{
    ballColor = ballColormsg.data;
}



/*******
 * @name:   void RcController::robotOdomCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& robotOdom_msg)
 * 
 * @brief:  odom_combined/position话题回调函数
*********/
// void RcController::robotOdomCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& robotOdom_msg)
// {
//     robot_pos.posX = robotOdom_msg->pose.pose.position.x;
//     robot_pos.posY = robotOdom_msg->pose.pose.position.y;
//     robot_pos.posZ = robotOdom_msg->pose.pose.position.z;
// }



/*******
 * @name:   string RcController::getAreaColor()
 * 
 * @brief:      
*********/
string RcController::getAreaColor()
{
    // Assuming Laser_Ranging is a class or structure that has members LaserL and LaserR
    if (Laser_Ranging.LaserL == Laser_Ranging.LaserR){
        return "false";
    }
    else{
        return (Laser_Ranging.LaserL < Laser_Ranging.LaserR) ? "Red" : "Blue";
    }
}




/*******
 * @name:  void RcController::machineStatusPub()
 * 
 * @brief:  
*********/
void RcController::machineStatusPub()
{
    robot_control::machine_status msg;
    msg.Roller = machine_status.Roller; 
    msg.Mode = machine_status.Mode;
    msg.KeepOrNot = machine_status.KeepOrNot;
    msg.PlaceOrNot = machine_status.PlaceOrNot;
    msg.RobotStatus = RobotStatus;
    machine_contorl_pub.publish(msg);
}



/*******
 * @name:   void RcController::serialMsgCallback(const ros_stm32_serial::serial_topic_msgs& serial_msg)
 * @brief:  通讯话题回调函数，用于获取通讯话题中的激光测距数据
*********/
void RcController::serialMsgCallback(const ros_stm32_serial::serial_topic_msgs& serial_msg)
{
    // 获取激光测距数据，将单位由mm转化为为m
    Laser_Ranging.LaserFront = serial_msg.LaserFront / 1000.0;
    Laser_Ranging.LaserL = serial_msg.LaserL / 1000.0;
    Laser_Ranging.LaserR = serial_msg.LaserR / 1000.0;
    Laser_Ranging.LaserRear = serial_msg.LaserRear / 1000.0;

    // 根据机器人实际速度,计算里程计
    ros::Time current_time = ros::Time::now();
    double Sampling_Time =(current_time - last_time).toSec();
    robot_pos.posX += (serial_msg.linearX * cos(serial_msg.angularZ) - serial_msg.linearY * sin(serial_msg.angularZ)) *  Sampling_Time;
    robot_pos.posY +=(serial_msg.linearX * sin(serial_msg.angularZ) + serial_msg.linearY * cos( serial_msg.angularZ)) * Sampling_Time;
    robot_pos.posZ = serial_msg.angularZ *Sampling_Time;
    last_time = current_time;
    
    // 根据复位标志位是否复位机器人状态
    if(serial_msg.flag == 1.0){
        RobotStatus = "Reset";
        machine_status.Mode =1;
        machine_status.PlaceOrNot =0;}
}



/*******
 * @name: void handleInitialMovement(float& laserD, ros::Rate& rate)
 * 
 * @brief:  
*********/
void RcController::handleInitialMovement(float& laserD, ros::Rate& rate)
{
    std::cout << "RobotStatus: " << RobotStatus << std::endl;

    if (areaColor != "Red" && areaColor != "Blue") {
        RobotStatus = "Initialized";
        rate.sleep();
        return;
    }

    laserD = (areaColor == "Red") ? Laser_Ranging.LaserR : Laser_Ranging.LaserL;
    // if(RobotStatus == "InitialMovementPoint2"){
    //     laserD = KeepY;} 
    if(RobotStatus == "InitialMovementPoint3" && laserD <= 1.6){
        laserD = 3.5;}

    PIDOutputX = computeLimitedPIDOutput('x', KeepX, Laser_Ranging.LaserFront, 1.16);
    PIDOutputY = computeLimitedPIDOutput('y', KeepY, laserD, 1.16);
    PIDOutputYaw = computeLimitedPIDOutput('w', initial_yaw, Imu_Data.Euler.yaw, 1.0);

    // 机器人在接近point3中会出现后退现象，故加此判断提前退出y轴与边界的保持性，消除该现象
    if (RobotStatus == "InitialMovementPoint2" && Laser_Ranging.LaserFront >= 2.5){
        PIDOutputY = 0.0;}
    cmd_vel_msg.linear.x = -PIDOutputX;
    cmd_vel_msg.linear.y =  (areaColor == "Red") ? PIDOutputY : -PIDOutputY;
    cmd_vel_msg.angular.z =  -PIDOutputYaw;

    std::cout << "cmd_vel_msg.linear.x: " << cmd_vel_msg.linear.x << std::endl;
    std::cout << "cmd_vel_msg.linear.y: " << cmd_vel_msg.linear.y << std::endl;
    std::cout << "cmd_vel_msg.angular.z: " << cmd_vel_msg.angular.z << std::endl;
    std::cout << "laserD: " << laserD << std::endl;

    // 以下为改变机器人状态的判断
    if (RobotStatus == "InitialMovementPoint1" && (0.050 < laserD && laserD<= 0.37)) {
        KeepX = 3.980;
        KeepY = 0.300;
        RobotStatus = "InitialMovementPoint2";
    } 
    else if (RobotStatus == "InitialMovementPoint2" && Laser_Ranging.LaserFront >= KeepX-0.035){
        KeepX = 0.0;
        KeepY = 1.66;
        RobotStatus = "InitialMovementPoint3";
    } 
    else if (RobotStatus == "InitialMovementPoint3") {
        cmd_vel_msg.linear.x = 0.0;
        cmd_vel_msg.linear.y = (areaColor == "Red") ? PIDOutputY : -PIDOutputY;
        cmd_vel_msg.angular.z = -PIDOutputYaw;
        if (1.6< laserD && laserD <= 3.1) {
            KeepX = 1.0;
            KeepY = 1.66;
            RobotStatus = "InitialMovementPoint4";}
    }
    else if(RobotStatus == "InitialMovementPoint4"){
        cmd_vel_msg.linear.x = -PIDOutputX;
        cmd_vel_msg.linear.y = 0.0;
        cmd_vel_msg.angular.z = -PIDOutputYaw;
        if(Laser_Ranging.LaserFront<2.3){
            cmd_vel_msg.linear.x = 0.0;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = -PIDOutputYaw;
            // 清空里程
            robot_pos.posX =0.0;
            robot_pos.posY =0.0;
            robot_pos.posZ = 0.0;
            // 更改状态
            KeepY =  (areaColor == "Red") ? 1.43 : -1.43;
            RobotStatus = "InitialMovementPoint5";}
    } 
    else if (RobotStatus == "InitialMovementPoint5"){
        PIDOutputY = computeLimitedPIDOutput('y', KeepY, robot_pos.posY, 1.0);
        cmd_vel_msg.linear.x = 0.0;
        cmd_vel_msg.linear.y =  (areaColor == "Red") ? -PIDOutputY : PIDOutputY;
        cmd_vel_msg.angular.z = -PIDOutputYaw;
        if(robot_pos.posY  > 0.7 || robot_pos.posY <-0.7){
            cmd_vel_msg.linear.x = 0.0;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = 0.0;
            // 清空里程
            robot_pos.posX =0.0;
            robot_pos.posY =0.0;
            robot_pos.posZ = 0.0;
            RobotStatus = "GrainSearch";}
        }        
}



/*******
 * @name: void::handlePreGrainSearch(float& laserD, ros::Rate& rate)
 * 
 * @brief:  
*********/
void RcController::handlePreGrainSearch(float& laserD, ros::Rate& rate)
{
    KeepX = 1.58;
    KeepY = 1.66;

    std::cout << "RobotStatus: " << RobotStatus << std::endl;
    if (areaColor != "Red" && areaColor != "Blue") {
        RobotStatus = "Initialized";
        rate.sleep();
        return;
    }
    // 获取激光测距数据
    laserD = (areaColor == "Red") ? Laser_Ranging.LaserR : Laser_Ranging.LaserL;
    // 计算速度
    PIDOutputX = computeLimitedPIDOutput('x', KeepX, Laser_Ranging.LaserRear, 0.9);
    PIDOutputY = computeLimitedPIDOutput('y', KeepY, laserD, 1.16);
    PIDOutputYaw = computeLimitedPIDOutput('w', initial_yaw, Imu_Data.Euler.yaw, 1.0);
    // 速度赋值
    cmd_vel_msg.linear.x = PIDOutputX;
    cmd_vel_msg.linear.y = (areaColor == "Red") ? PIDOutputY : -PIDOutputY;
    cmd_vel_msg.angular.z = -PIDOutputYaw;

    if ((1.50 <= laserD && laserD <= 1.81) && Laser_Ranging.LaserRear >=1.45) {
        // 速度赋值
        cmd_vel_msg.linear.x = 0.0;
        cmd_vel_msg.linear.y = 0.0;
        cmd_vel_msg.angular.z = 0.0;
        // 清零
        RobotStatus = "GrainSearch";}
}



/*******
 * @name: void handleSearching(bool& aligned_with_ball, ros::Rate& rate)
 * 
 * @brief:  
*********/
void RcController::handleSearching(bool& aligned_with_ball, ros::Rate& rate)
{
    std::cout << "RobotStatus: " << RobotStatus << std::endl;
    if(RobotStatus == "GrainSearch"){
        machine_status.Roller = 1; // 开启滚筒
        float targetZ = 325.0; // 对准小球的目标像素点
        if(ResetMachine == true){
            ros::Duration(1.0).sleep();
            machine_status.Mode = 0; // 寻球模式
            machine_status.KeepOrNot = 0; //设置内部拾取机构为复位状态
            ResetMachine = false;
        }
        if (ballColor == "Red" || ballColor == "Blue"){
            // 速度设置 
            cmd_vel_msg.linear.x = 0.0;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = 0.0;
            // 机械结构设置
            machine_status.Mode=1;                 //模式置为归仓模式 
            machine_status.PlaceOrNot =1;    //机构升起
            // 清零里程计
            robot_pos.posX = 0.0;
            robot_pos.posY = 0.0;
            robot_pos.posZ = 0.0;
            // 更改机器人状态
            RobotStatus = "PreHoming";
            aligned_with_ball = false;
            ballColor = "None";
            // 返回，不执行下列后续程序
            return;
        }
        else if(ballColor == "Purple"){
            // 速度设置 
            cmd_vel_msg.linear.x = 0.0;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = 0.0;
            // 机械结构置位
            machine_status.Mode=0;                 //模式置为寻球模式 
            machine_status.KeepOrNot = (Laser_Ranging.LaserL >= Laser_Ranging.LaserR) ? 1 : 2;    //1:左排  2:右排
            // 复位
            aligned_with_ball = false;
            ResetMachine = true;
            ballColor = "None";
            // 返回，不执行下列后续程序
            return;
        }             

        // 判断有无对准球
        if (!aligned_with_ball && !ResetMachine && (target_pos.Class == "BlueBall" || target_pos.Class == "RedBall")){//没对准时，旋转进行对准
            //计算速度 
            PIDOutputZ = computeLimitedPIDOutput('z', targetZ, target_pos.centerX, 1.0);
            // 速度赋值
            cmd_vel_msg.linear.x = 0.0;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = -PIDOutputZ;
            // 判断球与中心是否对准
            if (322 <= target_pos.centerX && target_pos.centerX <=327){
                aligned_with_ball = true;
                search_yaw = Imu_Data.Euler.yaw;}
                // 使用里程将下面打开
                // KeepX = target_pos.x3;
                // KeepY = target_pos.y3;} 
        }
        else if(target_pos.Class == "None"){//若“没对准球”且“画面中无球”时，机器人后退
            PIDOutputYaw = computeLimitedPIDOutput('w', initial_yaw, Imu_Data.Euler.yaw, 1.0);
            aligned_with_ball = false;
            cmd_vel_msg.linear.x = -0.5;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = -PIDOutputYaw;
        }
        else{
            // 计算速度
            PIDOutputX = computeLimitedPIDOutput('x',0.0, target_pos.x3, 1.16);
            PIDOutputY = computeLimitedPIDOutput('y', 0.0, target_pos.y3, 1.16);
            PIDOutputYaw = computeLimitedPIDOutput('w', search_yaw, Imu_Data.Euler.yaw, 1.0);
            if (ballColor == "None" && aligned_with_ball==true){
                cmd_vel_msg.linear.x = -PIDOutputX;
                cmd_vel_msg.linear.y = -PIDOutputY;
                cmd_vel_msg.angular.z = -PIDOutputYaw;}
        }
    }
    else{
        cmd_vel_msg.linear.x = 0.0;
        cmd_vel_msg.linear.y = 0.0;
        cmd_vel_msg.angular.z = 0.0;
        RobotStatus = "Something went wrong, Please Check line 721";
    }
    //调试信息
    std::cout << "search_yaw: " << search_yaw << std::endl; 
}


/*******
 * @name: void::handlePreHoming(float& laserD, ros::Rate& rate)
 * 
 * @brief:  
*********/
void RcController::handlePreHoming(float& laserD, ros::Rate& rate)
{
    std::cout << "RobotStatus: " << RobotStatus << std::endl;
    machine_status.Roller = 0; // 关闭滚筒
    KeepX = -3.0;
    // 计算速度
    PIDOutputX = computeLimitedPIDOutput('x', KeepX, robot_pos.posX, 1.0);
    PIDOutputYaw = computeLimitedPIDOutput('w', initial_yaw, Imu_Data.Euler.yaw, 1.0);
    // 速度赋值
    cmd_vel_msg.linear.x = PIDOutputX;
    cmd_vel_msg.linear.y = 0.0;
    cmd_vel_msg.angular.z = -PIDOutputYaw;
    // 更改条件
    if(KeepX - 0.1<robot_pos.posX &&  robot_pos.posX<KeepX + 0.1){
        RobotStatus = "Homing";
        flag1 += 1; 
        if(flag1 <= 3){
            KeepX = 0.080;
            KeepY = 1.69;}
        else if(3 < flag1 && flag1 <=6){
            KeepX = 0.080;
            KeepY = 2.410;}
        else if(6 < flag1 &&  flag1<=9){
            KeepX = 0.080;
            KeepY =0.910;}
        else{
            KeepX = 0.080;
            KeepY =0.155;}
    }
}

/*******
 * @name: void::handleHoming(float& laserD, ros::Rate& rate)
 * 
 * @brief:  
*********/
void RcController::handleHoming(float& laserD, ros::Rate& rate)
{
    std::cout << "RobotStatus: " << RobotStatus << std::endl;
    // KeepX = 0.15;
    // KeepY = 1.66;
    // if (barnX != -1 && barnY != -1) {
    //     KeepX = barnX;
    //     KeepY = barnY;}
    // 获取测距数据
    laserD = (areaColor == "Red") ? Laser_Ranging.LaserR : Laser_Ranging.LaserL;
    //计算速度 
    PIDOutputX = computeLimitedPIDOutput('x', KeepX, Laser_Ranging.LaserRear, 0.87);
    PIDOutputY = computeLimitedPIDOutput('y', KeepY, laserD, 1.16);
    PIDOutputYaw = computeLimitedPIDOutput('w', initial_yaw, Imu_Data.Euler.yaw, 1.0);
    // 速度赋值
    cmd_vel_msg.linear.x = PIDOutputX;
    cmd_vel_msg.linear.y = (areaColor == "Red") ? PIDOutputY : -PIDOutputY;
    cmd_vel_msg.angular.z = -PIDOutputYaw;
    // 更新状态条件
    if ((KeepY - 0.09 <= laserD && laserD <= KeepY + 0.05) && (0.026 < Laser_Ranging.LaserRear && Laser_Ranging.LaserRear <= 0.10)){
        KeepX = 1.9;
        KeepY = 1.66;
        machine_status.Mode = 1;        //置为归仓模式
        machine_status.PlaceOrNot = 0;  //复位归仓机构，放置小球
        cmd_vel_msg.linear.x = 0.0;
        cmd_vel_msg.linear.y = 0.0;
        cmd_vel_msg.angular.z = 0.0;
        RobotStatus = "Arrived";}
}



/*******
 * @name: void::handleHomingArrived(float& laserD, ros::Rate& rate)
 * 
 * @brief:  
*********/
void RcController::handleHomingArrived(float& laserD, ros::Rate& rate)
{
    std::cout << "RobotStatus: " << RobotStatus << std::endl;
    KeepX =1.66;  // 单位 m
    KeepY = 1.66;
    // 等待归仓完毕
    ros::Duration(1.0).sleep();
    // 回到预寻球状态
    RobotStatus = "PreGrainSearch";
}



/*******
 * @name: void RcController::UnifiedControl()
 * 
 * @brief:  
*********/
void RcController::UnifiedControl()
{
    ros::Rate rate(200); // 200 Hz
    float laserD = 0.0;
    bool aligned_with_ball =false; // 是否对准小球标志位
    while (ros::ok()){
        if (RobotStatus == "Initialized") {
            // 输出机器人此时状态
            std::cout << "RobotStatus: " << RobotStatus << std::endl;
            // 判断本方队伍颜色（通过出发区颜色判定）
            areaColor = getAreaColor();
            if(areaColor == "Red" || areaColor == "Blue"){
                // areaColor = (Laser_Ranging.LaserL < Laser_Ranging.LaserR) ? "Red" : "Blue";
                KeepX = 0.180;                                                              // 机器人x轴目标值，单位m 
                KeepY = 0.10;                                                              // 机器人y轴目标值，单位m 
                RobotStatus = "InitialMovementPoint1"; }      // 变更机器人运动状态
            else{
                RobotStatus = "Initialized";}
        }
        else if(RobotStatus ==  "Reset" ){
            // 处理重置运动逻辑
            KeepX = 0.180;                                                              // 机器人x轴目标值，单位m 
            KeepY = 0.100;                                                              // 机器人y轴目标值，单位m 
            RobotStatus = "InitialMovementPoint1";       // 变更机器人运动状态
        }   
        else if (RobotStatus ==  "InitialMovementPoint1" || RobotStatus ==  "InitialMovementPoint2" || RobotStatus ==  "InitialMovementPoint3"
        || RobotStatus ==  "InitialMovementPoint4" || RobotStatus ==  "InitialMovementPoint5"){
            // 处理初始运动逻辑(1区到3区运动规划)
            handleInitialMovement(laserD, rate);
        }
        else if (RobotStatus == "PreGrainSearch"){
            //到达指定位置对谷粒进行搜索
            handlePreGrainSearch(laserD, rate);
        }
        else if (RobotStatus == "GrainSearch") {
            // 处理谷粒搜索逻辑
            handleSearching(aligned_with_ball, rate);
        } 
        else if (RobotStatus == "PreHoming") {
            // 处理谷粒搜索逻辑
            handlePreHoming(laserD, rate);
        } 
        else if (RobotStatus == "Homing") {
            // 处理谷粒归仓运动逻辑
            handleHoming(laserD, rate);
        } 
        else if (RobotStatus == "Arrived") {
            //执行归仓处理逻辑
            handleHomingArrived(laserD, rate);
        }
        else {
            // 停止状态
            std::cout << "RobotStatus: " << RobotStatus << std::endl;
            cmd_vel_msg.linear.x = 0.0;
            cmd_vel_msg.linear.y = 0.0;
            cmd_vel_msg.angular.z = 0.0;       
            // 发布速度控制指令
            cmd_vel_pub.publish(cmd_vel_msg);
        }

        // 调试消息
        std::cout << "areaColor: " << areaColor << std::endl; 
        std::cout << "initial_yaw: " << initial_yaw << std::endl;
        std::cout << "Imu_Data.Euler.yaw: " << Imu_Data.Euler.yaw << std::endl;
        std::cout << "ballColor: " << ballColor << std::endl; 
        std::cout <<"robot_pos.pos.y" <<  robot_pos.posY << std::endl;
        std::cout << "aligned_with_ball: " << aligned_with_ball << std::endl; 
        std::cout << "KeepX: " << KeepX << std::endl; 
        std::cout << "KeepY: " << KeepY << std::endl;
        std::cout << "cmd_vel_msg.linear.x: " << cmd_vel_msg.linear.x << std::endl;
        std::cout << "cmd_vel_msg.linear.y: " << cmd_vel_msg.linear.y << std::endl;
        std::cout << "cmd_vel_msg.angular.z: " << cmd_vel_msg.angular.z << std::endl; 
        // 发布速度控制指令
        cmd_vel_pub.publish(cmd_vel_msg);
        // 发布机械状态控制指令
        machineStatusPub();
        rate.sleep(); // 保持200 Hz的频率
    }
}


/*******
 * @name: void RcController::CallbackThread()
 * 
 * @brief:  
*********/
void RcController::CallbackThread(){
    
    while(ros::ok())
    {
        ros::spinOnce();
    }
}

