#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main() {
  string path = "../input/lenna_test_image.png";
  Mat img = imread(path);

  cout << "(" << img.rows << "," << img.cols << ")" << endl;

  // Image information in OpenCV is stored in the form of BGR values as opposed to the standard RGB values

  // Fetching pixel information from the image
  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {

        Vec3i bgrPixel = img.at<Vec3b>(i, j);

        int tmp = 0;
        tmp = bgrPixel[0];
        bgrPixel[0] = bgrPixel[2];
        bgrPixel[2] = bgrPixel[1];
        bgrPixel[1] = tmp;

        img.at<Vec3b>(i, j) = bgrPixel;
    }
  }


  imwrite("../output/test.png", img);
  return 0;
}