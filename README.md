# Smart Home Project

This repository contains the implementation of a Smart Home system using a `MERN stack`, `C++`, and `device drivers` on a Raspberry Pi. The system is designed to control and monitor devices like LEDs, Air conitioners through a `web interface`.

## Overview

This project integrates several technologies to create a smart home environment. The web interface allows users to interact with various devices connected to a Raspberry Pi, which runs both a `web server` and a `C++ application` that controls the devices via `GPIO`.


## System Architecture

The system consists of the following main components:

1. **Web Application (MERN Stack)**
   - **Frontend:** Built with React.js, providing a user-friendly interface for interaction.
   - **Backend:** Implemented using Express.js and Node.js, handling API requests and business logic.
   - **Database:** MongoDB stores device states and user configurations.

2. **C++ Application**
   - Runs on a Raspberry Pi, interfacing directly with hardware devices through GPIO pins.
   - Communicates with the web application backend to receive commands and send device statuses.

3. **Yocto Linux Image**
   - Custom-built Linux distribution tailored for the Raspberry Pi.
   - Includes necessary kernel modules and drivers for hardware interaction.
   - Ensures a lightweight and secure operating environment for the embedded application.








