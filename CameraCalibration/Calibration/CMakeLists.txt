cmake_minimum_required(VERSION 3.10)
project(Omnimagnet_Project)
find_package( OpenCV REQUIRED )


add_executable(single_calibration Intrinsic_Calibration.cpp)
# add_executable(calibration2 camera_calibration.cpp)

INCLUDE_DIRECTORIES(/home/ashkan/eigen, /usr/local/lib, /usr/include/flycapture)

# target_link_libraries(calibration PRIVATE  "/usr/lib/libflycapture.so" ${OpenCV_LIBS})
target_link_libraries(single_calibration PRIVATE  "/usr/lib/libflycapture.so" ${OpenCV_LIBS})
