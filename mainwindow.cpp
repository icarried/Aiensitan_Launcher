#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(BackgroundXsize, BackgroundYsize + MenuYsize);
    //菜单栏创建
    Menu_Game = new QMenu(tr("&Game"),this);
    menuBar() -> addMenu(Menu_Game);

    //菜单操作创建
    Action_Newgame = new QAction(tr("&Newgame"),this);
    Menu_Game -> addAction(Action_Newgame);
    Action_Newgame -> setShortcut(tr("ctrl+G"));//设置快捷操作




    //背景
    img_background_mainwindow.load(":/background/img/background/background_mainwindow.jpg");
    Label_background_mainwindow.setParent(this);
    Label_background_mainwindow.resize(BackgroundXsize,BackgroundYsize);
    Label_background_mainwindow.move(0,MenuYsize);
    Label_background_mainwindow.setPixmap(img_background_mainwindow.scaled(BackgroundXsize,BackgroundYsize));
    //Label_background_mainwindow.hide();

    Window_Load = new LoadWidget(this);// 执行GameWidget的构造函数
    Window_Load->move(0,550 + MenuYsize);
    Window_Load->show();



    //槽函数
    connect(Action_Newgame,SIGNAL(triggered()),this,SLOT(Newgame()));
    //connect(&Label_Chessimg[place], SIGNAL(clicked()), this, SLOT(Do_LabelClick()));

}

void MainWindow::Newgame()
{
    if(GameWidget::isWindow_GameOpen == true){
        delete Window_Game;
        Window_Game = nullptr;
    }
    Window_Game = new GameWidget(this);// 执行GameWidget的构造函数
    Window_Game->move(0,25);
    Window_Game->show();
    //Window_Load->TextEdit_LogOutput.insertPlainText("-开始新游戏\n");
    //下面保持在最后一行添加(自动滚屏)
    Window_Load->LogOutput("+开始新游戏");
    //Window_Game->close();
    //Window_Game->show();
}

MainWindow::~MainWindow()
{
    if(GameWidget::isWindow_GameOpen == true){
        delete Window_Game;
        Window_Game = nullptr;
    }
}
//一个菜单操作要在h文件定义，在cpp创建并命名，在某菜单项中加入该操作，并把操作连接槽函数（同样要定义），写好槽函数
/*
 * m_pPreMenu=new QMenu(this);
 *m_pPreMenu->addAction(QString::fromLocal8Bit("50万"));
 *QObject::connect(m_pPreMenu,SIGNAL(triggered(QAction*)),this,SLOT(OnMenuTriggered(QAction*)));
 */
