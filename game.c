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

#define EVENT "/dev/input/event2"	/* arm */

#define FROM_X 300
#define FROM_Y 1200
#define SHIFT_X 350
#define SHIFT_Y 350

static int event_fd;

static inline void set_event(int type, int code, int value)
{
	int ret;
	struct input_event event;
	memset(&event, 0, sizeof(event));
	event.type = type;
	event.code = code;
	event.value = value;
	ret = write(event_fd, &event, sizeof(struct input_event));
	if (ret < sizeof(event))
		perror("write");
//	usleep(100);
}

void send_event(int x, int y)
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

void send_touch(int ix, int iy)
{
	int x, y;
	x = FROM_X + ix * SHIFT_X;
	y = FROM_Y + iy * SHIFT_Y;
	send_event(x, y);
}

void event_init()
{
	event_fd = open(EVENT, O_RDWR);
	if (event_fd < 0)
		perror(EVENT);
}

void event_destroy()
{
	close(event_fd);
}

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Usage: %s x y\n", argv[0]);
		exit(1);
	}

	event_init();
	send_touch(atoi(argv[1]), atoi(argv[2]));
	printf("\n");
	return 0;
}

