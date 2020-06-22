cmake_minimum_required(VERSION 3.10)
project(Omnimagnet_Project)
find_package( OpenCV REQUIRED )

add_library(
	telerobcamera
	telerobcamera.cpp
	telerobcamera.hpp
	)

add_executable(3DTarget main.cpp)
add_executable(filewrite filepracwrite.cpp)
add_executable(fileread filepracread.cpp)
# INCLUDE_DIRECTORIES("/home/ashkan/Desktop/naghi_C/build/")
INCLUDE_DIRECTORIES(/home/ashkan/eigen, /usr/local/lib, /usr/include/flycapture)

target_link_libraries(telerobcamera PRIVATE  "/usr/lib/libflycapture.so" ${OpenCV_LIBS})
# target_link_libraries(pigi PRIVATE "/home/ashkan/Desktop/naghi_C/build/libghazam.a" )
target_link_libraries(3DTarget PRIVATE telerobcamera "/usr/lib/libflycapture.so"  ${OpenCV_LIBS})

target_link_libraries(filewrite PRIVATE  ${OpenCV_LIBS})
target_link_libraries(fileread PRIVATE  ${OpenCV_LIBS})


# target_link_libraries(SystemRun PRIVATE omnimagnet type "/usr/local/lib/libcomedi.a")

# add_executable(CameraCalibration camera_calibration.cpp)

# target_link_libraries(CameraCalibration "/usr/lib/libSpinnaker.so"  ${OpenCV_LIBS})
