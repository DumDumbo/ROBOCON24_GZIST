import cv2
import os

# 源图像文件夹和目标图像文件夹
input_folder = r"D:\program_bags\Robocon24\CameraCalibration\CameraCalibrationTemplate\chess"
output_folder = r"D:\program_bags\Robocon24\CameraCalibration\CameraCalibrationTemplate\chess"

# 目标图像大小（宽度和高度）
target_width = 640  # 更改为你想要的宽度
target_height = 480  # 更改为你想要的高度

# 确保输出文件夹存在
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# 获取源图像文件夹中的所有图像文件
image_files = [f for f in os.listdir(input_folder) if f.endswith(('.jpg', '.jpeg', '.png', '.gif'))]

# 批量修改图像大小
for image_file in image_files:
    input_path = os.path.join(input_folder, image_file)
    output_path = os.path.join(output_folder, image_file)

    # 读取图像
    img = cv2.imread(input_path)

    # 调整图像大小
    resized_img = cv2.resize(img, (target_width, target_height))

    # 保存调整后的图像
    cv2.imwrite(output_path, resized_img)

print("图像大小修改完成！")
