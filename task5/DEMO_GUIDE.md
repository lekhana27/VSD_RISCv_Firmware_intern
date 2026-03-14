# Build and Flash Instructions

## Steps

1. Open the **PlatformIO project**
2. Connect the **VSDSquadron Mini board**
3. Build the project
4. Upload the firmware using **USB 2.0 to TTL UART serial converter**
5. Open a serial terminal in **PuTTY** to view UART logs

---

# UART Settings

| Parameter | Value |
|----------|------|
| Baudrate | 115200 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Flow Control | None |
| Port | COMx |

---

# PuTTY Configuration
 
   ![task44](ima/task44.png)

---

# Commands to Type

After opening serial monitor, press **Enter once** and run:

'''
help
led on
led off
blink 500 5
read 4
'''

---

# Expected Output (UART)

'''
   ![task43](ima/task43.png)

Commands:
help
led on
led off
blink <ms> <count>
read <pin>

LED ON
LED OFF
Blinking...
Done
Pin value: 1
'''

---

# Hardware Observation

- **led on** → LED turns ON  
- **led off** → LED turns OFF  
- **blink 500 5** → LED blinks 5 times with **500 ms delay**  
- **read 4** → Pin value printed on terminal  

UART text appears instantly **without glitches**.