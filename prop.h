#ifndef PROP_H
#define PROP_H
#define PROPSPEEDX 1
#define PROPSPEEDY 1
#include<QPixmap>
#include<QRect>

class Prop
{
public:
    Prop();
    QPixmap propPix;        //道具图片
    QRect propRect;         //道具外框
    int x;
    int y;                  //坐标
    bool propDirection;     //道具移动，为真则右移
    bool propFree;          //道具状态
};

class BulletProp:public Prop
{
public:
    BulletProp();
    void effect(bool& );
    void updatePosition();
};

#endif // PROP_H
