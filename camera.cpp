#include "camera.h"

#include <string>

void Camera::getEmptyFrame(cv::Mat &dst){
    // Setup cv capture
    this->open(0);
    assert(this->isOpened() == true);

    this->read(frame_);
    this->release();
    dst = frame_ = cv::Mat(frame_.rows, frame_.cols, frame_.type(), cv::Scalar(0,0,0));
}

void Camera::getFrame(cv::Mat &dst){
    if(this->isOpened() == true) this->read(dst);
    else dst = frame_;
}
