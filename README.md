# Floyd-Steinberg Dithering

This is an implementation of the Floyd-Steinberg Dithering algorithm in C++ and OpenCV. The end goal of this project is to implement parallel processing concepts to this algorithm to see how it performs when working on high-resolution images.

## Downloading and Installing OpenCV from source

Our code works on OpenCV 4.8.1. The steps I have taken to install this particular version of the OpenCV are given below. These steps will for the most part work the same way they did on my machine.

```bash
$ mkdir ~/opencv4.8-tmp && cd ~/opencv4.8-tmp
$ wget https://github.com/opencv/opencv/archive/4.8.1.zip -O opencv.zip
$ wget https://github.com/opencv/opencv_contrib/archive/4.8.1.zip -O opencv_contrib.zip
$ unzip opencv.zip
$ unzip opencv_contrib.zip
$ mv opencv-4.8.1/ opencv
$ mv opencv_contrib-4.8.1/ opencv_contrib
$ cd opencv && mkdir build && cd build
$ cmake -D CMAKE_BUILD_TYPE=DEBUG \
      -D CMAKE_INSTALL_PREFIX=~/opencv4.8-custom \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv4.8-tmp/opencv_contrib/modules \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
      -D BUILD_EXAMPLES=ON ..
$ make -j4
$ sudo make install
$ sudo apt install libopencv-dev
$ sudo apt-get install -y pkg-config # most linux installations have this preinstalled, but in case your system doesn't have it, run this line
$ export PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/home/parallels/opencv4.8-custom/lib/pkgconfig
$ pkg-config --cflags --libs opencv4 # This confirms that all the libraries have been symbolic linked
```

After the above steps are complete there is a huge chance you would get an error related to PATh variables and pkgconfig. Refer to the link below for the fix for this

<https://stackoverflow.com/questions/15320267/package-opencv-was-not-found-in-the-pkg-config-search-path>

The last command `pkg-config --cflags --libs opencv4` should give us a list of packages similar to the one below. The number of packages included can vary based on the version of OpenCV that is built, but the functionality should be more or less the same because we are only making use of the core package modules.

```bash
-I/usr/include/opencv4 -lopencv_stitching -lopencv_alphamat -lopencv_aruco -lopencv_barcode -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hdf -lopencv_hfs -lopencv_img_hash -lopencv_intensity_transform -lopencv_line_descriptor -lopencv_mcc -lopencv_quality -lopencv_rapid -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_shape -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_highgui -lopencv_datasets -lopencv_text -lopencv_plot -lopencv_ml -lopencv_videostab -lopencv_videoio -lopencv_viz -lopencv_wechat_qrcode -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_dnn -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core
```

This is how we know that we have OpenCV up and running from the source code.

**IMPORTANT NOTE:** I have tried this process on the Anvil supercomputer, however, due to the requirement of superuser permissions, and access to PATH variables, I was unable to get it to work. This should, however work well on your local system.

## Compiling the C++ Code

To build the code with a symbolic link to the CV package we will have to compile the code with the given flags

```bash
g++ -Wall -std=c++11 -o output_file program.cpp $(pkg-config --cflags --libs opencv4)
```

If the installation fails or you need to remove CV for any reason, the Stackoverflow post below will aid in the uninstallation of the program from your system

<https://stackoverflow.com/questions/9276169/removing-all-installed-opencv-libs>

## Compiling the report

The report handles references using Biber. From the `reports/` folder, run the following commands to generate the report with citations.

```bash
pdflatex project_report.tex
biber project_report
pdflatex project_report.tex
```

## Project Structure

- `input/`: This folder stores all the images that act as inputs to our program.
- `output/`: This folder stores all the outputs of the C++ program
- `time_measurements/`: This folder stores the execution time measurements for the serial and parallel implementations of our code. The data here will be used by the Python code to generate graphs.
- `src/`: This folder contains the main codebase of our project and acts as the point of entry for executing all the code.

Here is the breakdown of the files in the `src/` folder.

- `run_scripts.sh`: This is the entry point of our project. running this code will execute all other bash scripts to generate the readings and reports.
- `generate_batch_outputs.sh`: This file, when called by `run_scripts.sh` iterates through all the image files in the inputs/ folder, generating the output images.
- `generate_image.sh`: This file, when called by `run_scripts.sh` generates images based on the parameters input by the user.
- `generate_serial_readings.sh`: This script, when run by the `run_scripts.sh` code generates time readings for studying the performance of the program.
- `generate_parallel_readings.sh`: This script, when run by the `run_scripts.sh` code generates time readings for studying the performance of the program.
- `plots_and_calculations.py`: This Python code generates scaling and time plots based on the data from the `time_measurements/` folder.
- `main.cpp`: This is the main codebase that our algorithm and its parallelized form exist on. This code can either be run on its own or through the `run_scripts.sh` file, which is much easier

## How to run the project

Please ensure OpenCV has been installed as per the [instructions](#downloading-and-installing-opencv) above before any of the scripts below are run.

Ensure all the shell scripts have execute permissions. Make any changes needed in the `run_scripts.sh` file if you want to generate a single result or want to process a batch of images. This shell script can be run with

```bash
./run_scripts.sh
```

If you want to compile and execute the C program, run the following.

```shell
g++ -Wall -std=c++11 -o output_file main.cpp $(pkg-config --cflags --libs opencv4)

./output_file <input_filename> <greyscale(0 or 1)> <dithered(0 or 1)> <factor(0 or 1)> <parallel(0 or 1)> <threads(The value is system dependent)>
```
