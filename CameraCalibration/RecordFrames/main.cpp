#include <iostream>
#include <vector>
#include "telerobcamera.hpp"
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
// #include "print.h"  // This has the functions to print the camera and library version. TODO: move it somewhere else: 


int main () {
    if (mkdir("images", 0777) == -1){ 
        std::cerr << "Error :  " << strerror(errno) << std::endl; 
        std::cout<<"Use sudo!!!!!!!";
        return 0;    
    }
    else{
        std::cout << "Directory created"; 
    }


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
    std::cout<<"Press C to capture a frame from each camera.\n";
	char key = 0;
    int x = 1;
    while(key != 'q')
    {
		cam1.UpdateFrame();
		cam2.UpdateFrame();
        cv::imshow("image1", cam1.GetCurrentFrame());
        cv::imshow("image2", cam2.GetCurrentFrame());
        if (key == 'c')
        {
            std::cout<<"frames captured!\n";
            char filename1[200], filename2[200];
            sprintf(filename1, "%sleft%d.%s", "images/", x, "jpg");
            sprintf(filename2, "%sright%d.%s", "images/", x, "jpg");
            cam1.SaveCurrentFrame(filename1);
            cam2.SaveCurrentFrame(filename2);
            std::cout << "Saving img pair " << x << std::endl;
            x++;
        }
        key = cv::waitKey(30);        
    }
    
    return 0;
}
