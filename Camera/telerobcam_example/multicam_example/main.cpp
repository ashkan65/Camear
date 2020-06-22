#include <iostream>
#include <vector>
#include "telerobcamera.hpp"
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
// #include "print.h"  // This has the functions to print the camera and library version. TODO: move it somewhere else: 


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
	TelerobCamera cam1(pCameras[0]);
	TelerobCamera cam2(pCameras[1]);
	char key = 0;
    while(key != 'q')
    {
		cam1.UpdateFrame();
		cam2.UpdateFrame();
        cv::imshow("image1", cam1.GetCurrentFrame());
        cv::imshow("image2", cam2.GetCurrentFrame());
        key = cv::waitKey(30);        
    }
    return 0;
}
