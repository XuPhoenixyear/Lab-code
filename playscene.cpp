#include "playscene.h"
 PlayScene::PlayScene(int index)
 {
     qDebug()<<"打开了第"<<index<<"关";

     //设置鼠标追踪
      this->setMouseTracking(true);

     //设置固定大小
     this->setFixedSize(700,850);

     //设置标题
     this->setWindowTitle("飞机大战");

     //设置图片
     this->setWindowIcon(QIcon(":/photo/07.png"));

     //设置键盘焦点
     this->setFocusPolicy(Qt::StrongFocus);

     //创建菜单栏
     QMenuBar* bar = menuBar();
     this->setMenuBar(bar);

     //创建开始菜单
     QMenu* startMenu = bar->addMenu("开始");

     //创建菜单项
     QAction* quitAction = startMenu->addAction("退出");

     //初始化游戏时间
     playtime=0;

     //点击退出按钮 实现退出游戏
     connect(quitAction,&QAction::triggered,[=](){
         this->close();
     });


//设置地图滚动

     //初始化两张地图对象
     map1.load(":/photo/06.png");
     map2.load(":/photo/06.png");

     //设置起始地图位置
     map1Position_y=-this->height();
     map2Position_y=0;

     //设置地图滚动速度
     mapScrollSpeed=1;




//添加英雄飞机
     hero.planePix.load(":/photo/13.png");
     hero.px=this->width()*0.5-10;
     hero.py=this->height()-200;


//初始化敌机
     enemyRecord=0;

     //设置随机数种子
     srand((unsigned int)time(NULL));

//boss出场之后，停止刷新小飞机，场内最终只留BOOS
//游戏开始后一定时间开始出boss
//boss有一定的行进规律和攻击方式
//击杀完boss后通关

//初始化积分
     for(int i = 0;i<8;i++)
         score[i]=0;
     for(int i=0;i<10;i++)
     {
         QString str = QString(":/photo/22_num_%1.png").arg(i);
         scorePix[i].load(str);
     }

//刷新道具
     bltProp.propFree = false;

//定时器刷新场景
     //设置定时器间隔
     mTimer.setInterval(20); //20ms
     playTimeTimer.setInterval(1000);//1s

     //启动定时器
     mTimer.start();
     playTimeTimer.start();


     //监听定时器实现地图滚动
     connect(&mTimer,&QTimer::timeout,[=](){

         //更新场景
         updatePosition();

         //重新绘制场景
         update();

         //碰撞检测
         collisionDetection();

         //更新得分
         updateScore();
     });

     //统计游戏时间,到时间开始打boss
     connect(&playTimeTimer,&QTimer::timeout,[=](){
         playtime++; //游戏时间计数

         if(playtime%40==0)
         {
             bltProp.propFree = false;
         }
         if(playtime>=BOSSTIME)
             qDebug()<<"游戏进行了"<<playtime<<"s";
     });
 }

 void PlayScene::mapPosition(int wHeight)
 {
     //设置第一章图片滚动
     map1Position_y+=mapScrollSpeed;
     if(map1Position_y>=0)
     {
         map1Position_y=-wHeight;
     }

     //设置第二章图片滚动
     map2Position_y+=mapScrollSpeed;
     if(map2Position_y>=wHeight)
     {
         map2Position_y=0;
     }

 }

void PlayScene::paintEvent(QPaintEvent* )
{
     QPainter painter(this);

     //绘制地图
     painter.drawPixmap(0,map1Position_y,this->width(),this->height(),map1);
     painter.drawPixmap(0,map2Position_y,this->width(),this->height(),map2);

     //绘制英雄飞机
     if(!hero.heroFree)
     {
         painter.drawPixmap(hero.px,hero.py,60,60,hero.planePix);
//         painter.drawRect(hero.planeRect);
     }

     //绘制道具
     if(!bltProp.propFree)
     {
         painter.drawPixmap(bltProp.x,bltProp.y,30,30,bltProp.propPix);
     }


     //绘制子弹
     for(int i=0;i<50;i++)
     {
         //绘制初始弹夹子弹
         if(!hero.blt[i].bulletFree)
         {
             painter.drawPixmap(hero.blt[i].x,hero.blt[i].y,7,25,hero.blt[i].bulletPix);
 //            painter.drawRect(hero.blt[i].bulletRect);
         }
         //绘制2号弹夹子弹?
         if(hero.ifBltMore1)
         {
             if(!hero.blt2[i].bulletFree)
             {
                 painter.drawPixmap(hero.blt2[i].x,hero.blt2[i].y,7,25,hero.blt2[i].bulletPix);
 //                painter.drawRect(hero.blt2[i].bulletRect);
             }
         }

         //绘制3号弹夹子弹?
         if(hero.ifBltMore2)
         {
             if(!hero.blt3[i].bulletFree)
             {
                 painter.drawPixmap(hero.blt3[i].x,hero.blt3[i].y,7,25,hero.blt3[i].bulletPix);
   //              painter.drawRect(hero.blt3[i].bulletRect);
             }
         }

//         if(hero.ifBltMore3)
//         {
//             //绘制4号弹夹子弹?
//             if(!hero.blt4[i].bulletFree)
//             {
//                 painter.drawPixmap(hero.blt4[i].x,hero.blt4[i].y,7,25,hero.blt4[i].bulletPix);
//                 painter.drawRect(hero.blt4[i].bulletRect);
//             }
//             //绘制5号弹夹子弹?
//             if(!hero.blt5[i].bulletFree)
//             {
//                 painter.drawPixmap(hero.blt5[i].x,hero.blt5[i].y,7,25,hero.blt5[i].bulletPix);
//                 painter.drawRect(hero.blt5[i].bulletRect);
//             }
//         }

     }

     //绘制敌机
     for(int i = 0;i<20;i++)
     {
         if(!enemy[i].enemyFree)
         {
             painter.drawPixmap(enemy[i].x,enemy[i].y,60,60,enemy[i].enemyPix);
 //            painter.drawRect(enemy[i].enemyRect);
         }
         for(int j=0;j<10;j++)
         {
             if(!enemy[i].blt[j].bulletFree)               
             {
                 painter.drawPixmap(enemy[i].blt[j].x,enemy[i].blt[j].y,10,10,enemy[i].blt[j].bulletPix);
   //              painter.drawRect(enemy[i].blt[j].bulletRect);
             }
         }
     }

     //绘制boss
     if(!boss.enemyFree)
     {
         painter.drawPixmap(boss.x,boss.y,300,250,boss.enemyPix);
  //       painter.drawRect(boss.enemyRect);
         for(int i=0;i<BOSSBLTNUM;i++)
            if(!boss.bossBlt[i].bulletFree)               
            {
                painter.drawPixmap(boss.bossBlt[i].x,boss.bossBlt[i].y,45,45,boss.bossBlt[i].bulletPix);
    //            painter.drawRect(boss.bossBlt[i].bulletRect);
            }
         for(int i=0;i<BOSSBLTNUM2;i++)
             if(!boss.bossBlt2[i].bulletFree)
             {
                 painter.drawPixmap(boss.bossBlt2[i].x,boss.bossBlt2[i].y,20,20,boss.bossBlt2[i].bulletPix);
   //              painter.drawRect(boss.bossBlt2[i].bulletRect);
             }
         for(int i=0;i<2;i++)
             if(!boss.bossLaser[i].bulletFree)
             {
                 painter.drawPixmap(boss.bossLaser[i].x,boss.bossLaser[i].y,20,600,boss.bossLaser[i].bulletPix);
  //               painter.drawRect(boss.bossLaser[i].bulletRect);
             }
     }
     //绘制爆炸
     for(int i=0;i<20;i++)
     {
         if(!bombs[i].bombFree)
             painter.drawPixmap(bombs[i].x,bombs[i].y,45,45,bombs[i].pix[bombs[i].index]);
     }

     //绘制得分
     for(int i =0;i<8;i++)
         painter.drawPixmap(670-(i*30),30,30,30,scorePix[score[i]]);
}

 void PlayScene::keyPressEvent(QKeyEvent* e)
 {

     static int n = 0;
     //空格键发射子弹
     if(e->key()==Qt::Key_Space&&e->isAutoRepeat()==false)
     {
         hero.shoot();
     }
     else if(e->key()==Qt::Key_Space&&e->isAutoRepeat()==true)
     {
         //降低长按时子弹发射频率
         n++;

//       qDebug()<<"n = "<<n;

         if(n%7==0)
         {
             n=0;
             hero.shoot();
         }
     }
     else if(e->key()==Qt::Key_Q)
     {
         mTimer.stop();
         playTimeTimer.stop();
     }
     else if(e->key()==Qt::Key_R)
     {
         mTimer.start();
         playTimeTimer.start();
     }


 }

 void PlayScene::mouseMoveEvent(QMouseEvent* ev)
 {
      //边界为 -20~660 , 20~810 (700*850)

     if(ev->x()<20)
     {
         hero.px=-20;
         hero.planeRect.moveTo(ev->x()-15,ev->y());
     }
     if(ev->x()>660)
     {
         hero.px=660;
         hero.planeRect.moveTo(ev->x()-15,ev->y());
     }
     if(ev->y()>810)
     {
         hero.py=810;
         hero.planeRect.moveTo(ev->x()-15,ev->y());
     }
     if(ev->y()<20)
     {
         hero.py=-20;
         hero.planeRect.moveTo(ev->x()-15,ev->y());
     }
     if(ev->x()>=20&&ev->x()<=660)
     {
         hero.px=ev->x()-30;
         hero.planeRect.moveTo(ev->x()-15,ev->y());
     }
     if(ev->y()>=20&&ev->y()<=810)
     {
         hero.py=ev->y()-30;
         hero.planeRect.moveTo(ev->x()-15,ev->y());
     }
 }

 void PlayScene::enemyToScene()
 {
     enemyRecord++;

     //出场记录没过20直接退出
     if(enemyRecord<20)
     {
         return ;
     }

     //出场记录超过了20再次置0
     enemyRecord=0;

     //boss抵达战场之前放小飞机
     if(playtime < BOSSTIME||boss.arouse==true)
     {
         for(int i= 0;i<20;i++)
         {
             //如果敌机空闲，置为出场
             if(enemy[i].enemyFree)
             {
                 enemy[i].enemyFree=false;

                 //定时器开始工作
                 enemy[i].enemyTimer.start();

                 //设置定时间隔:1.5s,对于每个飞机而言，每1.5秒发射一颗子弹
                 enemy[i].enemyTimer.setInterval(2000);

                 connect(&enemy[i].enemyTimer,&QTimer::timeout,[=](){
                     enemy[i].updateBulletAngle(hero.px,hero.py);
                     enemy[i].shoot();
                 });

                 //设置敌机坐标
                 enemy[i].x = rand()%(700-enemy->enemyRect.width()); //随机数值 模 主界面剩余宽度
                 enemy[i].y = -enemy->enemyRect.height();
//               qDebug()<<"敌机出现在："<<enemy[i].x;
                 break;
             }
         }
     }
     else if(playtime == BOSSTIME&&boss.enemyFree)//考虑到小飞机全部离场需要时间   //小心多次连接,导致重复调用
     {
         boss.enemyFree=false;

         //设置boss坐标
         boss.x=(700-boss.enemyRect.width())/2;
         boss.y=-boss.enemyRect.height();

         boss.enemyRect.moveTo(boss.x,boss.y);

         //启动boss定时器
         boss.enemyTimer.setInterval(1000);//1s发一次子弹
         boss.enemyTimer.start();
         connect(&boss.enemyTimer,&QTimer::timeout,[=](){
             boss.shoot();
//           qDebug()<<"boss shoot";
         });

     }
 }

 bool PlayScene::ifKillingEnemy(Bullet* blt,EnemyPlane* enemy)
 {
     for(int j =0;j<50;j++)
     {
         //空闲的子弹(未显示)跳过
         if(blt[j].bulletFree)
         {
             continue;
         }
         //已经显示的飞机和子弹的矩形边框发生交互则同时消除两者
         //发生爆炸
         //普通敌人得100分,score[2]加1，表示+100
         if(enemy->enemyRect.intersects(hero.blt[j].bulletRect))
         {
             enemy->enemyFree=true;
             blt[j].bulletFree=true;

             //得分增加100
             score[2]++;

             //爆炸效果
             for(int k =0;k<20;k++)
             {
                 if(bombs[k].bombFree)
                 {
                     bombs[k].bombFree=false;

                     //设置爆炸坐标
                     bombs[k].x=enemy->x;
                     bombs[k].y=enemy->y;

                     enemy->enemyTimer.stop();
                     enemy->enemyTimer.disconnect();

                     //20个空闲爆炸效果里有一个能发生即可
                     break;
                 }
             }
             //该子弹击毁敌人，不必检测剩下子弹
             return true;
         }
     }
     return false;
 }
 //碰撞检测函数
 void PlayScene::collisionDetection()
 {
//英雄击毁敌机检测
     //对所有弹夹进行检测

     if(!hero.ifBltMore1)
     {
         for(int i = 0;i<20;i++)
         {
             if(enemy[i].enemyFree)
                 continue;
             ifKillingEnemy(hero.blt,&enemy[i]);
         }
     }
     else if(hero.ifBltMore1&&!hero.ifBltMore2)
     {
         for(int i = 0;i<20;i++)
         {
             if(enemy[i].enemyFree)
                 continue;
             if(!ifKillingEnemy(hero.blt2,&enemy[i]))
                 ifKillingEnemy(hero.blt,&enemy[i]);
         }
     }
     else if(hero.ifBltMore1&&hero.ifBltMore2)
     {
         for(int i = 0;i<20;i++)
         {
             if(enemy[i].enemyFree)
                 continue;
             if(!ifKillingEnemy(hero.blt3,&enemy[i]))
                 if(!ifKillingEnemy(hero.blt2,&enemy[i]))
                     ifKillingEnemy(hero.blt,&enemy[i]);
         }
     }
//     else if(hero.ifBltMore1&&hero.ifBltMore2&&hero.ifBltMore3)
//     {
//         for(int i=0;i<20;i++)
//         {
//             if(enemy[i].enemyFree)
//                 continue;

//             if(!ifKillingEnemy(hero.blt5,&enemy[i]))
//               if(!ifKillingEnemy(hero.blt4,&enemy[i]))
//                    if(!ifKillingEnemy(hero.blt3,&enemy[i]))
//                        if(!ifKillingEnemy(hero.blt2,&enemy[i]))
//                            ifKillingEnemy(hero.blt,&enemy[i]);
//         }
//     }


     //boss检测
     if(!boss.enemyFree)
     {
         //boss出现
         if(!hero.ifBltMore1) //只有初始弹夹
         {
             for(int i=0;i<50;i++)
             {
                 //未显示的子弹跳过
                 if(hero.blt[i].bulletFree)
                     continue;

                 heroAttackBoss(&hero.blt[i]);
                 if(boss.blood==0)
                     break;
             }//for循环尾
         }
         else if(hero.ifBltMore1&&!hero.ifBltMore2)
         {
             //开了2号弹夹
             for(int i =0;i<50;i++)
             {
                 if(hero.blt[i].bulletFree&&hero.blt2[i].bulletFree)
                     continue;
                 if(!hero.blt[i].bulletFree)
                 {
                     heroAttackBoss(&hero.blt2[i]);
                     if(boss.blood==0)
                         break;
                 }
                 if(!hero.blt2[i].bulletFree)
                 {
                     heroAttackBoss(&hero.blt[i]);
                     if(boss.blood==0)
                         break;
                 }
             }
         }
         else if(hero.ifBltMore1&&hero.ifBltMore2)
         {
             for(int i = 0; i<50;i++)
             {
                 if(hero.blt[i].bulletFree&&hero.blt2[i].bulletFree&&hero.blt3[i].bulletFree)
                     continue;
                 if(!hero.blt[i].bulletFree)
                 {
                     heroAttackBoss(&hero.blt3[i]);
                     if(boss.blood==0)
                         break;
                 }
                 if(!hero.blt2[i].bulletFree)
                 {
                     heroAttackBoss(&hero.blt2[i]);
                     if(boss.blood==0)
                         break;
                 }
                 if(!hero.blt3[i].bulletFree)
                 {
                     heroAttackBoss(&hero.blt[i]);
                     if(boss.blood==0)
                         break;
                 }
             }

         }
//         else if(hero.ifBltMore1&&hero.ifBltMore2&&hero.ifBltMore3)
//         {
//             for(int i = 0; i<50;i++)
//             {
//                 if(hero.blt[i].bulletFree&&hero.blt2[i].bulletFree&&hero.blt3[i].bulletFree&&hero.blt4[i].bulletFree&&hero.blt5[i].bulletFree)
//                     continue;
//                 if(!hero.blt[i].bulletFree)
//                     heroAttackBoss(&hero.blt[i]);
//                 if(!hero.blt2[i].bulletFree)
//                     heroAttackBoss(&hero.blt2[i]);
//                 if(!hero.blt3[i].bulletFree)
//                     heroAttackBoss(&hero.blt3[i]);
//                 if(!hero.blt4[i].bulletFree)
//                     heroAttackBoss(&hero.blt4[i]);
//                 if(!hero.blt5[i].bulletFree)
//                     heroAttackBoss(&hero.blt5[i]);

//             }
//         }
         //空血boss炸
         if(boss.blood==0)
         {

             boss.enemyFree = true;

             //击杀boss再得20000分,score[4]万位加2
             score[4]+=2;

             //爆炸效果
             for(int k =0;k<20;k++)
             {
                 if(bombs[k].bombFree)
                 {
                     bombs[k].bombFree=false;

                     //设置爆炸坐标
                     bombs[k].x=boss.x+(boss.enemyRect.width())/2;
                     bombs[k].y=boss.y+(boss.enemyRect.height())/2;

                     //boss死亡关闭定时器，断开连接
                     boss.enemyTimer.stop();
                     boss.enemyTimer.disconnect();

                     //20个空闲爆炸效果里有一个能发生即可
                     break;
                 }
             }

             //获胜对话框
             QDialog* note = new QDialog(this);
             note->resize(200,200);
             note->setAttribute(Qt::WA_DeleteOnClose);
             QLabel* noteLabel = new QLabel(note);
             noteLabel->setText("Victory!");
             QLabel* noteScore = new QLabel(note);
             int finalScore = (((((((score[7]*10+score[6])*10+score[5])*10)+score[4])*10+score[3])*10+score[2])*10+score[1])*10+score[0];
             QString str = QString("您的得分为:%1").arg(finalScore);
             noteScore->setText(str);
             noteScore->move(50,70);
             QPushButton* noteBtn = new QPushButton(note);
             noteBtn->setText("确 定");
             noteBtn->move(50,120);
             noteLabel->move(70,30);
             connect(noteBtn,&QPushButton::clicked,[=](){

                 emit this->sceneBack();
                 note->close();

             });
             note->exec();

           }

     }//boss检测尾

//hero死亡?
     if(!hero.heroFree)
     {
         for(int i=0;i<20;i++)
         {
             if(enemy[i].enemyFree)
                 continue;

             if(enemy[i].enemyRect.intersects(hero.planeRect))
             {
                 hero.life=0;

                 enemy[i].enemyFree = true;
                 hero.heroFree=true;

                 //爆炸效果
                 for(int k =0;k<20;k++)
                 {
                     if(bombs[k].bombFree)
                     {
                         bombs[k].bombFree=false;

                         //设置爆炸坐标
                         bombs[k].x=hero.px+30;
                         bombs[k].y=hero.py+30;

                         //20个空闲爆炸效果里有一个能发生即可
                         break;
                     }
                 }

                 break;
             }
             for(int j = 0;j<10;j++)
             {
                 if(enemy[i].blt[j].bulletRect.intersects(hero.planeRect))
                 {
                    hero.life=0;

                    enemy[i].blt[j].bulletFree = true;
                    hero.heroFree=true;

                    //爆炸效果
                    for(int k =0;k<20;k++)
                    {
                        if(bombs[k].bombFree)
                        {
                            bombs[k].bombFree=false;

                            //设置爆炸坐标
                            bombs[k].x=hero.px+30;
                            bombs[k].y=hero.py+30;

                            //20个空闲爆炸效果里有一个能发生即可
                            break;
                        }
                    }

                    break;
                 }
             }

         }
         if(!boss.enemyFree)
         {
             if(boss.enemyRect.intersects(hero.planeRect))
             {
                 hero.life=0;

                 hero.heroFree=true;

                 //爆炸效果
                 for(int k =0;k<20;k++)
                 {
                     if(bombs[k].bombFree)
                     {
                         bombs[k].bombFree=false;

                         //设置爆炸坐标
                         bombs[k].x=hero.px+30;
                         bombs[k].y=hero.py+30;

                         //20个空闲爆炸效果里有一个能发生即可
                         break;
                     }
                 }
             }
             for(int i=0;i<BOSSBLTNUM;i++)
             {
                 if(boss.bossBlt[i].bulletFree)
                     continue;
                 if(boss.bossBlt[i].bulletRect.intersects(hero.planeRect))
                 {
                     hero.life=0;

                     hero.heroFree=true;

                     //爆炸效果
                     for(int k =0;k<20;k++)
                     {
                         if(bombs[k].bombFree)
                         {
                             bombs[k].bombFree=false;

                             //设置爆炸坐标
                             bombs[k].x=hero.px+30;
                             bombs[k].y=hero.py+30;

                             //20个空闲爆炸效果里有一个能发生即可
                             break;
                         }
                     }

                     break;
                 }
             }
             for(int i=0;i<BOSSBLTNUM2;i++)
             {
                 if(boss.bossBlt2[i].bulletFree)
                     continue;
                 if(boss.bossBlt2[i].bulletRect.intersects(hero.planeRect))
                 {
                     hero.life=0;

                     hero.heroFree=true;

                     //爆炸效果
                     for(int k =0;k<20;k++)
                     {
                         if(bombs[k].bombFree)
                         {
                             bombs[k].bombFree=false;

                             //设置爆炸坐标
                             bombs[k].x=hero.px+30;
                             bombs[k].y=hero.py+30;

                             //20个空闲爆炸效果里有一个能发生即可
                             break;
                         }
                     }
                     break;
                 }
             }
             for(int i=0;i<2;i++)
             {
                 if(boss.bossLaser[i].bulletFree)
                     continue;
                 if(boss.bossLaser[i].bulletRect.intersects(hero.planeRect))
                 {
                     hero.life=0;

                     hero.heroFree=true;

                     //爆炸效果
                     for(int k =0;k<20;k++)
                     {
                         if(bombs[k].bombFree)
                         {
                             bombs[k].bombFree=false;

                             //设置爆炸坐标
                             bombs[k].x=hero.px+30;
                             bombs[k].y=hero.py+30;

                             //20个空闲爆炸效果里有一个能发生即可
                             break;
                         }
                     }

                     break;
                 }
             }
         }
     }

     if(hero.life==0)
     {
         //死亡弹出对话框
         QDialog* note = new QDialog(this);
         note->resize(200,200);
         note->setAttribute(Qt::WA_DeleteOnClose);
         QLabel* noteLabel = new QLabel(note);
         noteLabel->setText("Defeat!");
         QLabel* noteScore = new QLabel(note);
         int finalScore = (((((((score[7]*10+score[6])*10+score[5])*10)+score[4])*10+score[3])*10+score[2])*10+score[1])*10+score[0];
         QString str = QString("您的得分为:%1").arg(finalScore);
         noteScore->setText(str);
         noteScore->move(50,70);
         QPushButton* noteBtn = new QPushButton(note);
         noteBtn->setText("确 定");
         noteBtn->move(50,120);
         noteLabel->move(70,30);
         connect(noteBtn,&QPushButton::clicked,[=](){

             emit this->sceneBack();
             note->close();

         });
         note->exec();
     }

//道具拾取判断
     if(!bltProp.propFree)
     {
         if(!hero.ifBltMore1)
         {
             if(hero.planeRect.intersects(bltProp.propRect))
             {
                 bltProp.propFree = true;
                 bltProp.effect(hero.ifBltMore1);
                 bltProp.x = rand()%500+100;
                 bltProp.y = 30;
             }
         }
         else if(hero.ifBltMore1&&!hero.ifBltMore2)
         {
             if(hero.planeRect.intersects(bltProp.propRect))
             {
                 bltProp.propFree = true;
                 bltProp.effect(hero.ifBltMore2);
                 bltProp.x = rand()%500+100;
                 bltProp.y = 30;
             }
         }
         else if(hero.ifBltMore1&&hero.ifBltMore2)
         {
             if(hero.planeRect.intersects(bltProp.propRect))
             {
                 bltProp.propFree = true;
                 score[3]+=1;
                 bltProp.x = rand()%500+100;
                 bltProp.y = 30;
             }
         }
     }
 }
void PlayScene::heroAttackBoss(Bullet* blt)
{
    //显示的子弹与boss接触发生爆炸
    if(boss.enemyRect.intersects(blt->bulletRect)&&!blt->bulletFree)
    {
        //一发子弹一滴血
        boss.blood--;

        //一发子弹打中了加50,score[1]+=5，表示+50
        score[1]+=5;

        //子弹击中也有爆炸效果且子弹消失
         blt->bulletFree=true;

        //爆炸效果
        for(int k =0;k<20;k++)
        {
            if(bombs[k].bombFree)
            {
                bombs[k].bombFree=false;

                //设置爆炸坐标
                bombs[k].x=blt->x+1;
                bombs[k].y=boss.y+boss.enemyRect.height()/2;

                //20个空闲爆炸效果里有一个能发生即可
                break;
            }
        }

    }//子弹与矩形边框是否相交的判断尾
}
void PlayScene::updatePosition()
{
    for(int i=0;i<20;i++)
    {
       enemy[i].updateBulletAngle(hero.px,hero.py);
    }

    //敌机出场
    enemyToScene();

    //重新设置地图位置
    mapPosition(this->height());

    //重新计算英雄子弹
    hero.updateBullet();

    //重新计算敌机坐标和敌机子弹
    for(int i =0;i<20;i++)
    {
        if(!enemy[i].enemyFree)
        {
            //空闲状态不计算坐标
            if(enemy[i].enemyFree)
                return;
            //为真则横坐标正移动
            if(enemy[i].enemyDirection)
            {
                enemy[i].x+=enemy[i].enemySpeed_x;
            }
            else
                enemy[i].x-=enemy[i].enemySpeed_x;

            enemy[i].y+=enemy[i].enemySpeed_y;

            enemy[i].enemyRect.moveTo(enemy[i].x,enemy[i].y);

            if(enemy[i].y-enemy[i].enemyRect.height()>=850||enemy[i].x+enemy[i].enemyRect.width()<0||enemy[i].x>700)
            {
                enemy[i].enemyFree=true;
                enemy[i].enemyTimer.stop();
                enemy[i].enemyTimer.disconnect();
            }
        }

        enemy[i].updateBullet();
    }


    //重新计算boss坐标
    if(!boss.enemyFree)
    {
        boss.move();

        //重新计算boss子弹坐标
        boss.updateBullet();
    }

    //重新计算爆炸图片
    for(int i=0;i<20;i++)
    {
        if(!bombs[i].bombFree)
            bombs[i].updateInformation();
    }

    bltProp.updatePosition();

}
void PlayScene::updateScore()
{
    //score[8]，第一位score[0]代表得分的 个位
    for(int i=0;i<8;i++)
    {
        if(score[i]>9&&i<7)
        {
            score[i]-=10;
            score[i+1]+=1;
        }
        else if(i==7&&score[7]>9)
        {
            for(int j=0;j<8;j++)
                score[j]=9;      //8位数都变成9，代表最大值
        }
    }
}
