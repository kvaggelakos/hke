#pragma once

#include <string>
#include <vector>

#include <libusb-1.0/libusb.h>

class InputDevices {
  public:
    std::vector<std::string> getInputDevices();
  private:
    void printdev(libusb_device *dev);
};