#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <algorithm>

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
  std::vector<int> numDetections;
  classifier.detectMultiScale(equalizedImage,
    objects,
    numDetections,
    kScaleFactor,
    kMinNeighbors,
    /*cv::CASCADE_SCALE_IMAGE*/0,
    kMinSize);

  std::vector<std::pair<cv::Rect, int>> rectPairs;
  for (size_t i = 0; i <objects.size(); i++) {
    rectPairs.push_back(std::make_pair(objects[i], numDetections[i]));
  }

  std::sort(std::begin(rectPairs), std::end(rectPairs), [&](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  for (auto it = rectPairs.begin(); it != rectPairs.end(); it++) {
    printf("%d %d %d %d\n",
      it->first.x,
      it->first.y,
      it->first.width,
      it->first.height);
  }
  
  return EXIT_SUCCESS;
}
