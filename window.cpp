#include "window.h"
#include "adcreader.h"
#include <ctime>
#include <cmath>
#include "WateringThread.h"
#include "wiringPi.h"


Window::Window() : threshLow(10), threshHigh(65)
{
  
 
	// set up the initial plot data
	for( int index=0; index<plotDataSize; ++index )
	{
		xData[index] = index;
		yData[index] =10;
		y1Data[index]=threshLow;
		y2Data[index]=threshHigh;
	}

	//Initialize curves
	curve = new QwtPlotCurve;
	curve->setPen(QPen(Qt::green,2));
	curve1= new QwtPlotCurve;
	curve1->setPen(QPen(Qt::red,2));
	curve2 = new QwtPlotCurve;
	curve2->setPen(QPen(Qt::blue,2));

	//Initialize plots, buttons, labels and progressbar
	plot = new QwtPlot;
	button1 = new QPushButton("Xerophyte");
	button2 = new QPushButton("Mesophyte");
	button3 = new QPushButton("Hygrophyte");
	Label1 = new QLabel(this);
	bar1 = new QProgressBar(this);
	
	    
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
        
	//attach curves to plot
	curve->attach(plot);
        curve1->attach(plot);
	curve2->attach(plot);	

	//Label axis 
	plot->setAxisTitle(QwtPlot::xBottom, "Dryness (%)");
    	plot->setAxisTitle(QwtPlot::yLeft, "Time (x10 ms)");
	plot->replot();
	plot->show();
	
	// set up the vertical and horizontal layout 
	vLayout = new QVBoxLayout;
	vLayout->addWidget(Label1);
	
	vLayout->addWidget(button1);
	vLayout->addWidget(button2);
	vLayout->addWidget(button3);

	
	hLayout = new QHBoxLayout;
	hLayout->addLayout(vLayout);
	hLayout->addWidget(plot);

	setLayout(hLayout);

	// t.start starts the ADC thread
	
	t.start();
	
    
       
}

Window::~Window() {
	// tells the thread to no longer run its endless loop
        t.quit();
	
}

void Window::timerEvent( QTimerEvent * )
{
  //initialize output pin
  wiringPiSetup () ;
  pinMode (1, OUTPUT) ;
  
  //call getData() function to get data points from ADC reader thread 
  int result = t.getData();
  
  //convert values to percetages	
  double inVal = result/8.5;
  
  double inVal1 = threshLow/8.5;
  double inVal2 = threshHigh/8.5;

  
  if (inVal >= inVal2)
    {
      //open solenoid valve when inVal > than threshold High
      digitalWrite (1, HIGH) ;
      Label1->setText("Water Plant NOW!");
    }
  else if (inVal <= inVal1)
    {
      //close valve to stop watering plants
      digitalWrite (1, LOW) ;
      Label1->setText("Water level Good");
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
	
	plot->setAxisTitle(QwtPlot::xBottom, "Dryness (%)");
    	plot->setAxisTitle(QwtPlot::yLeft, "Time (x10 ms)");
	plot->replot();

	if(inVal/inVal2 <=1)
	  {// set the progress bar value
	    bar1->setValue( inVal/inVal2 * 100 );
	  }
	else
	  {
	    bar1->setValue(100);
	  }
       

}

//functions defining thresholds

int Window::setThresholds()
{
  
  threshLow = 150/8.5;
  return threshLow;
}

int Window::setThresholds1()
{
 
  threshLow = 200/8.5;
  return threshLow;
  
}

int Window::setThresholds2()
{
  
  threshLow = 250/8.5;
  return threshLow;
  
}

int Window::setThresholdsH()
{

  threshHigh = 450/8.5;
  return threshHigh;
  
}

int Window::setThresholdsH1()
{

  threshHigh = 550/8.5;
  return threshHigh;
  
}

int Window::setThresholdsH2()
{

  threshHigh = 650/8.5;
  return threshHigh;
}


