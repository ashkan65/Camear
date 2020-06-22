#include <iostream>
#include "telerobcamera.hpp"

TelerobCamera::TelerobCamera(){
    // Will add latter
};

TelerobCamera::TelerobCamera(CameraPtr pcams){
    pCam = pcams;
    Initial();
};

TelerobCamera::~TelerobCamera(){
    // Will add latter
    // pCam->DeInit();
};



void TelerobCamera::SaveCurrentFrame(std::string fileName){
    // UpdateFrame();
    cv::imwrite(fileName, CurrentImage);
};

void TelerobCamera::ReleaseCamera(){
    //Memory problem fix this!!!!!!!!!!!!!!!!
    pCam->DeInit();
};

cv::Mat TelerobCamera::GetCurrentFrame(){
    UpdateFrame();
    return CurrentImage;
};
// int TelerobCamera::TempUpdateFrame(){
//     //This is a temp file; I neeed to change it later ______ Ashkan:
//     int result;
//     try
//     {
//         // Errors (in case camera doesn't work)
//         // Retrieve TL device nodemap and print device information
//         INodeMap& nodeMapTLDevice = pCam->GetTLDeviceNodeMap();
//         // result = PrintDeviceInfo(nodeMapTLDevice);
//         // Initialize camera
//         pCam->Init();
//         // Retrieve GenICam nodemap
//         INodeMap& nodeMap = pCam->GetNodeMap();
//         // pCam->DeInit();
//         CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
//         if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
//         {
//             std::cout << "Unable to set acquisition mode to continuous (enum retrieval). Aborting..." << std::endl << std::endl;
//             return -1;
//         }
//         // Retrieve entry node from enumeration node
//         CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
//         if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
//         {
//             std::cout << "Unable to set acquisition mode to continuous (entry retrieval). Aborting..." << std::endl << std::endl;
//             return -1;
//         }
//         // Retrieve integer value from entry node
//         const int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();
//         // Set integer value from entry node as new value of enumeration node
//         ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
//         // std::cout << "Acquisition mode set to continuous..." << std::endl;
//     }
//     catch (Spinnaker::Exception& e)
//     {
//         std::cout << "Error: " << e.what() << std::endl;
//         result = -1;
//     }

//     pCam->BeginAcquisition();
//     pResultImage = pCam->GetNextImage();
//     pResultImage->Release();
//     // pCam->EndAcquisition();
//     if (pResultImage->IsIncomplete())
//         {
//             // Retrieve and print the image status description
//             std::cout << "Image incomplete: " << Image::GetImageStatusDescription(pResultImage->GetImageStatus())
//                  << "..." << std::endl
//                  << std::endl;
//         }
//     else
//         {
//             const size_t width = pResultImage->GetWidth();
//             const size_t height = pResultImage->GetHeight();
//             pResultImage = pResultImage->Convert(PixelFormat_BGR8, Spinnaker::IPP);
//             unsigned int XPadding = pResultImage->GetXPadding();
//             unsigned int YPadding = pResultImage->GetYPadding();
//             unsigned int rowsize = pResultImage->GetWidth();
//             unsigned int colsize = pResultImage->GetHeight();
//             CurrentImage = cv::Mat(colsize + YPadding, rowsize + XPadding, CV_8UC3, pResultImage->GetData(), pResultImage->GetStride());
//             // pResultImage->Release();
//         }
//     pCam->EndAcquisition(); 
// }

void TelerobCamera::UpdateFrame(){

// int a = TempUpdateFrame();


    try
    {
        // result = result | GrabNextImageByTrigger(nodeMap, pCam);
        // pCam->BeginAcquisition();
        ImagePtr pResultImage2 = pCam->GetNextImage();
        // pResultImage->Release();
        // pCam->EndAcquisition();
        if (pResultImage2->IsIncomplete())
            {
                // Retrieve and print the image status description
                std::cout << "Image incomplete: " << Image::GetImageStatusDescription(pResultImage2->GetImageStatus())
                     << "..." << std::endl
                     << std::endl;
            }
            else
            {
                const size_t width = pResultImage2->GetWidth();
                const size_t height = pResultImage2->GetHeight();
                pResultImage2 = pResultImage2->Convert(PixelFormat_BGR8, Spinnaker::IPP);
                unsigned int XPadding = pResultImage2->GetXPadding();
                unsigned int YPadding = pResultImage2->GetYPadding();
                unsigned int rowsize = pResultImage2->GetWidth();
                unsigned int colsize = pResultImage2->GetHeight();
                CurrentImage = cv::Mat(colsize + YPadding, rowsize + XPadding, CV_8UC3, pResultImage2->GetData(), pResultImage2->GetStride());
                // pResultImage->Release();
            }
        pResultImage2->Release();

    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        result = -1;
    }
    // pResultImage->Release();
};

int TelerobCamera::Initial(){
    int result;
    try
    {
        // Errors (in case camera doesn't work)
        // Retrieve TL device nodemap and print device information
        INodeMap& nodeMapTLDevice = pCam->GetTLDeviceNodeMap();
        result = PrintDeviceInfo(nodeMapTLDevice);
        // Initialize camera
        pCam->Init();
        // Retrieve GenICam nodemap
        INodeMap& nodeMap = pCam->GetNodeMap();
        // pCam->DeInit();
        CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
        if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
        {
            std::cout << "Unable to set acquisition mode to continuous (enum retrieval). Aborting..." << std::endl << std::endl;
            return -1;
        }
        // Retrieve entry node from enumeration node
        CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
        if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
        {
            std::cout << "Unable to set acquisition mode to continuous (entry retrieval). Aborting..." << std::endl << std::endl;
            return -1;
        }
        // Retrieve integer value from entry node
        const int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();
        // Set integer value from entry node as new value of enumeration node
        ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);
        std::cout << "Acquisition mode set to continuous..." << std::endl;
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        result = -1;
    }

    pCam->BeginAcquisition();
    // parameters = cv::aruco::DetectorParameters::create();
    // dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
};

int TelerobCamera::ConfigureTrigger(INodeMap& nodeMap)
{
    int result = 0;
    std::cout << std::endl << std::endl << "*** CONFIGURING TRIGGER ***" << std::endl << std::endl;
    if (chosenTrigger == SOFTWARE)
    {
        std::cout << "Software trigger chosen..." << std::endl;
    }
    else if (chosenTrigger == HARDWARE)
    {
        std::cout << "Hardware trigger chosen..." << std::endl;
    }
    try
    {
        //
        // Ensure trigger mode off
        //
        // *** NOTES ***
        // The trigger must be disabled in order to configure whether the source
        // is software or hardware.
        //
        CEnumerationPtr ptrTriggerMode = nodeMap.GetNode("TriggerMode");
        if (!IsAvailable(ptrTriggerMode) || !IsReadable(ptrTriggerMode))
        {
            std::cout << "Unable to disable trigger mode (node retrieval). Aborting..." << std::endl;
            return -1;
        }
        CEnumEntryPtr ptrTriggerModeOff = ptrTriggerMode->GetEntryByName("Off");
        if (!IsAvailable(ptrTriggerModeOff) || !IsReadable(ptrTriggerModeOff))
        {
            std::cout << "Unable to disable trigger mode (enum entry retrieval). Aborting..." << std::endl;
            return -1;
        }
        ptrTriggerMode->SetIntValue(ptrTriggerModeOff->GetValue());
        std::cout << "Trigger mode disabled..." << std::endl;
        //
        // Select trigger source
        //
        // *** NOTES ***
        // The trigger source must be set to hardware or software while trigger
        // mode is off.
        //
        CEnumerationPtr ptrTriggerSource = nodeMap.GetNode("TriggerSource");
        if (!IsAvailable(ptrTriggerSource) || !IsWritable(ptrTriggerSource))
        {
            std::cout << "Unable to set trigger mode (node retrieval). Aborting..." << std::endl;
            return -1;
        }
        if (chosenTrigger == SOFTWARE)
        {
            // Set trigger mode to software
            CEnumEntryPtr ptrTriggerSourceSoftware = ptrTriggerSource->GetEntryByName("Software");
            if (!IsAvailable(ptrTriggerSourceSoftware) || !IsReadable(ptrTriggerSourceSoftware))
            {
                std::cout << "Unable to set trigger mode (enum entry retrieval). Aborting..." << std::endl;
                return -1;
            }
            ptrTriggerSource->SetIntValue(ptrTriggerSourceSoftware->GetValue());
            std::cout << "Trigger source set to software..." << std::endl;
        }
        else if (chosenTrigger == HARDWARE)
        {
            // Set trigger mode to hardware ('Line0')
            CEnumEntryPtr ptrTriggerSourceHardware = ptrTriggerSource->GetEntryByName("Line0");
            if (!IsAvailable(ptrTriggerSourceHardware) || !IsReadable(ptrTriggerSourceHardware))
            {
                std::cout << "Unable to set trigger mode (enum entry retrieval). Aborting..." << std::endl;
                return -1;
            }
            ptrTriggerSource->SetIntValue(ptrTriggerSourceHardware->GetValue());
            std::cout << "Trigger source set to hardware..." << std::endl;
        }
        //
        // Turn trigger mode on
        //
        // *** LATER ***
        // Once the appropriate trigger source has been set, turn trigger mode
        // on in order to retrieve images using the trigger.
        //
        CEnumEntryPtr ptrTriggerModeOn = ptrTriggerMode->GetEntryByName("On");
        if (!IsAvailable(ptrTriggerModeOn) || !IsReadable(ptrTriggerModeOn))
        {
            std::cout << "Unable to enable trigger mode (enum entry retrieval). Aborting..." << std::endl;
            return -1;
        }
        ptrTriggerMode->SetIntValue(ptrTriggerModeOn->GetValue());
        // TODO: Blackfly and Flea3 GEV cameras need 1 second delay after trigger mode is turned on
        std::cout << "Trigger mode turned back on..." << std::endl << std::endl;
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        result = -1;
    }
    return result;
};
int TelerobCamera::GrabNextImageByTrigger(INodeMap& nodeMap, CameraPtr pCam)
{
    int result = 0;
    try
    {
        if (chosenTrigger == SOFTWARE)
        {
            CCommandPtr ptrSoftwareTriggerCommand = nodeMap.GetNode("TriggerSoftware");
            if (!IsAvailable(ptrSoftwareTriggerCommand) || !IsWritable(ptrSoftwareTriggerCommand))
            {
                std::cout << "Unable to execute trigger. Aborting..." << std::endl;
                return -1;
            }
            ptrSoftwareTriggerCommand->Execute();
            // TODO: Blackfly and Flea3 GEV cameras need 2 second delay after software trigger
        }
        else if (chosenTrigger == HARDWARE)
        {
            // Execute hardware trigger
            std::cout << "Use the hardware to trigger image acquisition." << std::endl;
        }
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        result = -1;
    }
    return result;
}


int TelerobCamera::ResetTrigger(INodeMap& nodeMap)
{
    int result = 0;
    try
    {
        CEnumerationPtr ptrTriggerMode = nodeMap.GetNode("TriggerMode");
        if (!IsAvailable(ptrTriggerMode) || !IsReadable(ptrTriggerMode))
        {
            std::cout << "Unable to disable trigger mode (node retrieval). Non-fatal error..." << std::endl;
            return -1;
        }
        CEnumEntryPtr ptrTriggerModeOff = ptrTriggerMode->GetEntryByName("Off");
        if (!IsAvailable(ptrTriggerModeOff) || !IsReadable(ptrTriggerModeOff))
        {
            std::cout << "Unable to disable trigger mode (enum entry retrieval). Non-fatal error..." << std::endl;
            return -1;
        }
        ptrTriggerMode->SetIntValue(ptrTriggerModeOff->GetValue());
        std::cout << "Trigger mode disabled..." << std::endl << std::endl;
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        result = -1;
    }
    return result;
}


int TelerobCamera::PrintDeviceInfo(INodeMap& nodeMap)
{
    std::cout << std::endl << "*** DEVICE INFORMATION ***" << std::endl << std::endl;
    try
    {
        FeatureList_t features;
        const CCategoryPtr category = nodeMap.GetNode("DeviceInformation");
        if (IsAvailable(category) && IsReadable(category))
        {
            category->GetFeatures(features);
            for (auto it = features.begin(); it != features.end(); ++it)
            {
                const CNodePtr pfeatureNode = *it;
                std::cout << pfeatureNode->GetName() << " : ";
                CValuePtr pValue = static_cast<CValuePtr>(pfeatureNode);
                std::cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << "Device control information not available." << std::endl;
        }
    }
    catch (Spinnaker::Exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}