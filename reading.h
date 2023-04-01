#ifndef READING_H
#define READING_H

//每一个Reading类对应一个加载的胜率库文件
#include <QDebug>
#include <QString>

#define ALLsituation 308915776    //456976   308915776
static int const MaxNumb=6;//最大棋子数 4 6

class Reading
{
public:
    Reading();
    ~Reading();

    FILE *Bin_WinrateFile;//文件起形参名，每个文件各对应一个
    int ChessOrder[2][MaxNumb/2]={{1,2,3},{-1,-2,-3}};//棋子次序对应的编号{1,2,3},{-1,-2,-3}     {{1,3},{-1,-3}};
    //每个对象都有不同的棋子次序，以上是为了方便测试的默认次序

    double* Winrate = new double [ALLsituation];//胜率数组
    bool isLoad = false;//代表是否已加载胜率文件

    static QString CStrToQStr(std::string);
    static std::string QStrToCStr(QString);
    //原生字符串和QT字符串的转换

    //void WinrateReading(long long OneofSituation, QString Address);
};

#endif // READING_H
