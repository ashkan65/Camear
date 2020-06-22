#include <iostream>
#include <vector>
#include "telerobcamera.hpp"
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/types.hpp>
// #include "print.h"  // This has the functions to print the camera and library version. TODO: move it somewhere else: 
////////////////////////////////////////
	// Setting up the HSV prametters:

	const int max_value_H = 360/2;
	const int max_value = 255;
	int low_H = 0, low_S = 0, low_V = 0;
	int high_H = max_value_H, high_S = max_value, high_V = max_value;
	static void on_low_H_thresh_trackbar(int, void *)
	{
	    low_H = std::min(high_H-1, low_H);
	    cv::setTrackbarPos("Low H", "Object Detection", low_H);
	}
	static void on_high_H_thresh_trackbar(int, void *)
	{
	    high_H = std::max(high_H, low_H+1);
	    cv::setTrackbarPos("High H", "Object Detection", high_H);
	}
	static void on_low_S_thresh_trackbar(int, void *)
	{
	    low_S = std::min(high_S-1, low_S);
	    cv::setTrackbarPos("Low S", "Object Detection", low_S);
	}
	static void on_high_S_thresh_trackbar(int, void *)
	{
	    high_S = std::max(high_S, low_S+1);
	    cv::setTrackbarPos("High S", "Object Detection", high_S);
	}
	static void on_low_V_thresh_trackbar(int, void *)
	{
	    low_V = std::min(high_V-1, low_V);
	    cv::setTrackbarPos("Low V", "Object Detection", low_V);
	}
	static void on_high_V_thresh_trackbar(int, void *)
	{
	    high_V = std::max(high_V, low_V+1);
	    cv::setTrackbarPos("High V", "Object Detection", high_V);
	}

cv::Mat frame_HSV1, frame_threshold1,frame_HSV2, frame_threshold2;




int main () {
    // if (mkdir("../capturedi_mages", 0777) == -1){ 
    //     std::cerr << "Error :  " << strerror(errno) << std::endl; 
    //     std::cout<<"Use sudo!!!!!!!";
    //     return 0;    
    // }
    // else{
    //     std::cout << "Directory created"; 
    // }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //Setup for the Cameras: --- DON'T MODIFIY ---
    FlyCapture2::Error error;      
	FlyCapture2::BusManager busMgr;

	unsigned int numCameras;
    error = busMgr.GetNumOfCameras(&numCameras);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        std::cout<< "something is wrong!\n"; 
        return -1;
    }
	std::cout << "Number of cameras detected: " << numCameras << std::endl;
	FlyCapture2::Camera *pCameras = new FlyCapture2::Camera[numCameras];
	for (unsigned int i = 0; i < numCameras; i++)
    {
        FlyCapture2::PGRGuid guid;
        error = busMgr.GetCameraFromIndex(i, &guid);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            error.PrintErrorTrace();
            std::cout << "Press Enter to exit." << std::endl;
            delete[] pCameras;
            std::cin.ignore();
            return -1;
        }

        // Connect to a camera
        error = pCameras[i].Connect(&guid);
        if (error != FlyCapture2::PGRERROR_OK)
        {
            error.PrintErrorTrace();
            delete[] pCameras;
            std::cout << "Press Enter to exit." << std::endl;
            std::cin.ignore();
            return -1;
        }
        std::cout<<i;	
    }
	///////////////////////////////////////////////


	// cv::namedWindow(window_capture_name);
    cv::namedWindow("Object Detection");
    // Trackbars to set thresholds for HSV values
    cv::createTrackbar("Low H", "Object Detection", &low_H, max_value_H, on_low_H_thresh_trackbar);
    cv::createTrackbar("High H", "Object Detection", &high_H, max_value_H, on_high_H_thresh_trackbar);
    cv::createTrackbar("Low S", "Object Detection", &low_S, max_value, on_low_S_thresh_trackbar);
    cv::createTrackbar("High S", "Object Detection", &high_S, max_value, on_high_S_thresh_trackbar);
    cv::createTrackbar("Low V", "Object Detection", &low_V, max_value, on_low_V_thresh_trackbar);
    cv::createTrackbar("High V", "Object Detection", &high_V, max_value, on_high_V_thresh_trackbar);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////
	TelerobCamera cam1(pCameras[0]);
	TelerobCamera cam2(pCameras[1]);
	char key = 0;
    while(key != 'q')
    {
		cam1.UpdateFrame();
		cam2.UpdateFrame();
		cvtColor(cam1.GetCurrentFrame(), frame_HSV1, cv::COLOR_BGR2HSV);
		cvtColor(cam2.GetCurrentFrame(), frame_HSV2, cv::COLOR_BGR2HSV);
		inRange(frame_HSV1, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), frame_threshold1);
		inRange(frame_HSV2, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), frame_threshold2);

        cv::imshow("image1", cam1.GetCurrentFrame()); 
        cv::imshow("Object Detection1", frame_threshold1);
        cv::imshow("Object Detection2", frame_threshold2);
        cv::imshow("image2", cam2.GetCurrentFrame());
        key = cv::waitKey(30);        
    }
    return 0;
}
