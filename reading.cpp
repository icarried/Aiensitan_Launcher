#include "reading.h"
#include "loadwidget.h"

Reading::Reading()
{

}
/*
void Reading::WinrateReading(long long OneofSituation, QString Address)//将某一局面传过来，并且把QString转为原生String
{
    //double winrate;//胜率读取时的载体
    std::string FilestorageSituationAddress = QStrToCStr(Address);
}
*/

QString Reading::CStrToQStr(std::string cstr){
    QString qstr;
    qstr = QString(QString::fromLocal8Bit(cstr.c_str()));
    return qstr;
}

std::string Reading::QStrToCStr(QString qstr){
    std::string cstr;
    cstr = std::string((const char *)qstr.toLocal8Bit());
    return cstr;
}

Reading::~Reading()
{
    delete [] Winrate;
}
