#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
class chooselevelscene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooselevelscene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    //建立游戏场景的指针
    PlayScene *play=NULL;
signals:
    //自定义一个信号，告诉主场景
    void choosesceneback();//自定义的信号不需要实现，只需要声明
public slots:
};

#endif // CHOOSELEVELSCENE_H
