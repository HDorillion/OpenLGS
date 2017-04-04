#include "matimageprocessor.h"

// Qt libs
//#include <QTimer>

// cv libs
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

// Static variables
cv::Scalar MatImageProcessor::lb_ = cv::Scalar(50-45,60,60);
cv::Scalar MatImageProcessor::ub_ = cv::Scalar(50+45,255,255);

// Static functions
void MatImageProcessor::Mat2QImage(const cv::Mat &src, QImage &dst){
    cv::Mat temp;
    cv::cvtColor(src, temp, cv::COLOR_BGR2RGB);
    dst = QImage((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    // Enforce deep copy of dest
    dst.bits();
}

void MatImageProcessor::QImage2Mat(QImage const& src, cv::Mat &dst){
    cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
    // deep copy just in case (my lack of knowledge with open cv)
    cv::cvtColor(tmp, dst, CV_BGR2RGB);
}

// Regular functions
MatImageProcessor::MatImageProcessor()
{

}

// processImage processes the image (will go in a class later)
void MatImageProcessor::processImage(const cv::Mat &src, QImage &dst){
    cv::Mat tmp, final;

    // Convert and process
    generateMask(src, fgmask_, bgmask_);

    src.copyTo(tmp);    
    tmp.setTo(cv::Scalar(0,0,0), fgmask_);
//    cv::Mat m_inverse = tmp.setTo(cv::Scalar(0,255,0), m_fgmask);
//    m_inv = tmp.setTo(cv::Scalar(0,0,0), m_invertedmask);
    final = tmp;

    cv::cvtColor(final, final, CV_HSV2BGR);

    // Return to QImage format
    Mat2QImage(final, dst);
}

// generateMask
void MatImageProcessor::generateMask(const cv::Mat &src, cv::Mat &fgmask, cv::Mat &bgmask){
    // Convert and process
    cv::cvtColor(src, src, CV_BGR2HSV);
    cv::inRange(src, lb_, ub_, bgmask);
    
    cv::bitwise_not(bgmask, fgmask);
}
