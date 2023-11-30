#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void floyd_steinberg_dithering(string input, int factor);
void normal_dithering(string input, int factor);

int main(int argc, char *argv[]) {
  
  string input = "../input/elden_ring_liurnia.png";
  int factor = 47;
  // string input = argv[1];
  // string output = argv[2];


  // The best way to confirm that the initial dithering works is to
  // test it on a grayscale image uncomment this line if testing is
  // needed.
  // cvtColor(img, img, COLOR_BGR2GRAY);

  normal_dithering(input, factor);
  floyd_steinberg_dithering(input, factor);
  
  return 0;
}

void normal_dithering(string input, int factor) {
  Mat img = imread(input);

  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {

        Vec3i oldbgrPixel = img.at<Vec3b>(i, j);
        Vec3i newbgrPixel;

        newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0)*255/factor;
        newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0)*255/factor;
        newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0)*255/factor;

        img.at<Vec3b>(i, j) = newbgrPixel;
    }
  }

  imwrite("../output/elden_ring_liurnia_dithered.png", img);
}

void floyd_steinberg_dithering(string input, int factor) {
  Mat img = imread(input);

  for(int i = 0; i < img.rows-1; i++) {
    for(int j = 0; j < img.cols-1; j++) {

        Vec3i oldbgrPixel = img.at<Vec3b>(i, j);
        Vec3i newbgrPixel;

        newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0) * 255.0/factor;
        newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0) * 255.0/factor;
        newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0) * 255.0/factor;

        Vec3i error = newbgrPixel - oldbgrPixel;

        // spreading out the error to other pixels in the image
        img.at<Vec3b>(i+1, j)     += (error * 7)/16.0;
        img.at<Vec3b>(i+1, j+1)   += (error * 1)/16.0;
        img.at<Vec3b>(i, j+1)     += (error * 5)/16.0;
        if(i > 0)
          img.at<Vec3b>(i-1, j+1) += (error * 3)/16.0;

        img.at<Vec3b>(i, j) = newbgrPixel;
    }
  }

  imwrite("../output/elden_ring_liurnia_steinberg.png", img);
}