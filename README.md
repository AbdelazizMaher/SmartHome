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

### Device Driver
- Manages hardware components such as GPIOs and LEDs.
- Provides an interface for the C++ application to interact with the hardware layer.

### C++ Application
- Implements core functionalities using design patterns for maintainability and scalability.
- Uses socket programming for efficient inter-process communication.
- Built and managed with CMake to streamline the build process.

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

## License
This project is licensed under the MIT License - see the LICENSE file for details.
