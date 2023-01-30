#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

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
#include<QRect>
#include<stdlib.h>
#include<enemybullet.h>
#include<math.h>

class EnemyPlane
{
public:
    EnemyPlane();

    //敌人图像
    QPixmap enemyPix;

    //敌机类型
    int choseType;

    //敌人坐标
    int x;
    int y;

    //敌人飞行速度
    int enemySpeed_x;
    int enemySpeed_y;

    //敌人状态
    bool enemyFree;

    //敌人弹夹
    EnemyBullet blt[10];

    //敌机子弹发射间隔记录
    int enemyBullerRecord;

    //敌人移动方向
    int enemyDirection;

    //敌人矩形边框(碰撞检测)
    QRect enemyRect;

    //敌机自带定时器
    QTimer enemyTimer;

    //敌人发射子弹
    void shoot();

    //更新子弹坐标(设置弹幕)
    void updateBullet();

    //更新子弹角度
    void updateBulletAngle(int,int);

};

#endif // ENEMYPLANE_H
