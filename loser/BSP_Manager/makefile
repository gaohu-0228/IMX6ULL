TARGET		?= led

CROSS_COMPILE := arm-linux-gnueabihf-

CC_PATH 	:= ~/gcc-arm/bin/

CC			:= $(CC_PATH)$(CROSS_COMPILE)gcc
LD			:= $(CC_PATH)$(CROSS_COMPILE)ld
OBJCOPY		:= $(CC_PATH)$(CROSS_COMPILE)objcopy
OBJDUMP		:= $(CC_PATH)$(CROSS_COMPILE)objdump

INCDIRS		:= ./ \

SRCDIRS		:= ./ \

INCLUDE		:= $(patsubst %, -I %, $(INCDIRS)) \

SFILES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.S))
CFILES := $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR := $(notdir $(SFILES))
CFILENDIR := $(notdir $(CFILES))

SOBJS		:= $(patsubst %, obj/%, $(SFILENDIR:.S=.o))
COBJS		:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS		:= $(SOBJS) $(COBJS)

VPATH		:= $(SRCDIRS)

$(TARGET).bin:$(OBJS)
	# $(LD) -Ttext 0X87800000 -o ledc.elf $^

	$(LD) -Timx6ul.lds -o ledc.elf $^
	$(OBJCOPY) -O binary -S ledc.elf $@
	$(OBJDUMP) -D -m arm ledc.elf > ledc.dis

.PHONY: clean

$(SOBJS) : obj/%.o : %.S
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

clean:
	rm -rf *.o *.bin *.elf *.dis