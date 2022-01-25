
#ifndef  OPCA_H_
#define  OPCA_H_

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <cstdint>

static bool isFirstCondition(const cv::Mat& src, int y, int x);
static bool isSecondCondition(const cv::Mat& src, int y, int x);
static bool isThirdCondition(const cv::Mat& src, int y, int x);
static bool isLastCondition(const cv::Mat& src, int y, int x);

void opca(const cv::Mat& src, cv::Mat& dst);

#endif // ! OPCA_H_
