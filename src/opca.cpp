
#include "opca.hpp"

static bool is_first_condition(const cv::Mat& src, int y, int x)
{
    cv::Point2i points[8] = { cv::Point2i(x, y - 1),
                              cv::Point2i(x + 1, y - 1),
                              cv::Point2i(x + 1, y),
                              cv::Point2i(x + 1, y + 1),
                              cv::Point2i(x, y + 1),
                              cv::Point2i(x - 1, y + 1),
                              cv::Point2i(x - 1, y),
                              cv::Point2i(x - 1, y - 1) };

    int sum = 0;

    for (int i = 0; i < 8; ++i)
        sum += src.at<uint8_t>(points[i]) / UINT8_MAX;

    return (sum >= 2 && sum <= 6);
}

static bool is_second_condition(const cv::Mat& src, int y, int x)
{
    cv::Point2i points[8] = { cv::Point2i(x, y - 1),
                              cv::Point2i(x + 1, y - 1),
                              cv::Point2i(x + 1, y),
                              cv::Point2i(x + 1, y + 1),
                              cv::Point2i(x, y + 1),
                              cv::Point2i(x - 1, y + 1),
                              cv::Point2i(x - 1, y),
                              cv::Point2i(x - 1, y - 1) };

    int sum = 0;

    for (int i = 0; i < 8; ++i)
    {
        int j = ((i + 2) - 2 + 1) % 8 + 2;
        sum += abs(src.at<uint8_t>(points[i]) / UINT8_MAX - src.at<uint8_t>(points[j - 2]) / UINT8_MAX);
    }

    return (sum == 2);
}

static bool is_third_condition(const cv::Mat& src, int y, int x)
{
    cv::Point2i points[6] = { cv::Point2i(x, y - 1),
                              cv::Point2i(x + 1, y),
                              cv::Point2i(x, y + 1),
                              cv::Point2i(x - 1, y),
                              cv::Point2i(x + 2, y),
                              cv::Point2i(x, y + 2) };

    bool parts[6] = {0};

    for (int i = 0; i < 6; ++i)
    {
        if (i == 1 || i == 2)
            parts[i] = (src.at<uint8_t>(points[i]) / UINT8_MAX) == 1;
        else
            parts[i] = (src.at<uint8_t>(points[i]) / UINT8_MAX) == 0;
    }

    return !((parts[1] && parts[3] && parts[4]) || (parts[2] && parts[0] && parts[5]));
}

static bool is_last_condition(const cv::Mat& src, int y, int x)
{
    cv::Point2i points[8] = { cv::Point2i(x, y - 1),
                              cv::Point2i(x + 1, y - 1),
                              cv::Point2i(x + 1, y),
                              cv::Point2i(x + 1, y + 1),
                              cv::Point2i(x, y + 1),
                              cv::Point2i(x - 1, y + 1),
                              cv::Point2i(x - 1, y),
                              cv::Point2i(x - 1, y - 1) };

    int сount = 0;

    for (int i = 0; i < 4; ++i)
    {
        bool parts[3] = {0};

        int j = 2 * i + 1;
        int k = ((2 * (i + 1) + 1) - 2 + 3) % 8 + 2;
        int m = ((2 * (i + 1) + 1) - 2 + 5) % 8 + 2;

        parts[0] = (src.at<uint8_t>(points[j]) / UINT8_MAX) == 0;
        parts[1] = (src.at<uint8_t>(points[k - 2]) / UINT8_MAX) == 1;
        parts[2] = (src.at<uint8_t>(points[m - 2]) / UINT8_MAX) == 1;

        if (parts[0] && parts[1] && parts[2])
            ++сount;
    }

    return (сount == 4);
}

void opca(const cv::Mat& src, cv::Mat& dst)
{
    src.copyTo(dst);

    bool isEnd = false;

    while (!isEnd)
    {
        isEnd = true;

        cv::Mat matrix(dst.size(), dst.type(), cv::Scalar(1));

        for (int y = 1; y < (src.rows - 1); ++y)
        {
            for (int x = 1; x < (src.cols - 1); ++x)
            {
                if ((dst.at<uint8_t>(y, x) / UINT8_MAX) == 1)
                {
                    if (is_first_condition(dst, y, x) && is_second_condition(dst, y, x) && is_third_condition(dst, y, x))
                    {
                        matrix.at<uint8_t>(y, x) = 0;
                        isEnd = false;
                    }
                }
            }
        }

        cv::multiply(dst, matrix, dst);
    }

    for (int y = 1; y < (src.rows - 1); ++y)
    {
        for (int x = 1; x < (src.cols - 1); ++x)
        {
            if ((dst.at<uint8_t>(y, x) / UINT8_MAX) == 1)
            {
                if (is_last_condition(dst, y, x))
                    dst.at<uint8_t>(y, x) = 0;
            }
        }
    }
}
