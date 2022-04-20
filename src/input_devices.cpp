#include "input_devices.h"

#include <iostream>

using namespace std;


vector<string> InputDevices::getInputDevices() {
  libusb_device **devs;
  libusb_context *ctx = NULL;
  ssize_t cnt;
  int r;

  // Init session
  r = libusb_init(&ctx);
  if (r < 0) {
    cout << "Could not initialize libusb" << endl;
    return vector<string>();
  }


  // Set verbosity level
  // libusb_set_debug(ctx, 3);

  cnt = libusb_get_device_list(ctx, &devs);
  if (cnt < 0) {
    cout << "Found 0 devices on usb..." << endl;
    return vector<string>();
  }

  ssize_t i;
  for (i = 0; i < cnt; i++) {
    this->printdev(devs[i]);
  }
  libusb_free_device_list(devs, 1);
  libusb_exit(ctx);

  return vector<string>();
}

void InputDevices::printdev(libusb_device *dev) {
  libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) {
		cout << "failed to get device descriptor" << endl;
		return;
	}

	cout << "Device Class: " << (int)desc.bDeviceClass << "  ";
	cout << "VendorID: " << desc.idVendor << "  ";
	cout << "ProductID: " << desc.idProduct << endl;

	// libusb_config_descriptor *config;
	// libusb_get_config_descriptor(dev, 0, &config);
	// cout<<"Interfaces: "<<(int)config->bNumInterfaces<<" ||| ";
	// const libusb_interface *inter;
	// const libusb_interface_descriptor *interdesc;
	// const libusb_endpoint_descriptor *epdesc;
	// for(int i=0; i<(int)config->bNumInterfaces; i++) {
	// 	inter = &config->interface[i];
	// 	cout<<"Number of alternate settings: "<<inter->num_altsetting<<" | ";
	// 	for(int j=0; j<inter->num_altsetting; j++) {
	// 		interdesc = &inter->altsetting[j];
	// 		cout<<"Interface Number: "<<(int)interdesc->bInterfaceNumber<<" | ";
	// 		cout<<"Number of endpoints: "<<(int)interdesc->bNumEndpoints<<" | ";
	// 		for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
	// 			epdesc = &interdesc->endpoint[k];
	// 			cout<<"Descriptor Type: "<<(int)epdesc->bDescriptorType<<" | ";
	// 			cout<<"EP Address: "<<(int)epdesc->bEndpointAddress<<" | ";
	// 		}
	// 	}
	// }
	// cout<<endl<<endl<<endl;
	// libusb_free_config_descriptor(config);
}
