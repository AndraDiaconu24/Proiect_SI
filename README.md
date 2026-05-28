# Distance Warning System with ATmega328p

This is a "parking sensor" style project based on an ATmega328p microcontroller (Arduino Nano). The system uses an ultrasonic sensor to measure the distance to the nearest object and provides visual and auditory feedback to the user depending on their proximity.

The project is developed **without using the standard Arduino libraries (no Arduino framework)**, interacting directly with the microcontroller registers through a custom hardware abstraction layer (HAL). This approach offers maximum control and efficiency.

## Functionality

The system constantly measures the distance and reacts as follows:
- **Over 15 cm:** The area is clear. The green LED is on, the buzzer is off, and the LCD displays the message `"Liber"` (Clear).
- **Between 10 cm and 15 cm:** Warning zone. The red LED turns on and the buzzer emits a low-frequency sound (slow beep). The LCD displays `"ATENTIE!"` (Warning).
- **Between 5 cm and 10 cm:** Danger zone. The red LED turns on and the buzzer emits a high-frequency sound (fast beep). The LCD displays `"PERICOL!!!"` (Danger).
- **Under 5 cm:** Imminent stop. The red LED is on, the buzzer emits a continuous sound, and the LCD displays `"STOP!!!!"`.

The exact distance measured by the sensor is constantly displayed on the first line of the LCD screen (e.g., `Dist: 12 cm`).

## Hardware Components

To replicate this project, you need the following components:
- **1x** Arduino Nano development board (ATmega328p)
- **1x** Ultrasonic Sensor (e.g., HC-SR04)
- **1x** I2C compatible LCD screen (e.g., 16x2)
- **1x** Active/Passive Buzzer
- **1x** Red LED
- **1x** Green LED
- **2x** Resistors (220Ω - 330Ω) for the LEDs
- Jumper wires and a Breadboard

### Default Pin Connections
*The pin configuration can be modified in the `src/main.c` file or drivers.*
- **Red LED:** Pin D3
- **Green LED:** Pin D4
- **Buzzer, Ultrasonic Sensor, LCD:** According to the configuration files in `drivers/`

## Project Structure

The project is modularly organized, separating the application logic from the hardware drivers:

```text
├── bsp/            # Board specific definitions (nano.h)
├── drivers/        # Hardware Abstraction Layer (HAL)
│   ├── buzzer/     # Buzzer control
│   ├── gpio/       # I/O pins initialization and control
│   ├── i2c/        # I2C communication (for LCD)
│   ├── lcd/        # LCD display control
│   ├── pwm/        # PWM signal generation
│   └── ultrasonic/ # Ultrasonic sensor reading
├── src/            # Main application source code
│   └── main.c      # Distance sensor operating logic
├── utils/          # Utility functions (e.g., delay.h)
└── Makefile        # Build and flash configuration
```

## Build & Flash

The project uses a robust `Makefile` to automate the build process.

### Prerequisites
- `avr-gcc` toolchain
- `avrdude` utility for flashing the code to the board
- `make`

### Available Commands

| Command | Description |
|---------|-------------|
| `make all BOARD=nano` | Compiles the entire project for Arduino Nano. |
| `make flash` | Flashes the resulting firmware to the connected board. |
| `make clean` | Deletes the generated build files (`.o`, `.elf`, `.hex`). |

## Contributors
- Diaconu Andra-Gabriela
- Tecuța Elena-Simona
