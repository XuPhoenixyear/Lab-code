#ifndef BOMB_H
#define BOMB_H
#include<QVector>
#include<QPixmap>
#include<QString>

class Bomb
{
public:
    Bomb();

    //爆炸资源数组
    QVector<QPixmap>pix;

    //爆炸位置
    int x;
    int y;

    //爆炸状态
    bool bombFree;

    //爆炸切图记录
    int bombRecord;

    //爆炸时加载的图片下标
    int index;

    //更新信息（播放图片、刷新间隔）
    void updateInformation();


};

#endif // BOMB_H
