#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<mypushbutton.h>
#include<playscene.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置 应用窗口固定大小
    this->setFixedSize(700,850);

    //设置应用图片
    this->setWindowIcon(QPixmap(":/photo/07.png"));

    //设置应用标题
    this->setWindowTitle("飞机大战");

    //开始按钮的创建
    MyPushButton* startBtn = new MyPushButton(":/photo/11(1).png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5-10,this->height()*0.5);

    //退出按钮
    MyPushButton* exitBtn = new MyPushButton(":/photo/12.png");
    exitBtn->setParent(this);
    exitBtn->move(this->width()*0.5-exitBtn->width()*0.5-10,this->height()*0.5+100);

    //开始按钮弹起动画实现
    connect(startBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点了开始按钮";
        startBtn->zoomDown();
        startBtn->zoomUp();

         //开始游戏后进入游戏场景

        //隐藏自身
        this->hide();

        //显示游戏场景
        PlayScene* playScene = new PlayScene(1);
        playScene->show();

        //监听
        connect(playScene,&PlayScene::sceneBack,[=](){

            playScene->mTimer.stop();
            playScene->playTimeTimer.stop();

            playScene->close();
            this->show();
        });
    });

    //退出按钮点击退出程序
    connect(exitBtn,&QPushButton::clicked,[=](){
        qDebug()<<"点了退出按钮";
        this->MainWindow::close();
    });




}

void MainWindow:: paintEvent(QPaintEvent* )
{
    //画家画背景
    QPainter painter(this);

    QPixmap pix;
    pix.load(":/photo/09.png");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);


    //设置大标题
    pix.load(":/photo/19.png");

    painter.drawPixmap(100,75,500,300,pix);

}


MainWindow::~MainWindow()
{
    delete ui;
}

