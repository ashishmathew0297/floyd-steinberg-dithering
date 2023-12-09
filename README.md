# floyd-steinberg-dithering
An implementation of Floyd Steinberg Dithering using OpenCV and C++ with the end goal of implementing parallel computing to improve its performance on either higher resolution images or a series of images.

# Important to Run the Code

The code works on OpenCV 4.8.1. The steps I have taken to install this particular version of the OpenCV are given below. These steps will for the most part work the same way they did on my machine.

```bash
$ mkdir ~/opencv4.8-tmp && cd ~/opencv4.8-tmp
$ wget https://github.com/opencv/opencv/archive/4.8.1.zip -O opencv.zip
$ wget https://github.com/opencv/opencv_contrib/archive/4.8.1.zip -O $ opencv_contrib.zip
$ unzip opencv.zip
$ unzip opencv_contrib.zip
$ mv opencv-4.8.1/ opencv
$ mv opencv_contrib-4.8.1/ opencv_contrib
$ cd opencv && mkdir build && cd build
$ cmake -D CMAKE_BUILD_TYPE=DEBUG \
      -D CMAKE_INSTALL_PREFIX=~/opencv4.5-custom \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv4.5-tmp/opencv_contrib/modules \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
      -D BUILD_EXAMPLES=ON ..
$ make -j4
$ sudo make install
$ sudo apt install libopencv-dev
$ sudo apt-get install -y pkg-config
$ export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/home/parallels/opencv4.8-custom/lib/pkgconfig
$ pkg-config --cflags --libs opencv4 # This confirms that all the libraries have been symbolic linked
```

The last command should give us a list of packages similar to the one below. The number of packages included can vary based on the version of OpenCV that is built, but the functionality should be more or less the same because we are only making use of the core package modules.

```bash
-I/usr/include/opencv4 -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_barcode -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_shape -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_ml -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core
```

This is how we know that we have OpenCV up and running from the source code.

## Compiling the C++ Code

To build the code with a symbolic link to the CV package we will have to compile the code with the given flags

```bash
g++ -Wall -std=c++11 -o output_file program.cpp $(pkg-config --cflags --libs opencv4)
```

If the installation fails or you need to remove CV for any reason, the stackoverflow post below will aid in the uninstallation of the program from your system

<https://stackoverflow.com/questions/9276169/removing-all-installed-opencv-libs>

