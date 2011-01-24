TARGET = game frame rgb cal
CPU = arm
#CPU = x86

ARMCC = arm-none-linux-gnueabi-gcc
#GCC = gcc
GCC = arm-none-linux-gnueabi-gcc

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

event.o:event.c event.h
	$(GCC) -o $@ $< -c $(CFLAGS)

recog.o:recog.c
	$(GCC) -o $@ $< -c $(CFLAGS)

image.o:image.c image.h
	$(GCC) -o $@ $< -c $(CFLAGS)

font.o:font.c font.h
	$(GCC) -o $@ $< -c $(CFLAGS)

rgb:rgb.c image.o font.o recog.o event.o
	$(GCC) -o $@ $^ $(CFLAGS)

cal:cal.c
	$(GCC) -o $@ $< -Wall -O2

clean:
	rm -rf $(TARGET) *.o

