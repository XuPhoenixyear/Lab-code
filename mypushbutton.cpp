#include "mypushbutton.h"

 MyPushButton::MyPushButton(QString image)
 {

     //保存默认显示路径
     this->normalImagePath = image;

     QPixmap pix;
     bool ret = pix.load(this->normalImagePath);
     if(!ret)
     {
         QString str = QString("%1 图片加载失败").arg(this->normalImagePath);
         qDebug()<<str;
         return;
     }

     //设定图片的大小
     this->setFixedSize(pix.width(),pix.height());

     //设置不规则图片的样式
     this->setStyleSheet("QPushButton{border:0px;}");

     //设置图片
     this->setIcon(pix);

     //设置图片的大小
     this->setIconSize(QSize(pix.width(),pix.height()));


 }

 void MyPushButton::zoomDown()
 {
     QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

     //设定时间间隔
     animation->setDuration(200);
     //设置动画对象起始位置
     animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
     //设置动画对象结束位置
     animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
     //设置缓和曲线
     animation->setEasingCurve(QEasingCurve::OutBounce);
     //执行动画
     animation->start();

 }

 void MyPushButton::zoomUp()
 {
     QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

     //设定时间间隔
     animation->setDuration(200);
     //设置动画对象起始位置
     animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
     //设置动画对象结束位置
     animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
     //设置缓和曲线
     animation->setEasingCurve(QEasingCurve::OutBounce);
     //执行动画
     animation->start();

 }
