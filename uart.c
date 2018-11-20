#include "uart.h"
#include "mmio.h"

#include "mailbox.h"

#define MBOX_TAG_LAST           0

void wait_cycles(unsigned int n){
    if(n) while(n--) { asm volatile("nop"); }
}

void uart_init() {
    register uint32_t reg;

    *UART0_CR = 0;                      // Turn off UART

    // Setup PL011 for the baudrate
    mailbox[0] = 9 * 4;                 // Buffer size in bytes. 9 * uint32
    mailbox[1] = MBOX_REQUEST;          // Process request
    mailbox[2] = TAG_SET_CLOCK_RATE;   // Set clock rate request
    mailbox[3] = 12;
    mailbox[4] = 8;
    mailbox[5] = 2;                     // UART Clock
    mailbox[6] = 4000000;               // 4MHz
    mailbox[7] = 0;                     // Clear turbo
    mailbox[8] = MBOX_TAG_LAST;
    mailbox_call(MBOX_CH_PROP);

    reg = *GPFSEL1;

    reg &= ~((7 << 12) | (7 << 15));    // Clear GPIO14 and GPIO15
    reg |= (4 << 12) | (4 << 15);       // Alternate function 0 for GPIO14 and GPIO15 (UART TX and RX)

    *GPFSEL1 = reg;                     // Set the function register
    *GPPUD = 0;                         // Enable Pin 14 and 15
    wait_cycles(150);
    *GPPUDCLK0 = (1 << 14) | (1 << 15); //Enable clock for pull-ups / pull-downs on Pin 14 and 15
    wait_cycles(150);
    *GPPUDCLK0 = 0;                     // Flush the GPIO setup

    *UART0_ICR = 0x7FF;                 // Clear all UART0 interrupts
    *UART0_IBRD = 2;                    // Set a 115200 baudrate
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0b11 << 5;            // Set 8 Bit word length
    *UART0_CR = 0x301;                  // Enable Tx, Rx and FIFO
}

void uart_putchar(char c) {
    do {
        asm volatile("NOP");
    } while(*UART0_FR & 0x20);          // Check if the transmit FIFO is full

    *UART0_DR = c;
}

char uart_getchar() {
    char ret;

    do {
        asm volatile("NOP");
    } while (*UART0_FR & 0x10);         // Check if the receive FIFO is empty

    ret = (char)(*UART0_DR);

    return ret == '\r' ? '\n' : ret;
}

void uart_puts(char *str) {
    while(*str) {
        if(*str== '\n') 
            uart_putchar('\r');
        uart_putchar(*str++);
    }
}