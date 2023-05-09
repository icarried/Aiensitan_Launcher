#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <QObject>
#include<QThread>
#include "loadwidget.h"

class Algorithm : public QThread
{
    Q_OBJECT
public:
    explicit Algorithm(QObject *parent = nullptr);
    ~Algorithm();
    unsigned int GetRid123= 0b0001110001110;//能读取胜率的棋子二进制格式，开头的一个0为空，目前为123，暂时无法读取其他胜率类型，使用二进制写法是因为要大量使用，减少开销
    unsigned int NowRid; //当前存活棋子，初始为当前棋盘某个已走状态，对于每个算法对象均不同
    const int TwoPower[13] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096};//快速返回2的次方而无需计算
    const long long The26Power[13] = {1, 26, 676, 17576, 456976, 11881376, 308915776,
                                      8031810176, 208827064576, 5429503678976, 141167095653376, 3670344486987776, 95428956661682176};//快速返回26的次方而无需计算
    int ChessList[12] = {0};//需要GetRid进行重新初始化，保存可读取的棋子列表，最多为保存12个棋子，但并非全部都用上，后面没用上的为0，棋子点数为1~12，下标上限为RidCount
    int RidCount = 0;//需要GetRid进行重新初始化，保存可读取的棋子总数，目前为6

    int SeachStep;//剩余搜索层数
    double AlgWinrate;//该对象的胜率
    long long SeachCountValue;//搜索总节点数，用于记录
    long long UnSureValue;//不确定末节点数，用于记录
    long long SeachtoReading;//搜索到残局库数，用于记录
    //参数分别为：棋子位置传递、偏移的棋子、偏移量(偏移指横走+1，竖走+5，斜走+6)
    void setAlgWay(int chessplacet[13], int changechess, int drift);//算法执行前的设置走法
    void CalWinrate();//计算对象的胜率保存在AlgWinrate
    //注意void GameWidget::BeforeAlgorithm(){//算法执行前的转换，也属于算法的一部分
protected:
    void run() override;
signals:

private:
    int ChessPlaceM[13];//1~6为己方，7~12为对方，25代表被吃位置，点数到位置
    int PlaceToChess[25];//0为没有棋子，1~6为己方，7~12为对方，位置到点数
    //int BOverplus;//蓝方剩余棋子数,每层都会重新计算

    bool CanGetWinrate();//用于判断从倒推算法生成数据中获取，false为数据不可获取，true为可获取

    void Exchange(){//局面互换，这个函数虽然简化了代码量，但运算量代价不小
        for (int point = 1, exch; point <= 6; point++) {//颜色互换
            exch = ChessPlaceM[point];
            ChessPlaceM[point] = ChessPlaceM[point + 6];
            ChessPlaceM[point + 6] = exch;
        }
        for (int point = 1; point <= 12; point++) {//交换局面
            if(ChessPlaceM[point] != 25) {
                ChessPlaceM[point] = 24 - ChessPlaceM[point];
            }
        }
        //由于原vb算法中是双方交替调用，所以局面不用互换。但此算法走向单一，因此ChessToPlace也要互换
        //重新生成PlaceToChess
        for (int place = 0; place < 25; place++) {
            PlaceToChess[place] = 0;//没有棋子为0
        }
        for (int point = 1; point <= 12; point++) {
            if(ChessPlaceM[point] < 25){
                PlaceToChess[ChessPlaceM[point]] = point;//把数据传递
            }
        }
        //交换NowRid的双方存活棋子
        unsigned int low =  (NowRid & 0b0000001111110) << 6;
        unsigned int high = (NowRid & 0b1111110000000) >> 6;
        NowRid = low | high;
    }

    double SearchWinrate(){//通过反复嵌套与分支搜索胜率
        //SeachCountValue++;//搜索总节点数增加//改为计算总末节点数
        //现在，末节点仅包括胜利节点（两种胜利方法）和搜索到头节点


        if (SeachStep == 0){
            UnSureValue++;//不确定末节点数增加
            SeachCountValue++;//搜索总末节点数增加
            return 0.5;
        }
        //如果现在存活棋子都被可获取棋子包含！！！@@@
        if((GetRid123 | NowRid) == GetRid123){
            long long winrate_index = 0;
            for(int order = 0; order < RidCount; order++){
                winrate_index += The26Power[order] * ChessPlaceM[ChessList[order]];//类似倒推里的PlaceToSituation()
            }
            SeachtoReading++;
            return LoadWidget::reading123.Winrate[winrate_index];
        }

        double backrate = 0;//储存返回的胜率
        double unpluspro[7] = {0};//未乘概率,配合点数没有参数0，为1~6
        int plus[7] = {0};//倍率,配合点数没有参数0，为1~6
        int theBOverplus = 0;//当前搜索节点的蓝方剩余棋子数,，在2020CCGC发现bug后的修复。从全局变为限定域
        for (int point = 7; point <= 12; point++) {//每存在一个对方棋子，对方棋子数+1
            if(ChessPlaceM[point] < 25){
                theBOverplus += 1;
            }
        }
        for(int point = 1; point <= 6; point++){//大循环，计算己方每个棋子的未乘概率，己方棋子为1~6
            if (ChessPlaceM[point] >= 25) {//如果棋子为被吃
                continue;//未乘概率和倍率仍然为默认的0，该棋子不用继续计算，指向大循环
            }else{//如果棋子存在
                plus[point] = 1;//设置存活棋子基本有的1倍率
            }
            //由于所有已胜情况都已在已胜的走前被提前简化算出，所以不用考虑走后已胜情况
            //如果一个棋子还差一格胜利，其未乘概率为1/6，相当于走法中出现胜率1必取1，不用考虑其他走法！！！如果能把提取棋子概率写完，则该步骤可以不需要
            if (ChessPlaceM[point] == 23 || ChessPlaceM[point] == 19 ||ChessPlaceM[point] == 18){
                unpluspro[point] = 1;
                SeachCountValue++;//搜索总末节点数增加
                continue;//该棋子不用继续计算，指向大循环
            }else if (theBOverplus == 1 && ((ChessPlaceM[point] <= 19 && PlaceToChess[ChessPlaceM[point] + 5] >= 7)//首先对方剩余最后一棋,判断能否吃掉对方最后一棋
                        || (ChessPlaceM[point] % 5 != 4 && ChessPlaceM[point] < 25 && PlaceToChess[ChessPlaceM[point] + 1] >= 7)
                        || (ChessPlaceM[point] <= 18 && ChessPlaceM[point] % 5 != 4 && PlaceToChess[ChessPlaceM[point] + 6] >= 7))) {
                unpluspro[point] = 1;//这是能吃掉对方最后一子的情况
                SeachCountValue++;//搜索总末节点数增加
                continue;//该棋子不用继续计算，指向大循环
            }
            int diechess;//被吃棋子
            int diechessplace;//被吃棋子位置
            //3种走法计算，取其中最大值为该棋子未乘概率
            //----------横走------------
            if (ChessPlaceM[point] % 5 != 4 && ChessPlaceM[point] < 25){
                diechess = 0;//清除被吃棋子，点数系列变量被吃为0
                diechessplace = 25;//清除被吃棋子位置
                PlaceToChess[ChessPlaceM[point]] = 0;//暂时消除走子的原位置（拿起棋子），点数系列消除为0
                ChessPlaceM[point] += 1;//走子位置暂时改变*(3种走法的差异代码位置)*
                if (PlaceToChess[ChessPlaceM[point]] > 0) {//判断是否吃子，是则将吃子储存(注意，此时已走子，不是ChessPlaceM[point]原位置)
                    diechess = PlaceToChess[ChessPlaceM[point]];
                    PlaceToChess[ChessPlaceM[point]] = 0;//暂时消除被吃棋子位置的数据，点数系列消除为0
                    diechessplace = ChessPlaceM[diechess];//记录被吃棋子的位置，便于之后还原
                    ChessPlaceM[diechess] = 25;//暂时消除被吃棋子位置的数据
                    NowRid -= TwoPower[diechess];//@移除被吃棋子的存活标记rid
                }
                PlaceToChess[ChessPlaceM[point]] = point;//移动拿起的棋子
                SeachStep--;//即将进入下一循环，搜索层数-1
                Exchange();//局面互换
                backrate =  1 - SearchWinrate();//得到对方未走胜率，进而得到己方已走胜率
                if (backrate > unpluspro[point]){//取最大的返回值
                    unpluspro[point] = backrate;
                }
                Exchange();//局面互换回
                SeachStep++;//搜索层数还原
                PlaceToChess[ChessPlaceM[point]] = diechess;//还原被吃子的位置(同样符合没有被吃的情况)
                if(diechess > 0){//如果存在被吃子
                    ChessPlaceM[diechess] = diechessplace;//还原被吃棋子的位置数据
                    NowRid += TwoPower[diechess];//@还原被吃棋子的存活标记rid
                }
                ChessPlaceM[point] -= 1;//还原走子位置*(3种走法的差异代码位置)*
                PlaceToChess[ChessPlaceM[point]] = point;//把移动的棋子放回去
            }
            //----------竖走------------
            if (ChessPlaceM[point] <= 19){
                diechess = 0;//清除被吃棋子，点数系列变量被吃为0
                diechessplace = 25;//清除被吃棋子位置
                PlaceToChess[ChessPlaceM[point]] = 0;//暂时消除走子的原位置（拿起棋子），点数系列消除为0
                ChessPlaceM[point] += 5;//走子位置暂时改变*(3种走法的差异代码位置)*
                if (PlaceToChess[ChessPlaceM[point]] > 0) {//判断是否吃子，是则将吃子储存(注意，此时已走子，不是ChessPlaceM[point]原位置)
                    diechess = PlaceToChess[ChessPlaceM[point]];
                    PlaceToChess[ChessPlaceM[point]] = 0;//暂时消除被吃棋子位置的数据，点数系列消除为0
                    diechessplace = ChessPlaceM[diechess];//记录被吃棋子的位置，便于之后还原
                    ChessPlaceM[diechess] = 25;//暂时消除被吃棋子位置的数据
                    NowRid -= TwoPower[diechess];//@移除被吃棋子的存活标记rid
                }
                PlaceToChess[ChessPlaceM[point]] = point;//移动拿起的棋子
                SeachStep--;//即将进入下一循环，搜索层数-1
                Exchange();//局面互换
                backrate = 1 - SearchWinrate();//得到对方未走胜率，进而得到己方已走胜率
                if (backrate > unpluspro[point]){//取最大的返回值
                    unpluspro[point] = backrate;
                }
                Exchange();//局面互换回
                SeachStep++;//搜索层数还原
                PlaceToChess[ChessPlaceM[point]] = diechess;//还原被吃子的位置(同样符合没有被吃的情况)
                if(diechess > 0){//如果存在被吃子
                    ChessPlaceM[diechess] = diechessplace;//还原被吃棋子的位置数据
                    NowRid += TwoPower[diechess];//@恢复被吃棋子的存活标记rid
                }
                ChessPlaceM[point] -= 5;//还原走子位置*(3种走法的差异代码位置)*
                PlaceToChess[ChessPlaceM[point]] = point;//把移动的棋子放回去
            }
            //----------斜走------------
            if (ChessPlaceM[point] <= 18 && ChessPlaceM[point] % 5 != 4){
                diechess = 0;//清除被吃棋子，点数系列变量被吃为0
                diechessplace = 25;//清除被吃棋子位置
                PlaceToChess[ChessPlaceM[point]] = 0;//暂时消除走子的原位置（拿起棋子），点数系列消除为0
                ChessPlaceM[point] += 6;//走子位置暂时改变*(3种走法的差异代码位置)*
                if (PlaceToChess[ChessPlaceM[point]] > 0) {//判断是否吃子，是则将吃子储存(注意，此时已走子，不是ChessPlaceM[point]原位置)
                    diechess = PlaceToChess[ChessPlaceM[point]];
                    PlaceToChess[ChessPlaceM[point]] = 0;//暂时消除被吃棋子位置的数据，点数系列消除为0
                    diechessplace = ChessPlaceM[diechess];//记录被吃棋子的位置，便于之后还原
                    ChessPlaceM[diechess] = 25;//暂时消除被吃棋子位置的数据
                    NowRid -= TwoPower[diechess];//@移除被吃棋子的存活标记rid
                }
                PlaceToChess[ChessPlaceM[point]] = point;//移动拿起的棋子
                SeachStep--;//即将进入下一循环，搜索层数-1
                Exchange();//局面互换
                backrate = 1 - SearchWinrate();//得到对方未走胜率，进而得到己方已走胜率
                if (backrate > unpluspro[point]){//取最大的返回值
                    unpluspro[point] = backrate;
                }
                Exchange();//局面互换回
                SeachStep++;//搜索层数还原
                PlaceToChess[ChessPlaceM[point]] = diechess;//还原被吃子的位置(同样符合没有被吃的情况)
                if(diechess > 0){//如果存在被吃子
                    ChessPlaceM[diechess] = diechessplace;//还原被吃棋子的位置数据
                    NowRid += TwoPower[diechess];//@恢复被吃棋子的存活标记rid
                }
                ChessPlaceM[point] -= 6;//还原走子位置*(3种走法的差异代码位置)*
                PlaceToChess[ChessPlaceM[point]] = point;//把移动的棋子放回去
            }
        }
        //计算倍率
        int beeatflag = 0;//预设被吃集合标志为0
        //这里的上子和下子是一片连号的被吃棋子统一的上下子
        int upchess  = 7;//上子，预设为不存在时的值
        int downchess = 0;//下子，预设为不存在时的值
        //倍率不为0则代表了存活棋子（因为对应的己方棋子可移动，则倍率不为0）
        for (int i = 1; i <= 6; i++)//计算己方所有编号的棋子
        {
            if (beeatflag)//被吃集合标志为1时
            {
                if (plus[i] > 0 || i == 6)//被吃集合标志为1，且遇到存活棋子或遍历到最大编号时，产生上子并计算
                {
                    if (i == 6 && !plus[i])
                        upchess = 7;//当遍历到最大编号仍为被吃棋子，说明上子不存在，设为最大编号+1=7
                    else
                        upchess = i;//其他情况上子等于当前遍历到的存活棋子
                    int beeatvalue = upchess - downchess - 1;//被吃集合量。下子不存在为0、上子不存在为6，也是为了配合这一算法
                    if(downchess == 0)//如果不存在下子，则把被吃集合量加到上子的倍率上
                        plus[upchess] += beeatvalue;
                    else if(upchess == 7)//如果不存在上子，则把被吃集合量加到下子的倍率
                        plus[downchess] += beeatvalue;
                    else if(unpluspro[upchess] > unpluspro[downchess])//如果上子的未乘概率大于下子的未乘概率，则把被吃集合量加到上子的倍率上
                        plus[upchess] += beeatvalue;
                    else//如果下子的未乘概率大于上子的未乘概率，则把被吃集合量加到下子的倍率（包括上下子未乘概率相等）
                        plus[downchess] += beeatvalue;
                    beeatflag = 0;
                }
            }
            else if(!plus[i])//被吃集合标志为0，且遇到已被吃棋子（包括了不存在下子的情况）
            {
                if (i == 6) {//防止5存活但6被吃这样的情况，这种情况属于这么算的特殊情况
                    upchess = 7;//此时没有上子，只有下子
                    downchess= 5;
                    plus[5] += 1;
                }
                beeatflag = 1;
                downchess= i - 1;//包括了1被吃的情况，该情况下子为0
            }
        }
        //已走胜率=1-未走胜率=1-1/6*掷后胜率，不使用循环来稍微加快运算
        backrate = (unpluspro[1]*plus[1]+unpluspro[2]*plus[2]+unpluspro[3]*plus[3]+unpluspro[4]*plus[4]+unpluspro[5]*plus[5]+unpluspro[6]*plus[6])/6;

        return backrate;
    }
};

#endif // ALGORITHM_H
