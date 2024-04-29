all:
	arm-none-eabi-gcc -ggdb -Wall BLINK_WKG2.c -T linker_script.ld -o blink.elf -mcpu=cortex-m3 -mthumb -nostdlib
	arm-none-eabi-objcopy -O binary blink.elf blink.bin

flash:
	st-flash write blink.bin 0x08000000

clean:
	rm -f *.bin *.hex *.elf

