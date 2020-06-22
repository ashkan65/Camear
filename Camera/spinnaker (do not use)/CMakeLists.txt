cmake_minimum_required(VERSION 3.10)
project(Omnimagnet_Project)
find_package( OpenCV REQUIRED )

add_library(
	telerobcamera
	telerobcamera.cpp
	telerobcamera.hpp
	)

add_executable(MultiImageCap multi_camera_image_capture.cpp)

add_executable(try try.cpp) 
add_executable(trig try2.cpp) 
add_executable(cv3 try3.cpp) 

# INCLUDE_DIRECTORIES("/home/ashkan/Desktop/naghi_C/build/")
INCLUDE_DIRECTORIES(/home/ashkan/eigen, /usr/local/lib, /usr/include/spinnaker)

target_link_libraries(telerobcamera PRIVATE  "/usr/lib/libSpinnaker.so" ${OpenCV_LIBS})
# target_link_libraries(pigi PRIVATE "/home/ashkan/Desktop/naghi_C/build/libghazam.a" )
target_link_libraries(MultiImageCap PRIVATE telerobcamera "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
target_link_libraries(try PRIVATE "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
target_link_libraries(trig PRIVATE "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
target_link_libraries(cv3 PRIVATE "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})

# target_link_libraries(SystemRun PRIVATE omnimagnet type "/usr/local/lib/libcomedi.a")

# add_executable(CameraCalibration camera_calibration.cpp)

# target_link_libraries(CameraCalibration "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
