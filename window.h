#ifndef WINDOW_H
#define WINDOW_H

#include <QLabel>
#include <QPushButton>
#include <QPen>
#include <qwt/qwt_thermo.h>
#include <qwt/qwt_knob.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <QProgressBar>
#include <QBoxLayout>
#include "adcreader.h"


// class definition 'Window'
class Window : public QWidget
{
  // must include the Q_OBJECT macro for for the Qt signals/slots framework to work with this class
  Q_OBJECT

 public:

  Window(); // default constructor - called when a Window is declared without arguments

  ~Window();

  void timerEvent( QTimerEvent * );

  public slots:
    
    int setThresholds();
    int setThresholds1();
    int setThresholds2();

    int setThresholdsH();
    int setThresholdsH1();
    int setThresholdsH2();
    
    // internal variables for the window class
 private:
   
    QwtPlot      *plot;
    QwtPlotCurve *curve;
    QwtPlotCurve *curve1;
    QwtPlotCurve *curve2;

    
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    
    QLabel *Label1; 
    QProgressBar *bar1;
    
    // layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
    QVBoxLayout  *vLayout;  // vertical layout
    QHBoxLayout  *hLayout;  // horizontal layout

    static const int plotDataSize = 100;

    // data arrays for the plot
    double xData[plotDataSize];
    double yData[plotDataSize];
    double y1Data[plotDataSize];
    double y2Data[plotDataSize];
    
    //Thresholds and ADC Thread instance
    int threshLow;
    int threshHigh;
    ADCreader t;
   
};

#endif // WINDOW_H
