#include "matimageprocessor.h"

// Qt libs
//#include <QTimer>

// cv libs
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

// Static variables
cv::Scalar MatImageProcessor::m_lb = cv::Scalar(5,60,60);
cv::Scalar MatImageProcessor::m_ub = cv::Scalar(40,255,255);

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
    cv::Mat mask, tmp;

    // Convert and process
    cv::cvtColor(src, tmp, CV_BGR2HSV);
    cv::inRange(tmp, m_lb, m_ub, mask);
    tmp = cv::Scalar(0,0,0);
    src.copyTo(tmp);

    cv::cvtColor(tmp, tmp, CV_HSV2BGR);

    // Return to QImage format
    Mat2QImage(src, dst);
}
