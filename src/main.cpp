#include "opencv2/opencv.hpp"
#include <iostream>
#include <omp.h>

using namespace cv;

void floyd_steinberg_dithering_serial(std::string input, int greyscale, int factor);
void floyd_steinberg_dithering_parallel(std::string input, int greyscale, int factor, int num_threads);
void quantization(std::string input, int greyscale, int factor);
void floyd_steinberg_calculation(Mat &img, Mat &result, int factor, int i, int j);

int main(int argc, char *argv[]) {
  
  double start = omp_get_wtime();

  // fetching command line arguments
  std::string input = argv[1];
  int greyscale = atoi(argv[2]);
  int dithered = atoi(argv[3]);
  int factor = atoi(argv[4]);
  int run_parallel_code = atoi(argv[5]);
  int num_threads = atoi(argv[6]);

  dithered == 1 ? floyd_steinberg_dithering_serial(input, greyscale, factor) : quantization(input, greyscale, factor);
  
  if(run_parallel_code == 1)
    floyd_steinberg_dithering_parallel(input, greyscale, factor, num_threads);

  double end = omp_get_wtime();
  double result = end - start;
  std::cout << result << " ";
  return 0;
}

void quantization(std::string input, int greyscale, int factor) {
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

  imwrite("../output/quantized_results/quantized_" + input, result);
}

uint8_t clamp(int value) {
  return max(0, min(value, 255));
}

void floyd_steinberg_dithering_serial(std::string input, int greyscale, int factor) {
  Mat img = imread("../input/" + input);
  if(greyscale == 1)
    cvtColor(img, img, COLOR_BGR2GRAY);
  Mat result = img.clone();
  for(int i = 0; i < img.rows; i++) {
    for(int j = 0; j < img.cols; j++) {
      floyd_steinberg_calculation(img, result, factor, i, j);
    }
  }
  imwrite("../output/serial_dithered_results/dithered_" + input, result);
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

void floyd_steinberg_dithering_parallel(std::string input, int greyscale, int factor, int num_threads) {
  Mat img = imread("../input/" + input);
  if(greyscale == 1)
    cvtColor(img, img, COLOR_BGR2GRAY);
  Mat result = img.clone();
  
  // This tracks the progress of the threads through the rows
  bool** progress = new bool*[img.rows];

  for (int i = 0; i < img.rows; i++){
    progress[i] = new bool[img.cols];
  }
  for (int i = 0; i < img.rows; i++){
    for (int j = 0; j < img.cols; j++)
      progress[i][j] = false;
  }
  
  omp_set_num_threads(num_threads);
  #pragma omp parallel shared(progress,img,result)
  {
    #pragma omp for schedule(static,1)
    for(int i = 0; i < img.rows; i++) {
      
      for(int j = 0; j < img.cols; j++) {
        
        // The first row of pixels gets priority as the thread working on it acts as
        // a pseudo master for the consequent workgroups
        if(i == 0) {
          floyd_steinberg_calculation(img, result, factor, i, j);
          progress[i][j] = true;
        } else {
          // From this block, the execution of rows other than the first row will be handled

          // This part of the code acts as the blocking mechanism while tracking the progress
          // of work in the thread above the current one ensuring that it is 2 pixels ahead
          if(j+2 < img.cols)
            while(progress[i-1][j+2] == false);
          else if(j+1 < img.cols)
            while(progress[i-1][j+1] == false);
          
          // Here we perform the Floyd-Steinberg calculation on the pixel after confirming that
          // the previous workgroups are done working on it
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

  imwrite("../output/parallel_dithered_results/parallel_dithered_" + input, result);
}

// https://stackoverflow.com/questions/13224155/how-does-the-omp-ordered-clause-work/
// #pragma omp for ordered schedule(static,1) could have worked too
// but it gave the wrong results for previous iterations of the code