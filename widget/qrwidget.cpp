#include "qrwidget.h"
#include <QPainter>
#include <QDebug>
#include <qrencode.h>

#define BORDER_WIDTH    6
#define QR_SCALE        7.5

QRWidget::QRWidget(QWidget *parent) :
    QWidget(parent),
    data("Hello QR")//Note: The encoding fails with empty string so I just default to something else. Use the setQRData() call to change this.
{
}

void QRWidget::setQRData(QString data){
    this->data=data;
    update();
}

void QRWidget::paintEvent(QPaintEvent *pe){
    QPainter painter(this);
    //NOTE: I have hardcoded some parameters here that would make more sense as variables.
    QRcode *qr = QRcode_encodeString(data.toStdString().c_str(), 1, QR_ECLEVEL_L, QR_MODE_8, 0);
    if(0!=qr){
        QColor fg("black");
        QColor bg("white");
        painter.setBrush(bg);
        painter.setPen(Qt::NoPen);
        painter.drawRect(0,0,width()+BORDER_WIDTH*2,height()+BORDER_WIDTH*2);
        painter.setBrush(fg);
        const int s=qr->width>0?qr->width:1;
//        const double w=width();
//        const double h=height();
//        const double aspect=w/h;
//        const double scale=((aspect>1.0)?h:w)/s;
        for(int y=0;y<s;y++){
            const int yy=y*s;
            for(int x=0;x<s;x++){
                const int xx=yy+x;
                const unsigned char b=qr->data[xx];
                if(b &0x01){
                    const double rx1=x*QR_SCALE, ry1=y*QR_SCALE;
                    QRectF r(rx1+BORDER_WIDTH, ry1+BORDER_WIDTH, QR_SCALE, QR_SCALE);
                    painter.drawRects(&r,1);
                }
            }
        }
        QRcode_free(qr);
    }
/*    else{
        QColor error("red");
        painter.setBrush(error);
        painter.drawRect(0,0,width(),height());
        qDebug()<<"QR FAIL: "<< strerror(errno);
	}*/
    qr=0;
}
