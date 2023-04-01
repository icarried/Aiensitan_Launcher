#include "clickedlabel.h"

void Clickedlabel::mouseReleaseEvent(QMouseEvent *)
{
    emit clicked(); // 在点击事件中发送信号
}
