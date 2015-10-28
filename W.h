#ifndef W_H
#define W_H
#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QFont>
#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QPushButton>
#include <stdio.h>
#include <QtGui/QLabel>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>


class PainterWidget: public QWidget{
	Q_OBJECT
		 protected:
             		void paintEvent(QPaintEvent*);
	     	public:
     		       PainterWidget();
				   void processImage(IplImage**);

		 public slots:
			void setPlus();
			void setMinus();
			void setNext();
			void setBack();
			void setPlay();
			void setOnOff();
			void update();

		private:
			QPushButton *btnPlus;
			QPushButton *btnMinus;
			QPushButton *btnNext;
			QPushButton *btnBack;
			QPushButton *btnPlay;
			QPushButton *btnOnOff;
			QLabel *speedText;
			int imageCount;
			int imageSpeed;
			int picNum;
			bool play_Flag;
			bool OnOff_Flag;
			bool filterFlag;
			QTimer *timer;
			QImage  qImage[5];
			QImage	processedQImage[5];
			


};

#endif
