#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#define BOSSTIME 1

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
#include"heroplane.h"
#include<QKeyEvent>
#include<ctime>
#include"bomb.h"
#include<stdlib.h>
#include"enemyboss.h"
#include<QDialog>
#include<QLabel>
#include<prop.h>

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
//   explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int index);

    //地图图片对象
    QPixmap map1;
    QPixmap map2;


    //地图y轴坐标
    int map1Position_y;
    int map2Position_y;

    //地图滚动幅度
    int mapScrollSpeed;

    //重写绘图事件
    void paintEvent(QPaintEvent* );

    //地图滚动坐标计算
    void mapPosition(int );

    //添加定时器
    QTimer mTimer;
    QTimer playTimeTimer;  //统计游戏进行时间

    //添加游戏时间统计
    int playtime;

    //添加英雄飞机
    HeroPlane hero;

    //添加敌机组
    EnemyPlane enemy[20]; //敌机的在场最大数量为20

    //设置敌机在场数
    int enemyRecord;

    //添加爆炸数组
    Bomb bombs[20];  //最大爆炸数量为敌机在场数量


    //添加boss
    EnemyBoss boss;

    int score[8];         //积分数组       //击杀一个普通敌人100分，每击中boss一次加50分(1000血的boss能拿50000分),击杀boss再得20000分
    QPixmap scorePix[10]; //积分图片

    //道具
    BulletProp bltProp;

    //重写键盘按下事件
    void keyPressEvent(QKeyEvent* );

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent* ev);



    //设置敌机出场
    void enemyToScene();

    //碰撞检测函数
    void collisionDetection();

    //更新坐标
    void updatePosition();

    void updateScore();  //更新得分

    bool ifKillingEnemy(Bullet*,EnemyPlane*);      //英雄飞机击毁敌机

    void heroAttackBoss(Bullet*);       //英雄攻击boss判定

signals:
    void sceneBack();
};

#endif // PLAYSCENE_H
