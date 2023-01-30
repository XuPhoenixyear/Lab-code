#ifndef HEROPLANE_H
#define HEROPLANE_H

#include<QDebug>
#include<QPushButton>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<QPaintEvent>
#include<QPixmap>
#include<QTimer>
#include<QMouseEvent>
#include<QEvent>
#include"bullet.h"
#include<QRect>
class HeroPlane
{
public:

    //飞机坐标
    int px ;
    int py;

    //飞机图像
    QPixmap planePix;

    //飞机生命
    int life;

    //飞机存活状态
    bool heroFree;

    //飞机定时器
    QTimer heroTimer;

    //子弹弹夹
    Bullet blt[50];
    Bullet blt2[50];      //2号弹夹
    Bullet blt3[50];      //3号弹夹
    Bullet blt4[50];      //4号弹夹
    Bullet blt5[50];      //5号弹夹

    //技能

    bool ifBltMore1;      //是否开启2号弹夹
    bool ifBltMore2;      //是否开启3号弹夹
//    bool ifBltMore3;      //是否开启4、5号弹夹

    //设置矩形边框(子弹发射以及判断碰撞)
    QRect planeRect;

    HeroPlane();

    //发射子弹
   void shoot();

    //更新子弹坐标
    void updateBullet();

};

#endif // HEROPLANE_H
