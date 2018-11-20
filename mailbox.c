#include "mailbox.h"

volatile uint32_t __attribute__((aligned(16))) mailbox[36];

int mailbox_call(uint8_t channel) {
    unsigned int message = (((unsigned int)((unsigned long)&mailbox)&~0xF) | (channel&0xF));

    do {
        asm volatile("NOP");
    } while (*MBOX_STATUS & MBOX_FULL); // Wait till the mailbox got emptied by the VideoCore

    *MBOX_WRITE = message;

    while(1) {
        do {
            asm volatile("nop");
        } while(*MBOX_STATUS & MBOX_EMPTY); // Wait till the mailbox got filled with a response

        if(message == *MBOX_READ)
            return mailbox[1] == MBOX_RESPONSE;
    }

    return 0;
}