CC := arm-linux-gnueabihf-gcc
LD := arm-linux-gnueabihf-ld
OBJCOPY := arm-linux-gnueabihf-objcopy
OBJDUMP := arm-linux-gnueabihf-objdump

BDIR = ./bsp
IDIR = ./imx6ull
ODIR = ./obj
PDIR = ./project

CLKDIR = $(BDIR)/clk
DELAYDIR = $(BDIR)/delay
LEDDIR = $(BDIR)/led
BEEPDIR = $(BDIR)/beep
KEYDIR = $(BDIR)/key
ALL_DIR = -I$(IDIR) -I$(PDIR) -I$(CLKDIR) -I$(DELAYDIR) -I$(LEDDIR) -I$(BEEPDIR) -I$(KEYDIR)

CCFLAGS = -Wall -nostdlib -c -O2 $(ALL_DIR)

########## object files #############
LIBAPI_OBJ =$(ODIR)/start.o \
			$(ODIR)/main.o \
			$(ODIR)/bsp_clk.o \
			$(ODIR)/bsp_delay.o \
			$(ODIR)/bsp_led.o \
			$(ODIR)/bsp_beep.o \
			$(ODIR)/bsp_key.o
###############################################
bsp.bin : $(LIBAPI_OBJ)
	$(LD) -Timx6ull.lds -o bsp.elf $^
	@echo ------ make bsp.elf OK. ------
	$(OBJCOPY) -O binary -S bsp.elf $@
	@echo ------ make $@ OK. ------
	$(OBJDUMP) -D -m arm bsp.elf > bsp.dis
	@echo ------ make bsp.dis OK. ------

clean:
	rm -rf *.elf *.bin *.dis $(ODIR)/*.o
###############################################
$(ODIR)/%.o : $(PDIR)/%.s
	$(CC) $(CCFLAGS) -o $@ $<

$(ODIR)/%.o : $(PDIR)/%.c
	$(CC) $(CCFLAGS) -o $@ $<

$(ODIR)/%.o : $(CLKDIR)/%.c
	$(CC) $(CCFLAGS) -o $@ $<

$(ODIR)/%.o : $(DELAYDIR)/%.c
	$(CC) $(CCFLAGS) -o $@ $<

$(ODIR)/%.o : $(LEDDIR)/%.c
	$(CC) $(CCFLAGS) -o $@ $<

$(ODIR)/%.o : $(BEEPDIR)/%.c
	$(CC) $(CCFLAGS) -o $@ $<