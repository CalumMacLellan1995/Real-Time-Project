
#include "mcp3008Spi.h"
#include "adcreader.h"
#include <QDebug>
using namespace std;

//call constructor
  mcp3008Spi a2d("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
  int a2dVal = 0;
  int a2dChannel = 0;
  unsigned char data[3];

//run function - infinite loop getting ADC data
void ADCreader::run()
{
	running = true;
	while (running)
	  {
	    data[0] = 1;  //  first byte transmitted -> start bit
	    data[1] = 0b10000000 |( ((a2dChannel & 7) << 4)); // second byte transmitted -> (SGL/DIF = 1, D2=D1=D0=0)
	    data[2] = 0; // third byte transmitted....don't care
 
	    a2d.spiWriteRead(data, sizeof(data) );
 
	    a2dVal = 0;
            a2dVal = (data[1]<< 8) & 0b1100000000; //merge data[1] & data[2] to get result
            a2dVal |=  (data[2] & 0xff);
	   
	}
}

//quit function - stops infinite loop
void ADCreader::quit()
{
	running = false;
	exit(0);
}

//getData() extracts data from infinite loop when called
int ADCreader::getData()
{
  output = a2dVal;
  return output;
}

