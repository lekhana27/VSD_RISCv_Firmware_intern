# CHANGELOG.md

All notable changes to this project will be documented in this file.  
This project follows a simple **semantic versioning style**.

---

# v1.0.0 – Initial Release

## Added

- Implemented **GPIO driver**
- Implemented **RCC driver** for peripheral clock control
- Added **UART debug driver** for serial communication
- Created **CLI (Command Line Interface)** module

### Added Commands

'''
help
led on
led off
blink <ms> <count>
read <pin>
'''

---

## Integrated

- **Timer / Delay module** for millisecond delays
- **UART line input handling** with basic editing
- **LED control via GPIO**
- **Command parsing and validation**

---

## Features

- **Case-insensitive command parsing**
- **Error handling for invalid input**
- **Structured folder organization**
- **Modular driver architecture**

---

## Known Limitations

- Blocking UART input (**no multitasking**)
- No interrupt-driven scheduling
- Single LED target by default

---

## Future Improvements (Planned)

- Interrupt-based **UART reception**
- **Non-blocking scheduler**
- **Multiple GPIO control**
- **PWM command support**
- **Command history feature**