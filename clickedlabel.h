#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QWidget>
#include<QLabel>

class Clickedlabel : public QLabel
{
    Q_OBJECT
public:
    Clickedlabel(QWidget *parent = nullptr): QLabel(parent){}
        ~Clickedlabel() {}
signals:
    void clicked(); // 点击信号
protected:
    void mouseReleaseEvent(QMouseEvent*); // 重载了鼠标释放事件

};

#endif // CLICKEDLABEL_H
