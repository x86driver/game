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

int main(void)
{
	int fd;
	char name[256]="Unknown";
	struct input_event event;
	int i;

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

	int x = 0, y = 0;
	//for (i = 0; i < 100;) {
	while (1) {
	read(fd, &event, sizeof(struct input_event));
	    if (event.type == 3) {
		if (event.code == 0)
			x = event.value;
		if (event.code == 1)
			y = event.value;
		if (x && y) {
	//		printf("[%d] %s ", i, ctime(&event.time.tv_sec));
			//printf("[%d] %d\t", i, event.type);
			//printf("%d\t", event.code);
			//printf("%d\n", event.value);
			printf("%d %d          \r", x, y);
			fflush(NULL);
			++i;
			x = y = 0;
		}
	    }
	}

//	grab_keyboard =1;
//	if(ioctl(fd,EVIOCGRAB,&grab_keyboard)){
//		perror("grab keyboard error");
//	}

//	scanf ("%d",&grab_keyboard );

	printf("\n");
	return 0;
}
