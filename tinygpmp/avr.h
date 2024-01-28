#ifdef __AVR_H__
#define __AVR_H__

#ifdef __AVR_ATmega328__
// #define UART_BAUD_RATE 38400
#define UART_BAUD_RATE 115200
#define I2C_CLOCK 100000
#define I2C_PRESCALER 1
#define I2C_BIT_RATE_REG ((F_CPU / I2C_CLOCK) - 16) / (2 * I2C_PRESCALER)
#endif

#ifdef __AVR_ATmega2560__
#define UART_BAUD_RATE 115200
#define I2C_CLOCK 100000
#define I2C_PRESCALER 1
#define I2C_BIT_RATE_REG ((F_CPU / I2C_CLOCK) - 16) / (2 * I2C_PRESCALER)
#endif

/**
 * @brief Puts a UART character to console
 */
int uart_putchar(char c, FILE *stream);

/**
 * @brief Initialize UART
 */
void setup_uart();

#endif
