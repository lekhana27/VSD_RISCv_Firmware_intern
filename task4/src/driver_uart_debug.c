#include <driver_usart_debug.h>

/*********************************************************************
 * @fn      HAL_UART_Init
 *
 * @brief   Initializes USART1 peripheral and configures GPIO for TX.
 *
 * @note    - Enables clocks for GPIOD and USART1.
 *          - Configures PD5 as USART1_TX (AF push-pull, 50MHz).
 *          - Sets baud rate to 115200 @ 24MHz system clock.
 *          - Enables transmitter and USART1.
 *
 * @return  none
 */
void HAL_UART_Init(void)
{
    /* Enable clocks: GPIOD + USART1 */
    RCC->APB2PCENR |= (1 << 5) | (1 << 14); // IOPD + USART1

    /* PD5 → USART1_TX (AF push-pull, 50MHz) */
    GPIOD->CFGLR &= ~(0xF << (5*4));
    GPIOD->CFGLR |=  (0xB << (5*4));

    /* PD6 → USART1_RX (Input Floating) */
    GPIOD->CFGLR &= ~(0xF << (6*4));
    GPIOD->CFGLR |=  (0x4 << (6*4));   // input floating

    /* Baudrate: 115200 @ 24MHz */
    USART1->BRR = SYSCLK / 115200;

    /* Enable TX + RX + USART */
    USART1->CTLR1 |= (1 << 3) | (1 << 2) | (1 << 13); // TE + RE + UE

}


/*********************************************************************
 * @fn      HAL_UART_SendChar
 *
 * @brief   Sends a single character over USART1.
 *
 * @param   c - Character to send
 *
 * @return  none
 *
 * @note    Waits until TXE (transmit data register empty) flag is set.
 */
void HAL_UART_SendChar(char c)
{
    while (!(USART1->STATR & (1 << 7))); // wait TXE
    USART1->DATAR = c;
}

/*********************************************************************
 * @fn      HAL_UART_ReadChar
 *
 * @brief   Receives a single character from USART1.
 *
 * @return  char - The received character
 *
 * @note    - Waits until RXNE (Receive Data Register Not Empty) flag is set.
 *          - Blocking function (waits indefinitely until data arrives).
 */
char HAL_UART_ReadChar(void)
{
    while (!(USART1->STATR & (1 << 5))); // RXNE flag
    return (char)USART1->DATAR;
}

/*********************************************************************
 * @fn      HAL_UART_SendString
 *
 * @brief   Sends a null-terminated string over USART1.
 *
 * @param   s - Pointer to the string to transmit
 *
 * @return  none
 *
 * @note    - Sends characters one by one using HAL_UART_SendChar().
 *          - Stops transmission when '\0' is reached.
 */
void HAL_UART_SendString(const char *s)
{
    while (*s)
        HAL_UART_SendChar(*s++);
}

/*********************************************************************
 * @fn      HAL_UART_ReadLine
 *
 * @brief   Reads a line of text from USART1 until ENTER is pressed.
 *
 * @param   buf    - Buffer to store received string
 * @param   maxLen - Maximum buffer length (including null terminator)
 *
 * @return  none
 *
 * @note    - Echoes typed characters back to terminal.
 *          - Supports Backspace for editing.
 *          - Terminates input on '\r' or '\n'.
 *          - Ensures null-terminated string.
 *          - Blocking function.
 */
void HAL_UART_ReadLine(char *buf, uint8_t maxLen)
{
    uint8_t i = 0;
    char c;

    while (1)
    {
        c = HAL_UART_ReadChar();

        /* ENTER pressed */
        if (c == '\r' || c == '\n')
        {
            HAL_UART_SendString("\r\n");
            buf[i] = '\0';
            return;
        }

        /* Backspace */
        if (c == 8 || c == 127)
        {
            if (i > 0)
            {
                i--;
                HAL_UART_SendString("\b \b"); // erase char on terminal
            }
            continue;
        }

        /* Normal character */
        if (i < maxLen - 1)
        {
            buf[i++] = c;
            HAL_UART_SendChar(c); // echo
        }
    }
}


/*********************************************************************
 * @fn      HAL_UART_Print
 *
 * @brief   Sends a string and optionally a number over USART1.
 *
 * @param   str  - Null-terminated string to print
 * @param   val  - Integer value to print. Use UART_NO_NUMBER for string-only
 * @param   base - Numerical base (10 = decimal, 16 = hex)
 *
 * @return  none
 *
 * @note    - Only supports base 10 and 16.
 *          - For decimal, prints negative sign if value < 0.
 *          - Uses internal buffer to convert number to string.
 */
void HAL_UART_Print(const char *str, int32_t val, uint8_t base)
{
    /* Print string */
    while (*str)
        HAL_UART_SendChar(*str++);

    /* String-only mode */
    if (val == UART_NO_NUMBER)
        return;

    if (base != 10 && base != 16)
        return;

    /* Zero */
    if (val == 0)
    {
        HAL_UART_SendChar('0');
        return;
    }

    /* Negative decimal */
    if (val < 0 && base == 10)
    {
        HAL_UART_SendChar('-');
        val = -val;
    }

    char buf[16];
    uint8_t i = 0;

    /* Convert number to string */
    while (val)
    {
        uint8_t d = val % base;
        buf[i++] = (d < 10) ? ('0' + d) : ('A' + d - 10);
        val /= base;
    }

    /* Send number string in correct order */
    while (i--)
        HAL_UART_SendChar(buf[i]);
}