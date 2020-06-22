The files in this folder are:

###CameraCalibration/RecordFrames
	Main.cpp
		This uses telerobcamera library and uses two camera and shows their feeds, by pressing "C", it records a frame from each of the cameras. 

		It records the images in build/images with names: right....jpg and left...jpg

###CameraCalibraion/Calibration
	This is opencv style, meaning is uses the setting files for camera calibraion and image lists. 

	Intrinsic_calibration.cpp:
		It also reads the images form the folder above. The address for images are in right_list and left_ist files. The settings are in setting_right and setting_left files.
		1- Read the readme inside the calibration folder
		Generates the light and left camera calibration files.

	Extrinsic_calibration.cpp
		Will come later (the Steriocalibration.cpp is not right)


###CameraCalibration/Calibration_master
	This is the downloaded version that modified for opencv 4.
	So far this works fine :D




