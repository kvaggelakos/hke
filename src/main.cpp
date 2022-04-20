#include <iostream>
#include <vector>
#include <string>

#include "input_devices.h"

int main() {
  std::cout << "Pick your keyboard device:" << std::endl;

  InputDevices id;
  std::vector<std::string> devices = id.getInputDevices();

  return 0;
}