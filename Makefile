TARGET = game frame rgb
CPU = arm
#CPU = x86
ARMCC = arm-none-linux-gnueabi-gcc

ifeq ($(CPU),arm)
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -static -D_ARM_
else
CC = gcc
CFLAGS = -D_PC_
endif

CFLAGS += -Wall -O2

all:$(TARGET)

game:game.c Makefile
	$(CC) -o $@ $< $(CFLAGS)

event:event.c
	$(CC) -o $@ $< $(CFLAGS)

frame:frame.c
	$(ARMCC) -o $@ $< $(CFLAGS)

rgb:rgb.c
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -rf $(TARGET)

