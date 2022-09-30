objs := start.o main.o

CC_PATH = ~/gcc-arm/bin/

ledc.bin:$(objs)
	$(CC_PATH)arm-linux-gnueabihf-ld -Ttext 0X87800000 -o ledc.elf $^
	$(CC_PATH)arm-linux-gnueabihf-objcopy -O binary -S ledc.elf $@
	$(CC_PATH)arm-linux-gnueabihf-objdump -D -m arm ledc.elf > ledc.dis

%.o:%.s
	$(CC_PATH)arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

%.o:%.S
	$(CC_PATH)arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

%.o:%.c
	$(CC_PATH)arm-linux-gnueabihf-gcc -Wall -nostdlib -c -o $@ $<

clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis