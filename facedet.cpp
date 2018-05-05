#include <stdlib.h>
#include <stdio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/ml.h>

int main (int argc, char **argv) {
  int i;
  IplImage *src_img = 0, *src_gray = 0;
  CvHaarClassifierCascade *cascade = 0;
  CvMemStorage *storage = 0;
  CvSeq *faces;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s <model> <image path>\n", argv[0]);
    return EXIT_FAILURE;
  }
  
  cascade = (CvHaarClassifierCascade *) cvLoad(argv[1], 0, 0, 0);
  if (!cascade) {
    fprintf(stderr, "Unable to load model\n");
    return EXIT_FAILURE;
  }

  src_img = cvLoadImage(argv[2]);
  if (!src_img) {
    fprintf(stderr, "Image coulnd't be loaded\n");
    return EXIT_FAILURE;
  }
  
  src_gray = cvCreateImage (cvGetSize(src_img), IPL_DEPTH_8U, 1);
  
  storage = cvCreateMemStorage (0);
  cvClearMemStorage (storage);
  cvCvtColor (src_img, src_gray, CV_BGR2GRAY);
  cvEqualizeHist (src_gray, src_gray);
  
  faces = cvHaarDetectObjects (src_gray, cascade, storage,
                               1.11, 4, 0, cvSize (40, 40));
  for (i = 0; i < (faces ? faces->total : 0); i++) {
    CvRect *r = (CvRect *) cvGetSeqElem (faces, i);
    printf("%d %d %d %d\n", r->x, r->y, r->width, r->height);
  }
  
  return EXIT_SUCCESS;
}
