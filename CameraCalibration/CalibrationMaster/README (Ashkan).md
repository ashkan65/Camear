## OpenCV C++ Stereo Camera Calibration

This  is the modified version of the calibraion master. 
### Dependencies

- OpenCV
- popt

### Compilation

Compile all the files using the following commands.

```bash
mkdir build && cd build
cmake ..
make
```

Make sure your are in the `build` folder to run the executables.

### Get images from Cameras

For "webcam" use the command bellow, 
```bash
./read -w [img_width] -h [img_height] -d [imgs_directory] -e [file_extension]
```

Once it is running, hit any key to grab frames. Images are saved with prefixes `left` and `right` in the desired directory.


For "Flir cameras" , you need to go to Desktop/CameraCalibraion/RecordFrames


### Intrinsic calibration of a single camera

This is only for lenses which follow the pinhole model. If you have fisheye lenses with a very wide field of view then see [this](https://github.com/sourishg/fisheye_stereo_calibration) repository. The calibration saves the camera matrix and the distortion coefficients in a YAML file. The datatype for these matrices is `Mat`.

Once you have compiled the sources run the following command to calibrate the intrinsics.

```bash
./calibrate -w [board_width] -h [board_height] -n [num_imgs] -s [square_size] -d [imgs_directory] -i [imgs_filename] -o [file_extension] -e [output_filename]
```

### Or just run:######################################
```bash
./calibrate -w 9 -h 6 -n 100 -s 8.1555555 -d "../../RecordFrames/build/images/" -i "left" -o "cam_left.yml" -e "jpg"
./calibrate -w 9 -h 6 -n 100 -s 8.1555555 -d "../../RecordFrames/build/images/" -i "right" -o "cam_right.yml" -e "jpg"
```

### Stereo calibration for extrinisics

Once you have the intrinsics calibrated for both the left and the right cameras, you can use their intrinsics to calibrate the extrinsics between them.

```bash
./calibrate_stereo -n [num_imgs] -u [left_cam_calib] -v [right_cam_calib] -L [left_img_dir] -R [right_img_dir] -l [left_img_prefix] -r [right_img_prefix] -o [output_calib_file] -e [file_extension]
```

### Or just run:#######################################
```bash
./calibrate_stereo -n 100 -u cam_left.yml -v cam_right.yml -L ../../RecordFrames/build/images/ -R ../../RecordFrames/build/images/ -l left -r right -o cam_stereo.yml -e jpg
```

### Undistortion and Rectification

Once you have the stereo calibration data, you can remove the distortion and rectify any pair of images so that the resultant epipolar lines become scan lines.

```bash
./undistort_rectify -l [left_img_path] -r [right_img_path] -c [stereo_calib_file] -L [output_left_img] -R [output_right_img]
```

For example run: ######################################

```bash
./undistort_rectify -l ../../RecordFrames/build/images/left1.jpg -r ../../RecordFrames/build/images/right1.jpg -c cam_stereo.yml -L left.jpg -R right.jpg
```


