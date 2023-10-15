"""
* @Brief：摄像头标定模板（基于matlab）
* @Author：ye
* @Date：2023/9/15
"""

import cv2
import numpy as np

# 摄像头编号
cap = cv2.VideoCapture(1)
cap.set(3, 640)
cap.set(4, 480)

# 摄像头参数（示例参数，请替换为你的实际参数）
# 用 MATLAB 获取的参数替代示例参数
# focal_length_x = 1096.799364241625  # 对应 IntrinsicMatrix(1,1)
# focal_length_y = 1095.388185214883  # 对应 IntrinsicMatrix(2,2)
# principal_point_x = 989.228009639475  # 对应 IntrinsicMatrix(1,3)
# principal_point_y = 527.397215449114  # 对应 IntrinsicMatrix(2,3)

# 畸变系数
# radial_distortion = np.array([-0.369064032362096, -0.342460023946724])
# tangential_distortion = np.array([0.001677895159744, 0.000284688814418])

"""
* @ModuleName: CorrectCameraDistortion(OriginalImage)
* @Parameter: OriginalImage
* @Author：ye
* @Date：2023/9/12
* @Brief：摄像头畸变矫正模块
* @Return： UndistortedImage or OriginalImage
"""


def CorrectCameraDistortion(OriginalImage):
    h, w = OriginalImage.shape[:2]

    # 使用 MATLAB 获取的参数
    K = np.array([[358.1774113817528, 0, 327.9882367421141],
                  [0, 477.0436831985908, 244.6479538824422],
                  [0, 0, 1]], dtype=np.float32)

    D = np.array([[-0.44557331, 0.32217923, 0.00137786, 0.00046421, -0.16520406]])

    # 矫正畸变
    UndistortedImage = cv2.undistort(OriginalImage, K, D)

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
        height, width, _ = image.shape
        print(height, width)
        cv2.imshow("EffectPreview", EffectPreview)
        cv2.waitKey(1)
