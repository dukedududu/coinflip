#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //设置主场景

    //设置固定窗口大小
    setFixedSize(1200,800);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币");
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始，背景音效
    QSound * bgm=new QSound(":/res/bgm.wav",this);
    bgm->setLoops(-1);//无限循环
    bgm->play();
    QSound * startsound=new QSound(":/res/TapButtonSound.wav",this);


    //开始按钮
    MyPushButton * startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);//将按钮设置到当前窗口
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);//设置按钮的位置

    //创建选择关卡对象
    choosescene=new chooselevelscene;

    //监听选择关卡的返回按钮信号
    connect(choosescene,&chooselevelscene::choosesceneback,this,[=](){
        choosescene->hide();//隐藏选择关卡场景
        this->setGeometry(choosescene->geometry());
        this->show();//重新现实主场景
    });

    connect(startBtn,&MyPushButton::clicked,[=](){
        //播放按钮声音
        startsound->play();
        //弹起特效
        startBtn->zoom1();
        startBtn->zoom2();


        //延时进入到选择关卡的场景（为了让弹起效果能被看到）
        QTimer::singleShot(500,this,[=](){
            //自身隐藏
            this->hide();
            //设置场景位置
            choosescene->setGeometry(this->geometry());
            //显示选择场景
            choosescene->show();


        });

    });
}
void MainScene::paintEvent(QPaintEvent *)
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

MainScene::~MainScene()
{
    delete ui;
}

