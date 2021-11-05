#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#pragma once
class forwardDiff
{
public:
	forwardDiff();
	cv::Mat forwardDiffFunction(cv::Mat img, int sizex);
};

