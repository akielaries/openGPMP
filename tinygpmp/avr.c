#include "avr.h"
#include <avr/io.h>
#include <util/delay.h>
#include <util/setbaud.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>

int uart_putchar(char c, FILE *stream) {
    // if character is newline, also send carriage return
    if (c == '\n') {
        uart_putchar('\r', stream);
    }
    // wait until the UART data register is empty
    loop_until_bit_is_set(UCSR0A, UDRE0);
    // send character to UART data register
    UDR0 = c;
    return 0;
}

// create a stream for stdout (printf)
FILE uart_stdout = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);


void setup_uart() {
#ifdef __AVR_ATmega2560__
    // disable USART during baud rate setting
    UCSR0B = 0;

#elif __AVR_ATmega328__
    // in case UART was put into power-reduction mode ...
    PRR &= ~ _BV(PRUSART0);

#endif

    // BAUD is defined via command line: -DBAUD=115200
    // config UART baud rate based on setbaud.h?
    //#include <util/setbaud.h>

    // UART baud HIGH BYTE
    UBRR0H = UBRRH_VALUE;
    // UART baud LOW BYTE
    UBRR0L = UBRRL_VALUE;

#if USE_2X
    // if 2x is defined set the U2X0 bit in the UART status register A
    UCSR0A |= _BV(U2X0);
#else
    // default to clearing the U2x0 bit
    UCSR0A &= ~_BV(U2X0);
#endif

#ifdef __AVR_ATmega2560__
    // set UART frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);  // 8N1

    // enable UART TX and RX (transmit x recieve)
    UCSR0B = _BV(TXEN0) | _BV(RXEN0);  // Enable transmitter and receiver

#elif __AVR_ATmega328__
    // UART Control and Status Register B:
    // - Enable transmitter only
    UCSR0B = _BV(TXEN0);

    // 8N1
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);

#endif

    // create redirect for stdout to UART stream
    stdout = &uart_stdout;
}

// Matrix addition function
void matrix_addition(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

void print_matrix(int matrix[2][2]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {


    // Set Pin 7 (Arduino Mega Pin 13) as an output
    DDRB |= (1 << PB7);

    // Initialize UART
    setup_uart();

    // Print a welcome message
    printf("UART Example: Hello, AVR!\n");

    // Main loop
    while (1) {
        PORTB ^= (1 << PB7);
        _delay_ms(100);      // Wait for 500 milliseconds


        printf("We're looping... wait 1000ms\n");
        _delay_ms(100);

    // Define matrices
    int matrixA[2][2] = {{1, 2}, {3, 4}};
    int matrixB[2][2] = {{5, 6}, {7, 8}};
    int resultMatrix[2][2];

    // Perform matrix addition
    matrix_addition(matrixA, matrixB, resultMatrix);

    // Print matrices and result
    printf("Matrix A:\n");
    print_matrix(matrixA);

    printf("Matrix B:\n");
    print_matrix(matrixB);

    printf("Result Matrix:\n");
    print_matrix(resultMatrix);

        _delay_ms(7500);

    }

    return 0;

}

