#include <opencv2/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#pragma once

class fftn
{
public:
	fftn();
	cv::Mat fftN( cv::Mat img);
};

