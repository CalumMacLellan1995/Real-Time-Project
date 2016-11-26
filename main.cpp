
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char* argv[])
{

  
  QApplication app(argc, argv);

  QHBoxLayout *hLayout = new QHBoxLayout;
  QPushButton *b1 = new QPushButton("A");
  QPushButton *b2 = new QPushButton("B");
  QPushButton *b3 = new QPushButton("C");
  hLayout->addWidget(b1);
  hLayout->addWidget(b2);
  hLayout->addWidget(b3);


  QVBoxLayout *vLayout = new QVBoxLayout;
  QPushButton *b4 = new QPushButton("D");
  QPushButton *b5 = new QPushButton("E");
  QPushButton *b6 = new QPushButton("F");
  vLayout->addWidget(b4);
  vLayout->addWidget(b5);
  vLayout->addWidget(b6);

  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->addLayout(hLayout);
  mainLayout->addLayout(vLayout);

  QWidget *w = new QWidget();

  w->setLayout(mainLayout);
  w->setWindowTitle("layouts");
 
  w->show();

  return app.exec();
}
