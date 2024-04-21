#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
/****************************************************************************************
 * @brief:  yolov5 推理文件
 *                  Subscribe:  订阅深度相机彩色话题
 *                  Publish:   1st:    '/yolov5/detection_image'(识别后图像) 
 *                                      2nd:   '/yolov5/BoundingBoxes'(话题的bounding_boxes列表存储着每个对象的物体框信息)
 *                      
 * @version: 1.0
 * 
 * @author: 修改自github/qq4464275a/Yolov5_ros仓库,
 *                     备份于github/DumDumbo/Dumbo/ROSLearning/Demo
 *                     
 * @details: 相较于原作者,本版本为scripts文件夹添加了"__pycache__","models","utils"三个文件夹
 *                      并替换了models文件夹的yolo.py文件,来自本机已跑通的Yolov5官方文件
 *                      github地址:/github/ultralytic/yolov5(V6.0)
 *                       
 *
 * @note:  编译yolov5_ros 以及 yolov5_ros_msgs请使用python3单独编译
 *                  catkin_make -DCATKIN_WHITELIST_PACKAGES='yolov5_ros'   'yolov5_ros_msgs' -DPYTHON_EXECUTABLE=/usr/bin/python3
 *
****************************************************************************************/"""

import cv2
import torch
import rospy
import numpy as np
from std_msgs.msg import Header
from sensor_msgs.msg import Image
from yolov5_ros_msgs.msg import BoundingBox, BoundingBoxes

class Yolo_Dect:
    def __init__(self):

        # load parameters
        yolov5_path = rospy.get_param('/yolov5_path', '')
        weight_path = rospy.get_param('~weight_path', '')
        image_topic = rospy.get_param('~image_topic', '/camera/color/image_raw')
        pub_topic = rospy.get_param('~pub_topic', '/yolov5/BoundingBoxes')
        self.camera_frame = rospy.get_param('~camera_frame', '')
        conf = rospy.get_param('~conf', '0.5')

        # load local repository(YoloV5:v6.0)
        self.model = torch.hub.load(yolov5_path, 'custom',
                                    path=weight_path, source='local')

        # which device will be used
        if (rospy.get_param('/use_cpu', 'false')):
            self.model.cpu()
        else:
            self.model.cuda()

        self.model.conf = conf
        self.color_image = Image()
        self.depth_image = Image()
        self.getImageStatus = False

        # Load class color
        self.classes_colors = {
            "purpleBall": (128, 0, 128),
            "redBall": (0, 0, 255)
        }

        # image subscribe
        self.color_sub = rospy.Subscriber(image_topic, Image, self.image_callback,
                                          queue_size=1, buff_size=52428800)

        # output publishers
        self.position_pub = rospy.Publisher(
            pub_topic,  BoundingBoxes, queue_size=1)

        self.image_pub = rospy.Publisher(
            '/yolov5/detection_image',  Image, queue_size=1)

        # if no image messages
        while (not self.getImageStatus) :
            rospy.loginfo("waiting for image.")
            rospy.sleep(2)

    def image_callback(self, image):
        self.boundingBoxes = BoundingBoxes()
        self.boundingBoxes.header = image.header
        self.boundingBoxes.image_header = image.header
        self.getImageStatus = True

        # 将Image话题的一维数据转化重新排列组合成三维的Numpy数组（height，width， channels）
        # 若话题图形本身为rgb8的编码，无须转换。若不是请转换为rgb8
        # 可使用print(image.encoding)进行查看, 因本相机为rgb8,故无须转换
        self.color_image = np.frombuffer(image.data, dtype=np.uint8).reshape(
            image.height, image.width, -1)

        # 获取推理结果
        results = self.model(self.color_image)
        # xmin    ymin    xmax   ymax  confidence  class    name

        #  只有输入图像时rgb8时,才对检测结果results进行解析
        if image.encoding == 'rgb8':
            boxs = results.pandas().xyxy[0].values
            self.dectshow(self.color_image, boxs, image.height, image.width)
            cv2.waitKey(3)

        else:
            rospy.logwarn("Please check image encoding, from yolo_v5.py line 92")

    def dectshow(self, org_img, boxs, height, width):
        img = org_img.copy()
        # 使用opencv 展示图像时需要的格式默认为bgr8, 而上述yolov5推理时需要的是rgb8,故在展示函数需要转换.
        img = cv2.cvtColor(img, cv2.COLOR_RGB2BGR)

        count = 0
        for i in boxs:
            count += 1

        for box in boxs:
            boundingBox = BoundingBox()
            boundingBox.probability =np.float64(box[4])
            boundingBox.xmin = np.int64(box[0])
            boundingBox.ymin = np.int64(box[1])
            boundingBox.xmax = np.int64(box[2])
            boundingBox.ymax = np.int64(box[3])
            boundingBox.num = np.int16(count)
            boundingBox.Class = box[-1]
            # Process detection results


            if box[-1] in self.classes_colors.keys():
                color = self.classes_colors[box[-1]]
            else:
                color = np.random.randint(0, 183, 3)
                self.classes_colors[box[-1]] = color

            cv2.rectangle(img, (int(box[0]), int(box[1])),
                          (int(box[2]), int(box[3])), (int(color[0]),int(color[1]), int(color[2])), 2)

            if box[1] < 20:
                text_pos_y = box[1] + 30
            else:
                text_pos_y = box[1] - 10
                
            cv2.putText(img, box[-1],
                        (int(box[0]), int(text_pos_y)-10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (int(color[0]), int(color[1]), int(color[2])), 2, cv2.LINE_AA)


            self.boundingBoxes.bounding_boxes.append(boundingBox)
            self.position_pub.publish(self.boundingBoxes)
        self.publish_image(img, height, width)
        cv2.imshow('YOLOv5', img)

    def publish_image(self, imgdata, height, width):
        image_temp = Image()
        header = Header(stamp=rospy.Time.now())
        header.frame_id = self.camera_frame
        image_temp.height = height
        image_temp.width = width
        image_temp.encoding = 'bgr8'
        image_temp.data = np.array(imgdata).tobytes()
        image_temp.header = header
        image_temp.step = width * 3
        self.image_pub.publish(image_temp)


def main():
    rospy.init_node('yolov5_ros', anonymous=True)
    yolo_dect = Yolo_Dect()
    rospy.spin()


if __name__ == "__main__":

    main()
