#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void floyd_steinberg_dithering(string input, int factor);
void quantization(string input, int factor);

int main(int argc, char *argv[]) {
  
  string input = "../input/gradient_wb.jpg";
  int factor = 1;

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

  imwrite("../output/gradient_wb_quantized.jpg", img);
}

uint8_t clamp(int value) {
  return max(0, min(value, 255));
}

void floyd_steinberg_dithering(string input, int factor) {
  Mat img = imread(input);
  Mat result = img.clone();

  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {

        Vec3i oldbgrPixel = img.at<Vec3b>(j, i);
        Vec3i newbgrPixel;
        int quantization_error[3] = {0};

        // if(i < 2 && j < 2) {
        //   cout << "before" << endl;
        //   cout << img.at<Vec3b>(0, 0) << img.at<Vec3b>(0, 1) << img.at<Vec3b>(0, 2) << img.at<Vec3b>(0, 3) << endl;
        // }

        newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0) * 255.0/factor;
        newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0) * 255.0/factor;
        newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0) * 255.0/factor;

        result.at<Vec3b>(j, i) = newbgrPixel;

        // spreading out the error to other pixels in the image
        for(int k = 0; k < 3; k++) {
          quantization_error[k] = (int)img.at<Vec3b>(j, i)[k] - newbgrPixel[k];
          if(i + 1 < img.rows)
            img.at<Vec3b>(j, i+1)[k]     = clamp((int)img.at<Vec3b>(j, i+1)[k]   + (quantization_error[k] * 7)/16.0);
          if(i + 1 < img.rows && j+1 < img.cols)
            img.at<Vec3b>(j+1, i+1)[k]   = clamp((int)img.at<Vec3b>(j+1, i+1)[k] + (quantization_error[k] * 1)/16.0);
          if(j + 1 < img.cols)
            img.at<Vec3b>(j+1, i)[k]     = clamp((int)img.at<Vec3b>(j+1, i)[k]   + (quantization_error[k] * 5)/16.0);
          if (j > 0)
            img.at<Vec3b>(j-1, i+1)[k] = clamp((int)img.at<Vec3b>(j-1, i+1)[k] + (quantization_error[k] * 3)/16.0);
        }
        
        // if(i < 3 && j < 3){
        //   cout << oldbgrPixel << newbgrPixel << "[" << quantization_error[0] << "," << quantization_error[1] << "," << quantization_error[2] <<"]" << endl;
        //   cout << "after" << endl;
        //   cout << img.at<Vec3b>(0, 0) << img.at<Vec3b>(0, 1) << img.at<Vec3b>(0, 2) << img.at<Vec3b>(0, 3) << endl << endl;
        // }
    }
  }

  imwrite("../output/gradient_wb_steinberg.jpg", result);
}