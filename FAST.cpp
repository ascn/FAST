#include <stdio.h>
#include "opencv2/opencv.hpp"

#include "FAST.hpp"

using namespace cv;

std::vector<Point2f> getCircle(Point2f p) {
    std::vector<Point2f> ret;
    ret.push_back(Point2f(p.x, p.y - 3));
    ret.push_back(Point2f(p.x + 1, p.y - 3));
    ret.push_back(Point2f(p.x + 2, p.y - 2));
    ret.push_back(Point2f(p.x + 3, p.y - 1));
    ret.push_back(Point2f(p.x + 3, p.y));
    ret.push_back(Point2f(p.x + 3, p.y + 1));
    ret.push_back(Point2f(p.x + 2, p.y + 2));
    ret.push_back(Point2f(p.x + 1, p.y + 3));
    ret.push_back(Point2f(p.x, p.y + 3));
    ret.push_back(Point2f(p.x - 1, p.y + 3));
    ret.push_back(Point2f(p.x - 2, p.y + 2));
    ret.push_back(Point2f(p.x - 3, p.y + 1));
    ret.push_back(Point2f(p.x - 3, p.y));
    ret.push_back(Point2f(p.x - 3, p.y - 1));
    ret.push_back(Point2f(p.x - 2, p.y - 2));
    ret.push_back(Point2f(p.x - 1, p.y - 3));
    return ret;
}

std::vector<Point2f> detectFASTFeatures(Mat m, int threshold, int n) {
    Mat img;
    cvtColor(m, img, CV_BGR2GRAY);
    std::vector<Point2f> ret;
    for (int i = 3; i < img.rows - 3; ++i) {
        const double *imgI = img.ptr<double>(i);
        for (int j = 3; j < img.cols - 3; ++j) {
            int intensity = img.at<uchar>(i, j);
            std::vector<Point2f> circle = getCircle(Point2f(i, j));
            int count_plus = 0, count_minus = 0;
            for (int k = 0; k < circle.size(); ++k) {
                Point2f p = circle[k];
                if (img.at<uchar>(p.x, p.y) > intensity + threshold) {
                    count_plus++;
                } else if (img.at<uchar>(p.x, p.y) < intensity - threshold) {
                    count_minus++;
                }
            }
            if (count_plus > n || count_minus > n) {
                ret.push_back(Point2f(j, i));
            }
        }
    }
    return ret;
}
