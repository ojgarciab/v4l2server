/*
 * v4l2server.cpp
 *
 *  Created on: 07/04/2015
 *      Author: Oscar Javier Garcia Baudet
 */

#include <Ice/Ice.h>
#include <iostream>
#include <fstream>

#include "v4l2.h"
#include "camerai.h"

/** Interface class to define callback function */
class FrameCallback {
 public:
  // Callback function called when new frame is fetched from camera
  virtual int onFrame(void* buffer, int length) = 0;
 protected:
  ~FrameCallback() {
  }
};

int main(int argc, char** argv) {
  std::vector<Ice::ObjectPtr> cameras;
  Ice::CommunicatorPtr ice_communicator;

  try {
    /* Initialize communicator with command line parameters */
    ice_communicator = Ice::initialize(argc, argv);
    Ice::PropertiesPtr prop = ice_communicator->getProperties();
    std::string Endpoints = prop->getProperty("CameraSrv.Endpoints");

    int nCameras = prop->getPropertyAsInt("CameraSrv.NCameras");
    cameras.resize(nCameras);
    Ice::ObjectAdapterPtr adapter = ice_communicator
        ->createObjectAdapterWithEndpoints("CameraServer", Endpoints);
    for (int i = 0; i < nCameras; i++) {  //build camera objects
      std::stringstream objIdS;
      objIdS << i;
      std::string objId = objIdS.str();  // should this be something unique??
      std::string objPrefix("CameraSrv.Camera." + objId + ".");
      std::string cameraName = prop->getProperty(objPrefix + "Name");
      Ice::ObjectPtr object = new cameraserver::CameraI(objPrefix,
                                                        ice_communicator);
      adapter->add(object, ice_communicator->stringToIdentity(cameraName));

    }
    adapter->activate();
    ice_communicator->waitForShutdown();

  } catch (const Ice::Exception& ex) {
    std::cerr << ex << std::endl;
    exit(-1);
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    exit(-1);
  }
}
