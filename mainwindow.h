#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "gamewidget.h"
#include "loadwidget.h"

#include <QMainWindow>
#include <QMenu>
#include <QLabel>
#include <QMenuBar>
#include <QToolBar>
#include <QPainter>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    const int MenuYsize = 25;//菜单纵长
    const int BackgroundXsize = 1000;//背景纵长
    const int BackgroundYsize = 750;//背景横长


private:
    GameWidget* Window_Game = nullptr;
    LoadWidget* Window_Load = nullptr;
    QMenu *Menu_Game = nullptr;
    //暂无QMenu *viewMenu;

    //创建菜单项
    QAction *Action_Newgame = nullptr;
    //暂无QAction *openAction;

    QPixmap img_background_mainwindow;//棋子图片
    QLabel Label_background_mainwindow;

private slots:
    void Newgame();
};
#endif // MAINWINDOW_H
