#include "enemyboss.h"

EnemyBoss::EnemyBoss()
{
    //给boss装载图片
    enemyPix.load(":/photo/24_boss1.png");

    //给boss的子弹装配图片
    for(int i = 0;i<BOSSBLTNUM;i++)
        bossBlt[i].bulletPix.load(":/photo/23_enemy_bullet_3.png");

    for(int i=0;i<2;i++)
        bossLaser[i].bulletPix.load(":/photo/25_bossLaser.png");

    for(int i=0;i<BOSSBLTNUM2;i++)
        bossBlt2[i].bulletPix.load(":/photo/23_enemy_bullet_1.png");

    //敌机初始坐标
    x=(700-enemyRect.width())/2;
    y=-enemyRect.height()/3;

    //敌机初始状态
    enemyFree=true;

    //敌机初始速度
    enemySpeed_x=1;
    enemySpeed_y=1;

    //敌机移动方向
    enemyDirection=rand()%2;

    //设置敌机矩形边框
    enemyRect.setWidth(300);
    enemyRect.setHeight(250);
    enemyRect.moveTo(x,y);

    //初始化敌机发射子弹间隔记录
    enemyBullerRecord=0;

    for(int i=0;i<10;i++)
        blt[i].bulletFree=true;

    //boss血条初始化,10000滴血
    blood = 500;

    //驻足时间
    stoptime=250;//8s

    arouse=0;

    //变向次数统计
    changeNum=0;

    //子弹初始化
    for(int i=0;i<BOSSBLTNUM;i++)
    {
        switch(i%5)
        {
        case 0:bossBlt[i].angle=PI/6;break;
        case 1:bossBlt[i].angle=PI/3;break;
        case 2:bossBlt[i].angle=PI/2;break;
        case 3:bossBlt[i].angle=2*PI/3;break;
        case 4:bossBlt[i].angle=5*PI/6;break;
        }

        bossBlt[i].bulletRect.setWidth(45);
        bossBlt[i].bulletRect.setHeight(45);
        bossBlt[i].bulletFree=true;
    }

    for(int i =0;i<BOSSBLTNUM2;i++)
    {
        switch(i%3)
        {
        case 0:bossBlt2[i].x=x+enemyRect.width()*0.5-4;break;
        case 1:bossBlt2[i].x=x+enemyRect.width()*0.5-14;break;
        case 2:bossBlt2[i].x=x+enemyRect.width()*0.5-24;break;
        }

        bossBlt2[i].bulletRect.setWidth(20);
        bossBlt2[i].bulletRect.setHeight(20);
        bossBlt2[i].bulletFree=true;
    }
    for(int i = 0;i < 2;i++)
    {
        bossLaser[i].bulletFree=true;
        bossLaser[i].bulletRect.setWidth(20);
        bossLaser[i].bulletRect.setHeight(600);//300*250
    }


}

void EnemyBoss::shoot()
{
    if(y>=20)
    {
        if(changeNum==0)
        {
            attack4();
        }
        else if(changeNum!=0)
        {
            if(changeNum%3!=0&&changeNum%6!=0)
            {
                attack2();
                if(x>=(700-enemyRect.width())/2-10&&x<=(700-enemyRect.width())/2+10)
                    attack3();
            }
            else if(changeNum%3==0&&changeNum%6!=0)
                attack1();
            else if(changeNum%6==0&&x>=(700-enemyRect.width())/2-10&&x<=(700-enemyRect.width())/2+10)
                attack4();
            else
                attack1();
        }
    }
}
void EnemyBoss::attack2()
{
    //发射小子弹,三个平行的位置上
    arouse=0;
    enemyTimer.setInterval(500);
    int location[3]={0};
    for(int i = 0;i<BOSSBLTNUM2;i++)
    {
        if(bossBlt2[i].bulletFree)
        {
            switch(i%3)
            {
            case 0:bossBlt2[i].x=x+enemyRect.width()*0.5+10;break;
            case 1:bossBlt2[i].x=x+enemyRect.width()*0.5-10;break;
            case 2:bossBlt2[i].x=x+enemyRect.width()*0.5-30;break;
            }
        }

        if(bossBlt2[i].bulletFree&&location[0]==0&&bossBlt2[i].x==x+enemyRect.width()*0.5+10)
        {
            location[0]=1;
            bossBlt2[i].y=y+enemyRect.height();
            bossBlt2[i].bulletFree=false;
//            qDebug()<<"boss shoot 1";
        }
        else if(bossBlt2[i].bulletFree&&location[1]==0&&bossBlt2[i].x==x+enemyRect.width()*0.5-10)
        {
            location[1]=1;
            bossBlt2[i].y=y+enemyRect.height();
            bossBlt2[i].bulletFree=false;
//          qDebug()<<"boss shoot 2";
        }
        else if(bossBlt2[i].bulletFree&&location[2]==0&&bossBlt2[i].x==x+enemyRect.width()*0.5-30)
        {
            location[2]=1;

            bossBlt2[i].y=y+enemyRect.height();
            bossBlt2[i].bulletFree=false;
//           qDebug()<<"boss shoot 3";
        }
        if(location[0]&&location[1]&&location[2])
        {
//            qDebug()<<"boss shoot break";
            break;
        }
    }
//    qDebug()<<"boss shoot blt";
}
void EnemyBoss::attack3()
{
    //召唤小飞机
    arouse = 1;
}
void EnemyBoss::attack4()
{
    //发射激光
    arouse=0;
    enemyTimer.setInterval(1000);

    if(bossLaser[0].bulletFree)
    {
        bossLaser[0].x=x+enemyRect.width()*0.4-7;
        bossLaser[0].y=y+enemyRect.height()-5;
        bossLaser[0].bulletFree=false;
    }
    if(bossLaser[1].bulletFree)
    {
        bossLaser[1].x=x+enemyRect.width()*0.6-7;
        bossLaser[1].y=y+enemyRect.height()-5;
        bossLaser[1].bulletFree=false;
    }
//    qDebug()<<"Laser!";
}
void EnemyBoss::attack1()
{
    arouse = 0;
    //向五个方向同时发射子弹
    enemyTimer.setInterval(1000);
    int direction[5]={0};
    for(int i=0;i<BOSSBLTNUM;i++)
    {

        if(bossBlt[i].bulletFree&&direction[0]==0&&bossBlt[i].angle==PI/6)
        {
            direction[0]=1;
            bossBlt[i].bulletFree=false;
            bossBlt[i].x=x+enemyRect.width()*0.5-14;
            bossBlt[i].y=y+enemyRect.height();
//                qDebug()<<"1";
        }
        else if(bossBlt[i].bulletFree&&direction[1]==0&&bossBlt[i].angle==PI/3)
        {
            direction[1]=1;
            bossBlt[i].bulletFree=false;
            bossBlt[i].x=x+enemyRect.width()*0.5-14;
            bossBlt[i].y=y+enemyRect.height();
//                qDebug()<<"2";
        }
        else if(bossBlt[i].bulletFree&&direction[2]==0&&bossBlt[i].angle==PI/2)
        {
            direction[2]=1;
            bossBlt[i].bulletFree=false;
            bossBlt[i].x=x+enemyRect.width()*0.5-14;
            bossBlt[i].y=y+enemyRect.height();
//                qDebug()<<"3";
        }
        else if(bossBlt[i].bulletFree&&direction[3]==0&&bossBlt[i].angle==2*PI/3)
        {
            direction[3]=1;
            bossBlt[i].bulletFree=false;
            bossBlt[i].x=x+enemyRect.width()*0.5-14;
            bossBlt[i].y=y+enemyRect.height();
//                qDebug()<<"4";
        }
        else if(bossBlt[i].bulletFree&&direction[4]==0&&bossBlt[i].angle==5*PI/6)
        {
            direction[4]=1;
            bossBlt[i].bulletFree=false;
            bossBlt[i].x=x+enemyRect.width()*0.5-14;
            bossBlt[i].y=y+enemyRect.height();
//                qDebug()<<"5";
        }
        if(direction[0]&&direction[1]&&direction[2]&&direction[3]&&direction[4])
        {
//                qDebug()<<"break";
            break;
        }
    }
}
void EnemyBoss::updateBullet()
{
    //更新打出去的子弹的位置
    for(int i=0;i<BOSSBLTNUM;i++)
    {
        if(!bossBlt[i].bulletFree)
        {
            bossBlt[i].x+=round(BOSSBULLETSPEED*cos(bossBlt[i].angle));
            bossBlt[i].y+=round(BOSSBULLETSPEED*sin(bossBlt[i].angle));

            bossBlt[i].bulletRect.moveTo(bossBlt[i].x,bossBlt[i].y);

            //子弹越界消失
            if(bossBlt[i].y>840||bossBlt[i].y<-10||bossBlt[i].x>690||bossBlt[i].x<-10)
                bossBlt[i].bulletFree=true;
        }
    }
    for(int i=0;i<BOSSBLTNUM2;i++)
    {
        if(!bossBlt2[i].bulletFree)
        {
            bossBlt2[i].y+=BOSSBULLETSPEED;
            bossBlt2[i].bulletRect.moveTo(bossBlt2[i].x,bossBlt2[i].y);

            if(bossBlt2[i].y>840||bossBlt2[i].y<-10||bossBlt2[i].x>690||bossBlt2[i].x<-10)
                bossBlt2[i].bulletFree=true;
        }
    }

    for(int i = 0;i<2;i++)
    {
        if(!bossLaser[i].bulletFree)
        {
            bossLaser[i].bulletRect.moveTo(bossLaser[i].x,bossLaser[i].y);

            if(stoptime<=150)
                bossLaser[i].bulletFree=true;
        }
    }
   //注：20ms刷新一次子弹
}
void EnemyBoss::move()
{
    //入场时
    if(y<20)
        y+=enemySpeed_y;
    else if(y>=20)
    {
        //每转向两次之后居中停一会儿
        if(changeNum%2==0&&stoptime!=0&&x>=(700-enemyRect.width())/2-10&&x<=(700-enemyRect.width())/2+10)
        {
            stoptime--;
            return;
        }
        else if(changeNum%2!=0&&stoptime<=0)
            stoptime=250; //重新装填驻足时间

       //到达指定位置之后，y不动,开始左右摆动
        if(enemyDirection)//为真右移
            x+=enemySpeed_x;
        else
            x-=enemySpeed_x;

        //到达边界开始转向
        if(x<=25||x>=375)
        {
            enemyDirection=!enemyDirection; //方向取反
            changeNum++;
        }

        enemyRect.moveTo(x,y);
    }
     enemyRect.moveTo(x,y);
}
