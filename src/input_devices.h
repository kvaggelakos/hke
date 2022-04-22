#pragma once

#include <string>
#include <vector>

#include <libusb-1.0/libusb.h>

struct InputDeviceInfo
{
  std::string manufacturer;
  uint8_t deviceClass;
  uint16_t idVendor;
  uint16_t idProduct;
};



class InputDevices {
  public:
    std::vector<InputDeviceInfo> getInputDevices();
  private:
    InputDeviceInfo getDeviceInfo(libusb_device *dev);
};