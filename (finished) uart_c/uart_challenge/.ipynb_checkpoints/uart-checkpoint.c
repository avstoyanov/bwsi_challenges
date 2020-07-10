
// Hardware Imports
#include "inc/hw_memmap.h" // Peripheral Base Addresses
#include "inc/lm3s6965.h" // Peripheral Bit Masks and Registers

// Component Header
#include "uart.h"

// UART Channels - You can use these names, but don't uncomment them!
// #define UART0 0
// #define UART1 1
// #define UART2 2

// Reading modes - You can use these names, but don't uncomment them!
// #define NONBLOCKING 0
// #define BLOCKING 1

void uart_init(uint8_t uart)
{
  // Implement me!!
    UART2_CTL_R &= ~(UART_CTL_UARTEN); // 0x0000.0001
    UART2_IBRD_R &= ~(UART_IBRD_DIVINT_M); UART2_FBRD_R &= ~(UART_FBRD_DIVFRAC_M);
    UART2_IBRD_R |= 0x0a; UART2_FBRD_R |= 0x36;
    UART2_LCRH_R |= UART_LCRH_WLEN_8; // 0x0000.0060
    UART2_LCRH_R &= ~(UART_LCRH_PEN); // 0x0000.0002
    UART2_CTL_R |= UART_CTL_UARTEN; // 0x0000.0001
    
}

uint8_t uart_read(uint8_t uart, int blocking, int *read)
{
  // Implement me!!
    // UART2_LCRH_R |= UART_LCRH_FEN; // 0000.0010
    if (blocking){
        while (UART2_FR_R & UART_FR_RXFE); // 0x00000010
        *read = 1;
        return UART2_DR_R & UART_DR_DATA_M; // 0x000000FF
    }
    if (UART2_FR_R & UART_FR_RXFF) { // 0x00000040
        *read = 1;
        return UART2_DR_R & UART_DR_DATA_M; // 0x000000FF
    } else {
        *read = 0;
        return 0;
    }
}

void uart_write(uint8_t uart, uint32_t data)
{
  // Implement me!!
    while (UART2_FR_R & UART_FR_BUSY); // 0x00000008
    UART2_DR_R = (data & UART_DR_DATA_M); // 0x000000FF
}

void uart_write_str(uint8_t uart, char *str) {
  while (*str) { // Loop until null terminator
    uart_write(uart, (uint32_t)*str++);
  }
}

inline void nl(uint8_t uart) {
  uart_write(uart, '\n');
}

void uart_write_hex(uint8_t uart, uint32_t data) {
  uint32_t nibble;

  for (int shift = 28; shift >= 0; shift -=4) {
    nibble = (data >> shift) & 0xF;
    if (nibble > 9) {
      nibble += 0x37;
    } else {
      nibble += 0x30;
    }
    uart_write(uart, nibble);
  }
}


void UART0_IRQHandler(void)
{
}
    