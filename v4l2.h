/*
 * v4l2.h
 *
 *  Created on: 07/04/2015
 *      Author: redstar
 */

#ifndef JDEROBOT_COMPONENTS_V4L2SERVER_V4L2_H_
#define JDEROBOT_COMPONENTS_V4L2SERVER_V4L2_H_

#include <iostream>

namespace v4l2 {

class Camera {
 private:
  /* Camera device name */
  std::string device_;
  /* Camera file descriptor */
  int camera_fd_;
  /* Image width */
  int width_;
  /* Image height */
  int height_;
  /* Frames per second requested */
  int fps_;
  /* Camera active (capturing frames) */
  bool active_;

 public:
  Camera(std::string device, int width, int height, int fps);
  Camera(std::string device, int width, int height);
  void Start() throw (std::string);
  void Stop();
  bool is_active();
  ~Camera();
};

} /* namespace */

#endif /* JDEROBOT_COMPONENTS_V4L2SERVER_V4L2_H_ */