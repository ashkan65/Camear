#ifndef CAMTR_H
#define CAMTR_H
/*****************************************************
type.h  (requires opencv and spinlib library)  defines matrix types: 

    Inherits:
		Spinnaker
		Opencv
Ver 1.0 by Ashkan July-2019		
*****************************************************/
#include <chrono>
#include <Spinnaker.h>
#include <SpinGenApi/SpinnakerGenApi.h>
#include <SpinVideo.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <thread>
// #include <iostream>
// #include <sstream>
using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;



enum triggerType
{
    SOFTWARE,
    HARDWARE
};
const triggerType chosenTrigger = SOFTWARE;

class TelerobCamera{
	private:
		CameraPtr pCam = nullptr;     /* pointer to the camera */
		int result = 0;
		int error = 0;
		ImagePtr pResultImage; 			//PointGray Image 
		cv::Mat CurrentImage; 			//Opencv Image
		//Dict of the IDs for the targets:
		int GrabNextImageByTrigger(INodeMap& nodeMap, CameraPtr pCam);
		int ResetTrigger(INodeMap& nodeMap);
		int ConfigureTrigger(INodeMap& nodeMap);

	public:
		TelerobCamera();
		~TelerobCamera();
		TelerobCamera(CameraPtr pcam); 
		int Initial();
					//( pointer to camera   , pointer target pose, Target id, Size of the target in (mm), calibration file name)   
		void ReleaseCamera();	// Releases the camera (use it when you are done)! 
		void SaveCurrentFrame(std::string fileName); // Updates and saves the current frame to the filename. You can draw the coordiante for the marker and also add the markers ID for ALL OF THE IDs.   
		cv::Mat GetCurrentFrame();	//Returns the current frame from the camera (Type : opencv Mat)
		int PrintDeviceInfo(INodeMap& nodeMap);	//Prints the device (use it to be sure the camera is detected.)
		void UpdateFrame(); //Updates the frame
		int TempUpdateFrame();
};
#endif // CAMTR_H

