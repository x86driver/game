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

int main(void)
{
	char name[256]="Unknown";
	struct input_event event;

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

	send_event(fd, 1044, 2951);
//	ioctl(fd, EVIOCSKEYCODE, 330);
/*
	int x = 0, y = 0;
	int i = 0;
	while (1) {
	read(fd, &event, sizeof(struct input_event));

	    if (event.type == 3) {
		if (event.code == 0)
			x = event.value;
		if (event.code == 1)
			y = event.value;
		if (x && y) {
			printf("\r%d %d          ", x, y);
			fflush(NULL);
			++i;
			x = y = 0;
		}
	    }

		printf("[%d] %d\t%d\t%d\n", i++, event.type, event.code, event.value);
	}
*/
	printf("\n");
	return 0;
}
