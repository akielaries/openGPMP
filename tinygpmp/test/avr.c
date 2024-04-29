#include "avr.h"
#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
#include <util/setbaud.h>

#ifdef __AVR_ATmega2560__

// red for signaing wait LED 11
#define PIN_SLP PB5
// yellow LED 12
#define PIN_GEN PB6
// red LED pin 13
#define PIN_MLT PB7

#elif __AVR_ATmega328P__

// yellow LED pin 8
#define PIN_GEN PB0
// red LED pin 9
#define PIN_MLT PB1
// red for signaing wait LED 11
#define PIN_SLP PB2

#endif

#ifdef __AVR_ATmega2560__

// if N is assigned to a value too high then we get some undefined behavior
#define N 24

#elif __AVR_ATmega328P__

#define N 16

#endif

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

#elif __AVR_ATmega328P__
    // in case UART was put into power-reduction mode ...
    PRR &= ~_BV(PRUSART0);

#endif

    // BAUD is defined via command line: -DBAUD=115200
    // config UART baud rate based on setbaud.h?
    // #include <util/setbaud.h>

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
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); // 8N1

    // enable UART TX and RX (transmit x recieve)
    UCSR0B = _BV(TXEN0) | _BV(RXEN0); // Enable transmitter and receiver

#elif __AVR_ATmega328P__
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

void std_mtx_add(const double *A, const double *B, double *C) {
    // MTX A AND B MUST BE SAME SIZE
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // perform matrix addition
            C[i * N + j] = A[i * N + j] + B[i * N + j];
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

    // set data direction on designated pins making them outputs
    DDRB |= (1 << PIN_GEN);
    DDRB |= (1 << PIN_MLT);
    DDRB |= (1 << PIN_SLP);

    // blink 30 times
    for (volatile uint8_t i = 0; i < 30; i++) {

        // toggle state of pin
        PORTB ^= (1 << PIN_GEN);
        PORTB ^= (1 << PIN_MLT);

        _delay_ms(100);
    }

    // Initialize UART
    setup_uart();

    double A[N * N];
    double B[N * N];
    double C[N * N];

    // Main loop
    while (1) {
        printf("Generating matrices A and B\n");

        // toggle yellow pin on while matrices are getting generated
        PORTB ^= (1 << PIN_GEN);

        for (int i = 0; i < N * N; ++i) {
            A[i] = (double)rand() / RAND_MAX;
            B[i] = (double)rand() / RAND_MAX;
        }

        // toggle yellow as off
        PORTB ^= (1 << PIN_GEN);

        printf("Multiplying matrices A and B\n");

        // toggle red as on while matrices are being multiplied
        PORTB ^= (1 << PIN_MLT);

        // Perform matrix addition
        std_mtx_add(A, B, C);

        // toggle red as off
        PORTB ^= (1 << PIN_MLT);

        // reached end of code, pause for a bit
        PORTB ^= (1 << PIN_SLP);

        _delay_ms(3000);

        PORTB ^= (1 << PIN_SLP);
    }

    return 0;
}
