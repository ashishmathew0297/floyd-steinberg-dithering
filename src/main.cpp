#include "opencv2/opencv.hpp"
#include <iostream>
#include <omp.h>

using namespace std;
using namespace cv;

void floyd_steinberg_dithering(string input, int factor);
void floyd_steinberg_dithering_parallel(string input, int factor, int num_threads);
void quantization(string input, int factor);
void floyd_steinberg_calculation(Mat &img, Mat &result, int factor, int i, int j);

int main(int argc, char *argv[]) {
  
  double start = omp_get_wtime();

  // fetching command line arguments
  string input = argv[1]; 
  int dithered = atoi(argv[2]);
  int factor = atoi(argv[3]);
  int run_parallel_code = atoi(argv[4]);
  int num_threads = atoi(argv[5]);

  dithered == 1 ? floyd_steinberg_dithering(input, factor) : quantization(input, factor);
  
  if(run_parallel_code == 1)
    floyd_steinberg_dithering_parallel(input, factor, num_threads);

  double end = omp_get_wtime();
  double result = end - start;
  cout << result << " ";
  return 0;
}

void quantization(string input, int factor) {
  Mat img = imread("../input/" + input);
  Mat result = img.clone();

  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {

        Vec3i oldbgrPixel = img.at<Vec3b>(i, j);
        Vec3i newbgrPixel;

        newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0) * 255/factor;
        newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0) * 255/factor;
        newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0) * 255/factor;

        result.at<Vec3b>(i, j) = newbgrPixel;
    }
  }

  imwrite("../output/quantized_" + input, result);
}

uint8_t clamp(int value) {
  return max(0, min(value, 255));
}

void floyd_steinberg_dithering(string input, int factor) {
  Mat img = imread("../input/" + input);
  Mat result = img.clone();
  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {
      floyd_steinberg_calculation(img, result, factor, i, j);
    }
  }
  imwrite("../output/dithered_" + input, result);
}


void floyd_steinberg_calculation(Mat &img, Mat &result, int factor, int i, int j) {
  Vec3i oldbgrPixel = img.at<Vec3b>(i, j);
  Vec3i newbgrPixel;
  int quantization_error[3] = {0};

  newbgrPixel[0] = round(factor*oldbgrPixel[0]/255.0) * 255.0/factor;
  newbgrPixel[1] = round(factor*oldbgrPixel[1]/255.0) * 255.0/factor;
  newbgrPixel[2] = round(factor*oldbgrPixel[2]/255.0) * 255.0/factor;

  result.at<Vec3b>(i, j) = newbgrPixel;

  // spreading out the error to other pixels in the image
  for(int k = 0; k < 3; k++) {
    quantization_error[k] = (int)img.at<Vec3b>(i, j)[k] - newbgrPixel[k];
    if(i + 1 < img.rows)
      img.at<Vec3b>(i+1, j)[k]   = clamp((int)img.at<Vec3b>(i+1, j)[k]   + (quantization_error[k] * 7)/16.0);
    if(i + 1 < img.rows && j + 1 < img.cols)
      img.at<Vec3b>(i+1, j+1)[k] = clamp((int)img.at<Vec3b>(i+1, j+1)[k] + (quantization_error[k] * 1)/16.0);
    if(j + 1 < img.cols)
      img.at<Vec3b>(i, j+1)[k]   = clamp((int)img.at<Vec3b>(i, j+1)[k]   + (quantization_error[k] * 5)/16.0);
    if (i + 1 < img.rows && j > 0)
      img.at<Vec3b>(i+1, j-1)[k] = clamp((int)img.at<Vec3b>(i+1, j-1)[k] + (quantization_error[k] * 3)/16.0);
  }
}

void floyd_steinberg_dithering_parallel(string input, int factor, int num_threads) {
  Mat img = imread("../input/" + input);
  Mat result = img.clone();
  
  // This tracks the progress of the threads through the rows
  bool** progress = new bool*[img.rows];

  // This keeps track of the current workgroup's progress
  bool* workgroup_progress = new bool[img.rows];

  for (int i = 0; i < img.rows; i++){
    progress[i] = new bool[img.cols];
  }
  for (int i = 0; i < img.rows; i++){
    for (int j = 0; j < img.cols; j++)
      progress[i][j] = false;
  }
  for (int k = 0; k < img.rows; k++){
    workgroup_progress[k] = false;
  }
  
  omp_set_num_threads(num_threads);
  #pragma omp parallel shared(progress,workgroup_progress,img,result)
  {
    #pragma omp for schedule(static,1)
    for(int i = 0; i < img.rows; i++) {
      
      for(int j = 0; j < img.cols; j++) {
        if(i == 0) {
          {
          floyd_steinberg_calculation(img, result, factor, i, j);
          progress[i][j] = true;
          if(j == img.cols-1)
            workgroup_progress[i] = true;
          }
        } else {
          // Checking previous thread progress in case our current worker thread is
          // at the third or second last pixel
          if(j+2 < img.cols || j+1 < img.cols)
            while(progress[i-1][j+2] == false && progress[i-1][j+1] == false);
          else if(j == img.cols-1)
            workgroup_progress[i] = true;
          else
            while(workgroup_progress[i-1] == false);
          floyd_steinberg_calculation(img, result, factor, i, j);
          progress[i][j] = true;
        }
      }
    }
  }

  //Freeing up space taken up by trackers
  for (int i = 0; i < img.rows; i++){
    delete[] progress[i];
  }
  delete[] progress;
  delete [] workgroup_progress;

  imwrite("../output/parallel_dithered_" + input, result);
}

// https://stackoverflow.com/questions/13224155/how-does-the-omp-ordered-clause-work/
// #pragma omp for ordered schedule(static,1) could have worked too but it gave the wrong results