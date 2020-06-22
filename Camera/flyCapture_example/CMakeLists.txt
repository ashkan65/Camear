cmake_minimum_required(VERSION 3.10)
project(Omnimagnet_Project)
find_package( OpenCV REQUIRED )

# add_library(
# 	telerobcamera
# 	telerobcamera.cpp
# 	telerobcamera.hpp
# 	)

# add_executable(MultiImageCap multi_camera_image_capture.cpp)

add_executable(run SingleCameraEx.cpp) 


# INCLUDE_DIRECTORIES("/home/ashkan/Desktop/naghi_C/build/")
INCLUDE_DIRECTORIES(/home/ashkan/eigen, /usr/local/lib, /usr/include/flycapture)

# target_link_libraries(telerobcamera PRIVATE  "/usr/lib/libSpinnaker.so" ${OpenCV_LIBS})
# target_link_libraries(pigi PRIVATE "/home/ashkan/Desktop/naghi_C/build/libghazam.a" )
# target_link_libraries(MultiImageCap PRIVATE telerobcamera "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
target_link_libraries(run PRIVATE "/usr/lib/libflycapture.so"  ${OpenCV_LIBS})
# target_link_libraries(trig PRIVATE "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
# target_link_libraries(cv3 PRIVATE "/usr/lib/flycapture.so"  ${OpenCV_LIBS})

# target_link_libraries(SystemRun PRIVATE omnimagnet type "/usr/local/lib/libcomedi.a")

# add_executable(CameraCalibration camera_calibration.cpp)

# target_link_libraries(CameraCalibration "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
