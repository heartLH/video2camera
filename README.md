# video2camera
ROS package change video to camera topic "usb_camera/image_raw"
# Description
This Rosbag can convert the video to ros topic ,as camera can.There are two args in launch .First args if your video's path ,and second args define whether show your video by OpenCV.1 means show and 0 means not.The topic name is "/usb_cam/image_raw". 
# Dependence
OpenCV3
# usage
roslaunch video2camera video2camera.launch
