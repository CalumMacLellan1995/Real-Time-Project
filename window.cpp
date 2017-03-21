#include "window.h"
// #include "adcreader.h"
#include <ctime>
#include <cmath>  // for sine stuff


Window::Window() : gain(5), count(0)
{
  
  //knob = new QwtKnob;
	// set up the gain knob
  //	knob->setValue(gain);
	//gain = setGain();
	// use the Qt signals/slots framework to update the gain -
	// every time the knob is moved, the setGain function will be called
  // 	connect( knob, SIGNAL(valueChanged(double)), SLOT(setGain(double)) );

	// set up the thermometer
  //	thermo = new QwtThermo; 
  //	thermo->setFillBrush( QBrush(Qt::red) );
	//thermo->setRange(0, 20);
  //	thermo->show();

  //	printf("hello");
	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] =10;
		y1Data[index]=gain;
		y2Data[index]=gain-1;
	}

	curve = new QwtPlotCurve;
	curve->setPen(QPen(Qt::green,2));
	curve1= new QwtPlotCurve;
	curve1->setPen(QPen(Qt::red,2));
	curve2 = new QwtPlotCurve;
	curve2->setPen(QPen(Qt::blue,2));
	
	plot = new QwtPlot;
	button0 = new QPushButton("Water Plants" );
	button1 = new QPushButton("Xerophyte");
	button2 = new QPushButton("Mesophyte");
	button3 = new QPushButton("Hygrophyte");
	Label1 = new QLabel(this);
	bar1 = new QProgressBar(this);
	
	connect( button0, SIGNAL(clicked()), SLOT(water()));     
        connect( button1, SIGNAL(clicked()), SLOT(setThresholds()) );
	connect( button2, SIGNAL(clicked()), SLOT(setThresholds1()) );
	connect( button3, SIGNAL(clicked()), SLOT(setThresholds2()) );
	
	connect( button1, SIGNAL(clicked()), SLOT(setThresholdsH()) );
	connect( button2, SIGNAL(clicked()), SLOT(setThresholdsH1()) );
	connect( button3, SIGNAL(clicked()), SLOT(setThresholdsH2()) );
	
	// make a plot curve from the data and attach it to the plot
	curve->setSamples(xData, yData, plotDataSize);
	curve1->setSamples(xData,y1Data,plotDataSize);
	curve2->setSamples(xData,y2Data,plotDataSize);
      
	curve->attach(plot);
	curve1->attach(plot);
	curve2->attach(plot);	

	plot->replot();
	plot->show();


	// set up the layout - knob above thermometer
	vLayout = new QVBoxLayout;
	vLayout->addWidget(Label1);
	vLayout->addWidget(button0);
	vLayout->addWidget(button1);
	vLayout->addWidget(button2);
	vLayout->addWidget(button3);

	
	// plot to the left of knob and thermometer
	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout);
	hLayout->addWidget(plot);

	setLayout(hLayout);

	// This is a demo for a thread which can be
	// used to read from the ADC asynchronously.
	// At the moment it doesn't do anything else than
	// running in an endless loop and which prints out "tick"
	// every second.
//	adcreader = new ADCreader();
//	adcreader->start();
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
//	adcreader->quit();
	// wait until the run method has terminated
//	adcreader->wait();
//	delete adcreader;
}

void Window::timerEvent( QTimerEvent * )
{
  
  //	double inVal = gain * sin( M_PI * count/50.0 );
  double inVal = WaterValue-count; // rand()%50+1;
  double inVal1 = threshLow;
  double inVal2 = threshHigh;
  ++count;
  
  if (inVal > inVal1 && inVal < inVal2)
    {
      Label1->setText("Water level Good");
      //      Label1->setAlignment(Qt::AlignLeft);
    }
  else
    {
      Label1->setText("Water Plant NOW!");
      // Label1->setAlignment(Qt::AlignLeft);
    }
	// add the new input to the plot
	memmove( yData, yData+1, (plotDataSize-1) * sizeof(double) );
	yData[plotDataSize-1] = inVal;
	curve->setSamples(xData, yData, plotDataSize);

	memmove( y1Data, y1Data+1, (plotDataSize-1) * sizeof(double) );
	y1Data[plotDataSize-1] = inVal1;
	curve1->setSamples(xData, y1Data, plotDataSize);
       
	memmove( y2Data, y2Data+1, (plotDataSize-1) * sizeof(double) );
	y2Data[plotDataSize-1] = inVal2;
	curve2->setSamples(xData, y2Data, plotDataSize);
	
	
	plot->replot();
	

	if(inVal/inVal2 <=1)
	  {// set the thermometer value
	    bar1->setValue( inVal/inVal2 * 100 );
	  }
	else
	  {
	    bar1->setValue(100);
	  }
       

	if(inVal < inVal1)
	  {
	    count =0;
	  }
}


// this function can be used to change the gain of the A/D internal amplifier
/*
void Window::setGain(double gain)
{
//srand(time(0));

//gain=rand()%50+1;
  // for example purposes just change the amplitude of the generated input
  
  this->gain = gain;
}
*/

int Window::setThresholds()
{
  
  threshLow = 10;
  return threshLow;
}

int Window::setThresholds1()
{
 
  threshLow = 15;
  return threshLow;
  
}

int Window::setThresholds2()
{
  
  threshLow = 20;
  return threshLow;
  
}

int Window::setThresholdsH()
{

  threshHigh = 35;
  return threshHigh;
  
}

int Window::setThresholdsH1()
{

  threshHigh = 45;
  return threshHigh;
  
}

int Window::setThresholdsH2()
{

  threshHigh = 55;
  return threshHigh;
}

int Window::water()
{
  count = 0;
  return count;
}
