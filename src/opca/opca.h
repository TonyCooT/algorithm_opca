#pragma once

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class Opca
{
private:
    bool isFirstCondition(const cv::Mat& src, int y, int x);
    bool isSecondCondition(const cv::Mat& src, int y, int x);
    bool isThirdCondition(const cv::Mat& src, int y, int x);
    bool isLastCondition(const cv::Mat& src, int y, int x);
public:
    Opca();
    ~Opca();
    void opca(const cv::Mat& src, cv::Mat& dst);
};
