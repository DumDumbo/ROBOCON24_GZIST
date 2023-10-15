"""
* @Brief：解析xml文件获取摄像头畸变参数
* @Author：ye
* @Date：2023/9/12
"""
from calibration import CameraCalibrator
# 创建一个CameraCalibrator实例
calibrator = CameraCalibrator(image_size=(640, 480))

# 加载XML文件中的参数
calibrator.load_params(param_file='camera_params.xml')

# 现在，你可以访问加载的参数，例如摄像机矩阵、畸变系数、新摄像机矩阵等
print("Camera Matrix:")
print(calibrator.matrix)

print("Distortion Coefficients:")
print(calibrator.dist)

print("New Camera Matrix:")
print(calibrator.new_camera_matrix)

print("ROI:")
print(calibrator.roi)

