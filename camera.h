#ifndef CAMERA_H
#define CAMERA_H

// CV libs
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

class String;

class Camera : public cv::VideoCapture
{
public:
    Camera() :
        cv::VideoCapture(){}
    Camera(const std::string & filename) :
        cv::VideoCapture(filename){}
    Camera(const std::string & filename, int apiPreference) :
        cv::VideoCapture(filename, apiPreference){}
    Camera(int index) :
        cv::VideoCapture(index){}

    void getEmptyFrame(cv::Mat &dst);
    void getFrame(cv::Mat &dst);

private:
    cv::Mat frame_;
};

#endif // CAMERA_H
