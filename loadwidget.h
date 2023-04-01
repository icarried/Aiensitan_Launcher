#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QFrame>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>

//#include <cstdio>
#include <stdio.h>
//#include <iostream>

#include "reading.h"

#include "QDebug"

//1~6 2~5 3~4
//static Reading reading124;//356
//static Reading reading125;//256
//static Reading reading126;//156
//static Reading reading134;//346
//static Reading reading135;//246
//static Reading reading136;//146
//static Reading reading145;//236
//static Reading reading234;//345
//static Reading reading235;//245
//所有对称不重复情况已在上边


class LoadWidget : public QFrame
{
    Q_OBJECT

public:
    LoadWidget(QWidget *parent = nullptr);
    ~LoadWidget();

    const int LoadWidgetXsize = 1000;//该窗口横长
    const int LoadWidgetYsize = 200;//该窗口纵长

    const int ButtonXsize = 100;//按钮横尺寸
    const int ButtonYsize = 60;//按钮竖尺寸

    const int ButtonXlength = 125;//按钮间隔横长
    const int ButtonYlength = 80;//按钮间隔竖长

    const int LineWidth = 6;//边框宽度

    static Reading reading123;//创建一个对应123-1-2-3的类456

    QString file_path;//配置文件获得的加载胜率文件位置


    QTextEdit TextEdit_LogOutput;//日志输出框
    QSettings config_winrate;//创建配置文件


    //槽函数
    void Do_LoadWinrateFile();
    void Do_ViewWinrateFilePath();

    void LogOutput(QString);//日志输出函数
    bool isFileExist(QString);//判断文件是否存在（全路径）

private:
    QPushButton Button_LoadWinrateFile;
    QPushButton Button_ViewWinrateFilePath;


    QLineEdit LineEdit_WinrateFilePath;
    QLabel Label_WinrateFilePath;
};
#endif // LOADWIDGET_H
