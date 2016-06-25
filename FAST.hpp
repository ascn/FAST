#include <stdio.h>
#include "opencv2/opencv.hpp"

using namespace cv;

std::vector<Point2f> getCircle(Point2f p);

std::vector<Point2f> detectFASTFeatures(Mat m, int threshold, int n = 12);
