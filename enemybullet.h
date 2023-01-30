#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#define PI 3.14159265375
#include"bullet.h"
#include<complex>
#define enemyBulletSpeed 6
class EnemyBullet:public Bullet
{
    //继承有子弹图片资源、子弹坐标、子弹移动速度、子弹矩形边框、子弹是否闲置
public:
    EnemyBullet();

    //敌机子弹偏转角(发射方向)
    double deltX;
    double deltY;

    //子弹发射角度
    double angle;

};

#endif // ENEMYBULLET_H
