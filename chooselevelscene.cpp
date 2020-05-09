#include "chooselevelscene.h"
#include<QAction>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QSound>
chooselevelscene::chooselevelscene(QWidget *parent) : QMainWindow(parent)
{
    //设置固定窗口大小
    setFixedSize(1200,800);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("选择关卡");

    //创建菜单栏
    QMenuBar * bar=menuBar();
    setMenuBar(bar);
    //添加开始菜单
    QMenu *startmenu=bar->addMenu("开始");

    //创建退出的菜单项
    QAction *quit=startmenu->addAction("退出");
    connect(quit,&QAction::triggered,[=](){
        this->close();
    });
    //准备关卡按钮和返回按钮音效 bgm

    QSound * choosesound=new QSound(":/res/TapButtonSound.wav",this);
    QSound * backsound=new QSound(":/res/BackButtonSound.wav",this);

    //添加返回按钮
    MyPushButton * backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);//将按钮设置到当前窗口
    backBtn->move(this->width()-backBtn->width()-10,this->height()-backBtn->height()-10);//设置按钮的位置
    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        //播放返回按钮音效
        backsound->play();
        //延时0.5秒
        QTimer::singleShot(500,this,[=](){
            emit this->choosesceneback();//发送一个自定义的信号
        });

    });
    //创建选择关卡的按钮
    for(int i=0;i<16;i++)
    {
        MyPushButton * chooseBtn=new MyPushButton(":/res/LevelIcon.png");
        chooseBtn->setParent(this);//将按钮设置到当前窗口
        chooseBtn->move(100+i%4*300,200+i/4*150);

        //监听每个按钮的点击事件
        connect(chooseBtn,&MyPushButton::clicked,this,[=](){
            //播放选择关卡音效
            choosesound->play();
            this->hide();

            play=new PlayScene(i+1);
            play->show();
            play->setGeometry(this->geometry());

            connect(play,&PlayScene::choosesceneback,this,[=](){
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;
            });
        });
        //创建按钮上的关卡数字
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(chooseBtn->width(),chooseBtn->height());
        label->setText(QString::number(i+1));
        label->move(100+i%4*300,200+i/4*150);
        //设置对齐方式(水平居中和垂直居中)
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //由于Label部件会覆盖按钮部件,按钮部件会接收不到信号
        //设置让鼠标进行穿透(帮助文档里的 51号属性）
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }

}
void chooselevelscene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/bg_0.jpg");//加载图片
    //绘制背景图
    painter.drawPixmap(0,0,pix);
   //painter(0,0 ,this->width(),this->height(),pix)如果图片和窗口不是一个大小可以这样拉伸；

    //画背景上的图标
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,30,pix);
}
