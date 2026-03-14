#ifndef CLI_H
#define CLI_H

#include "driver_usart_debug.h"
#include "driver_gpio.h"
#include "driver_rcc.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/* LED CONFIG */
#define LED_PORT GPIOD
#define LED_PIN 4

// Command Line Interface
void CLI_Process(char *cmd);

#endif