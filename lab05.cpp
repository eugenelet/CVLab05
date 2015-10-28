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
#include <iostream>
#include "W.h"

using namespace std;

IplImage *detect_and_draw( IplImage* );

int main(int argc, char *argv[]) {
	IplImage *img[5];

        img[0] = cvLoadImage("01.jpg",1);
        img[1] = cvLoadImage("02.jpg",1);
        img[2] = cvLoadImage("03.jpg",1);
        img[3] = cvLoadImage("04.jpg",1);
        img[4] = cvLoadImage("05.jpg",1);
	

	
	QApplication app(argc,argv);
	PainterWidget *widget = new PainterWidget();
	widget->processImage(img);
	widget->resize(1080,800);
	widget->setWindowTitle("Lab4");
	widget->show();
	return app.exec();
}






QImage& cvxCopyIplImage(const IplImage *pIplImage, QImage &qImage)
{   //implement the conversion function here
	if(!pIplImage) return qImage;

	if(qImage.isNull())
        {
                int w = pIplImage->width;
                int h = pIplImage->height;
                qImage = QImage(w, h, QImage::Format_RGB32);
        }

	int x, y;
	for(x = 0; x < pIplImage->width; ++x)
        {
	   for(y = 0; y < pIplImage->height; ++y)
	   {
	      CvScalar color = cvGet2D(pIplImage, y, x);

	      int r = (int)color.val[2];
	      int g = (int)color.val[1];
	      int b = (int)color.val[0];

	      qImage.setPixel(x, y, qRgb(r,g,b));
	   }
        }
   return qImage;
}
