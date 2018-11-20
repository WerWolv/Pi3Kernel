#pragma once

#include "mmio.h"

extern volatile uint32_t mailbox[36];

#define MBOX_REQUEST    0

#define MBOX_CH_POWER   0   // Power management
#define MBOX_CH_FB      1   // Framebuffer
#define MBOX_CH_VUART   2   // Virtual UART
#define MBOX_CH_VCHIQ   3   // VideoCore interface
#define MBOX_CH_LEDS    4   // LEDS
#define MBOX_CH_BTNS    5   // Buttons
#define MBOX_CH_TOUCH   6   // Touch screen
#define MBOX_CH_COUNT   7   //
#define MBOX_CH_PROP    8   // Property Tags (ARM -> VC)

#define VIDEOCORE_MBOX  (MMIO_BASE + 0x0000B880)
#define MBOX_READ       ((volatile uint32_t*)(VIDEOCORE_MBOX + 0x00))
#define MBOX_POLL       ((volatile uint32_t*)(VIDEOCORE_MBOX + 0x10))
#define MBOX_SENDER     ((volatile uint32_t*)(VIDEOCORE_MBOX + 0x14))
#define MBOX_STATUS     ((volatile uint32_t*)(VIDEOCORE_MBOX + 0x18))
#define MBOX_CONFIG     ((volatile uint32_t*)(VIDEOCORE_MBOX + 0x1C))
#define MBOX_WRITE      ((volatile uint32_t*)(VIDEOCORE_MBOX + 0x20))

#define MBOX_RESPONSE   0x80000000 
#define MBOX_FULL       0x80000000
#define MBOX_EMPTY      0x40000000

enum {
    /* Videocore */
    TAG_GET_FIRMWARE_VERSION = 0x1,

    /* Hardware */
    TAG_GET_BOARD_MODEL = 0x10001,
    TAG_GET_BOARD_REVISION,
    TAG_GET_BOARD_MAC_ADDRESS,
    TAG_GET_BOARD_SERIAL,
    TAG_GET_ARM_MEMORY,
    TAG_GET_VC_MEMORY,
    TAG_GET_CLOCKS,

    /* Config */
    TAG_GET_COMMAND_LINE = 0x50001,

    /* Shared resource management */
    TAG_GET_DMA_CHANNELS = 0x60001,

    /* Power */
    TAG_GET_POWER_STATE = 0x20001,
    TAG_GET_TIMING,
    TAG_SET_POWER_STATE = 0x28001,

    /* Clocks */
    TAG_GET_CLOCK_STATE = 0x30001,
    TAG_SET_CLOCK_STATE = 0x38001,
    TAG_GET_CLOCK_RATE = 0x30002,
    TAG_SET_CLOCK_RATE = 0x38002,
    TAG_GET_MAX_CLOCK_RATE = 0x30004,
    TAG_GET_MIN_CLOCK_RATE = 0x30007,
    TAG_GET_TURBO = 0x30009,
    TAG_SET_TURBO = 0x38009,

    /* Voltage */
    TAG_GET_VOLTAGE = 0x30003,
    TAG_SET_VOLTAGE = 0x38003,
    TAG_GET_MAX_VOLTAGE = 0x30005,
    TAG_GET_MIN_VOLTAGE = 0x30008,
    TAG_GET_TEMPERATURE = 0x30006,
    TAG_GET_MAX_TEMPERATURE = 0x3000A,
    TAG_ALLOCATE_MEMORY = 0x3000C,
    TAG_LOCK_MEMORY = 0x3000D,
    TAG_UNLOCK_MEMORY = 0x3000E,
    TAG_RELEASE_MEMORY = 0x3000F,
    TAG_EXECUTE_CODE = 0x30010,
    TAG_GET_DISPMANX_MEM_HANDLE = 0x30014,
    TAG_GET_EDID_BLOCK = 0x30020,

    /* Framebuffer */
    TAG_ALLOCATE_BUFFER = 0x40001,
    TAG_RELEASE_BUFFER = 0x48001,
    TAG_BLANK_SCREEN = 0x40002,
    TAG_GET_PHYSICAL_SIZE = 0x40003,
    TAG_TEST_PHYSICAL_SIZE = 0x44003,
    TAG_SET_PHYSICAL_SIZE = 0x48003,
    TAG_GET_VIRTUAL_SIZE = 0x40004,
    TAG_TEST_VIRTUAL_SIZE = 0x44004,
    TAG_SET_VIRTUAL_SIZE = 0x48004,
    TAG_GET_DEPTH = 0x40005,
    TAG_TEST_DEPTH = 0x44005,
    TAG_SET_DEPTH = 0x48005,
    TAG_GET_PIXEL_ORDER = 0x40006,
    TAG_TEST_PIXEL_ORDER = 0x44006,
    TAG_SET_PIXEL_ORDER = 0x48006,
    TAG_GET_ALPHA_MODE = 0x40007,
    TAG_TEST_ALPHA_MODE = 0x44007,
    TAG_SET_ALPHA_MODE = 0x48007,
    TAG_GET_PITCH = 0x40008,
    TAG_GET_VIRTUAL_OFFSET = 0x40009,
    TAG_TEST_VIRTUAL_OFFSET = 0x44009,
    TAG_SET_VIRTUAL_OFFSET = 0x48009,
    TAG_GET_OVERSCAN = 0x4000A,
    TAG_TEST_OVERSCAN = 0x4400A,
    TAG_SET_OVERSCAN = 0x4800A,
    TAG_GET_PALETTE = 0x4000B,
    TAG_TEST_PALETTE = 0x4400B,
    TAG_SET_PALETTE = 0x4800B,
    TAG_SET_CURSOR_INFO = 0x8011,
    TAG_SET_CURSOR_STATE = 0x8010

} rpi_mailbox_tag_t;

int mailbox_call(uint8_t channel);