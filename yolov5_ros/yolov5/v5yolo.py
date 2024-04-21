#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# YOLOv5 🚀 by Ultralytics, GPL-3.0 license
"""
Run YOLOv5 detection inference on images, videos, directories, globs, YouTube, webcam, streams, etc.

Usage - sources:
    $ python detect.py --weights yolov5s.pt --source 0                               # webcam
                                                     img.jpg                         # image
                                                     vid.mp4                         # video
                                                     screen                          # screenshot
                                                     path/                           # directory
                                                     list.txt                        # list of images
                                                     list.streams                    # list of streams
                                                     'path/*.jpg'                    # glob
                                                     'https://youtu.be/Zgi9g1ksQHc'  # YouTube
                                                     'rtsp://example.com/media.mp4'  # RTSP, RTMP, HTTP stream

Usage - formats:
    $ python detect.py --weights yolov5s.pt                 # PyTorch
                                 yolov5s.torchscript        # TorchScript
                                 yolov5s.onnx               # ONNX Runtime or OpenCV DNN with --dnn
                                 yolov5s_openvino_model     # OpenVINO
                                 yolov5s.engine             # TensorRT
                                 yolov5s.mlmodel            # CoreML (macOS-only)
                                 yolov5s_saved_model        # TensorFlow SavedModel
                                 yolov5s.pb                 # TensorFlow GraphDef
                                 yolov5s.tflite             # TensorFlow Lite
                                 yolov5s_edgetpu.tflite     # TensorFlow Edge TPU
                                 yolov5s_paddle_model       # PaddlePaddle
"""
import os
import sys
import torch
import threading
from flask import Flask, Response, render_template


from models.common import DetectMultiBackend
from utils.torch_utils import select_device
from utils.dataloaders import LoadStreams
from utils.general import (Profile, check_img_size, cv2, non_max_suppression,  scale_boxes)
from utils.plots import Annotator, colors




import rospy
import numpy as np

from std_msgs.msg import Header
from sensor_msgs.msg import Image
from yolov5_ros_msgs.msg import BoundingBox, BoundingBoxes
"""*********************************************************************************************************************
* @Describe: 公共声明
*********************************************************************************************************************"""

# 设置相机参数
camera_Width = 640
camera_Height = 480
camera_Horizontal_View_Angle = 120


"""*********************************************************************************************************************
* @Function: 基于flask无线图传
*********************************************************************************************************************"""

# class WirelessVideo:
#     def __init__(self):
#         # 实例化 Flask
#         self.app = Flask(__name__)
#         self.image = None

#     def display(self):
#         while True:
#             image = self.image.get()
#             self.image.task_done()
#             if image is not None:
#                 ret, buffer = cv2.imencode('.jpg', image)
#                 frame = buffer.tobytes()
#                 yield (b'--frame\r\n'
#                        b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
#             else:
#                 print("image is None")
#                 pass

#     @app.route('/')
#     def index(self):
#         return render_template('index.html')

#     @app.route('/video_feed')
#     def video_feed(self):
#         return Response(self.display(), mimetype='multipart/x-mixed-replace; boundary=frame')

#     def run(self):
#         self.app.run(host='0.0.0.0', port=5005)



class  Yolo_Dect:
    def __init__(self):
        self.yolov5 =  rospy.get_param('/yolov5_path', '')
        self.weights= rospy.get_param('~weight_path', '')
        self.device='0'
        self.imgsz=(640, 640)
        self.half=False
        self.vid_stride=1
        self.conf_thres=0.55
        self.iou_thres=0.45
        self.line_thickness=3
        self.hide_labels=False
        self.hide_conf=False
        self.getImageStatus = False
        # image subscribe
        self.color_sub = rospy.Subscriber('/camera/color/image_raw', Image, self.yolo_Threading,
                                          queue_size=1, buff_size=52428800)
        self.color_image=Image()
        # if no image messages
        while (not self.getImageStatus) :
            rospy.loginfo("waiting for image.")
            rospy.sleep(2)



    def yolo_Threading(self, image):
        self.getImageStatus = True

        self.color_image = np.frombuffer(image.data, dtype=np.uint8).reshape(
            image.height, image.width, -1)
        self.color_image = cv2.cvtColor(self.color_image, cv2.COLOR_RGB2BGR)
        """
        Description: Pre_Work
        """
        # Load model
        global det, center_x, x2, x1, target1, target2
        # im0 = '0' 
        device = select_device(self.device)
        model = DetectMultiBackend(self.weights, device=device, fp16=self.half)
        # model = torch.hub.load(self.yolov5, 'custom', path=self.weights, source='local')
        stride, names, pt = model.stride, model.names, model.pt
        imgsz = check_img_size(self.imgsz, s=stride)  # check image size

        """
        Description:  Dataloader 、Warm up and Run inference
        """
        # Dataloader
        bs = 1
        dataset = LoadStreams(self.color_image, img_size=self.imgsz, stride=stride, auto=pt, vid_stride=self.vid_stride)
        bs = len(dataset)

        # Warm up
        model.warmup(imgsz=(1 if pt or model.triton else bs, 3, *imgsz))  # warmup

        # Run inference
        seen, windows, dt = 0, [], (Profile(), Profile(), Profile())  # dt is for record time
        for path, im, im0s, vid_cap, s in dataset:
            with dt[0]:
                im = torch.from_numpy(im).to(model.device)
                im = im.half() if model.fp16 else im.float()  # uint8 to fp16/32
                im /= 255  # 0 - 255 to 0.0 - 1.0
                if len(im.shape) == 3:
                    im = im[None]  # expand for batch dim

            # Inference
            with dt[1]:
                pred = model(im, augment=False, visualize=False)

            # NMS
            with dt[2]:
                pred = non_max_suppression(pred, self.conf_thres, self.iou_thres, classes=None, max_det=1000)

            results = []
            # Process predictions
            for i, det in enumerate(pred):  # per image
                seen += 1
                # batch_size >= 1
                p, im0, frame = path[i], im0s[i].copy(), dataset.count
                s += f'{i}: '


            p = Path(p)  # to Path

            """
                * Description: Print location 、write result and stream result
            """

            # define class(Annotator) as annotator
            annotator = Annotator(im0, line_width=line_thickness, example=str(names))
            if len(det):
                # Rescale boxes from img_size to im0 size
                det[:, :4] = scale_boxes(im.shape[2:], det[:, :4], im0.shape).round()

            # write result
            for *xyxy, conf, cls in reversed(det):
                c = int(cls)  # integer class
                label = None if hide_labels else (names[c] if hide_conf else f'{names[c]} {conf:.2f}')
                annotator.box_label(xyxy, label, color=colors(c, True))

            # Stream results    ;    im0-->(height:640; width:480; layer:3)
            im0 = annotator.result()
            # im0_data.put(im0)
            windows.append(p)
            cv2.namedWindow(str(p), cv2.WINDOW_NORMAL | cv2.WINDOW_KEEPRATIO)  # allow window resize (Linux)
            cv2.resizeWindow(str(p), im0.shape[1], im0.shape[0])
            # cv2.line(im0, (320, 0), (320, 480), (0, 255, 0))
            cv2.imshow(str(p), im0)
            cv2.waitKey(1)  # 1 millisecond


def main():
    rospy.init_node('v5yolo', anonymous=True)
    yolo_dect = Yolo_Dect()
    rospy.spin()

if __name__ == '__main__':
    main()
    # thread_yolo = threading.Thread(target=yolo_Threading)
    # thread_Display = threading.Thread(target=Display_Threading)

    # thread_yolo.start()
    # thread_Display.start()
