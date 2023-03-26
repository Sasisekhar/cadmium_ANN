| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- |

# A simple implementation of ANN on RT-CADMIUM

This example instantiates a simple ANN model (taken from the helloworld example from TFLM for ESP32).
Uses the ESP32 supporting variant of Cadmium V2.
The ANN predicts the sine value of a given input. Good example to showcase an implementation of TFLM on a microcontroller platform. 
***THIS PROJECT CURRENTLY DOESN'T SUPPORT SIMULATION.*** Support for is still under developement.

## How to use example
Takes a numerical (float) value from the serial port (stdin) and predicts the sine value of the same.

### Installation of ESP-IDF
Follow the steps given [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) for the complete installation guide. Installation as a VS Code Extension is recomendded, steps for which are provided [here](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md).

### Setting up the dependencies
- Create a folder names `components` in the current directory (`cadmium_ANN/`).
- Clone the [Cadmium_V2 fork for ESP32](https://github.com/Sasisekhar/RT-CADMIUM_ESP32) into the components folder and rename it to cadmium_v2 (be sure to run `git submodule update --init --recursive` to fetch all the submodules).
- Download and extract the [boost library](https://www.boost.org/users/download/) into the components folder.
- Clone the [tflite-lib](https://github.com/Sasisekhar/tflite-lib) and [esp-nn](https://github.com/espressif/esp-nn.git) libraries.

### Building and deploying the code
- For the VS Code extension:
- - Open the parent directory in VS Code
- - Plug in the ESP32 and ensure the correct port shows up on the bottom panel
- - Click the 🔥icon (Build, Flash and monitor)

## Example folder contents

The project **cadmium_ANN** contains one main source file in C++ language [main_rt_model.cpp](main/main_rt_model.cpp). The file is located in folder [main](main). FUrther includes are present in the [include](main/include/) folder.

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── components
|   ├── boost_x_yy_z
|   ├── cadmium_v2
|   ├── esp-nn
|   └── tflite-lib
├── main
|   ├── include
|   |   ├── ANN_TFLM.hpp
|   |   ├── ANNatomic.hpp
|   |   ├── ANNsystem.hpp
|   |   ├── model.cc
|   |   └── model.h
│   ├── CMakeLists.txt
│   └── main_rt_modep.cpp
└── README.md                  This is the file you are currently reading
```
Additionally, the project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.