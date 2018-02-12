#ifndef ELIR_STEREO_CAMERA_ELP_CAMERA_HPP
#define ELIR_STEREO_CAMERA_ELP_CAMERA_HPP

#include <thread>
#include <exception>

#include "opencv2/core/core.hpp"
#include "opencv2/core/version.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"

#include <ros/ros.h>

namespace elp 
{

class ElpCameraException: public std::exception 
{
  public:
    explicit ElpCameraException(const char* msg)
        :msg_(msg)
    {
      
    }

  virtual ~ElpCameraException()
  {

  }

  protected:
    virtual const char* what() 
    {
     return msg_.c_str();
    }
    std::string msg_;
};

class ElpCamera
{
  public:
    /**    
     * brief Default Constructor for ElpCamera.
     * 
     * Default Constructor for ElpCamera.
     * 
     * @return nothing 
     *
     */  
    explicit ElpCamera();
    /**    
     * brief Default Constructor for ElpCamera.
     * 
     * Default Constructor for ElpCamera.
     * 
     * @return nothing 
     *
     */  
    typedef void (*GRABCALLBACK)(cv::Mat src);
    virtual ~ElpCamera();
    /**    
     * brief Configures the camera callback method.
     * 
     * This method configures the camera callback method that will receive the images from streaming.
     * 
     * @param callback Function pointer to the desired callback.
     * @return void. 
     *
     */  
    void setupCallback(const GRABCALLBACK callback);
    /**    
     * brief Starts the camera streaming.
     * 
     * This method starts the camera streaming.
     * 
     * @return void. 
     *
     */  
    void startStreaming();
    /**    
     * brief Stops the camera streaming.
     * 
     * This method stops the camera streaming.
     * 
     * @return void. 
     *
     */  
    void stopStreaming();
     
  protected:
    /**    
     * brief Stops the camera streaming.
     * 
     * This method stops the camera streaming.
     * 
     * @return void. 
     *
     */  
    void imageAcquisition();

    int image_width_;
    int image_height_;

    bool is_streaming_; 

    std::thread *img_aqt_th_;
    GRABCALLBACK callback_;
};
} // elp namespace
#endif //ELIR_STEREO_CAMERA_ELP_CAMERA_HPP
