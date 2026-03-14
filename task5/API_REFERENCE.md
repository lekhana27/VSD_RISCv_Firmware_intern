# Driver Public API Documentation

# GPIO Driver

## 1. HAL_GPIO_Init

'''
void HAL_GPIO_Init(GPIO_RegDef_t *GPIOx, uint8_t pin, GPIO_Mode_t mode, GPIO_CNF_t cnf);
'''

### Purpose
Initializes the specified GPIO pin with the given mode and configuration.

### Parameters

- **GPIOx** – Pointer to the GPIO peripheral (GPIOA, GPIOC, GPIOD, etc.)
- **pin** – Pin number (0–15)
- **mode** – Pin mode (Input, Output, Analog, etc.)
- **cnf** – Pin configuration (Push-Pull, Open-Drain, Pull-Up, Pull-Down, etc.)

### Return Values
None

### Constraints / Notes

- RCC clock for the port must be enabled first.
- Only valid pin numbers (0–15).

### Example

'''
HAL_GPIO_Init(GPIOD, 4, GPIO_MODE_OUTPUT_50MHz, GPIO_CNF_PUSH_PULL);
'''

---

## 2. HAL_GPIO_WritePin

'''
void HAL_GPIO_WritePin(GPIO_RegDef_t *GPIOx, uint8_t pin, uint8_t state);
'''

### Purpose
Sets GPIO pin HIGH or LOW.

### Parameters

- **GPIOx** – Pointer to the GPIO peripheral (GPIOA, GPIOC, GPIOD, etc.)
- **pin** – Pin number to write (0–7)
- **state** – Pin state: `0 = LOW`, `1 = HIGH`

### Return Values
None

### Notes

- Pin must be configured as output.

### Example

'''
HAL_GPIO_WritePin(GPIOD, 4, 1);
'''

---

## 3. HAL_GPIO_TogglePin

'''
void HAL_GPIO_TogglePin(GPIO_RegDef_t *GPIOx, uint8_t pin);
'''

### Purpose
Toggles the output state of the specified GPIO pin.

### Parameters

- **GPIOx** – Pointer to the GPIO peripheral (GPIOA, GPIOC, GPIOD, etc.)
- **pin** – Pin number to toggle (0–7)

### Return Values
None

### Example

'''
HAL_GPIO_TogglePin(GPIOD, 4);
'''

---

## 4. HAL_GPIO_ReadPin

'''
uint8_t HAL_GPIO_ReadPin(GPIO_RegDef_t *GPIOx, uint8_t pin);
'''

### Purpose
Reads the current logic level of the specified GPIO pin.

### Parameters

- **GPIOx** – Pointer to the GPIO peripheral (GPIOA, GPIOC, GPIOD, etc.)
- **pin** – Pin number to read (0–7)

### Return

- **uint8_t** – Pin state: `0 = LOW`, `1 = HIGH`

### Example

'''
HAL_GPIO_ReadPin(GPIOA, 2);
'''

---

# UART Driver

## 1. HAL_UART_Init

'''
void HAL_UART_Init(void);
'''

### Purpose
Initializes USART1 peripheral and configures TX/RX pins.

### Parameters
None

### Return
None

### Notes

- Enables clocks for GPIOD and USART1
- Configures **PD5 as USART1_TX (AF push-pull, 50MHz)**
- Sets baud rate to **115200 @ 24MHz system clock**
- Enables transmitter and USART1

### Example

'''
HAL_UART_Init();
'''

---

## 2. HAL_UART_SendChar

'''
void HAL_UART_SendChar(char c);
'''

### Purpose
Sends a single character over USART1.

### Parameters

- **c** – Character to send

### Return
None

### Notes

- Waits until **TXE (transmit data register empty)** flag is set.

### Example

'''
HAL_UART_SendChar('A');
'''

---

## 3. HAL_UART_SendString

'''
void HAL_UART_SendString(const char *s);
'''

### Purpose
Sends null-terminated string over UART.

### Parameters

- **s** – Pointer to the string to transmit

### Return
None

### Notes

- Sends characters one by one using `HAL_UART_SendChar()`
- Stops transmission when `'\0'` is reached

### Example

'''
HAL_UART_SendString("Hello\\r\\n");
'''

---

## 4. HAL_UART_ReadChar

'''
char HAL_UART_ReadChar(void);
'''

### Purpose
Receives a single character from USART1.

### Parameters
None

### Return

- **char** – The received character

### Notes

- Waits until **RXNE (Receive Data Register Not Empty)** flag is set
- Blocking function (waits indefinitely until data arrives)

### Example

'''
val = HAL_UART_ReadChar();
'''

---

## 5. HAL_UART_ReadLine

'''
void HAL_UART_ReadLine(char *buf, uint8_t maxLen);
'''

### Purpose
Reads a line of text from USART1 until ENTER is pressed.

### Parameters

- **buf** – Buffer to store received string
- **maxLen** – Maximum buffer length (including null terminator)

### Return
None

### Notes

- Echoes typed characters back to terminal
- Supports **Backspace** for editing
- Terminates input on `'\r'` or `'\n'`
- Ensures **null-terminated string**
- Blocking function

---

## 6. HAL_UART_Print

'''
void HAL_UART_Print(const char *str, int32_t val, uint8_t base);
'''

### Purpose
Sends a string and optionally a number over USART1.

### Parameters

- **str** – Null-terminated string to print
- **val** – Integer value to print. Use `UART_NO_NUMBER` for string-only
- **base** – Numerical base (`10 = decimal`, `16 = hex`)

### Return
None

### Notes

- Only supports **base 10 and 16**
- For decimal, prints negative sign if value < 0
- Uses internal buffer to convert number to string

### Example

'''
HAL_UART_Print("Frequency is 1kHz", UART_NO_NUMBER, 0);
'''

---

# RCC / Delay Driver

## 1. HAL_RCC_APB2_Enable

'''
void HAL_RCC_APB2_Enable(RCC_APB2Periph_t periph);
'''

### Purpose
Enables the clock for the specified APB2 peripheral.

### Parameters

- **periph** – Peripheral bitmask to enable (RCC_APB2Periph_t)

### Return
None

### Example

'''
HAL_RCC_APB2_Enable(RCC_APB2Periph_GPIOA);
'''

---

## 2. HAL_RCC_APB2_Disable

'''
void HAL_RCC_APB2_Disable(RCC_APB2Periph_t periph);
'''

### Purpose
Disables the clock for the specified APB2 peripheral.

### Parameters

- **periph** – Peripheral bitmask to disable (RCC_APB2Periph_t)

### Return
None

### Example

'''
HAL_RCC_APB2_Disable(RCC_APB2Periph_GPIOA);
'''

---

## 3. HAL_Delay_Init

'''
void HAL_Delay_Init(void);
'''

### Purpose
Initializes the SysTick timer for **1ms tick generation**.

### Parameters
None

### Return
None

### Notes

- Sets up SysTick without enabling interrupts
- For interrupt based delays, ensure the **NVIC exception is enabled**

### Example

'''
HAL_Delay_Init();
'''

---

## 4. HAL_Delay_ms

'''
void HAL_Delay_ms(uint32_t ms);
'''

### Purpose
Provides a blocking delay for a specified number of milliseconds.

### Parameters

- **ms** – Number of milliseconds to delay

### Return
None

### Notes

- Uses a simple **busy-wait loop**
- Accuracy depends on CPU clock

### Example

'''
HAL_Delay_ms(500);
'''

---

## 5. HAL_Delay_us

'''
void HAL_Delay_us(uint32_t us);
'''

### Purpose
Provides a blocking delay for a specified number of microseconds.

### Parameters

- **us** – Number of microseconds to delay

### Return
None

### Notes

- Uses a **busy-wait loop based on CPU cycles**
- Approximate delay

### Example

'''
HAL_Delay_us(50000);
'''

---

# CLI Driver

## CLI_Process

'''
void CLI_Process(char *cmd);
'''

### Purpose
Parses and executes user command string.

### Supported Commands

'''
help
led on
led off
blink
read
'''

### Parameter

- **cmd** – Null-terminated command string entered by user

### Return
None

### Notes

- Case-insensitive
- Blocking during **blink**

### Example

'''
CLI_Process("led on");
'''