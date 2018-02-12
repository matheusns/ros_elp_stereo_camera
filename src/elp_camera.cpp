#include "include/elp_camera.hpp"

namespace elp
{
ElpCamera::ElpCamera()
    : callback_(nullptr)
    , image_width_(1280)
    , image_height_(720)
    , is_streaming_(true)
    , img_aqt_th_(nullptr)
{
    
} 

ElpCamera::~ElpCamera()
{
    if (img_aqt_th_ != nullptr) delete img_aqt_th_;
}

void ElpCamera::setupCallback(const GRABCALLBACK callback)
{
    if (callback != nullptr && is_streaming_)
    {
        imageAcquisition();
    }

}

void ElpCamera::startStreaming()
{
    if (!is_streaming_ && callback_ != nullptr)
    {
        img_aqt_th_ = new std::thread(&ElpCamera::imageAcquisition, this);
    }
}

void ElpCamera::stopStreaming()
{

}

void ElpCamera::imageAcquisition()
{
    cv::VideoCapture right_camera(0);
    cv::VideoCapture left_camera(0);

    right_camera.set(CV_CAP_PROP_FRAME_WIDTH, image_width_);
    left_camera.set(CV_CAP_PROP_FRAME_WIDTH, image_width_);

    right_camera.set(CV_CAP_PROP_FRAME_HEIGHT, image_height_);
    left_camera.set(CV_CAP_PROP_FRAME_HEIGHT, image_height_);

    right_camera.set( CV_CAP_PROP_FOURCC ,CV_FOURCC('M', 'J', 'P', 'G') );
    left_camera.set( CV_CAP_PROP_FOURCC ,CV_FOURCC('M', 'J', 'P', 'G') );


    is_streaming_ = false;
}
} // elp namespace 