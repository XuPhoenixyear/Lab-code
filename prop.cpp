#include "prop.h"

Prop::Prop()
{

}

BulletProp::BulletProp()
{
    x=rand()%500+100; //100~600
    y=30;

    propFree = true;

    if(rand()%2==1)
        propDirection=true;
    else
        propDirection=false;

    propPix.load(":/photo/26_BulletProp.png");
    propRect.setWidth(30);
    propRect.setHeight(30);
    propRect.moveTo(x,y);
}
void BulletProp::effect(bool& ifBltMore)
{
    ifBltMore = true;
}
void BulletProp::updatePosition()
{
    if(y<850&&!propFree)
    {
        if(propDirection)
        {
            x+=PROPSPEEDX;
            y+=PROPSPEEDY;
        }
        else
        {
            x-=PROPSPEEDX;
            y+=PROPSPEEDY;
        }

        //到达边界方向取反
        if(x<=25||x>=675)
            propDirection = !propDirection;

        propRect.moveTo(x,y);
    }
    else if(y>850)
    {
        propFree = true;
        y=30;
        x=rand()%500+100;
    }
}
