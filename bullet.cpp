#include "bullet.h"

Bullet::Bullet()
{
    //初始化成员属性
    bulletPix.load(":/photo/14.png");
    bulletSpeed = 1;

    x=350;
    y=425;

    bulletRect.setWidth(7);
    bulletRect.setHeight(25);
    bulletRect.moveTo(x,y);
}

