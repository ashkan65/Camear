#include <iostream>
#include "telerobcamera.hpp"

TelerobCamera::TelerobCamera(){
    // Will add latter
};

TelerobCamera::TelerobCamera(FlyCapture2::Camera& pcams){
    pCam = &pcams;
    int I = Initial();
};

TelerobCamera::~TelerobCamera(){
        pCam->StopCapture();
        pCam->Disconnect();
        // delete pCam;
};

void TelerobCamera::PrintCameraInfo(FlyCapture2::CameraInfo *pCamInfo)
{
    std::cout << std::endl;
    std::cout << "*** CAMERA INFORMATION ***" << std::endl;
    std::cout << "Serial number - " << pCamInfo->serialNumber << std::endl;
    std::cout << "Camera model - " << pCamInfo->modelName << std::endl;
    std::cout << "Camera vendor - " << pCamInfo->vendorName << std::endl;
    std::cout << "Sensor - " << pCamInfo->sensorInfo << std::endl;
    std::cout << "Resolution - " << pCamInfo->sensorResolution << std::endl;
    std::cout << "Firmware version - " << pCamInfo->firmwareVersion << std::endl;
    std::cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << std::endl
         << std::endl;
};

int TelerobCamera::Initial(){
    // Get the camera information
    error = pCam->GetCameraInfo(&camInfo);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        delete pCam;
        std::cout << "Press Enter to exit." << std::endl;
        std::cin.ignore();
        return -1;
    }

    PrintCameraInfo(&camInfo);
    // Turn trigger mode off
    trigMode.onOff = false;
    error = pCam->SetTriggerMode(&trigMode);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        delete pCam;
        std::cout << "Press Enter to exit." << std::endl;
        std::cin.ignore();
        return -1;
    }
    // Turn Timestamp on
    imageInfo.timestamp.onOff = true;
    error = pCam->SetEmbeddedImageInfo(&imageInfo);
    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        delete pCam;
        std::cout << "Press Enter to exit." << std::endl;
        std::cin.ignore();
        return -1;
    }
    // Start streaming on camera
    error = pCam->StartCapture();

    if (error != FlyCapture2::PGRERROR_OK)
    {
        error.PrintErrorTrace();
        delete pCam;
        std::cout << "Press Enter to exit." << std::endl;
        std::cin.ignore();
        return -1;
    }
	return 0;
};


void TelerobCamera::UpdateFrame(){
    error = pCam->RetrieveBuffer( &FCImage_raw );
    if ( error != FlyCapture2::PGRERROR_OK )
    {
    	error.PrintErrorTrace();
        std::cout << "capture error" << std::endl;
    }
}; //Updates the frame


cv::Mat TelerobCamera::GetCurrentFrame(){
	FCImage_raw.Convert( FlyCapture2::PIXEL_FORMAT_BGR, &FCImage_RGB );
	// convert to OpenCV Mat
	unsigned int rowBytes = (double)FCImage_RGB.GetReceivedDataSize()/(double)FCImage_RGB.GetRows();       
	// cv::Mat CVImage_RGB;
	CVImage_RGB = cv::Mat(FCImage_RGB.GetRows(), FCImage_RGB.GetCols(), CV_8UC3, FCImage_RGB.GetData(),rowBytes);
	return CVImage_RGB;
};	

void TelerobCamera::SaveCurrentFrame(std::string fileName){
    // UpdateFrame();
    cv::imwrite(fileName, CVImage_RGB);
};