#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int i);
    int levelIndex;
    void paintEvent(QPaintEvent *);

    //维护每个关卡的数据
    int gameArray[4][4];
    MyCoin *coinbtn[4][4];//维护币的数据

    //游戏胜利标识
    bool iswin;
signals:
    void choosesceneback();
public slots:
};

#endif // PLAYSCENE_H
