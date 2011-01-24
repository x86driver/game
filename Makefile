TARGET = game frame rgb cal
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

recog.o:recog.c
	$(GCC) -o $@ $< -Wall -c -g

image.o:image.c image.h
	$(GCC) -o $@ $< -Wall -c -g

font.o:font.c font.h
	$(GCC) -o $@ $< -Wall -c -g

rgb:rgb.c image.o font.o recog.o
	$(GCC) -o $@ $^ -Wall -g

cal:cal.c
	$(GCC) -o $@ $< -Wall -O2

clean:
	rm -rf $(TARGET) *.o

