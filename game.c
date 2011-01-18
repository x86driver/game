#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#ifdef _ARM_
#define EVENT "/dev/input/event2"	/* arm */
#else
#define EVENT "/dev/input/event3"	/* pc */
#endif

int fd;

void set_event(int type, int code, int value)
{
	int ret;
	struct input_event event;
	memset(&event, 0, sizeof(event));
	event.type = type;
	event.code = code;
	event.value = value;
	ret = write(fd, &event, sizeof(struct input_event));
	if (ret < sizeof(event))
		perror("write");
//	usleep(100);
}

void send_event(int fd, int x, int y)
{
	set_event(3, 0, x);
	set_event(3, 0, y);
	set_event(1, 330, 1);
	set_event(3, 48, 959);
	set_event(3, 53, x);
	set_event(3, 54, y);
	set_event(0, 2, 0);
	set_event(0, 0, 0);
//	sleep(1);
	set_event(1, 330, 0);
	set_event(3, 48, 0);
	set_event(3, 53, x);
	set_event(3, 54, y);
	set_event(0, 2, 0);
	set_event(3, 48, 0);
	set_event(0, 2, 0);
	set_event(0, 0, 0);
}

int main(int argc, char **argv)
{
	char name[256]="Unknown";
	struct input_event event;

	if (argc < 3) {
		printf("Usage: %s count delay\n", argv[0]);
		exit(1);
	}

	fd=open(EVENT, O_RDWR);
	if (fd<0) {
		perror("open keyboard error");
		exit(1);
	} else
		printf("open %s successful\n", EVENT);


	if(ioctl(fd,EVIOCGNAME(sizeof(name)),name)<0){
		perror("get device name error");
	}

	printf ("keyboard name :%s\n",name);

	int from_x = 300;
	int from_y = 1200;

	int shift_x = 350;
	int shift_y = 350;

/*
	int ix = atoi(argv[1]);
	int iy = atoi(argv[2]);

	int x = (from_x + ix*shift_x);
	int y = (from_y + iy*shift_y);
	printf("x: %d y: %d\n", x, y);
*/

	int x, y;
	int i, j;
	int count;
    for (count = 0; count < atoi(argv[1]); ++count) {
	for (i = 0; i < 5; ++i) {
		for (j = 0; j < 5; ++j) {
			x = (from_x + j*shift_x);
			y = (from_y + i*shift_y);
			send_event(fd, x, y);
			usleep(atoi(argv[2]));
		}
	}
    }

//	send_event(fd, x, y);
//	send_event(fd, 1044, 2951);

	printf("\n");
	return 0;
}
