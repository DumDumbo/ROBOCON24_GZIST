"""
* @Brief：摄像头标定模板（基于opencv）
* @Author：ye
* @Date：2023/9/12
"""

import cv2
import numpy as np

"""
* @Brief：摄像头参数设置
* @Author：ye
* @Date：2023/9/12
* @Parameters： width：宽度
* @             height： 高度
"""
cap = cv2.VideoCapture(1)
cap.set(3, 640)
cap.set(4, 480)

"""
* @brief：摄像机3x3内参矩阵
* @Parameters：focal_length: 实际的焦距值
* @            principal_point_x: 实际的主点x坐标
* @            principal_point_y: 实际的主点y坐标
* @Template: cameraMatrix=np.array([[focal_length, 0, principal_point_x],
* @                                 [0, focal_length, principal_point_y],
* @                                 [0, 0, 1]])
"""

# 摄像机校正后内参(需要乘1000)
CameraMatrix = np.array([[360.90311809, 0.0, 334.29041245],
                         [0.0, 481.11318605, 239.64849122],
                         [0.0, 0.0, 1.0]], dtype=np.float32)

"""
* @brief：畸变系数矩阵
* @Parameters：Radial Distortion(径向畸变参数)：k1, k2, k3
* @            Tangential Distortion(切向畸变参数)：p1, p2
* @Template：distortion_coefficients = np.array([k1, k2, k3, p1, p2])  # 实际的畸变系数
"""
# distortion_coefficients = np.array([[-3.92042072, - 7.74516813, - 1.67826787,
#                                      - 1.83169177, 2.47859508]])  # 实际的畸变系数
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
    UndistortedImage = cv2.undistort(src=OriginalImage, cameraMatrix=CameraMatrix,
                                     distCoeffs=distortion_coefficients)
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
        # 水平合并图像
        EffectPreview = cv2.hconcat([image, CorrectedImage])
        # 在合并的图像上绘制信息
        cv2.putText(img=EffectPreview, text="Before", org=(260, 70), fontFace=cv2.FONT_HERSHEY_SIMPLEX,
                    fontScale=1, color=(0, 255, 0), thickness=2)
        cv2.putText(img=EffectPreview, text="After", org=(960, 70), fontFace=cv2.FONT_HERSHEY_SIMPLEX,
                    fontScale=1, color=(0, 255, 0), thickness=2)
        # 查看图像的width和height
        width, height, channels = EffectPreview.shape
        print(width, height, channels)
        cv2.imshow('EffectPreview', EffectPreview)
        cv2.waitKey(1)
