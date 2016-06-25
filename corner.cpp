#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "FAST.hpp"

using namespace cv;

int main(int argc, char **argv) {
    if (argc != 2) {
        return -1;
    }
    Mat c_img, img;
    img = imread(argv[1]);
    img.copyTo(c_img);
    imshow("Source", img);
    std::vector<Point2f> corners = detectFASTFeatures(img, 20, 12);
    for (int i = 0; i < corners.size(); ++i) {
        Point2f p = corners[i];
        circle(c_img, p, 2, Scalar(0, 0, 0));
    }
    imshow("Detected Corners", c_img);
    waitKey(0);
    return 0;
}

