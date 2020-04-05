#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>

int main (int argc, char **argv) {
  /* Parameters */
  const double kScaleFactor = 1.11;
  const int kMinNeighbors = 4;
  const cv::Size kMinSize = cv::Size(40, 40);

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <model> <image path>\n", argv[0]);
    return EXIT_FAILURE;
  }

  auto classifier = cv::CascadeClassifier(argv[1]);
  
  cv::Mat srcImage = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
  cv::Mat equalizedImage;
  cv::equalizeHist(srcImage, equalizedImage);
  
  std::vector<cv::Rect> objects;
  std::vector<int> rejectLevels;
  std::vector<double> levelWeights;
  classifier.detectMultiScale(equalizedImage,
    objects,
    rejectLevels,
    levelWeights,
    kScaleFactor,
    kMinNeighbors,
    cv::CASCADE_SCALE_IMAGE,
    kMinSize,
    cv::Size(),
    true);

  for (size_t i = 0; i < objects.size(); i++) {
    printf("Face detected : %d %d %d %d rejectLevels=%d levelWeights=%.10f\n",
      objects[i].x,
      objects[i].y,
      objects[i].width,
      objects[i].height,
      rejectLevels[i],
      levelWeights[i]);
  }
  
  return EXIT_SUCCESS;
}
