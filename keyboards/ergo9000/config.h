#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

// Split KB configuration
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_PIN_SWAP // Swap the TX and RX on 'master' and 'slave' halves of the keyboard.
#define SERIAL_USART_TX_PIN GP2     // USART TX pin
#define SERIAL_USART_RX_PIN GP3     // USART RX pin

#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SCL_PIN
#define I2C1_SCL_PIN GP13
#undef I2C1_SDA_PIN
#define I2C1_SDA_PIN GP12

#define OLED_DISPLAY_ADDRESS 0x3c
