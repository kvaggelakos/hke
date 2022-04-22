#include "input_devices.h"

#include <iostream>


std::vector<InputDeviceInfo> InputDevices::getInputDevices() {
  libusb_device **devs;
  libusb_context *ctx = NULL;
  ssize_t cnt;
  int r;
  std::vector<InputDeviceInfo> res;

  // Init session
  r = libusb_init(&ctx);
  if (r < 0) {
    std::cout << "Could not initialize libusb" << std::endl;
    return res;
  }

  cnt = libusb_get_device_list(ctx, &devs);
  if (cnt < 0) {
    std::cout << "Found 0 devices on usb..." << std::endl;
    return res;
  }

  ssize_t i;
  for (i = 0; i < cnt; i++) {
    res.emplace_back(this->getDeviceInfo(devs[i]));
  }

  libusb_free_device_list(devs, 1);
  libusb_exit(ctx);

  return res;
}

InputDeviceInfo InputDevices::getDeviceInfo(libusb_device *dev) {
  libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
    std::cerr << "Could not get device descriptor" << std::endl;
    throw;
	}

  unsigned char tmp[256];

  libusb_device_handle *handle = NULL;
  int ret = 0;
  ret = libusb_open(dev, &handle);

  if (ret == LIBUSB_SUCCESS) {
    libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, tmp, sizeof(tmp));
  } else {
    libusb_close(handle);
    std::cerr << "Could not read from USB device" << std::endl;
    throw;
  }
  libusb_close(handle);
  std::string manufacturer(reinterpret_cast<char*>(tmp));

  InputDeviceInfo idi;
  idi.deviceClass = desc.bDeviceClass;
  idi.idVendor = desc.idVendor;
  idi.idProduct = desc.idProduct;
  idi.manufacturer = manufacturer;

  return idi;
}