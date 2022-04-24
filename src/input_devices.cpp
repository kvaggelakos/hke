#include "input_devices.h"

#include <filesystem>
#include <iostream>
#include <fcntl.h>
#include <libevdev-1.0/libevdev/libevdev.h>

const static int MAX_STR = 255;

std::string wchar2string(wchar_t* str)
{
  std::string mystring;
  while( *str )
    mystring += (char)*str++;
  return  mystring;
}


std::vector<InputDeviceInfo> InputDevices::getInputDevices() {
  std::vector<InputDeviceInfo> res;
  int fd, rc;
  struct libevdev *dev;

  for (const auto & entry : std::filesystem::directory_iterator("/dev/input/")) {
    std::cout << "Checking: " << entry.path() << std::endl;
    fd = open(const_cast<char*>(entry.path().c_str()), O_RDONLY|O_NONBLOCK);
    rc = libevdev_new_from_fd(fd, &dev);
    if (rc < 0) {
      std::cerr << "Could not read from device: " << entry.path() << std::endl;
      continue;
    }

    char name[256] = "???";
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);

    InputDeviceInfo idi;
    idi.vendor_id = libevdev_get_id_vendor(dev);
    idi.product_id = libevdev_get_id_product(dev);
    idi.bus_id = libevdev_get_id_bustype(dev);
    idi.path = entry.path();
    idi.name = std::string(name);

    res.emplace_back(idi);
    libevdev_free(dev);
  }

  return res;
}
