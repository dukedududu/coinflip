#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QPixmap>
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalImgpath=normalImg;
    this->pressImgpath=pressImg;
    QPixmap pix;
    bool ret=pix.load(normalImg);
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

}
void MyPushButton::zoom1()//下
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");//建立动画对象
    //设置时间间隔
    animation->setDuration(200);
    //设置开始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    animation->start();

}

void MyPushButton::zoom2()//上
{
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //设置时间间隔
    animation->setDuration(200);
    //设置开始位置
    animation->setStartValue(QRect(this->x(),this->y()+20,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始
    animation->start();

}
void MyPushButton::mousePressEvent(QMouseEvent * e)
{
    if(this->pressImgpath!="")//按下的路径不为空
      {
        QPixmap pix;
        bool ret=pix.load(this->pressImgpath);
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

        }
    //让父类执行其他
    return QPushButton::mousePressEvent(e);
}
void MyPushButton::mouseReleasEvent(QMouseEvent * e)
{
    if(this->pressImgpath!="")//按下的路径不为空,切换为初始图片
      {
        QPixmap pix;
        bool ret=pix.load(this->pressImgpath);
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

        }
    //让父类执行其他
    return QPushButton::mouseReleaseEvent(e);
}
