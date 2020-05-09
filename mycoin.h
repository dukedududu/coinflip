#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    //btnImg 传入金币路径或者银币路径
    MyCoin(QString btnImg);

    //设置金币的属性
    int posx;
    int posy;
    bool flag;//正反标识

    void changeflag();//改变标识
    QTimer *time1;
    QTimer *time2;
    int min=1;
    int max=8;

    //执行动画的标志
    bool isanimation=false;

    //重写按下
    void mousePressEvent(QMouseEvent * e);
    //游戏胜利标识
    bool iswin=false;//如果不加初始值，有的金币会被禁用

signals:

public slots:
};

#endif // MYCOIN_H
