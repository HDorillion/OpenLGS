#ifndef MATIMAGEPROCESSOR_H
#define MATIMAGEPROCESSOR_H

#include <QImage>

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"

class QImage;

class MatImageProcessor
{
public:
    MatImageProcessor();

    // Static functions
    static void Mat2QImage(const cv::Mat &src, QImage &dst);
    static void QImage2Mat(QImage const& src, cv::Mat &dst);
    // Regular functions
    void processImage(const cv::Mat &src, QImage &dst);
    void generateMask(const cv::Mat &src, cv::Mat &fgmask, cv::Mat &bgmask);

    static cv::Scalar lb_, ub_;

private:
    cv::Mat fgmask_, bgmask_, norm_, inv_;
};

#endif // MATIMAGEPROCESSOR_H
