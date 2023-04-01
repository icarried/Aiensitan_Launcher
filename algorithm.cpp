#include "algorithm.h"

Algorithm::Algorithm(QObject *parent) : QThread(parent)
{
    //初始化对象数据
    SeachCountValue = 0;//搜索总节点数
    UnSureValue = 0;//不确定末节点数
    SeachtoReading = 0;//搜索到残局数
    SeachStep = 6;//剩余搜索层数
    NowRid = 0b1111111111110;//当前存活棋子，初始为当前棋盘某个已走状态，对于每个算法对象均不同，会随着当前对象局面改变而改变
    RidCount = 0;//重新初始化，初始化完成前作为下标
    for(int point = 1; point <= 12; point++){
        if(GetRid123 & TwoPower[point]){//GetRid每有一个1时RidCount+1，并把点数加入列表
            ChessList[RidCount] = point;
            RidCount++;
        }
    }
    //RidCount和ChessList初始化完成！！！！该初始化方式要求顺序格式为123456-1-2-3-4-5-6取其中值
}

void Algorithm::run(){
    CalWinrate();
    exit(0);//返回
}

void Algorithm::setAlgWay(int chessplacet[13], int changechess, int drift){//算法执行前的连接函数,以当前局面为参数
    for(int point = 1; point <= 12; point++){
        ChessPlaceM[point] = chessplacet[point];//传递位置信息
    }
    ChessPlaceM[changechess] += drift;//位置偏移，形成改对象走法后的局面
    for (int point = 1; point <= 12; point++) {
        if(point != changechess && ChessPlaceM[point] == ChessPlaceM[changechess]){//存在偏移到的地方有其他棋子
            ChessPlaceM[point] = 25;//则属于吃子
            break;
        }
    }
    //生成PlaceToChess和SeachStep
    for (int place = 0; place < 25; place++) {
        PlaceToChess[place] = 0;//没有棋子为0
    }
    int chessnumb = 0;
    for (int point = 1; point <= 12; point++) {
        if(ChessPlaceM[point] < 25){
            PlaceToChess[ChessPlaceM[point]] = point;//把数据传递
            chessnumb++;
        }else{
            NowRid -= TwoPower[point];//如果棋子已死亡，则从存活棋子标记中去除
        }
    }
    /*去除分别加层
    if (chessnumb <= 8){
        SeachStep += 1;
    }
    if (chessnumb <= 6){
        SeachStep += 1;
    }
    if (chessnumb <= 5){
        SeachStep += (6 - chessnumb);
    }
    */
}

void Algorithm::CalWinrate(){//计算对象的胜率保存在AlgWinrate
    bool alleaten_B = true;//蓝方全被吃，红胜
    for(int place = 0; place < 25; place++){
        if(PlaceToChess[place] <= 12 && PlaceToChess[place] >= 7){
            alleaten_B = false;
            break;
        }
    }
    if((PlaceToChess[24] >=1 && PlaceToChess[24] <= 6) || alleaten_B == true){
        AlgWinrate = 1;//若己方已胜，则则无需计算
    }else{
        Exchange();//应该从对方开始被调用
        AlgWinrate = 1 - SearchWinrate();//得到对方未走胜率，进而得到己方已走胜率
    }
}


/*
bool Algorithm::CanGetWinrate()//用于判断从倒推算法生成数据中获取，false为数据不可获取，true为可获取，以后可改为无需函数！！我直接写到大循环里算了
{
    //获取的数据中不计入的棋子
    if((GetRid123 | NowRid) == GetRid123)//如果现在存活棋子都被可获取棋子包含
        return true;
    else
        return false;
}
*/

Algorithm::~Algorithm()
{

}
