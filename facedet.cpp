#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/core/utils/logger.hpp>

using namespace cv;

int main (int argc, char **argv) {
  utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <model> <image path>\n" << std::endl;
    return EXIT_FAILURE;
  }
  
  Mat src = imread(argv[2], IMREAD_COLOR);
  Mat srcGray;
  cvtColor(src, srcGray, COLOR_BGR2GRAY);
  equalizeHist(srcGray, srcGray);

  CascadeClassifier faceCascade;
  faceCascade.load(argv[1]);

  std::vector<Rect> faces;
  faceCascade.detectMultiScale(srcGray, faces);

  for (auto face : faces) {
    std::cout << face.x << " " << face.y << " " << face.width << " " << face.height << std::endl;
  }
  
  return EXIT_SUCCESS;
}
