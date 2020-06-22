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
#include <opencv2/viz.hpp>
// #include "print.h"  // This has the functions to print the camera and library version. TODO: move it somewhere else: 



int main () {
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cv::FileStorage cal_file("../../../CalibrationMaster/build/cam_stereo.yml", cv::FileStorage::READ);
    cv::Mat cameraMatrix1, cameraMatrix2, Projection1, Projection2, Rect1, Rect2; 
    cal_file["K1"] >> cameraMatrix1;
    cal_file["K2"] >> cameraMatrix2;
    cal_file["P1"] >> Projection1;
    cal_file["P2"] >> Projection2;
    cal_file["R1"] >> Rect1;
    cal_file["R2"] >> Rect2;
// std::cout<< Rect2;
    cv::Mat pnts3D(1,1,CV_64F);
	//////////////////////////////////////////////
	TelerobCamera cam1(pCameras[0]);
	TelerobCamera cam2(pCameras[1]);

    cv::Point Pt1, Pt2;
	char key = 0;
    while(key != 'q')
    {
		cam1.UpdateFrame();
		cam2.UpdateFrame();
        cam1.FilterCurrentFrame();
        cam2.FilterCurrentFrame();
        std::cout <<"This is one frame : ";
        Pt1 = cam1.GetTargetPose();
        Pt2 = cam2.GetTargetPose();
        cv::Mat Taret1 = (cv::Mat_<double>(2,1) << Pt1.x, Pt1.y);
        cv::Mat Taret2 = (cv::Mat_<double>(2,1) << Pt2.x, Pt2.y);

        cv::triangulatePoints(Projection1,Projection2,Taret1,Taret2,pnts3D);

        // std::cout << cam1.GetTargetPose();
        std::cout << pnts3D<<std::endl;
        cv::imshow("image1", cam1.GetCurrentFrame()); 
        // cv::imshow("Object Detection1", cam1.GetCurrentFilteredFrame());
        // cv::imshow("Object Detection2", cam2.GetCurrentFilteredFrame());
        cv::imshow("image2", cam2.GetCurrentFrame());
        key = cv::waitKey(30);        
    }
    return 0;
}




//////////////////////////////////

