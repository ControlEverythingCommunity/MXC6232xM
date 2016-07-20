// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MXC6232xM
// This code is designed to work with the MXC6232xM_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MXC6232xM_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, MXC6232xM I2C address is 0x10(16)
	ioctl(file, I2C_SLAVE, 0x10);

	// Sets up the accelerometer to begin reading.
	char config[1] = {0x00};
	write(file, config, 1);
	sleep(1);

	// Read data from register(0x00)
	// Status, X msb, X lsb, Y msb, Y lsb
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[5] = {0};
	if(read(file, data, 5) != 5)
	{
		printf("Error : Input/Output error \n");
		exit(1);
	}
	else
	{
		// Convert the data
		int xAccl = ((data[1] & 0x0F) * 256 + data[2]);
		if (xAccl > 2047)
		{
			xAccl = xAccl - 4096;
		}

		int yAccl = ((data[3] & 0x0F) * 256 + data[4]);
		if (yAccl > 2047)
		{
			yAccl = yAccl - 4096;
		}

		// Output data to screen
		printf("Acceleration in X-Axis : %d \n", xAccl);
		printf("Acceleration in Y-Axis : %d \n", yAccl);
	}
}
