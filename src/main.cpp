#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void floyd_steinberg_dithering(string input, int factor);
void quantization(string input, int factor);

int main(int argc, char *argv[]) {
  
  string input = "../input/lenna_gray.bmp";
  int factor = 1;


  // The best way to confirm that the initial dithering works is to
  // test it on a grayscale image uncomment this line if testing is
  // needed.
  // cvtColor(img, img, COLOR_BGR2GRAY);

  quantization(input, factor);
  floyd_steinberg_dithering(input, factor);
  
  return 0;
}

void quantization(string input, int factor) {
  Mat img = imread(input);

  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {

        Vec3i oldbgrPixel = img.at<Vec3b>(i, j);
        Vec3i newbgrPixel;

        newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0) * floor(255/factor);
        newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0) * floor(255/factor);
        newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0) * floor(255/factor);

        img.at<Vec3b>(i, j) = newbgrPixel;
    }
  }

  imwrite("../output/lenna_gray_quantized.tif", img);
}

uint8_t clamp(int value) {
  return max(0, min(value, 255));
}

void floyd_steinberg_dithering(string input, int factor) {
  Mat img = imread(input);

  for(int i = 0; i < img.rows-1; i++) {
    for(int j = 0; j < img.cols-1; j++) {

        Vec3i oldbgrPixel = img.at<Vec3b>(j, i);
        Vec3i newbgrPixel;
        Vec3i error;

        if(i < 2 && j < 2) {
          cout << "before" << endl;
          cout << img.at<Vec3b>(0, 0) << img.at<Vec3b>(0, 1) << img.at<Vec3b>(0, 2) << img.at<Vec3b>(0, 3) << endl;
        }

        newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0) * 255.0/factor;
        newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0) * 255.0/factor;
        newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0) * 255.0/factor;

        img.at<Vec3b>(j, i) = newbgrPixel;

        error[0] = newbgrPixel[0] - oldbgrPixel[0];
        error[1] = newbgrPixel[1] - oldbgrPixel[1];
        error[2] = newbgrPixel[2] - oldbgrPixel[2];

        // spreading out the error to other pixels in the image
        img.at<Vec3b>(j, i+1)[0]     = clamp(img.at<Vec3b>(j, i+1)[0] + (error[0] * 7)/16.0);
        img.at<Vec3b>(j, i+1)[1]     = clamp(img.at<Vec3b>(j, i+1)[1] + (error[1] * 7)/16.0);
        img.at<Vec3b>(j, i+1)[2]     = clamp(img.at<Vec3b>(j, i+1)[2] + (error[2] * 7)/16.0);

        img.at<Vec3b>(j+1, i+1)[0]   = clamp(img.at<Vec3b>(j+1, i+1)[0] + (error[0] * 1)/16.0);
        img.at<Vec3b>(j+1, i+1)[1]   = clamp(img.at<Vec3b>(j+1, i+1)[1] + (error[1] * 1)/16.0);
        img.at<Vec3b>(j+1, i+1)[2]   = clamp(img.at<Vec3b>(j+1, i+1)[2] + (error[2] * 1)/16.0);

        img.at<Vec3b>(j+1, i)[0]     = clamp(img.at<Vec3b>(j+1, i)[0] + (error[0] * 5)/16.0);
        img.at<Vec3b>(j+1, i)[1]     = clamp(img.at<Vec3b>(j+1, i)[1] + (error[1] * 5)/16.0);
        img.at<Vec3b>(j+1, i)[2]     = clamp(img.at<Vec3b>(j+1, i)[2] + (error[2] * 5)/16.0);

        if(i > 0) {
          img.at<Vec3b>(j+1, i-1)[0] = clamp(img.at<Vec3b>(j+1, i-1)[0] + (error[0] * 3)/16.0);
          img.at<Vec3b>(j+1, i-1)[1] = clamp(img.at<Vec3b>(j+1, i-1)[1] + (error[1] * 3)/16.0);
          img.at<Vec3b>(j+1, i-1)[2] = clamp(img.at<Vec3b>(j+1, i-1)[2] + (error[2] * 3)/16.0);
        }
        
        if(i < 3 && j < 3){
          cout << oldbgrPixel << newbgrPixel << error << endl;
          cout << "after" << endl;
          cout << img.at<Vec3b>(0, 0) << img.at<Vec3b>(0, 1) << img.at<Vec3b>(0, 2) << img.at<Vec3b>(0, 3) << endl << endl;
        }
    }
  }

  imwrite("../output/lenna_gray_steinberg.tif", img);
}