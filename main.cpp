//该程序由 哈尔滨理工大学 陈泳吉 独立制作
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow Window_Launcher;// 执行窗口的构造函数
    Window_Launcher.show();
    return app.exec();
}
