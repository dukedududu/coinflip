#include "mycoin.h"
#include<QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{
//
//}
 MyCoin::MyCoin(QString btnImg)
 {
     QPixmap pix;
     bool ret=pix.load(btnImg);
     if(!ret)//判断是否加载成功
     {
         qDebug()<<"加载图片失败";
         return;
     }
     //设置图片固定大小
     this->setFixedSize(pix.width(),pix.height());
     //设置不规则图片样式
     this->setStyleSheet("QPushButton{border:0px}");
     //设置图标
     this->setIcon(pix);
     //设置图标大小
     this->setIconSize(QSize(pix.width(),pix.height()));
     time1 = new QTimer(this);
     time2 = new QTimer(this);
     //监听信号 并且实现正面翻转成反面
     connect(time1,&QTimer::timeout,[=](){
         QPixmap pix;
         QString str=QString(":/res/Coin000%1.png").arg(this->min++);
         pix.load(str);
         //设置图片固定大小
         this->setFixedSize(pix.width(),pix.height());
         //设置不规则图片样式
         this->setStyleSheet("QPushButton{border:0px}");
         //设置图标
         this->setIcon(pix);
         //设置图标大小
         this->setIconSize(QSize(pix.width(),pix.height()));
         //判断翻完了重置
         if(this->min>this->max)
         {
             this->min=1;
             isanimation=false;
             time1->stop();
         }


     });
     connect(time2,&QTimer::timeout,[=](){
         QPixmap pix;
         QString str=QString(":/res/Coin000%1.png").arg(this->max--);
         pix.load(str);
         //设置图片固定大小
         this->setFixedSize(pix.width(),pix.height());
         //设置不规则图片样式
         this->setStyleSheet("QPushButton{border:0px}");
         //设置图标
         this->setIcon(pix);
         //设置图标大小
         this->setIconSize(QSize(pix.width(),pix.height()));
         //判断翻完了重置
         if(this->max<this->min)
         {
             this->max=8;
             isanimation=false;
             time2->stop();
         }


     });
 }
 void MyCoin::mousePressEvent(QMouseEvent * e)//为了优化翻币效果
 {
    if(this->isanimation||this->iswin)//胜利了就不能再点击coinbtn
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
 }


void  MyCoin::changeflag()
{
    if(this->flag)//如果是正面
    {
        time1->start(30);//正翻反定时器
        isanimation=true;
        this->flag=false;
    }
    else//如果是反面
    {
        time2->start(30);
        isanimation=true;
        this->flag=true;
    }
}
