#ifndef WATERINGTHREAD
#define WATERINGTHREAD

#include <QThread>

class WateringThread : public QThread
{
 public:

  WateringThread() {running = 0;};
  void quit();
  void run(bool stop);
  bool wateringstop();
  bool water();

 private:
  bool running;
  bool open;
};

#endif
