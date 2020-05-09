#include "playscene.h"
#include<QMenuBar>
#include"mypushbutton.h"
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{
//
//}
PlayScene::PlayScene(int i)
{

    this->levelIndex=i;
    //初始化游戏场景
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

    //添加翻金币、胜利和返回按钮音效 bgm
        QSound *lipSound = new QSound(":/res/ConFlipSound.wav",this);
        QSound *winSound = new QSound(":/res/LevelWinSound.wav",this);
        QSound * backsound=new QSound(":/res/BackButtonSound.wav",this);


    //返回按钮
    MyPushButton * backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);//将按钮设置到当前窗口
    backBtn->move(this->width()-backBtn->width()-10,this->height()-backBtn->height()-10);//设置按钮的位置
    connect(backBtn,&MyPushButton::clicked,[=](){
        //播放返回按钮音效
        backsound->play();
        //延时0.5秒
        QTimer::singleShot(500,this,[=](){
            emit this->choosesceneback();//发送一个自定义的信号
        });

    });
    //显示选择的当前关卡
    QLabel *label=new QLabel;
    label->setParent(this);
    //设置字体
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str=QString("level:%1").arg(this->levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str);
    label->setGeometry(20,this->height()-100,170,100);
    //设置字体颜色
    label->setStyleSheet("color:white");

    dataConfig config;

    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
         for(int j=0;j<4;j++)
         {
              this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
         }
    }

    //胜利图片加载但是未显示
        QLabel* winLabel = new QLabel;
        QPixmap tmpPix;
        tmpPix.load(":/res/LevelCompletedDialogBg.png");
        winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
        winLabel->setPixmap(tmpPix);
        winLabel->setParent(this);
        winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());


    //显示金币背景图案
    for(int i=0;i<4;i++)
     {
        for(int j=0;j<4;j++)
        {
            QLabel *label=new QLabel;
            QPixmap pix=QPixmap(":/res/BoardNode(1).png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(400+i*120,200+j*120);
            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            MyCoin *coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(400+i*120,200+j*120);

            //设置金币属性
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->gameArray[i][j];//1 代表正面，2 代表反面
            //将币数据放入二维数组，以便维护使用
            coinbtn[i][j]=coin;

            //点击金币进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //播放翻金币音效
                lipSound->play();
                coin->changeflag();
                this->gameArray[i][j]=!this->gameArray[i][j];

                //防止在胜利的同时手快点了其他金币然后又被全被禁用的bug
                 for(int i = 0; i < 4; i++)
                      {
                          for(int j = 0; j < 4; j++)
                              {
                                    this->coinbtn[i][j]->iswin=true;
                              }
                      }

                //翻转周围，延时效果更好
                QTimer::singleShot(300,this,[=](){
                    if(coin->posx+1<=3)//右侧翻转条件
                        {
                        coinbtn[coin->posx+1][coin->posy]->changeflag();
                        this->gameArray[coin->posx+1][coin->posy]=!this->gameArray[coin->posx+1][coin->posy];
                        }
                    if(coin->posx-1>=0)//左侧翻转条件
                        {
                        coinbtn[coin->posx-1][coin->posy]->changeflag();
                        this->gameArray[coin->posx-1][coin->posy]=!this->gameArray[coin->posx-1][coin->posy];
                        }
                    if(coin->posy-1>=0)//上侧翻转条件
                        {
                        coinbtn[coin->posx][coin->posy-1]->changeflag();
                        this->gameArray[coin->posx][coin->posy-1]=!this->gameArray[coin->posx][coin->posy-1];
                        }
                    if(coin->posy+1<=3)//下侧翻转条件
                        {
                        coinbtn[coin->posx][coin->posy+1]->changeflag();
                        this->gameArray[coin->posx][coin->posy+1]=!this->gameArray[coin->posx][coin->posy+1];
                        }

                    //解除其他金币的禁用
                     for(int i = 0; i < 4; i++)
                          {
                              for(int j = 0; j < 4; j++)
                                  {
                                        this->coinbtn[i][j]->iswin=false;
                                  }
                          }
                    //判断游戏是否胜利
                    this->iswin=true;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)//有一个币为银币
                                {
                                    this->iswin=false;
                                    break;
                                }
                        }

                    }
                    if(this->iswin==true)
                    {
                        //播放胜利音效
                        winSound->play();
                        //给所以coin赋值true标志
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {

                                coinbtn[i][j]->iswin=true;
                            }

                        }
                        //设置胜利图片砸下来动画(和开始按钮一样）
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y()+20,winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+150,winLabel->width(),winLabel->height()));
                        //设置弹跳曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //开始
                        animation->start();

                     }

                });

            });
        }
     }

}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;

    QString str=QString(":/res/bg_%1.jpg").arg(this->levelIndex);
    pix.load(str);

 /*
    if(this->levelIndex==1){
        pix.load(":/res/bg_1.jpg");//加载图片
    }
    if(this->levelIndex==2){
        pix.load(":/res/bg_2.jpg");//加载图片
    }
    if(this->levelIndex==3){
        pix.load(":/res/bg_3.jpg");//加载图片
    }
    if(this->levelIndex==4){
        pix.load(":/res/bg_4.jpg");//加载图片
    }
    if(this->levelIndex==5){
        pix.load(":/res/bg_5.jpg");//加载图片
    }
    if(this->levelIndex==6){
        pix.load(":/res/bg_6.jpg");//加载图片
    }
    if(this->levelIndex==7){
        pix.load(":/res/bg_1.jpg");//加载图片
    }
    if(this->levelIndex==8){
        pix.load(":/res/bg_8.jpg");//加载图片
    }
    if(this->levelIndex==9){
        pix.load(":/res/bg_9.jpg");//加载图片
    }
    if(this->levelIndex==10){
        pix.load(":/res/bg_10.jpg");//加载图片
    }
    if(this->levelIndex==11){
        pix.load(":/res/bg_11.jpg");//加载图片
    }
    if(this->levelIndex==12){
        pix.load(":/res/bg_12.jpg");//加载图片
    }
    if(this->levelIndex==13){
        pix.load(":/res/bg_13.jpg");//加载图片
    }
    if(this->levelIndex==14){
        pix.load(":/res/bg_14.jpg");//加载图片
    }
    if(this->levelIndex==15){
        pix.load(":/res/bg_15.jpg");//加载图片
    }
    if(this->levelIndex==16){
        pix.load(":/res/bg_16.jpg");//加载图片
    }
    */
    //绘制背景图
    painter.drawPixmap(0,0,pix);
   //painter(0,0 ,this->width(),this->height(),pix)如果图片和窗口不是一个大小可以这样拉伸；

    //画背景上的图标
    pix.load(":/res/Title.png");
    painter.drawPixmap(0,30,pix);

}
