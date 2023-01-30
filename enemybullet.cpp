#include "enemybullet.h"

EnemyBullet::EnemyBullet()
{
    //初始化成员属性
    bulletPix.load(":/photo/23_enemy_bullet_1.png");
    bulletSpeed = 5;

    x=0;
    y=0;

    bulletRect.setWidth(10);
    bulletRect.setHeight(10);
    bulletRect.moveTo(x,y);

    angle=PI/2;
}
