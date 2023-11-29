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
  cout << img;

  imwrite("../output/test.png", img);
  return 0;
}