#include "bomb.h"

Bomb::Bomb()
{
    //初始化爆炸图片数组，16张图
    for(int i=1;i<=16;i++)
    {
        //字符串拼接
        QString str=QString(":/photo/21_bomb_%1.png").arg(i);

        //将路径下的图片存入数组
        pix.push_back(QPixmap(str));
    }

    //初始化坐标
    x=0;
    y=0;

    //初始化爆炸状态
    bombFree=true;

    //当前播放图片下标
    index=0;

    //爆炸记录
    bombRecord=0;
}

void Bomb::updateInformation()
{
    //空闲状态
    if(bombFree)
        return;
    bombRecord++;

    //暂定爆炸时间间隔为2
    if(bombRecord<2)
    {
        //记录爆炸间隔未到
        return ;
    }

    //到了2之后

    //重置记录
    bombRecord=0;

    //切换播放爆炸图片
    index++;

    //爆炸一共有16张图
    if(index>15)
    {
        index=0;
        //一次爆炸完成,更改状态
        bombFree=true;
    }

}
