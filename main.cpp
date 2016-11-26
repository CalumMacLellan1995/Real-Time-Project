#include <stdio.h>
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <cmath>

int main(int argc, char* argv[])
{
  int value=10;
  // printf("Bitch enter a number: \n");
  //  scanf("%d", &value);
  
  static const int plotDataSize = 10;
  double yData[plotDataSize];
  double xData[plotDataSize];
  
  QApplication app(argc, argv);

  //adding horizontal pushbuttons
  QHBoxLayout *hLayout = new QHBoxLayout;
  QPushButton *b1 = new QPushButton("A");
  QPushButton *b2 = new QPushButton("B");
  QPushButton *b3 = new QPushButton("C");
  hLayout->addWidget(b1);
  hLayout->addWidget(b2);
  hLayout->addWidget(b3);

  //adding vertical pushbuttons
  QVBoxLayout *vLayout = new QVBoxLayout;
  QPushButton *b4 = new QPushButton("D");
  QPushButton *b5 = new QPushButton("E");
  QPushButton *b6 = new QPushButton("F");
  vLayout->addWidget(b4);
  vLayout->addWidget(b5);
  vLayout->addWidget(b6);

  //Creating plot window
   
  QwtPlotCurve *curve = new QwtPlotCurve;
  QwtPlot *plot = new QwtPlot;

  for (int index=0; index<plotDataSize; ++index)
    {
      xData[index]=index;
  
      yData[index]=value;
      // yData[index]=sin(M_PI*index/50);
    }    
      
      curve->setSamples(xData, yData, plotDataSize);
      curve->attach(plot);

      plot->replot();
      plot->show();
      

  
  //Creating main layout window

  QVBoxLayout *mainLayout = new QVBoxLayout;

  mainLayout->addLayout(hLayout);
  mainLayout->addLayout(vLayout);
  mainLayout->addWidget(plot);
  
  QWidget *w = new QWidget();

  w->setLayout(mainLayout);
  w->setWindowTitle("layouts");
 
  w->show();

  return app.exec();
}
