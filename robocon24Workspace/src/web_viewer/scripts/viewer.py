#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rospy
from flask import Flask, Response, render_template
from sensor_msgs.msg import Image 
import cv2



class ViewerFlask:
    def __init__(self):
       self.App = Flask(__name__)       # 实例化Flask
       self.image_sub = rospy.Subscriber('/yolov5/detection_image', Image, self.Display)

    def Display(self, Image):
        ret, buffer = cv2.imencode('.jpg', Image)
        if ret:
            frame = buffer.tobytes()
            yield(b'--frame/r/n'
                        b'Content-Type: Image/jpeg\r\n\r\n' + frame + b'\r\n')
        else:
            print("Somethiing went wrong! From Pkg: web_viewer  File: viewer.py  Line: 26")
            pass


    def index(self):
        return render_template("index.html")
                

    def video_feed(self):
        return Response(self.Display(), mimetype='multipart/x-mixed-replace; boundary=frame')



    def start(self):
       self.App.route('/')(self.index)
       self.App.route('/video_feed')(self.video_feed)
       self.App.run(host='0.0.0.0', port=8008)
    

if __name__ == "__main__":
    # 节点初始化
    rospy.init_node('viewer', anonymous=True)
    # 实例化类
    Viewer = ViewerFlask()
    try:
        Viewer.start()
        rospy.spin()
    except rospy.ROSInterruptException:
        rospy.logwarn("failed, From Pkg: web_viewer  File: viewer.py  Line: 26")
