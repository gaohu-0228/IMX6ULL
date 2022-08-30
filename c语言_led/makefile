objs := start.o main.o

led.bin : $(objs)
	arm-linux-gnueabihf-ld -Timx6ull.lds $^ -o led.elf
	arm-linux-gnueabihf-objcopy -O binary -S -g led.elf $@
	arm-linux-gnueabihf-objdump -D led.elf > led.dis

%.o : %.s
	arm-linux-gnueabihf-gcc -Wall -nostdlib -O2 -c $< -o $@
%.o : %.c
	arm-linux-gnueabihf-gcc -Wall -nostdlib -O2 -c $< -o $@

clean:
	rm -rf *.o led.bin led.elf led.dis