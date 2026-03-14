# CH32V00x Bare-Metal Firmware (GPIO + RCC + UART + Delay)

This project is a bare-metal firmware framework for CH32V00x (RISC-V) MCUs. It demonstrates how to build clean, layered drivers (RCC, GPIO, UART, Delay) and use them in a simple LED blink application with UART debug prints.

---

# Project Structure

Application (main.c)

'''
Application (main.c)
│
├── driver_rcc.c / driver_rcc.h      → Clock control + SysTick delay
├── driver_gpio.c / driver_gpio.h    → GPIO configuration & control
├── driver_uart_debug.c / .h         → Debug UART (TX only)
'''

Dependency flow:

'''
RCC  →  GPIO  →  UART  →  Application
'''

---

# RCC Driver (driver_rcc)

## Purpose

Controls clock enabling for peripherals and provides delay utilities.

---

## APIs

### HAL_RCC_APB2_Enable(RCC_APB2Periph_t periph)

What it does  
Enables clock for an APB2 peripheral by setting the corresponding bit in RCC->APB2PCENR.

Logic

- ORs the peripheral bitmask into APB2PCENR  
- Safe to call multiple times  

Used in application

'''
HAL_RCC_APB2_Enable(RCC_GPIOD);
'''

Enables the clock for GPIOD before configuring LED pins.

---

### HAL_RCC_APB2_Disable(RCC_APB2Periph_t periph)

What it does  
Disables clock for an APB2 peripheral.

Logic

- Clears the peripheral bitmask in APB2PCENR

Used in application  
(Not used – but useful for power saving)

---

# Delay APIs

### HAL_Delay_Init()

What it does  
Initializes the delay system (SysTick or busy-wait based, depending on implementation).

Logic

- Prepares timing resources before delays are used

Used in application

'''
HAL_Delay_Init();
'''

Called once during startup.

---

### HAL_Delay_ms(uint32_t ms)

What it does  
Provides a blocking delay in milliseconds.

Logic

- Busy-wait loop calibrated for system clock

Used in application

'''
HAL_Delay_ms(50);
'''

Creates visible LED blinking and readable UART output.

---

### HAL_Delay_us(uint32_t us)

What it does  
Provides a blocking microsecond delay.

Logic

- Uses NOP-based loop scaled to CPU clock

Used in application  
(Not directly used)

---

# GPIO Driver (driver_gpio)

## Purpose

Configures and controls GPIO pins using direct register access.

---

## APIs

### HAL_GPIO_Init(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_Mode_t mode, GPIO_CNF_t cnf)

What it does  
Configures a GPIO pin’s mode and configuration.

Logic

- Each pin uses 4 bits in CFGLR  
- Clears existing config  
- Writes new MODE + CNF combination  

Used in application

'''
HAL_GPIO_Init(GPIOD, 4,
              GPIO_MODE_OUTPUT_50MHz,
              GPIO_CNF_PUSH_PULL);
'''

Configures PD4 as LED output.

---

### HAL_GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, uint8_t state)

What it does  
Sets a GPIO pin HIGH or LOW.

Logic

- Writes to output data register

Used in application  
(Not used – toggle used instead)

---

### HAL_GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin)

What it does  
Toggles the current output state of a pin.

Logic

- XOR operation on output data register

Used in application

'''
HAL_GPIO_TogglePin(GPIOD, 4);
'''

Toggles LED state every loop iteration.

---

### HAL_GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin)

What it does  
Reads current logic level of a GPIO pin.

Logic

- Reads input data register  
- Shifts and masks pin bit  

Used in application  
(Not used – available for buttons/sensors)

---

# UART Debug Driver (driver_uart_debug)

## Purpose

Provides a simple TX-only debug UART without printf or libc.

---

## APIs

### HAL_UART_Init()

What it does  
Initializes USART1 TX on PD5 at 115200 baud.

Logic

- Enables clocks for GPIOD, AFIO, and USART1  
- Configures PD5 as AF push-pull  
- Sets baud rate register  
- Enables transmitter and USART  

Used in application

'''
HAL_UART_Init();
'''

Initializes UART before any debug prints.

---

### HAL_UART_SendChar(char c)

What it does  
Sends a single character over UART.

Logic

- Waits for TXE flag  
- Writes character to data register  

Used internally by

- HAL_UART_Print()

---

### HAL_UART_Print(const char *str, int32_t val, uint8_t base)

What it does  
Prints a string and optionally a number (decimal or hex).

Logic

- Sends string character-by-character  
- Converts integer to ASCII manually  
- Supports negative decimal numbers  

Used in application

'''
HAL_UART_Print("LED Toggle Count: ", UART_NO_NUMBER, 0);
HAL_UART_Print("", led_count, 10);
'''

Used for banners and runtime debug logs.

---

# Application (main.c)

## Purpose

Demonstrates real hardware usage of all drivers together.

---

# Application Flow

1. System initialization  
2. UART initialization for debug  
3. Delay system initialization  
4. GPIO clock enable  
5. LED pin configuration  
6. Startup banner via UART  
7. Infinite loop  

Loop actions

- Toggle LED  
- Print counter  
- Delay  

---

# Key Application Code

'''
HAL_UART_Init();
HAL_Delay_Init();
HAL_RCC_APB2_Enable(RCC_GPIOD);

HAL_GPIO_Init(GPIOD, 4,
              GPIO_MODE_OUTPUT_50MHz,
              GPIO_CNF_PUSH_PULL);
'''

Inside loop

'''
HAL_GPIO_TogglePin(GPIOD, 4);
HAL_UART_Print("LED Toggle Count: ", UART_NO_NUMBER, 0);
HAL_UART_Print("", led_count, 10);
HAL_UART_Print("\r\n", UART_NO_NUMBER, 0);
HAL_Delay_ms(50);
'''

---

# Firmware Architecture Flow

'''
+--------------------------------------------------+

main.c
SystemInit()
HAL_UART_Init()
HAL_Delay_Init()
HAL_RCC_APB2_Enable(RCC_GPIOD)
HAL_GPIO_Init(GPIOD, 4, OUTPUT_PP)

while (1)
{
HAL_GPIO_TogglePin(GPIOD, 4)
HAL_UART_Print("LED Toggle Count: ", ...)
HAL_Delay_ms(50)
}

+------------------------+
                     |
                     v
+--------------------------------------------------+
|                 HAL / DRIVER APIs                |
+------------------------+-------------------------+
|                        |                         |
|     RCC Driver         |       GPIO Driver       |
| HAL_RCC_APB2_Enable()  |     HAL_GPIO_Init()     |
| HAL_RCC_APB2_Disable() |  HAL_GPIO_TogglePin()   |
+------------------------+-------------------------+

                     |
                     v
+--------------------------------------------------+
|               UART Debug Driver                  |
|                HAL_UART_Init()                   |
|              HAL_UART_SendChar()                 |
|               HAL_UART_Print()                   |
+------------------------+

                     |
                     v
+--------------------------------------------------+
|                 Delay / SysTick                  |
|               HAL_Delay_Init()                   |
|                HAL_Delay_ms()                    |
|                HAL_Delay_us()                    |
|                SysTick_Handler()                 |
+------------------------+

                     |
                     v
+--------------------------------------------------+
|             MCU Hardware Registers               |
|                RCC->APB2PCENR                    |
|            GPIOD->CFGLR / OUTDR                  |
|       USART1->BRR / CTLR1 / DATAR / STATR        |
|           SysTick->CTLR / CNT / CMP              |
+--------------------------------------------------+
'''

---

# Build and Flash Instructions

1. Open the PlatformIO project  
2. Connect the VSDSquadron Mini board  
3. Build the project (firmware.bin and firmware.elf generated)  
4. Upload the executable firmware file into the FLASH of MCU  
5. Connect USB 2.0 to TTL UART serial converter to the system (PC) for UART output  
6. Open a serial terminal in PuTTY to view UART logs  

---

# UART Configuration

- UART Port: UART1  
- Baud Rate: 115200  
- Data Format: **8 data bits, No parity, 1 stop bit (8N1)**  

UART output displays timestamped logs confirming correct timer operation.