# Smart Home Project

## Overview
The Smart Home project integrates web development, device drivers, C++ applications, and Yocto to create a comprehensive system that interacts with hardware and provides a user-friendly interface.

## Project Flow
### Device Registration and Control:
- Users can register devices through the webpage. Each device starts in an "off" state by default.
- Users can toggle the state of each device, turning it "on" or "off" with a click.
- State changes are synchronized with MongoDB, ensuring real-time updates in the database and informing the C++ application to adjust the hardware state accordingly.

### Firmware Over-The-Air (FOTA) Updates:
- Users can upload a new version of the C++ application through the webpage.
- The system automatically replaces the existing application on the Raspberry Pi with the uploaded version, ensuring that the latest software is always running.

## Components
### Web Development
The `mernAPP` directory contains the web development portion of the Smart Home project, built using the MERN stack.

#### Components:
- **Background.js**: 
  - Renders the background image for the application's user interface, enhancing the visual presentation.
- **DeviceForm.js**:
  - Provides a form for users to register new devices into the system.
  - Fetches existing devices from the Express.js server and displays them in the interface.
  - Communicates with the Express.js server to add devices and with the C++ application on the Raspberry Pi to synchronize the device list.
- **DeviceTag.js**:
  - Displays a tag for each registered device, showing its identifier, name, and current status.
  - Allows users to toggle the state of devices, sending a request to the Express.js server to update the status.
- **Fota.js**:
  - Handles firmware uploads for the C++ application.
  - Reads the selected firmware file and sends it as binary data to the FOTA server on the Raspberry Pi.
- **Header.js**:
  - Displays the application header with the title "Smart Home" and an accompanying image.

#### Interaction with Servers:
- The ReactJS application uses `Axios` to interact with the backend servers:
  - **Express.js Server**: 
    - Manages device data, including fetching the list of devices and updating their states.
    - Facilitates device registration and state toggling.
  - **FOTA Server**:
    - Receives firmware updates as binary data, allowing the C++ application on the Raspberry Pi to be updated seamlessly.

The web interface thus serves as a central hub for managing devices and updating the system firmware, making it an integral part of the Smart Home project.

---

### LinuxModules
A custom GPIO driver, `gpioDriver`, which interacts with `GPIO pin 21` on the Raspberry Pi. The driver provides a simple interface for controlling the pin state `(high or low)` through a character device and provides an interface for the `C++ application` to interact with the hardware layer

#### File Operations

- **Open (`driver_open`):** Invoked when the device file is opened. Sets up the device or checks initial conditions.
- **Write (`driver_write`):** Handles data written to the device file. Accepts a character ('0' or '1') to set the GPIO pin state.
- **Read (`driver_read`):** Returns an error as this driver is set up for output-only.
- **Release (`driver_release`):** Cleans up any resources when the device file is closed.

#### Makefile
The provided Makefile is structured to build the `gpioDriver` module:
- Compiles `gpio.c` and `gpio-file-operations.c` into `gpioDriver.o`.
- Uses `KERNEL_SRC` for kernel source directory reference.
- Includes `modules_install` and `clean` targets for installing and cleaning up the module.

#### File Overview

- **gpio.c:** Contains the main initialization and exit functions for the GPIO driver.
- **gpio-file-operations.h:** Declares file operation functions for the driver.
- **gpio-file-operations.c:** Implements the file operations (`open`, `write`, `read`, `release`).

#### Usage

Once the module is loaded, it creates a device file (e.g., `/dev/led-home`). Writing '0' or '1' to this file will set GPIO pin 21 to low or high, respectively.

---

### C++ Application
- Implements core functionalities using design patterns for maintainability and scalability.
- Uses socket programming for efficient inter-process communication.
- Built and managed with CMake to streamline the build process.

---

### Yocto
- Customizes the Linux image to fit the project's needs.
- Includes various recipes:
  - **CMake Recipe**: Integrates CMake into the Yocto build process.
  - **Module Recipe**: Compiles and integrates kernel modules.
  - **Devtool**: Assists in development and debugging.
  - **Startup**: Configures startup scripts and services.
  - **WiFi and Static IP**: Configures network settings for connectivity.
  - **Frontend and Nginx**: Deploys the web interface and configures the Nginx server.

## Getting Started
1. **Clone the Repository**: Instructions to clone the project repository.
2. **Building the Project**: Steps to build each component using Yocto and CMake.
3. **Running the Application**: How to start the system and access the web interface.

## Project Structure
- `/cppApp`: Contains the C++ application source code and build system.
- `/deviceDrivers`: Includes the code for device drivers managing hardware.
- `/mernAPP`: Houses the MERN stack components, including React frontend and Node.js backend.
- `/yoctoImage`: Yocto project configuration files and recipes for building the system image.

