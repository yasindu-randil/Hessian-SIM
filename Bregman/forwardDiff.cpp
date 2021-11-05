#include "forwardDiff.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
forwardDiff::forwardDiff()
{
}

cv::Mat forwardDiff::forwardDiffFunction( cv::Mat img, int sizex)
{
    cv::Mat tempX = img;
    cv::Mat diff, out;

    int width = tempX.cols;
    int height = tempX.rows;
    int channels = sizex;
    cv::resize(img, tempX, cv::Size(width + 1, height + 1));
    cv::Mat temp1 = cv::Mat::zeros(tempX.size(), CV_32FC(channels + 1));
    cv::Mat temp2 = cv::Mat::zeros(tempX.size(), CV_32FC(channels + 1));




    for (int row = 0; row < height; row++) {
        for (int col = 1; col < width; col++) {
            //process pixel:
            temp1.at<float>( row, col) = img.at<float>(row, col);
        }
    }

    //temp2(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
    for (int row = 0; row < height; row++) {
        for (int col = 1; col < width; col++) {
            //process pixel:
            temp2.at<float>(row, col) = img.at<float>(row, col);
        }
    }

    //temp2(1:SIZE(1),1:SIZE(2),1:SIZE(3))=data;
    for (int row = 0; row < height; row++) {
        for (int col = 1; col < width; col++) {
            //process pixel:
            temp2.at<float>(row, col) = img.at<float>(row, col);
        }
    }

    absdiff(temp1, temp2, diff);
    //out = temp1(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3)); 
    for (int row = 0; row < height; row++) {
        for (int col = 1; col < width; col++) {
            //process pixel:
            temp2.at<float>(row, col) = img.at<float>(row, col);
        }
    }

    out = cv::abs(out);
    std::cout << "Forward Differenciation - Done!" << std::endl;
    return out;

}
