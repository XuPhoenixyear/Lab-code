#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include<QPropertyAnimation>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    MyPushButton(QString image);
    QString normalImagePath;  //默认显示图片途径

    void zoomDown();   //向下跳跃
    void zoomUp();   //向上跳跃


signals:

};

#endif // MYPUSHBUTTON_H
