TARGET = game
CPU = arm
#CPU = x86

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

clean:
	rm -rf $(TARGET)

