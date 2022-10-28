
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opca.hpp"

void preprocess(const cv::Mat& src, cv::Mat& dst);
void pause();

int main()
{
    cv::Mat image, grey, preprocessed, dst;

    image = cv::imread("dataset/csgo.jpg", cv::IMREAD_COLOR);
    cvtColor(image, grey, cv::COLOR_BGR2GRAY);
    preprocess(grey, preprocessed);
    opca(preprocessed, dst);

    cv::imshow("Preprocessed", preprocessed);
    cv::imshow("Skeleton", dst);
    pause();
    cv::destroyAllWindows();

    return 0;
}

void preprocess(const cv::Mat& src, cv::Mat& dst)
{
    src.copyTo(dst);

    cv::medianBlur(dst, dst, 9);
    cv::threshold(dst, dst, 80, 255, cv::THRESH_BINARY);
    cv::erode(dst, dst, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9)));
    cv::dilate(dst, dst, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9)));

    for (int y = 0; y < src.rows; ++y)
    {
        dst.at<uint8_t>(y, 0) = 0;
        dst.at<uint8_t>(y, src.cols - 1) = 0;
    }

    for (int x = 0; x < src.cols; ++x)
    {
        dst.at<uint8_t>(0, x) = 0;
        dst.at<uint8_t>(src.rows - 1, x) = 0;
    }
}

void pause()
{
    while (cv::waitKey(5) != 27) {}
}
