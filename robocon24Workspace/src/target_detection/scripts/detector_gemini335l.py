#!/usr/bin/env python
#coding=utf-8

"""
/****************************************************************************************
 * @brief:  获取彩图中所有目标的深度信息并发布至/target话题
 * 
 * @version: 1.0
 * 
 * @author: YYY
 *                     
 * @details: 	订阅话题:        /yolov5/detection_image
 *							    /camera/depth/image_raw
 *							    /yolov5/BoundingBoxes
 *							发布话题:	  /target
 *							相机型号:	  orbbec gemini 335L
 *				
 *
 * @note:   
****************************************************************************************/"""

import rospy
import message_filters
import numpy as np
import cv2
from target_detection.msg import position, Positions
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image
from std_msgs.msg import String as StringMsg
from std_msgs.msg import Int8
from std_msgs.msg import Header
from yolov5_ros_msgs.msg import  BoundingBox, BoundingBoxes


# displayImage = True

class tragetDetection:
	
	def __init__(self):
		
		self.bridge = CvBridge()                                                  # 创建CvBridge对象     

        # 图像设置
		self.pictureHeight=  480  				#设置图像高度
		self.pictureWidth =  640   				#设置图像宽度
		vertAngle = 0.59341194568               #RGB图垂直视场角
		horizontalAngle =  0.82030474844  	    #RGB图水平视场角
		
		# 预先计算垂直/水平视场角的正切值（目的:"后续频繁使用时不需要重复计算"）
		self.tanVertical = np.tan(vertAngle)
		self.tanHorizontal = np.tan(horizontalAngle)

		# last position
		self.lastPosition = None

		self.targetDist = 4000
		
        # 订阅RGB图和深度图话题
		img_sub = message_filters.Subscriber('/yolov5/detection_image', Image)
		dep_sub = message_filters.Subscriber('/camera/depth/image_raw', Image)
		Box_sub = message_filters.Subscriber('/yolov5/BoundingBoxes', BoundingBoxes)
        # 同步两话题时间戳
		self.timeSynchronizer = message_filters.ApproximateTimeSynchronizer([img_sub, dep_sub, Box_sub], 10, 0.5)

        # 将tragetDetection类中的trackObject方法作为回调函数
		self.timeSynchronizer.registerCallback(self.getTarget)

		# 创建话题发布对象，发布物体位置信息
		self.posPublisher = rospy.Publisher('/posTargets', Positions, queue_size=1)

		# /target话题时间戳
		self.header = Header()
		
        # 提示信息
		rospy.loginfo("\033[92mDetector Initialized \033[0m")
	

	def getTarget(self, image_data, depth_data, box_data):
		# 检查RGB图是否为rgb8格式
		if(image_data.encoding != 'rgb8'):
			raise ValueError('image is not rgb8 as expected')
		
		#将两张图片都转换为Numpy数组
		frame = self.bridge.imgmsg_to_cv2(image_data, desired_encoding='bgr8')
		depthFrame = self.bridge.imgmsg_to_cv2(depth_data, desired_encoding='passthrough')#"16UC1")	
		
		# 检测图像尺寸与初始化设定的是否一致
		if(np.shape(frame)[0:2] != (self.pictureHeight, self.pictureWidth)):
			raise ValueError('image does not have the right shape. shape(frame): {}, shape parameters:{}'.format(np.shape(frame)[0:2], (self.pictureHeight, self.pictureWidth)))


		self.Positions = Positions()
		# 获取所有目标框数据
		boxPos = box_data.bounding_boxes
		
		for box in boxPos:
			target = position()
			target.Class = box.Class
			if target.Class == "None":
				target.centerX = 0
				target.centerY = 0
				target.angleX = 0
				target.angleY = 0
				target.distance = 0
			else:
				target.centerX = (box.xmax + box.xmin) // 2
				target.centerY = (box.ymax + box.ymin) // 2
				target.angleX = self.__calculateAngleX(target.centerX)
				target.angleY = self.__calculateAngleY(target.centerY)
				target.distance = self. __analyseBox(target.centerX, target.centerY, depthFrame)
				# if target.distance == -1:
				# 	target.distance = 0
				# else:
				# 	pass


			self.Positions.positions.append(target)
			# 发布话题
			self.Positions.header = self.header
			self.Positions.header.stamp = rospy.Time.now()
			self.Positions.header.frame_id = box_data.header.frame_id
			self.posPublisher.publish(self.Positions)
			

	
	"""
	*@ FunctionName:	__publishPosition(self, pos):
	*
	*@ brief:	整合数据,发布物体位置信息
	"""	
	# def __publishPosition(self, pos):
	# 	self.Header.stamp = rospy.Time.now()
	# 	self.Header.frame_id = "TargetsPos"
	# 	# 发布物体位置信息（目标框像素X坐标、Y坐标、水平角度，垂直角度，距离,）
	# 	posMsg = Positions(self.Header,pos)
	# 	self.posPublisher.publish(posMsg)


	"""
	*@ FunctionName: 	__calculateAngleX(self, x):
	*
	*@ brief:	获取对象的水平坐标,计算与图像中心偏移量,再通过反正切函数
				计算对象位置相对于图像中心的水平角度
	"""	
	def __calculateAngleX(self, x):
		centerX = float(x)
		displacement = 2*centerX/self.pictureWidth-1
		angle = -1*np.arctan(displacement*self.tanHorizontal)
		return angle
	

	"""
	*@ FunctionName: 	__calculateAngleY(self, pos):
	*
	*@ brief:	获取对象的垂直坐标,计算与图像中心偏移量,再通过反正切函数
				计算对象位置相对于图像中心的垂直角度
	"""	
	def __calculateAngleY(self, y):
		centerY = float(y)
		displacement = 2*centerY/self.pictureHeight-1
		angle = -1*np.arctan(displacement*self.tanVertical)
		return angle


	'''
	*@ FunctionName: 	__analyseBox(self, centerX, centerY, depthFrame):
	*
	*@ Arguments:	
	*		centerX: 		所识别到对象X坐标
	*		centerY:		所识别到对象Y坐标
	*		depthFrame: 	深度图像
	*
	*@ Return:
	*		center: 			对象圆心坐标
    *    	AverageDistance: 	对象的距离
	'''
	def __analyseBox(self, centerX, centerY, depthFrame):

		# 用于获取圆心的坐标，并将其四舍五入为整数值，以便用于索引图像数组。
		center = [centerX, centerY]
 
		# 找出在不离开对象的情况下，我们可以在x/y方向上走多远
		minSize = 2

		# 获取该区域内（即对象内）的所有深度点
		depthObject = depthFrame[(center[1]-minSize):(center[1]+minSize), (center[0]-minSize):(center[0]+minSize)]

		# 去除区域内的无效点，例如INF或NAN值
		depthArray = depthObject[np.isfinite(depthObject)]
		# print "depthArray", depthArray
		# È¥³ýÁãÖµ
		valid_depths = depthArray[depthArray != 0]
		# print "valid_depths", valid_depths
		# 获得所有有效点的平均值作为距离信息
		averageDistance = np.mean(valid_depths)

		# 对平均距离进行判断，过滤可能计算错误的过广或过小的无效数据
		if(averageDistance>=170 or averageDistance<=4000):
			# print "averageDistance", averageDistance
			pass
		else:
			averageDistance=-1

		if len(depthArray) == 0:
			rospy.logwarn('empty depth array. all depth values are nan')

		# 返回对象的中心坐标和平均距离。
		return averageDistance


if __name__ == '__main__':
	# ros节点初始化
	rospy.init_node('detector_gemini335l')

	# 实例化类
	Detect = tragetDetection()

	try:
		rospy.spin()
	except rospy.ROSInterruptException:
		rospy.logwarn('failed')
