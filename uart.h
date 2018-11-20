#pragma once

#include "mmio.h"

#define UART0_BASE (0x00201000)

#define UART0_DR   (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x00) // UART 0 Data Register
#define UART0_FR   (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x18) // UART 0 Flag Register
#define UART0_IBRD (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x24) // UART 0 Integer Baud rate divisor
#define UART0_FBRD (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x28) // UART 0 Fractional Baud rate divisor
#define UART0_LCRH (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x24) // UART 0 Line Control Register
#define UART0_CR   (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x30) // UART 0 Control Register
#define UART0_IMSC (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x38) // UART 0 Interupt Mask Set Clear Register
#define UART0_ICR  (volatile uint32_t*)(MMIO_BASE + UART0_BASE + 0x44) // UART 0 Interupt Clear register

void uart_init();
char uart_getchar();
void uart_putchar(char c);
void uart_puts(char *str);