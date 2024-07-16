#!/usr/bin/env python
#coding=utf-8

import rospy
from robot_control.msg import pidMsgs
import matplotlib.pyplot as plt
from collections import deque

class PIDVisualizer:
    def __init__(self):
        rospy.init_node('visualization', anonymous=True)
        rospy.Subscriber('/pid', pidMsgs, self.pid_data_callback)

        # 使用 deque 来存储数据，限制最大长度以避免内存占用过多
        self.setpoint_value = None
        self.feedback_values = deque(maxlen=100)
        self.time_values = deque(maxlen=100)

        # 初始化 Matplotlib 图表
        self.fig, self.ax = plt.subplots()
        self.ax.set_xlabel('Time (s)')
        self.ax.set_ylabel('Value')

    def pid_data_callback(self, data):
        current_time = rospy.get_time()

        if self.setpoint_value is None:
            self.setpoint_value = data.setpoint

        # 添加新数据到 deque
        self.feedback_values.append(data.feedback)
        self.time_values.append(current_time - self.time_values[0] if self.time_values else 0)

        # 更新图表
        self.update_plot()

    def update_plot(self):
        # 清空之前的内容
        self.ax.clear()
        
        if not self.time_values:
            return
        
        # 绘制反馈曲线
        self.ax.plot(self.time_values, self.feedback_values, label='Feedback', color='red')
        
        # 绘制设定值水平线
        if self.setpoint_value is not None:
            self.ax.plot(self.time_values, [self.setpoint_value] * len(self.time_values), label='Setpoint', color='green')

        self.ax.legend()
        plt.pause(0.01)  # 给Matplotlib时间处理事件

    def run(self):
        rospy.spin()

if __name__ == '__main__':
    pid_visualizer = PIDVisualizer()
    pid_visualizer.run()

