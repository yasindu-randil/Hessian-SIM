#include "fftn.h"


//Constructor
fftn::fftn()
{
	std::cout << " Inside fftn" << std::endl;
}

cv::Mat fftn::fftN(cv::Mat I)
{
    cv::Mat padded;
    int m = cv::getOptimalDFTSize(I.rows);
    int n = cv::getOptimalDFTSize(I.cols); // on the border add zero values
    cv::copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));
    cv::Mat planes[] = { cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32FC1) };
    cv::Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
    dft(complexI, complexI);            // this way the result may fit in the source matrix
    std::cout << " FFT N dimension processed!" << std::endl;
	return complexI;
}
