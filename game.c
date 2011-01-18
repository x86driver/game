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

#ifdef _ARM_
#define EVENT "/dev/input/event2"	/* arm */
#else
#define EVENT "/dev/input/event3"	/* pc */
#endif

static inline void set_event(int type, int code, int value, struct input_event *event)
{
	event->type = type;
	event->code = code;
	event->value = value;
}

void send_event(int fd, int x, int y)
{
	struct input_event event[17];
	struct input_event *ev = &event[0];
	set_event(3, 0, x, ev++);
	set_event(3, 1, y, ev++);
	set_event(1, 300, 1, ev++);
	set_event(3, 48, 35, ev++);
	set_event(3, 53, x, ev++);
	set_event(3, 54, y, ev++);
	set_event(0, 2, 0, ev++);
	set_event(0, 0, 0, ev++);
	set_event(1, 300, 0, ev++);
	set_event(3, 48, 0, ev++);
	set_event(3, 53, x, ev++);
	set_event(3, 54, y, ev++);
	set_event(0, 2, 0, ev++);
	set_event(0, 0, 0, ev++);
	set_event(3, 48, 0, ev++);
	set_event(0, 2, 0, ev++);
	set_event(0, 0, 0, ev);
	write(fd, &event, sizeof(event));
}

int main(void)
{
	int fd;
	char name[256]="Unknown";
	struct input_event event;

	fd=open(EVENT, 0);
	if (fd<0) {
		perror("open keyboard error");
		exit(1);
	} else
		printf("open %s successful\n", EVENT);


	if(ioctl(fd,EVIOCGNAME(sizeof(name)),name)<0){
		perror("get device name error");
	}

	printf ("keyboard name :%s\n",name);

//	send_event(fd, 1100, 3000);
	ioctl(fd, EVIOCSKEYCODE, 330);
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
