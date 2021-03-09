## Requirements

This project is a complete ray-tracing game engine solution written in C++. It requires special tools to work properly. Bellow, you can check if your computer is fully compatible with it.

### Hardware requirements

|      | Required                           | Recommended             |
|------|------------------------------------|-------------------------|
| GPU  | Discrete with hardware ray-tracing | RTX 3080                |
| CPU  | High speed and 4 thread unit       | AMD Ryzen 9 5900X       |
| RAM  | 16 GB                              | 32 GB of 3200 MHz CL16  |
| Disk | Enough space to clone respository  | M.2 PCI Express 4.0 SSD |

### Windows requirements

|                   | Required                      | Recommended                                   |
|-------------------|-------------------------------|-----------------------------------------------|
| OS                | Windows 7                     | Windows 10                                    |
| Source control    | Latest Git with LFS support   | -                                             |
| Project generator | CMake 3.17                    | -                                             |
| Vulkan SDK        | latest                        | 1.2.170.0                                     |
| GPU Drivers       | latest stable                 | -                                             |
| JS Toolchain      | Latest NodeJS and npm         | npm 6.14.0 & NodeJS 14.5.0                    |
| C/C++ Toolchain   | Microsoft Visual C++ Compiler | Microsoft Visual C++ Compiler 15.9 v14.6 v141 |

### Unix requirements

|                   | Required                    | Recommended                |
|-------------------|-----------------------------|----------------------------|
| OS                | Linux                       | Linux Mint 20.1            |
| Source control    | Latest Git with LFS support | -                          |
| Project generator | CMake 3.17                  | -                          |
| Vulkan SDK        | latest                      | 1.2.170.0                  |
| GPU Drivers       | latest stable               | -                          |
| JS Toolchain      | Latest NodeJS and npm       | npm 6.14.0 & NodeJS 14.5.0 |
| C/C++ Toolchain   | GCC & G++                   | GCC & G++ v 9.3.0          |

Unix is very versatile and diverse platform. To work on this project you need to have installed additional dependencies. Most of them should be already installed in your OS if you correctly installed other tools mentioned in the table above, but in some cases, even if you installed everything correctly there still might be missing packages. You can easily fix that if you have `apt` available in your OS by installing everything that is necessary. Type these commands in your terminal:

```
sudo apt update
sudo apt upgrade
sudo apt install libglm-dev libxcb-dri3-0 libxcb-present0 libpciaccess0 libpng-dev libxcb-keysyms1-dev libxcb-dri3-dev libx11-dev g++ gcc g++-multilib libmirclient-dev libwayland-dev libxrandr-dev libxcb-randr0-dev libxcb-ewmh-dev git python3 bison libx11-xcb-dev liblz4-dev libzstd-dev xorg-dev
```