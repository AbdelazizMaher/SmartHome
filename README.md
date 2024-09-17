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
The C++ application is the core of the Smart Home project, implementing key functionalities to control devices and interact with the server. It is designed with modularity and maintainability in mind, utilizing design patterns and efficient inter-process communication.

#### Components:

- **Client Handler (`clientHandler`):**
  - Manages HTTP requests from the web interface.
  - Routes requests to appropriate modules based on the type of action required (e.g., device control, status update).
  - Implements functionality for handling GET and POST requests, parsing them, and extracting necessary data for further processing.

- **Device Manager (`deviceManager`):**
  - Manages device-specific operations and interactions with hardware.
  - Implements classes for different devices (e.g., `led`, `airConditioner`).
    - **`led.cpp`:** Controls LED hardware by interacting with the GPIO driver. Allows toggling LED states (on/off) based on received commands.
    - **`airConditioner.cpp`:** Interfaces with the dummy air conditioning unit, logging the state of the device.
  - Encapsulates device-related logic to ensure a clean separation between application logic and hardware control.

- **JSON Parsing (`parser` and `nlohmann`):**
  - Utilizes the nlohmann JSON library for parsing and handling JSON data.
  - Parses incoming requests and configurations, extracting necessary information such as device states, commands, and parameters.
  - Provides a robust interface for converting between JSON objects and internal data structures, enabling smooth data exchange.

- **Service Manager (`serviceManager`):**
  - Acts as the main orchestrator for the application's functionalities.
  - Maintains a continuous loop to process incoming requests and delegate tasks to appropriate modules.
  - Integrates with `clientHandler` and `deviceManager` to execute commands, update device states, and interact with the web interface.
  - Uses socket programming to communicate with the web server, sending and receiving data to synchronize device states and handle user commands.


---

### Yocto
The Yocto Project is used to customize the Linux image for the Smart Home project, ensuring a tailored environment for the specific hardware and software requirements.

- **Custom Recipes**: The Yocto image includes several custom recipes to incorporate essential tools and services:
  - **CMake Integration**: A recipe to add CMake for building the C++ application directly on the device if needed.
  - **Kernel Modules**: Automatically installs and loads custom kernel modules like `gpioDriver` for GPIO control on the Raspberry Pi.
  - **Startup Configuration**: Includes startup scripts and services to initialize applications like `device-controller` and `frontend`.
  - **Network Configuration**: Recipes to set up `dhcpcd` for managing network interfaces and `iptables` for network security.
  - **Web and FOTA Services**: Integrates Node.js for the FOTA server and Nginx for the web interface, facilitating interaction with the C++ application.

- **Image Specifics**: Two different image configurations (`smarthome-image-rpi-bplus.bb` and `smarthome-image-rpi4.bb`) are provided to support both the Raspberry Pi B+ and Raspberry Pi 4:
  - **Common Features**:
    - **SSH Access**: Includes Dropbear SSH server for secure shell access to the device.
    - **Debugging Tools**: `strace`, `bash`, `make`, and `cmake` for in-field debugging and building.
    - **Static IP Configuration**: Sets a static IP for the network interface (`eth0` for Pi B+ and `wlan0` for Pi 4) through `dhcpcd.conf`, ensuring reliable communication in a network.
    - **Device Control**: Integrates `device-controller`, which manages device states and synchronization with the frontend.
  - **Raspberry Pi B+ Specifics**:
    - Focuses on Ethernet (`eth0`) for network connectivity.
  - **Raspberry Pi 4 Specifics**:
    - Includes `wpa-supplicant` for Wi-Fi management (`wlan0`).
    - Adds extra firmware (`linux-firmware-bcm43455`) for additional hardware support.

By customizing the Yocto image, the Smart Home project ensures a reliable and optimized runtime environment for both the software stack and hardware interaction, enabling seamless integration of device control, network management, and user interface functionalities.


