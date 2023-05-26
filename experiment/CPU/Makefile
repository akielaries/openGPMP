asm:
	nasm -f elf64 test_func.asm -o test_func.o 

cc:
	gcc -no-pie -z noexecstack msg.c test_func.o -o main

clean:
	rm *.o main

