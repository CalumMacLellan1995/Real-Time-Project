#include "window.h"
#include "mcp3008Spi.h"
#include "adcreader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  // create the window
  Window window;
  window.showMaximized();

  // call the window.timerEvent function every 40 ms
  window.startTimer(10);

  // execute the application
  return app.exec();

}
