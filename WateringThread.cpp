#include "WateringThread.h"
#include <wiringPi.h>

void WateringThread :: run(bool)
{

  wiringPiSetup () ;
  pinMode (1, OUTPUT);
  running = true;

  while(running)
    {
    if (open == true)
      {
	digitalWrite (1, HIGH);
      }
    else if (open == false)
      {
	digitalWrite (1, LOW);
      }
    else
      {
	digitalWrite (1, LOW);
      }
    
    }
}

bool WateringThread::water()
{
  open = true;
  return open;
}

bool WateringThread::wateringstop()
{
  open = false;
  return open;
}

void WateringThread :: quit()
{
  running = false;
  exit(0);
}

