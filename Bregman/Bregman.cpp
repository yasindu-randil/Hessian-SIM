

#include "mex.h"
#include <opencv2/core.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>

// Helper functions
cv::Mat forwardDifferenciation(cv::Mat img);

// Debugging function
std::string type2str(int type);

void mexFunction(int nlhs, mxArray* plhs[], int nrhs, const mxArray* prhs[])
{
    int i;
    char* str[100];

    /* Check for proper number of input and output arguments */
    if (nrhs < 2) {
        mexErrMsgIdAndTxt("MATLAB:mxcreatecharmatrixfromstr:minrhs",
            "At least two input arguments required.");
    }
    if (nlhs > 1) {
        mexErrMsgIdAndTxt("MATLAB:mxcreatecharmatrixfromstr:maxlhs",
            "Too many output arguments.");
    }

    // *********************************** reading and stacking *************************************


    std::vector<cv::Mat> img;
    
    // Read the mulit framed imaged into a  vector of cv::Mat
    imreadmulti("C:\\Users\\yryas\\OneDrive\\Desktop\\Hessian SIM\\Hessian SIM\\raw-data\\Actin_97hz_7ms exposure raw data.tif", img, cv::IMREAD_UNCHANGED);

    int width = img[0].cols;
    int height = img[0].rows;
    int numberofFrames = img.size();

    // Convert to CV_32FC1 from CV_16U
    for (int i = 0; i < numberofFrames; i++) {
        img[i].convertTo(img[i], CV_32FC1);
    }

    //cv::namedWindow("Hessian-SIM", cv::WINDOW_AUTOSIZE);
    //cv::imshow("Hessian-SIM", img);


    // *********************************** Initialization *************************************

    int iterBregman = 100; //number of iiterations
    double lamda = 0.5;
    int gexiang = 1;
    int siranu = 150; //mu value
    int zbei = 1; // sigma value
    double minVal;
    double maxVal, tempVal=0.0;
    cv::Point minLoc;
    cv::Point maxLoc;
    // get the time 

    int yFlag = numberofFrames; 

    if (yFlag < 3)
    {
        zbei = 0;
        //y(:,:,end+1:end+(3-size(y,3)))=repmat(y(:,:,end),[1,1,3-size(y,3)]);
        std::cout << "Number of data frame is smaller than 3, the t and z-axis of Hessian was turned off(sigma=0) " << std::endl;
    }

    // Get the maimum elemnt value
    for ( int i=0; i< numberofFrames; i++)
    {
        cv::minMaxLoc(img[i], &minVal, &maxVal, &minLoc, &maxLoc);
        if (tempVal < maxVal)
        {
            tempVal = maxVal;
        }
    }

    int yMax = tempVal; 

    // Divide each element by yMax

    for (int i = 0; i < numberofFrames; i++) {
        img[i] = img[i] / yMax;
    }
 
    int sizeX[] = { width, height, numberofFrames };
    cv::Mat x = cv::Mat::zeros(3, sizeX, CV_32FC1);
    std::cout << " " << type2str(img[179].type()) << " Mat img  = " << " Width: " << width << " height: " << height << " Frames: " << img.size() << std::endl;
   
    // *********************************** Start Point *************************************


    //// ***************************** FFT of difference operator ****************************

    //// *********************************** Iteration ***************************************
    //
    //// *********************************** Renew *******************************************

    //// ************************ calculate the dirivative of x **********************************

    //cv::Mat frac = img * (siranu / lamda);
    //forwardDifferenciation(img);

    //*********************************** String Program *******************************************

    for (i = 0; i < nrhs; i++) {
        /* Check input to be sure it is of type char. */
        if (!mxIsChar(prhs[i])) {
            mexErrMsgIdAndTxt("MATLAB:mxcreatecharmatrixfromstr:invalidInputType",
                "Input must be of type char.");
        }
        /* Copy the string data from prhs and place it into str. */
        str[i] = mxArrayToString(prhs[i]);
    }
    char* char_arr;
    auto s = std::to_string(yMax);
    std::string str_obj(s);
    char_arr = &str_obj[0];
    str[2] = char_arr;
//    /* Create a 2-Dimensional string mxArray with NULL padding. */
    plhs[0] = mxCreateCharMatrixFromStrings((mwSize)3, (const char**)str);

    /* If compile with -DSPACE_PADDING, convert NULLs to spaces */
#if defined(SPACE_PADDING)
    {
        mwSize j;
        mwSize nelem = mxGetNumberOfElements(plhs[0]);
        mxChar* charData = (mxChar*)mxGetData(plhs[0]);
        for (j = 0; j < nelem; j++) {
            if (charData[j] == (mxChar)0) {
                charData[j] = (mxChar)' ';
            }
        }
    }
#endif
    /* Free the allocated memory */
    for (i = 0; i < nrhs; i++) {
        mxFree(str[i]);
    }
    //*********************************** End of String Program *******************************************
}

cv::Mat forwardDifferenciation(cv::Mat img)
{
    cv::Mat tempX = img;
    cv::Mat diff, out;

    int width = tempX.cols;
    int height = tempX.rows;
    int channels = 180;
    cv::resize(img, tempX, cv::Size(width+1, height+1));
    cv::Mat temp1= cv::Mat::zeros(tempX.size(), CV_32FC(channels +1));
    cv::Mat temp2 = cv::Mat::zeros(tempX.size(), CV_32FC(channels + 1));


    for (int i = 0; i < 180; i++) {

        for ( int row = 0; row < img.rows; row++) {
            for ( int col = 1; col < img.cols; col++) {
                //process pixel:
                //img.at<double>(i, row, col) = img.at<double>(i, row, col) / yMax;
            }
        }
    }
    //temp2(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3))=data;
    for (int i = 0; i < 180; i++) {

        for ( int row = 0; row < img.rows; row++) {
            for ( int col = 1; col < img.cols; col++) {
                //process pixel:
                //img.at<double>(i, row, col) = img.at<double>(i, row, col) / yMax;
            }
        }
    }
    //temp2(1:SIZE(1),1:SIZE(2),1:SIZE(3))=data;
    for (int i = 0; i < 180; i++) {

        for (int row = 0; row < img.rows; row++) {
            for (int col = 1; col < img.cols; col++) {
                //process pixel:
                //img.at<double>(i, row, col) = img.at<double>(i, row, col) / yMax;
            }
        }

    }
    absdiff(temp1, temp2, diff);
    //out = temp1(position(1):SIZE(1),position(2):SIZE(2),position(3):SIZE(3)); 
    for (int i = 0; i < 180; i++) {

        for (int row = 0; row < img.rows; row++) {
            for (int col = 1; col < img.cols; col++) {
                //process pixel:
                //img.at<double>(i, row, col) = img.at<double>(i, row, col) / yMax;
            }
        }

    }

    out = cv::abs(out);
    std::cout << "Forward Differenciation - Done!" << std::endl;
    return out;
}

std::string type2str(int type) {
    std::string r;

    uchar depth = type & CV_MAT_DEPTH_MASK;
    uchar chans = 1 + (type >> CV_CN_SHIFT);

    switch (depth) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
    }

    r += "C";
    r += (chans + '0');

    return r;
}