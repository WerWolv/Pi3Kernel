#include "uart.h"
#include <stdio.h>

void kernel_main() {
    uart_init();
    uart_puts("UART running!\n");

    while(1) {

        char c = uart_getchar();

        char nr[10];

        sprintf(nr, "%d", c);

        if(c == '\n') {
            uart_putchar('\r');
            uart_putchar('\n');
        } else if(c == 'a')
            uart_puts("\b \b");
        else uart_puts(nr);
    }
}