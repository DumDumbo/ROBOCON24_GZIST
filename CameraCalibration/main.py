"""
* @Brief：摄像头标定模板
* @Author：ye
* @Date：2023/9/12
"""

import cv2
import numpy as np

# 摄像头编号
cap = cv2.VideoCapture(1)

# 摄像头参数（示例参数，请替换为你的实际参数）
focal_length = 1000  # 实际的焦距值
principal_point_x = 500  # 实际的主点x坐标
principal_point_y = 400  # 实际的主点y坐标
# distortion_coefficients = np.array([0.1, 0.2, 0.01, 0.001, 0.0])  # 实际的畸变系数
distortion_coefficients = np.array([[-0.44557331, 0.32217923, 0.00137786, 0.00046421, -0.16520406]])  # 实际的畸变系数
"""
* @ModuleName: CorrectCameraDistortion(OriginalImage)
* @Parameter: OriginalImage
* @Author：ye
* @Date：2023/9/12
* @Brief：摄像头畸变矫正模块
* @Return： UndistortedImage or OriginalImage
"""


def CorrectCameraDistortion(OriginalImage):
    UndistortedImage = cv2.undistort(image, np.array([[focal_length, 0, principal_point_x],
                                                      [0, focal_length, principal_point_y],
                                                      [0, 0, 1]]), distortion_coefficients)
    if UndistortedImage is None:
        return OriginalImage
    else:
        return UndistortedImage


if __name__ == "__main__":
    while True:
        # 读取图像
        ret, image = cap.read()
        # 矫正畸变
        CorrectedImage = CorrectCameraDistortion(image)
        cv2.imshow('CorrectedImage', CorrectedImage)
        cv2.imshow('image', image)
        cv2.waitKey(1)
