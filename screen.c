#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "screen.h"

#define FRAMEBUFFER "/dev/graphics/fb0"

static int screen_fd;
static struct fb_var_screeninfo screen;
static unsigned char *data;

unsigned short *screen_init()
{
	screen_fd = open(FRAMEBUFFER, O_RDONLY);
	if (screen_fd == -1)
		perror(FRAMEBUFFER);
	ioctl(screen_fd, FBIOGET_VSCREENINFO, &screen);
	data = (unsigned char *)mmap(NULL, screen.xres*screen.yres*(screen.bits_per_pixel/8),
		PROT_READ, MAP_SHARED, screen_fd, 0);
	if (data == MAP_FAILED)
		perror("mmap");
	return (unsigned short*)malloc(screen.xres*screen.yres*(screen.bits_per_pixel/8));
}

void screen_destroy(unsigned short *rgb565)
{
	munmap(data, screen.xres*screen.yres);
	close(screen_fd);
	free(rgb565);
}

void screen_capture(unsigned short *rgb565)
{
	memcpy(rgb565, data, screen.xres*screen.yres*(screen.bits_per_pixel/8));
}

/*
int main()
{
	screen_init();
	unsigned char *rgb565 = screen_init();
	screen_capture(rgb565);
	FILE *fp = fopen("test.raw", "wb");
	if (!fp)
		perror("test.raw");
	fwrite(rgb565, screen.xres*screen.yres*(screen.bits_per_pixel/8), 1, fp);
	fclose(fp);
	screen_destroy(rgb565);

	return 0;
}
*/
