#include <stdint.h>

// This is the symbol defined in the linker script.
extern unsigned long _end_of_ram;

// We'll implement main a bit further down but we need the symbol for
// the initial program counter / start address.
void main();

// This is our interrupt vector table that goes in the dedicated section.
__attribute__ ((section(".interrupt_vectors"), used))
void (* const interrupt_vectors[])(void) = {
    // The first 32bit value is actually the initial stack pointer.
    // We have to cast it to a function pointer since the rest of the array
    // would all be function pointers to interrupt handlers.
    (void (*)(void))((unsigned long)&_end_of_ram),

    // The second 32bit value is the initial program counter aka. the
    // function you want to run first.
    main
};

void wait() {
    // Do some NOPs for a while to pass some time.
    for (unsigned int i = 0; i < 2000000; ++i) __asm__ volatile ("nop");
}

void main() {
    // Enable port C clock gate.
    // 7.3.7 APB2 peripheral clock enable register (RCC_APB2ENR)
    // Address: 0x18
    // Reset value: 0x0000 0000

    //So we want to set bit 4 of this register to 1 to enable port C, but where is 
    //this register in memory? We're only being told that it is at address 0x18 
    //within the memory for RCC configuration. So let's go back to section 3.3 to 
    //consult the memory map. There, "Reset and clock control RCC" is listed 
    //at 0x4002 1000. Adding 0x18 we get 0x4002 1018.
    *((volatile unsigned int *)0x40021018) |= (1 << 4);

    // Configure GPIO C pin 13 as output.
    // 9.2.2 Port configuration register high (GPIOx_CRH) (x=A..G)
    // Address offset: 0x04
    // Reset value: 0x4444 4444
    // The bits for pin 13 are 20-23. Note the reset value 0x4444 4444: We'll 
    // have to leave the other bits with those values to avoid changing the 
    // config of any other pins. The section specifies an address offset of 0x04, 
    // but what is the base for this? Our trusty memory map in section 3.3 
    // points us at 0x4001 1000 for GPIO Port C, so we get 0x4001 1004.
    // The bits for pin 14 are 24-27
    *((volatile unsigned int *)0x40011004) = ((0x44444444 // The reset value
        & ~(0xfU << 20)  // Clear out the bits for pin 13
        & ~(0xfU << 24)  // Clear out the bits for pin 14
        & ~(0xfU << 28)) // Clear out the bits for pin 15
        |  (0x3U << 20)  // Set both MODE bits for pin 13
        |  (0x3U << 24)  // Set both MODE bits for pin 14
        |  (0x3U << 28)); // Set both MODE bits for pin 15

    while (1) {
        // Set the output bit.
        // 9.2.5 Port bit set/reset register (GPIOx_BSRR) (x=A..G)
        // Address offset: 0x10
        // Reset value: 0x0000 0000
        //Finally, we need to toggle the pin between high and low to blink the LED. 
        //We can use the trick described in section 9.1.2 to atomically set/reset 
        //only the pin we're interested in. The BSRR register for that purpose is 
        //at offset 0x10 (16) as described in section 9.2.5. We need to set bit 13 
        //to make PC13 high and bit 29 (pin + 0x10) to make it low respectively.
        *((volatile unsigned int *)0x40011010) = (1U << 13);
        *((volatile unsigned int *)0x40011010) = (1U << 14);
        *((volatile unsigned int *)0x40011010) = (1U << 15);
        wait();

        // RESET
        *((volatile unsigned int *)0x40011010) = (1U << 29);
        *((volatile unsigned int *)0x40011010) = (1U << 30);
        *((volatile unsigned int *)0x40011010) = (1U << 31);
        wait();
    }
}

