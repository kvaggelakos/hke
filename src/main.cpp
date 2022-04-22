#include <iostream>
#include <vector>
#include <string>

#include "input_devices.h"

int main() {
  std::cout << "Pick your keyboard device:" << std::endl;

  InputDevices inputDevices;
  std::vector<InputDeviceInfo> devices = inputDevices.getInputDevices();

  for (auto idi : devices) {
    std::cout << idi.manufacturer << std::endl;
  }

  return 0;
}