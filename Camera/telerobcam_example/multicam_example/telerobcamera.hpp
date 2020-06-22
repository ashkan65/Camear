#ifndef TELCAM_H
#define TELCAM_H
/*****************************************************
type.h  (requires opencv and spinlib library)  defines matrix types: 

    Inherits:
		Flycapture
		Opencv
Ver 1.0 by Ashkan July-2019		
*****************************************************/
#include <chrono>
#include "FlyCapture2.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <thread>
// #include <iostream>
// #include <sstream>


class TelerobCamera{
	private:
		FlyCapture2::Camera* pCam = new FlyCapture2::Camera;     /* pointer to the camera */
		FlyCapture2::PGRGuid guid;
		FlyCapture2::Error error;
		FlyCapture2::CameraInfo camInfo;
		FlyCapture2::TriggerMode trigMode;
		FlyCapture2::EmbeddedImageInfo imageInfo;
		FlyCapture2::Image FCImage_raw;   //Flycapture Image
		FlyCapture2::Image FCImage_RGB;   //Flycapture Image
		cv::Mat CVImage_RGB; 			//Opencv Image
		// int GrabNextImageByTrigger(INodeMap& nodeMap, CameraPtr pCam);
		// int ResetTrigger(INodeMap& nodeMap);
		// int ConfigureTrigger(INodeMap& nodeMap);

	public:
		TelerobCamera();
		~TelerobCamera();
		TelerobCamera(FlyCapture2::Camera& pcams); 
		int Initial();
		void PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo);
		void UpdateFrame(); //Updates the frame
		cv::Mat GetCurrentFrame();	//Returns the current frame from the camera (Type : opencv Mat)
		void SaveCurrentFrame(std::string fileName); // Updates and saves the current frame to the filename. You can draw the coordiante for the marker and also add the markers ID for ALL OF THE IDs.   

		// 			//( pointer to camera   , pointer target pose, Target id, Size of the target in (mm), calibration file name)   
		// void ReleaseCamera();	// Releases the camera (use it when you are done)! 
		// int PrintDeviceInfo(INodeMap& nodeMap);	//Prints the device (use it to be sure the camera is detected.)
		
		// int TempUpdateFrame();
};
#endif // TELCAM_H