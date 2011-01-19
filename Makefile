TARGET = game frame rgb
CPU = arm
#CPU = x86

ARMCC = arm-none-linux-gnueabi-gcc
GCC = gcc

ifeq ($(CPU),arm)
CC = arm-none-linux-gnueabi-gcc
CFLAGS = -static -D_ARM_
else
CC = gcc
CFLAGS = -D_PC_
endif

CFLAGS += -Wall -O2

all:$(TARGET)

game:game.c
	$(CC) -o $@ $< $(CFLAGS)

event:event.c
	$(CC) -o $@ $< $(CFLAGS)

frame:frame.c
	$(ARMCC) -o $@ $< $(CFLAGS)

rgb:rgb.c
	$(GCC) -o $@ $< -Wall -g

clean:
	rm -rf $(TARGET)

