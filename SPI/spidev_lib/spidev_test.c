#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>

#define PCKT_SIZE 8

/*	FUNCTIONS PROTOTYPES	*/
static void exit_with(const char*);
static void send_message(int);
static void receive_message(int);
static void create_pipe();
/*	END OF PROTOTYPES	*/



/*	STATIC VARIABLES	*/
static const char *pipepath = "/var/run/spi_pipe";
static const char *device = "/dev/spidev0.0";
static uint8_t mode = 0;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay = 0;
/*	END OF STATIC VARIABLES	*/



/*	MAIN	*/
int main(int argc, char *argv[])
{
	int status = 0;
	int file_desc;

	file_desc = open(device, O_RDWR);
	if (file_desc < 0)
	{
		exit_with("can't open device");
	}

	/*	set spi mode	*/
	status = ioctl(file_desc, SPI_IOC_WR_MODE, &mode);
	if (status == -1)
	{
		exit_with("can't set spi mode");
	}

	status = ioctl(file_desc, SPI_IOC_RD_MODE, &mode);
	if (status == -1)
	{
		exit_with("can't get spi mode");
	}

	/*	set bits per word	*/
	status = ioctl(file_desc, SPI_IOC_WR_BITS_PER_WORD, &bits);
	if (status == -1)
	{
		exit_with("can't set bits per word");
	}

	status = ioctl(file_desc, SPI_IOC_RD_BITS_PER_WORD, &bits);
	if (status == -1)
	{
		exit_with("can't get bits per word");
	}

	/*	set max speed hz	*/
	status = ioctl(file_desc, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
	if (status == -1)
	{
		exit_with("can't set max speed hz");
	}

	status = ioctl(file_desc, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
	if (status == -1)
	{
		exit_with("can't get max speed hz");
	}

	/*	print spi status	*/
	printf("spi mode: %d\n", mode);
	printf("bits per word: %d\n", bits);
	printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

	send_message(file_desc);
	receive_message(file_desc);
	close(file_desc);

	return status;
}
/*	END OF MAIN	*/



/*	FUNCTIONS IMPLEMENTATION	*/
static void exit_with(const char *error_message)
{
	perror(error_message);
	exit(EXIT_FAILURE);
}


static void create_pipe()
{
    mode_t mode = 0666;
    int status = mkfifo(pipepath, mode);
    if(status == EEXIST)
    {
        fprintf(stderr, "Pipe at %s already exists, go on\n", pipepath);
    }
}


static void send_message(int file_desc)
{
	int status;
	uint8_t trans[PCKT_SIZE] = {0xAA, 0x21, 0x32, 0x12, 0x23, 0x42, 0x19, 0xEA};
	uint8_t rec[PCKT_SIZE] = {1, 0, 0, 0, 0, 0, 0, 0};

	struct spi_ioc_transfer msg = 
	{
		.tx_buf = (unsigned long)trans,
		.rx_buf = (unsigned long)rec,
		.len = PCKT_SIZE,
		.delay_usecs = delay,
		.speed_hz = speed,
		.bits_per_word = bits,
	};

	/*
	if (write(file_desc, trans, PCKT_SIZE) != PCKT_SIZE)
	{
		exit_with("can't write to SPI device");
	}
	*/	
	status = ioctl(file_desc, SPI_IOC_MESSAGE(1), &msg);
	if (status < 1)
	{
		exit_with("can't send spi message");
	}
	
	/*
	unsigned i;
	for(i = 0; i < PCKT_SIZE; i++)
	{
		printf("%.2X ", rec[i]);
	}
	puts("");
	*/
}

static void receive_message(int fd)
{
	uint8_t rec[PCKT_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0};
	int status;
	FILE *pipe_device;	

    struct spi_ioc_transfer msg =
    {
		.tx_buf = 0,
        .rx_buf = (unsigned long)rec,
        .len = PCKT_SIZE,
        .delay_usecs = delay,
        .speed_hz = speed,
        .bits_per_word = bits,
    };

	status = ioctl(fd, SPI_IOC_MESSAGE(1), &msg);
    if (status < 1)
    {
        exit_with("can't send spi message");
    }

	/*	create pipe	*/
	create_pipe();	
	pipe_device = fopen(pipepath, "w");
	if(pipe_device == NULL)
	{
		exit_with("error opening pipe");
	}

	/*	read values from spi_device
	if(read(fd, rec, PCKT_SIZE) != PCKT_SIZE)
	{
		exit_with("can't read from spi device");
	}
	*/

	/*	throw values to pipe	*/
	unsigned i;
    for(i = 0; i < PCKT_SIZE; i++)
    {
		sleep(0);
        fprintf(pipe_device, "%.2X ", rec[i]);
		fprintf(stdout, "%.2X ", rec[i]);
    }
		
	fclose(pipe_device);
}

/*	END OF IMPLEMENTATION	*/
