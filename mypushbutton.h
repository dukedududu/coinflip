#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //参数1：正常显示图片路径，参数2：按压后显示的图片路径
    MyPushButton(QString normalImg,QString pressImg="");
    QString normalImgpath;
    QString pressImgpath;
    //弹跳特效
    void zoom1();//下
    void zoom2();//上
    //重写按下和释放事件
    void mousePressEvent(QMouseEvent * e);
    void mouseReleasEvent(QMouseEvent * e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H
