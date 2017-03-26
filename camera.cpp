#include "camera.h"

#include <string>

void Camera::getEmptyFrame(cv::Mat &dst){
    // Setup cv capture
    this->open(0);
    assert(this->isOpened() == true);

    this->read(m_frame);
    this->release();
    dst = m_frame = cv::Mat(m_frame.rows, m_frame.cols, m_frame.type(), cv::Scalar(0,0,0));
}

void Camera::getFrame(cv::Mat &dst){
    if(this->isOpened() == true) this->read(dst);
    else dst = m_frame;
}
