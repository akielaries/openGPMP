#include <stdint.h>

// STM32 register definitions
#define RCC_BASE       0x40021000
#define GPIOB_BASE     0x40010C00
#define USART1_BASE    0x40013800

#define RCC_APB2ENR    (*(volatile uint32_t *)(RCC_BASE + 0x18))
#define GPIOB_CRH      (*(volatile uint32_t *)(GPIOB_BASE + 0x04))
#define USART1_SR      (*(volatile uint32_t *)(USART1_BASE + 0x00))
#define USART1_DR      (*(volatile uint32_t *)(USART1_BASE + 0x04))
#define USART1_BRR     (*(volatile uint32_t *)(USART1_BASE + 0x08))
#define USART1_CR1     (*(volatile uint32_t *)(USART1_BASE + 0x0C))
#define USART1_CR2     (*(volatile uint32_t *)(USART1_BASE + 0x10))
#define USART1_CR3     (*(volatile uint32_t *)(USART1_BASE + 0x14))

// Function to initialize the UART
void setup_uart() {
    // Enable GPIOB and USART1 clocks
    RCC_APB2ENR |= 0x00000018;

    // Configure USART1 TX (PB6) and RX (PB7) pins as alternate function push-pull
    GPIOB_CRH &= 0xFFFFF00F;
    GPIOB_CRH |= 0x000008B0;

    // Configure the baud rate (115200 @ 72MHz)
    USART1_BRR = 0x1D4C; 

    // Enable USART1, transmitter, and receiver
    USART1_CR1 = 0x0000202C;
}

// Function to send a character via UART
void uart_putchar(char c) {
    // Wait until the transmit data register is empty
    while (!(USART1_SR & 0x00000080));
    
    // Send the character
    USART1_DR = c;
}

// Function to send a string via UART
void uart_puts(const char *str) {
    while (*str != '\0') {
        uart_putchar(*str);
        str++;
    }
}

int main() {
    // Initialize UART
    setup_uart();

    // Main loop
    while (1) {
        // Do some processing or tasks here
        // For example, send a message via UART
        uart_puts("UART Example: Hello, STM32!\n");
    }

    return 0;
}

