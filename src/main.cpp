#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

#include "input_devices.h"
#include "keypress.h"

int main() {

  InputDevices input_devices;
  std::vector<InputDeviceInfo> devices = input_devices.getInputDevices();

  for (int i = 0; i < devices.size(); i++) {
    std::cout << i << "\t" << devices[i].name << std::endl;
  }

  // Get the keyboard option
  std::cout << "Pick your keyboard device:" << std::endl;
  std::string option;
  std::cin >> option;
  InputDeviceInfo selected = devices[std::stoi(option)];
  std::cout << "Selected device: " << selected.name << std::endl;

  // Read from device
  KeyPress kp;
  std::cout << "Press the key to replace" << std::endl;
  int old_key = kp.listenForKeyPress(selected.path);
  std::cout << "Press the key to replace it with" << std::endl;
  int new_key = kp.listenForKeyPress(selected.path);


  // Write to file
  std::ofstream file;
  file.open("/etc/udev/hwdb.d/50-keyboard.hwdb", std::ios::out);
  file << "# evdev:input:b<bus_id>v<vendor_id>p<product_id>e<version_id>-<modalias>" << std::endl;
  file << "evdev:input:" << std::uppercase << std::hex
    << "b" << std::setfill('0') << std::setw(4) << selected.bus_id
    << "v" << std::setfill('0') << std::setw(4) << selected.vendor_id
    << "p" << std::setfill('0') << std::setw(4) << selected.product_id
    << "*" << std::endl;
  file << " KEYBOARD_KEY_" << std::hex << old_key << "=" << "KEYBOARD_KEY_" << new_key << std::endl;
  file.close();


  // Update hwdb
  std::system("systemd-hwdb update");
  std::system("udevadm trigger");

  std::cout << "Done!" << std::endl;

  return 0;
}