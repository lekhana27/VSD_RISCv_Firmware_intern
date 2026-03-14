# Embedded Firmware Basics

This document provides background concepts required for the internship.

---

## What is Embedded Firmware?

Embedded firmware is low-level software that runs directly on a **microcontroller (MCU)** or **System-on-Chip (SoC)**.

It controls hardware peripherals such as:

- GPIO
- Timers
- Serial interfaces (UART, SPI, I2C)
- Sensors and external devices

Firmware acts as a bridge between:

- **Hardware** (registers, peripherals)
- **Higher-level application logic**

---

## Types of Firmware Development

There are several ways to develop firmware depending on the resources provided by the microcontroller manufacturer.

### 1. Hardware Abstraction Layer (HAL)

HAL provides **high-level APIs** for configuring microcontroller peripherals.

**Characteristics**

- **Level of abstraction:** High  
- **Ease of use:** Easier for beginners  
- **Code verbosity:** More lines of code for simple tasks  
- **Portability:** Excellent across devices  
- **Performance:** Slightly slower due to abstraction layers

---

### 2. Low Layer (LL)

LL libraries provide a **lighter and faster alternative to HAL**, allowing more direct hardware access.

**Characteristics**

- **Level of abstraction:** Medium  
- **Ease of use:** Moderate  
- **Code verbosity:** Less verbose than HAL  
- **Portability:** Good, but less than HAL  
- **Performance:** Faster than HAL

---

### 3. Bare-Metal C Programming

Bare-metal programming interacts **directly with hardware registers using C**.

**Characteristics**

- **Level of abstraction:** Low  
- **Ease of use:** Challenging for beginners  
- **Code verbosity:** Direct and compact  
- **Portability:** Limited (hardware-specific)  
- **Performance:** Very high

---

### 4. Assembly Language

Assembly interacts with hardware **at the lowest possible level**, directly controlling the processor instructions.

**Characteristics**

- **Level of abstraction:** Lowest  
- **Ease of use:** Very difficult  
- **Code verbosity:** Can be verbose for complex tasks  
- **Portability:** Very limited  
- **Performance:** Highest possible

---

## What is a Firmware Library or API?

A **firmware library** is a collection of reusable functions that provide a clean interface to hardware.

Example:

```c
gpio_write(LED_PIN, 1);