#ifndef MCP3008SPI_H
#define MCP3008SPI_H

#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <QThread>

class mcp3008Spi : public QThread
{
public:
        
        mcp3008Spi();	
        mcp3008Spi(std::string devspi, unsigned char spiMode, unsigned int spiSpeed, unsigned char spibitsPerWord);
       ~mcp3008Spi();
      
       unsigned char mode;
       unsigned char bitsPerWord;
       unsigned int speed;
       int spifd;

       int spiOpen(std::string devspi);
       int spiClose();
       int getData();
       int spiWriteRead( unsigned char *data, int length);
       void quit();
       //       void run();
       
private:
	bool running;
	int a2dVal;
	//int output;
};

#endif
