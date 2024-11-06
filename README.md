# MicroSat-Connect

## Project Overview
MicroSat-Connect is an embedded system project that interfaces an ARM-based microcontroller with a RockBLOCK+ satellite modem for remote monitoring and control. The project enables Short Burst Data (SBD) communication over satellite, allowing the microcontroller to control relays and monitor system status via AT commands. The system also communicates with an external system (System X) to trigger alerts.

## Hardware Configuration
- **Microcontroller**: ARM-based STM32F401CC.
- **Satellite Modem**: RockBLOCK+ for satellite communication.
- **Communication Interface**: Serial (TX, RX, Ground).
- **Relay Control**: Managed by a GPIO pin on the microcontroller.
- **System X Interface**: Monitors an active low signal using another GPIO pin.

## Requirements
- **Communication**: Uses AT commands in binary mode to send/receive SBD messages with the satellite network.
- **Relay Control**: 
  - Receives an SBD with "TURNON" to close the relay.
  - Receives an SBD with "TURNOFF" to open the relay.
- **System X Monitoring**: 
  - Detects a low signal and sends an "ALERT" message via SBD.
- **Operating System**: FreeRTOS (alternatively, provided a version without an OS, using NVIC for nested interrupts).
- **Development Environment**: Eclipse IDE.
- **Code Standards**: Implemented MISRA C guidelines using Cppcheck 2.12.0, with exceptions in cases necessary for functionality.


## Project Structure
- **MCAL Layer**: Low-level drivers for microcontroller peripherals.
  - Modules: MRCC, MGPIO, MSYSTK, MEXIT, MTIM3, MNVIC, MUART.
- **HAL Layer**: High-level driver for RockBLOCK modem communication.
- **Application Layer**: Main application logic, including relay and System X monitoring.

  ![image](https://github.com/user-attachments/assets/081a22f8-01ea-4ff0-856f-573e2db286c0)


## Software Design
The software architecture is divided into modular layers, with FreeRTOS handling task management, semaphores, and queues:
1. **Satellite Modem Driver**: Manages AT command handling and SBD communication.
2. **UART Driver**: Handles serial communication with interrupt-driven transmission and reception.
3. **Application Logic**: Processes SBD messages, controls relay based on message content, and monitors System X.

  ![image](https://github.com/user-attachments/assets/cbe23bb9-45ff-4401-98f0-062a0d587645)


## Build and Run
1. **IDE**: Eclipse IDE is recommended for building and running the project.
2. **Operating System**: FreeRTOS for task scheduling; alternatively, NVIC interrupts for non-RTOS version.

## Code Quality
- **MISRA C Compliance**: Cppcheck 2.12.0 was used to enforce MISRA C rules. Some exceptions were made for necessary functionality (e.g., unused variable for register read in `MSTK_program.c` at line 192).
