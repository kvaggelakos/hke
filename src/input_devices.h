#pragma once

#include <string>
#include <vector>


struct InputDeviceInfo {
  std::string name;
  std::string path;
  uint16_t bus_id;
  uint16_t vendor_id;
  uint16_t product_id;
};



class InputDevices {
  public:
    std::vector<InputDeviceInfo> getInputDevices();
};