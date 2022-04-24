#include "keypress.h"

#include <libevdev-1.0/libevdev/libevdev.h>
#include <iostream>
#include <fcntl.h>
#include <vector>


int KeyPress::listenForKeyPress(std::string path) {
  struct libevdev *dev = NULL;
  int fd = open(const_cast<char*>(path.c_str()), O_RDONLY);
  int rc = libevdev_new_from_fd(fd, &dev);
  if (rc) {
    std::cerr << "Failed to open device" << std::endl;
    return -1;
  }

  struct input_event ev;
  std::vector<int> keys;
  do {
    rc = libevdev_next_event(dev, LIBEVDEV_READ_FLAG_NORMAL, &ev);
    if (rc == 0 && ev.type == EV_MSC) {
      keys.emplace_back(ev.value);
    }
  } while (rc == 0 && keys.size() < 2);
  std::cout << "Pressed key: " << std::hex << keys.back() << std::endl;

  libevdev_free(dev);
  return keys.back();
}