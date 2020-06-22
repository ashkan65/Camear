#include <iostream>
#include <vector>
#include "telerobcamera.hpp"
#include <unistd.h>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;






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
    SystemPtr system = System::GetInstance();
    
    // Retrieve list of cameras from the system
    std::cout << "\nGetting Camera(s)\n";

    CameraList camList = system->GetCameras();
    const unsigned int numCameras = camList.GetSize();
    std::cout << "Number of cameras detected: " << numCameras << std::endl;
    if (numCameras == 0)
    {
        // Clear camera list before releasing system
        camList.Clear();
        // Release system
        system->ReleaseInstance();
        std::cout << "Not enough cameras!" << std::endl;
        std::cout << "Done! Press Enter to exit..." << std::endl;
        getchar();
        return -1;
    }
    TelerobCamera cam1(camList.GetByIndex(0));
    TelerobCamera cam2(camList.GetByIndex(1));
    int x = 0;
    // for(int i = 1; i <= 40; i = i + 1)
    cv::Mat img1, img2;
    while(1)
    {
        img1 = cam1.GetCurrentFrame();
        img2 = cam2.GetCurrentFrame();
        cv::imshow("IMG1", img1);
        cv::imshow("IMG2", img2);
        if( cv::waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
        // if (cv::waitKey(60) > 0) {
        //     x++;
        //     char filename1[200], filename2[200];
        //     sprintf(filename1, "%sleft%d.%s", "../capturedi_mages/", x, "jpg");
        //     sprintf(filename2, "%sright%d.%s", "../capturedi_mages/", x, "jpg");
        //     cam1.SaveCurrentFrame(filename1);
        //     cam2.SaveCurrentFrame(filename2);
        //     std::cout << "Saving img pair " << x << std::endl;
        // }
    }
    return 0;
}


