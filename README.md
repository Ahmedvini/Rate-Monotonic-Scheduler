# Rate Monotonic Scheduler (Atmega32)

This project implements the **Rate Monotonic Scheduling (RMS)** algorithm using the Atmega32 microcontroller, developed during my internship at **AMIT** and supported by **Orange Digital Center (ODC)**. RMS is a fixed-priority algorithm used for scheduling tasks in real-time systems. The project demonstrates real-time scheduling techniques, embedded C programming, and microcontroller interfacing.

## Features
- Fixed-priority task scheduling based on frequency (RMS)
- Deadline handling for real-time tasks
- Microcontroller interfacing and embedded system design

## Requirements

### Hardware
- Atmega32 Microcontroller
- LEDs for task indication
- Breadboard, jumpers, and power supply

### Software
- **Atmel Studio** for development.
- **USBasp** or **AVR programmer** for flashing.

## Setup

1. Open the project in Atmel Studio and compile the source code (`RateMonotonic.c`).

2. Use an AVR programmer to flash the `RateMonotonic.hex` file to the Atmega32 microcontroller.

3. Connect the LEDs according to the circuit described in `LED_interface.h` and `DIO_interface.h`.

4. Power the circuit to observe task scheduling. The LEDs will indicate the execution of tasks based on their priorities.

## Proteus Simulation

For those using Proteus for simulation, refer to the image below to see the circuit connection used in the project. The Proteus schematic demonstrates the connection of LEDs, Atmega32, and other components.

![Proteus Connection Diagram](Rate%20Monotonic%20Scheduler/proteus/RateMonotonic.png)

## Future Enhancements
- Implement additional scheduling algorithms (e.g., Earliest Deadline First).
- Add task monitoring and performance metrics.
- Introduce user interaction through LCD or keypad.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments
Thanks to **AMIT** and **Orange Digital Center (ODC)** for their support during my internship, which provided me with hands-on experience in real-time systems and embedded development.
