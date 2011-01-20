#include <stdio.h>

#define MIN_I 0
#define MAX_I 40

#define MIN_J 50
#define MAX_J 70

#define MIN_K 0
#define MAX_K 30

#define WIDTH 320

int main()
{
	int i, j, k;
	for (i = MIN_I; i < MAX_I; ++i) {
		for (j = MIN_J; j < MAX_J; ++j) {
			for (k = MIN_K; k < MAX_K; ++k) {
				if ((2*i + 5*j + 4*k) == WIDTH)
					printf("%d %d %d\n", i, j, k);
			}
		}
	}

	return 0;
}
