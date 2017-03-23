#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include <linux/stat.h>

#define FIFO_FILE	"/var/run/spi_pipe"

int main(void)
{
	FILE *fp;
	char readbuf[80];
	int n;

	/* Create the FIFO if it does not exist */
	//umask(0);
	//mknod(FIFO_FILE, S_IFIFO|0666, 0);

	while(1)
	{
		fp = fopen(FIFO_FILE, "r");
		fscanf(fp, "%d", &n);
		printf("Received: %d\n", n);
		fclose(fp);
	}

	return 0;
}

