#ifndef BULLET_H
#define BULLET_H
#include <QMainWindow>
#include<QDebug>
#include<QPushButton>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPainter>
#include<QPaintEvent>
#include<QPixmap>
#include<QTimer>
#include<QKeyEvent>

class Bullet
{
public:
    Bullet();

    //子弹图片资源
    QPixmap bulletPix;

    //子弹坐标
    int x;
    int y;

    //子弹移动速度
    int bulletSpeed;

    //子弹矩形边框(碰撞检测)
    QRect bulletRect;

    //子弹是否闲置
    bool bulletFree;
};

#endif // BULLET_H
