# Manage keybindings for a device
This utility helps re-bind keys on your keyboard. My use case was to swap Caps Lock with Esc.
There are many other ways to do this, but none that work between plugging in and out your keyboard.

## Install deps

```
sudo apt install libevdev-dev
```

## Build
```
mkdir build
cd build
cmake ..
make
```

## Run
It needs sudo to read from the USB devices.

```
sudo ./hke
```