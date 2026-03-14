# PWM Driver (TIM1) – Bare-Metal Library

## Library Implemented
driver_pwm_tim

A lightweight bare-metal PWM driver that configures TIM1 Channel 1 to generate a PWM signal using direct register access.  
Designed for low-level MCU control without HAL/RTOS overhead.

---

# API List

## HAL_PWM_Init(uint32_t freq_hz, uint16_t resolution)

Description:  
Initializes TIM1 for PWM output.

- Enables TIM1 clock  
- Calculates Prescaler (PSC) & Auto-Reload (ARR)  
- Configures PWM Mode 1 on Channel 1  
- Enables preload registers  
- Enables Main Output (MOE)  
- Sets initial duty cycle to 0%

---

## HAL_PWM_SetDuty(uint16_t duty)

Description:  
Updates PWM duty cycle by writing to CCR register.

- Clamps value to ARR range  
- Takes effect immediately or on next update event  

---

## HAL_PWM_Start(void)

Description:  
Starts timer counter → PWM signal begins.

---

## HAL_PWM_Stop(void)

Description:  
Stops timer counter → PWM signal halts.

---

# Formulas Used

### Timer Clock (24MHz)

'''
Timer_Clock = SystemCoreClock
'''

### Auto-Reload Register (ARR)

'''
ARR = resolution − 1
'''

### Prescaler (PSC)

'''
PSC = (Timer_Clock / (freq_hz × resolution)) − 1
'''

### PWM Frequency

'''
PWM_Freq = Timer_Clock / ((PSC + 1) × (ARR + 1))
'''

### Duty Cycle %

'''
Duty% = (CCR / (ARR + 1)) × 100
'''

---

# Registers Used

| Register | Purpose |
|--------|--------|
| RCC->APB2PCENR | Enable TIM1 clock |
| TIM1->PSC | Prescaler value |
| TIM1->ATRLR | Auto-Reload Register (Period) |
| TIM1->CNT | Counter reset |
| TIM1->CHCTLR1 | PWM Mode & Preload config |
| TIM1->CCER | Channel output enable |
| TIM1->CH1CVR | Duty cycle compare value (CCR1) |
| TIM1->BDTR | Main Output Enable (MOE) |
| TIM1->CTLR1 | Counter enable (CEN), ARPE |

---

# Flow Chart

'''
+--------------------------------------------------+

main.c
SystemInit()
HAL_PWM_Init(freq, resolution)
HAL_PWM_SetDuty(value)
HAL_PWM_Start()

while (1)
{
HAL_PWM_SetDuty(duty++) // change brightness
HAL_Delay_ms(10)
}

+------------------------+
                     |
                     v
+--------------------------------------------------+
|                 HAL / DRIVER APIs                |
+------------------------+-------------------------+
|                        |                         |

PWM Driver               RCC Driver
HAL_PWM_Init()           Enable TIM1 Clock
HAL_PWM_SetDuty()
HAL_PWM_Start()
HAL_PWM_Stop()

+------------------------+-------------------------+
                     |
                     v
+--------------------------------------------------+

PWM Driver

• Calculate PSC (Prescaler)
• Calculate ARR (Auto Reload)
• Configure PWM Mode 1
• Enable CCR Preload
• Enable Channel Output
• Enable Main Output (MOE)
• Start Counter (CEN)

+------------------------+
                     |
                     v
+--------------------------------------------------+

Timer / Clock Path

SystemCoreClock
↓
Timer Clock (APB2)
↓
Prescaler Division (PSC)
↓
Auto Reload Counter (ARR)

+------------------------+
                     |
                     v
+--------------------------------------------------+

MCU Hardware Registers

RCC->APB2PCENR (TIM1 Clock Enable)
TIM1->PSC (Prescaler)
TIM1->ATRLR (Period / ARR)
TIM1->CNT (Counter Reset)
TIM1->CHCTLR1 (PWM Mode + Preload)
TIM1->CCER (Channel Enable)
TIM1->CH1CVR (Duty Cycle / CCR1)
TIM1->BDTR (MOE – Main Output)
TIM1->CTLR1 (CEN – Counter Enable)

+------------------------+
                     |
                     v
+--------------------------------------------------+

PWM Output Pin

Alternate Function Push-Pull GPIO  
Generates PWM Waveform  
Used for LED Dim / Motor / Buzzer

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