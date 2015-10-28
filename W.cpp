#include "W.h"
#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QFont>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <QTimer>
#include <QImage>
#include <string>

#include <iostream>
using namespace std;


QImage& cvxCopyIplImage(const IplImage *pIplImage, QImage &qImage);


void PainterWidget::paintEvent(QPaintEvent* event){
	QPainter painter(this);
	
	if(filterFlag){
		painter.drawImage(0,0,processedQImage[picNum]);
	}
	else{
		painter.drawImage(0,0,qImage[picNum]);
	}
}


void PainterWidget::processImage(IplImage** pIplImage){
	IplImage *processIplImage[5];
	for(int i=0; i<5; i++){
		processIplImage[i]=cvCloneImage(pIplImage[i]);
		}
	for(int i=0; i<5 ; i++){
        static CvHaarClassifierCascade* cascade = 0;
        cascade = (CvHaarClassifierCascade*)cvLoad("haarcascade_frontalface_alt.xml", 0, 0, 0 );
        if( !cascade ){
                fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
        }
	
        static CvMemStorage* storage = 0;
        storage =cvCreateMemStorage(0);
        CvSeq* faces;
        faces =  cvHaarDetectObjects(processIplImage[i], cascade, storage,1.1, 2,CV_HAAR_DO_CANNY_PRUNING,cvSize(20, 20),cvSize(20, 20) );

		if (faces)
        {
            for(int j= 0; j< faces->total; j++)
            {
                CvPoint pt1, pt2;
                CvRect* rectangle = (CvRect*)cvGetSeqElem(faces, j);
                pt1.x = rectangle->x;
                pt2.x = rectangle->x + rectangle->width;
                pt1.y = rectangle->y;
                pt2.y = rectangle->y + rectangle->height;
                cvRectangle( processIplImage[i], pt1,pt2, CV_RGB(255,0,0), 3, 8, 0 );
                }
        }

	}
	
	for(int i=0; i<5; i++){
		qImage[i]=cvxCopyIplImage(pIplImage[i],qImage[i]);
		processedQImage[i]=cvxCopyIplImage(processIplImage[i], processedQImage[i]);
		}
	
}

PainterWidget::PainterWidget(){
	imageCount=0;
	imageSpeed=500;
	picNum=0;
	filterFlag=false;
	play_Flag=false;
	OnOff_Flag=false;
	timer = new QTimer(this);
	
     btnPlus= new QPushButton(this);
     btnPlus->setText("+");
     btnPlus->setFont(QFont("Courier", 18, QFont::Bold));
     btnPlus->setGeometry(580,100,110,50);


      btnMinus= new QPushButton(this);
      btnMinus->setText("-");
      btnMinus->setFont(QFont("Courier", 18, QFont::Bold));
      btnMinus->setGeometry(700,100,110,50);


          btnPlay= new QPushButton(this);
          btnPlay->setText("Play");
          btnPlay->setFont(QFont("Courier", 18, QFont::Bold));
          btnPlay->setGeometry(600,200,110,50);

          btnNext= new QPushButton(this);
          btnNext->setText("Next");
          btnNext->setFont(QFont("Courier", 18, QFont::Bold));
          btnNext->setGeometry(580,300,110,50);

          btnBack= new QPushButton(this);
          btnBack->setText("Back");
          btnBack->setFont(QFont("Courier", 18, QFont::Bold));
          btnBack->setGeometry(700,300,110,50);

          btnOnOff= new QPushButton(this);
          btnOnOff->setText("DETECT");
          btnOnOff->setFont(QFont("Courier", 18, QFont::Bold));
          btnOnOff->setGeometry(600,400,110,50);
		  
          speedText= new QLabel(this);
          speedText->setNum(imageSpeed);
          speedText->setFont(QFont("Courier", 18, QFont::Bold));
          speedText->setGeometry(900,500,110,50);
		  
		connect( btnNext, SIGNAL(clicked()), this, SLOT(setNext()));
        connect( btnBack, SIGNAL(clicked()), this, SLOT(setBack()));
        connect( btnPlus, SIGNAL(clicked()), this, SLOT(setPlus()));
        connect( btnMinus, SIGNAL(clicked()), this, SLOT(setMinus()));
        connect( btnPlay, SIGNAL(clicked()), this, SLOT(setPlay()));
        connect( btnOnOff, SIGNAL(clicked()), this, SLOT(setOnOff()));
		connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	

}


void PainterWidget::update(){
	picNum++;
	picNum%=5;
	timer->start(imageSpeed);
	repaint();
	
}

void PainterWidget::setNext(){
	picNum++;
	picNum%=5;
	repaint();
}

void PainterWidget::setBack(){
	picNum--;
	if(picNum<0){picNum=4;}
	repaint();
}


void PainterWidget::setPlus(){
	imageSpeed+=200;
    speedText->setNum(imageSpeed);
	repaint();
}
void PainterWidget::setMinus(){
	imageSpeed-=200;
    speedText->setNum(imageSpeed);
	repaint();
}
void PainterWidget::setPlay(){
	if(play_Flag){
		play_Flag=false;
		timer->stop();
	}
	else{
		play_Flag=true;
		timer->start(imageSpeed);
	}
}

void PainterWidget::setOnOff(){
	filterFlag=!filterFlag;
	repaint();
}



