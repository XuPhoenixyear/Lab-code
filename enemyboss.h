#ifndef ENEMYBOSS_H
#define ENEMYBOSS_H
#include"enemyplane.h"

#define BOSSBULLETSPEED 10
#define BOSSBLTNUM 25
#define BOSSBLTNUM2 30
class EnemyBoss:public EnemyPlane
{
public:
    EnemyBoss();

    //攻击：激光、子弹
    EnemyBullet bossBlt[BOSSBLTNUM];
    EnemyBullet bossLaser[2];
    EnemyBullet bossBlt2[BOSSBLTNUM2];

    //boss 增加血量计算
    int blood;

    //驻足时间
    int stoptime;

    //转向次数
    int changeNum;

    //召唤小飞机
    bool arouse;

    //boss 移动方式计算
    void move();

    //boss 攻击方式重写
    void shoot();

    //boss 子弹刷新重写
    void updateBullet();

    //boss 攻击方式
    void attack1();
    void attack2();
    void attack3();
    void attack4();
};

#endif // ENEMYBOSS_H
