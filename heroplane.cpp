#include "heroplane.h"

HeroPlane::HeroPlane()
{
    life=1;

    //设置矩形边框大小
    planeRect.setWidth(30);
    planeRect.setHeight(30);
    planeRect.moveTo(px+15,py+30);

    for(int i=0;i<50;i++)
    {
        blt[i].bulletFree=true;
        blt2[i].bulletFree=true;
        blt3[i].bulletFree=true;
        blt4[i].bulletFree=true;
        blt5[i].bulletFree=true;
    }

    heroTimer.setInterval(1);//1ms

    heroFree=false;

    //设置2、3、4、5弹夹状态
    ifBltMore1=false;  //false表示不启用
    ifBltMore2=false;
//    ifBltMore3=false;

}

//发射子弹
void HeroPlane::shoot()
{
    for(int i=0;i<50;i++)
    {
        if(blt[i].bulletFree)
        {
            blt[i].bulletFree=false;
            blt[i].x=px+27; //中间位置
            blt[i].y=py;
            break;
        }
    }
    if(ifBltMore1)
    {
        for(int i = 0;i<50;i++)
        {
            if(blt2[i].bulletFree) //2号弹夹启用
            {
                blt2[i].bulletFree=false;
                blt2[i].x=px+15; //中间靠左位置
                blt2[i].y=py;
                break;
            }
        }
    }
    if(ifBltMore2)
    {
        for(int i = 0;i<50;i++)
        {
            if(blt3[i].bulletFree) //3号弹夹启用
            {
                blt3[i].bulletFree=false;
                blt3[i].x=px+39; //中间靠左位置
                blt3[i].y=py;
                break;
            }
        }
    }
//    if(ifBltMore3)
//    {
//        for(int i = 0;i<50;i++)
//        {
//            if(blt4[i].bulletFree) //4号弹夹启用
//            {
//                blt4[i].bulletFree=false;
//                blt4[i].x=px+3; //中间靠左位置
//                blt4[i].y=py;
//                break;
//            }
//        }
//        for(int i = 0;i<50;i++)
//        {
//            if(blt5[i].bulletFree) //5号弹夹启用
//            {
//                blt5[i].bulletFree=false;
//                blt5[i].x=px+51; //中间靠左位置
//                blt5[i].y=py;
//                break;
//            }
//        }
//    }
}

//更新子弹坐标
void HeroPlane::updateBullet()
{
    for(int i=0;i<50;i++)
    {
        //初始弹夹
        if(!blt[i].bulletFree)
        {
            blt[i].y-=20;
            blt[i].bulletRect.moveTo(blt[i].x,blt[i].y);
            if(blt[i].y<=-20)
            {
                blt[i].bulletFree=true;
            }
        }

        if(ifBltMore1)
        {
            //2号弹夹
            if(!blt2[i].bulletFree)
            {
                blt2[i].y-=20;
                blt2[i].bulletRect.moveTo(blt2[i].x,blt2[i].y);
                if(blt2[i].y<=-20)
                {
                    blt2[i].bulletFree=true;
                }
            }
        }


        if(ifBltMore2)
        {
            //3号弹夹
            if(!blt3[i].bulletFree)
            {
                blt3[i].y-=20;
                blt3[i].bulletRect.moveTo(blt3[i].x,blt3[i].y);
                if(blt3[i].y<=-20)
                {
                    blt3[i].bulletFree=true;
                }
            }
        }


//        if(ifBltMore3)
//        {
//            //4号弹夹
//            if(!blt4[i].bulletFree)
//            {
//                blt4[i].y-=20;
//                blt4[i].bulletRect.moveTo(blt4[i].x,blt4[i].y);
//                if(blt4[i].y<=-20)
//                {
//                    blt4[i].bulletFree=true;
//                }
//            }

//            //5号弹夹
//            if(!blt5[i].bulletFree)
//            {
//                blt5[i].y-=20;
//                blt5[i].bulletRect.moveTo(blt5[i].x,blt5[i].y);
//                if(blt5[i].y<=-20)
//                {
//                    blt5[i].bulletFree=true;
//                }
//            }
//        }

    }

}

