# APPLICATION_GUIDE.md — How the Application Works

This document explains the **application layer logic** of the UART Command Console project.  
It focuses on **behavior and flow**, not low-level driver details.

---

# Application States / Modes

The application runs in a simple **interactive console mode** with two main states:

## Idle / Wait for Input

- System waits for user command from UART  
- Displays prompt

'''
>
'''

## Command Execution

- Parses received command  
- Executes corresponding GPIO or timing action  
- Returns to **Idle state** after completion

---

# Task Flow / State Machine

## High-Level Flow

'''
Start
↓
System Init (Clock + UART + GPIO + Timer)
↓
Print Welcome Banner
↓
Loop Forever
├─ Show Prompt
├─ Read UART Line
├─ Parse Command
├─ Execute Action
└─ Return to Prompt
'''

---

## State Machine (Simplified)

'''
[INIT] → [WAIT_INPUT] → [PROCESS_CMD] → [WAIT_INPUT]
'''

---

# Timing Behavior

## Blink Command

- Uses delay timer `HAL_Delay_ms` for LED toggling  
- Delay value provided by user

'''
blink <ms> <count>
'''

## UART Input

- **Blocking read** — system waits until **ENTER** is pressed  
- No background tasks or interrupts used (**polling model**)

---

# Driver Orchestration

The application coordinates multiple drivers:

| Driver | Purpose |
|------|------|
| RCC | Enables peripheral clocks |
| GPIO | Controls LED and reads pin values |
| UART | Receives commands and prints responses |
| Timer / Delay | Provides millisecond delays for blinking |

---

## Flow Example (Blink Command)

'''
UART receives string
↓
CLI parses parameters
↓
GPIO toggles LED
↓
Timer provides delay
↓
UART prints "Done"
'''

---

# Edge Cases Handled

## Invalid Command

'''
Error: Unknown command
'''

## Invalid Blink Values

- Rejects **zero or negative delay/count**

## Invalid Pin Number

- Accepts only **0–15**

## Backspace Support

- User can correct typed input

## Buffer Limit

- Prevents overflow using **maximum line length check**

## Case Insensitivity

- Commands converted to **lowercase before parsing**

---

# Limitations

- Blocking UART input (**no multitasking**)
- No interrupt-based scheduling
- Continuous blink not supported unless looped by user
- Single LED target by default

---

# Design Goal

The application is intentionally **simple and deterministic**, making it easy to:

- Understand **driver interaction**
- Demonstrate **CLI control**
- Debug **hardware behavior**
- Extend with **new commands later**