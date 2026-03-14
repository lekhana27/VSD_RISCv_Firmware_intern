# UART Command Console + GPIO Control Panel

## Project Summary

A **bare-metal firmware project** that provides a **UART Command Line Interface (CLI)** to control GPIO pins. Users can send text commands from a serial terminal to turn an LED on/off, blink it with delay and count, and read pin states. The project focuses on simple driver architecture and direct hardware control without an RTOS.

## Target Hardware

VSDSquadron Mini

## Supported Drivers

GPIO – Pin init, read, write, toggle  
UART – Serial TX/RX for CLI  
Timer / Delay – ms/us blocking delays  

## Folder Structure

'''
task4/
│
├─ submission/
│ ├─ include/
│ │ ├─ driver_gpio.h
│ │ ├─ driver_rcc.h
│ │ ├─ driver_usart_debug.h
│ │ └─ cli.h
│ │
│ ├─ src/
│ │ ├─ main.c
│ │ ├─ driver_gpio.c
│ │ ├─ driver_rcc.c
│ │ ├─ driver_usart_debug.c
│ │ └─ cli.c
│
├─ Readme.md
└─ Evidence.md
│
├─ images (.jpeg/.png)
└─ video (.mp4)
'''

## Quick Start (Build + Flash)

Open the **PlatformIO project**  
Connect the **VSDSquadron Mini board**  
Build the project (firmware.bin and firmware.elf generated)  
Connect **USB 2.0 to TTL UART serial converter** to the system (PC) for UART output  
Open a serial terminal in **PuTTY** to view UART logs