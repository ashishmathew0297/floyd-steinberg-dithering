#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void floyd_steinberg_dithering(Mat img, int factor);
void normal_dithering(Mat img, int factor);

int main(int argc, char *argv[]) {
  
  string input = "../input/elden_ring_liurnia.png";
  int factor = 31;
  // string input = argv[1];
  // string output = argv[2];

  Mat img = imread(input);

  // The best way to confirm that the initial dithering works is to
  // test it on a grayscale image uncomment this line if testing is
  // needed.
  // cvtColor(img, img, COLOR_BGR2GRAY);

  normal_dithering(img, factor);
  
  return 0;
}

void normal_dithering(Mat img, int factor) {
  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {

        Vec3i bgrPixel = img.at<Vec3b>(i, j);

        bgrPixel[0] = round(factor*bgrPixel[0]/255)*255/factor;
        bgrPixel[1] = round(factor*bgrPixel[1]/255)*255/factor;
        bgrPixel[2] = round(factor*bgrPixel[2]/255)*255/factor;

        img.at<Vec3i>(i, j) = bgrPixel;
    }
  }

  imwrite("../output/elden_ring_liurnia_dithered.png", img);
}

void floyd_steinberg_dithering(Mat img, int factor) {
  for(int i = 0; i < img.rows-1; i++) {
    for(int j = 0; j < img.cols-1; j++) {

        Vec3i bgrPixel = img.at<Vec3b>(i, j);

        bgrPixel[0] = round(factor*bgrPixel[0]/255) * 255/factor;
        bgrPixel[1] = round(factor*bgrPixel[1]/255) * 255/factor;
        bgrPixel[2] = round(factor*bgrPixel[2]/255) * 255/factor;

        Vec3i error = bgrPixel - img.at<Vec3i>(i, j);

        // spreading out the error to other pixels in the image
        img.at<Vec3i>(i+1, j)     += (error * 7)/16;
        img.at<Vec3i>(i+1, j+1)   += (error * 1)/16;
        img.at<Vec3i>(i, j+1)     += (error * 5)/16;
        if(i > 0)
          img.at<Vec3i>(i-1, j+1) += (error * 3)/16;

        img.at<Vec3i>(i, j) = bgrPixel;
    }
  }

  imwrite("../output/elden_ring_liurnia_steinberg.png", img);
}