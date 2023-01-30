#include "enemyplane.h"

EnemyPlane::EnemyPlane()
{
    //设置敌机类型
    choseType=rand()%3;
    if(choseType==0)
    {
        enemyPix.load(":/photo/15.png");
    }
    else if(choseType==1)
    {
        enemyPix.load(":/photo/16.png");
    }
    else if(choseType==2)
    {
        enemyPix.load(":/photo/17.png");
    }

    //敌机初始坐标
    x=0;
    y=0;

    //敌机初始状态
    enemyFree=true;

    //敌机初始速度
    enemySpeed_x=1;
    enemySpeed_y=3;

    //敌机移动方向
    enemyDirection=rand()%2;

    //设置敌机矩形边框
    enemyRect.setWidth(60);
    enemyRect.setHeight(60);
    enemyRect.moveTo(x,y);

    //初始化敌机发射子弹间隔记录
    enemyBullerRecord=0;

    for(int i=0;i<10;i++)
        blt[i].bulletFree=true;
}

void EnemyPlane::shoot()
{
    for(int i=0;i<10;i++)
    {
        if(blt[i].bulletFree)
        {
            //设置敌机子弹出场位置
            blt[i].bulletFree=false;
            blt[i].x=x+enemyRect.width()*0.5;
            blt[i].y=y+enemyRect.height();
            break;
        }
    }
}

void EnemyPlane::updateBullet()
{
    //更新打出去的子弹的位置
    for(int i=0;i<10;i++)
    {
        if(!blt[i].bulletFree)
        {
            //计算子弹坐标
            blt[i].x+=(round(enemyBulletSpeed*cos(blt[i].angle)));
            blt[i].y+=(round(enemyBulletSpeed*sin(blt[i].angle)));

            blt[i].bulletRect.moveTo(blt[i].x,blt[i].y);
            if(blt[i].y>840||blt[i].x<0||blt[i].x>690||blt[i].y<-10)
            {
                blt[i].bulletFree=true;
            }
        }
    }
}

void EnemyPlane::updateBulletAngle(int heroX,int heroY)
{
    //设置子弹发射角度
    for(int j=0;j<10;j++)
    {
           //将未打出的子弹调整角度
        if(blt[j].bulletFree==true)
         {   //设置子弹跟踪,当前子弹速度设为10
            blt[j].deltX=heroX-x;
            blt[j].deltY=heroY-y;

            //防止分母为0
            if(blt[j].deltX==0)
            {
                if(heroX>=x)
                    blt[j].deltX=0.00001;
                else
                    blt[j].deltX=-0.00001;
            }
            if(blt[j].deltY==0)
            {
                if(heroY>=y)
                    blt[j].deltY=0.00001;
                else
                    blt[j].deltY=-0.00001;
            }

            //求角度
            if(blt[j].deltX>0&&blt[j].deltY>0)
            {
                blt[j].angle = atan(fabs(blt[j].deltY/blt[j].deltX));
            }
            else if(blt[j].deltX<0&&blt[j].deltY>0)
            {
                blt[j].angle = PI-atan(fabs(blt[j].deltY/blt[j].deltX));
            }
            else if(blt[j].deltX<0&&blt[j].deltY<0)
            {
                blt[j].angle=PI+atan(fabs(blt[j].deltY/blt[j].deltX));
            }
            else if(blt[j].deltX>0&&blt[j].deltY<0)
            {
                blt[j].angle=2*PI-atan(fabs(blt[j].deltY/blt[j].deltX));
            }
            else
                qDebug()<<"False";
        }
    }
}
