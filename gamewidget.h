#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <QLineEdit>
#include <QFont>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QFileDialog>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include <QLineF>
#include <QString>
#include <QTextCodec>
#include <QTextStream>
#include <QEvent>



#include "clickedlabel.h"
#include "algorithm.h"


class GameWidget : public QWidget
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = nullptr);
    ~GameWidget();


    static bool isWindow_GameOpen;//用以记录游戏窗口是否打开

    //重写
    //void paintEvent(QPaintEvent *);

    //尺寸位置数
    const int ButtonXlength = 125;//按钮间隔横长
    const int ButtonYlength = 80;//按钮间隔竖长
    const int ButtonXline = 600;//按钮阵列起点横坐标
    const int ButtonYline = 20;//按钮阵列起点纵坐标
    const int ButtonXsize = 100;//按钮横尺寸
    const int ButtonYsize = 60;//按钮竖尺寸

    const int BoardXline = 25;//棋盘阵列起点横坐标
    const int BoardYline = 20;//棋盘阵列起点纵坐标
    const int BoardLength = 100;//棋盘单位边长

    const int LabelXline = ButtonXline;//标签起点横坐标
    const int LabelYline = 325;//标签起点纵坐标
    const int SpaceUnderLabel = 20; //标签下方间距
    const int LabelYlength = 50;//标签间隔竖长
\
    //槽函数
    void Do_SwichControl_R();
    void Do_SwichControl_B();
    void Do_SwichControl_N();

    void Do_AIconrolMove();
    void Do_CreateMannual();
    void Do_ProduceRandom();
    void Do_RetractMove();
    void Do_RedoMove();
    void Do_SwichGameModel();


    //非槽函数
    void Refurbish();//棋盘显示刷新
    void RefurColor();//刷新随机数颜色
    void ChessMoveTo(int);//棋子移动时做的事,参数为移动到的位置，需预先设定提起棋子和位置
    void EndLayout();//结束布局，对局正式开始前的设置
    //void BeforeAlgorithm();//算法执行前的数据变换操作
    /*
    bool iEnableOperator = true;//控制控件是否可以操作

    bool eventFilter(QObject *obj, QEvent *event){//如果变量为真，过滤掉画图以外的操作
        if (iEnableOperator == true)
        {
            if(event->type() == QEvent::Paint)
                return false;
            else
                return true;
        }
        else
        {
             return QWidget::eventFilter(obj, event);
        }
    };
    */

    int Random6(){//1~6的随机数生成
        int back = qrand() % 6 + 1;
        return back;
    }

    int Poi(int point)//点数转换为具体点数
    {
        int thepoint = (point - 1) % 6 + 1;
        return thepoint;
    }

    //原chessmanual.h文件内容
    int LOGlayout[12];//初始布局记录，参数为角区位置
    int LayoutToPlace[12] = {0,1,2,5,6,10,14,18,19,22,23,24};//布局号数转位置
    QString PlaceToManual[25] = {
        "A5", "B5", "C5", "D5", "E5",
        "A4", "B4", "C4", "D4", "E4",
        "A3", "B3", "C3", "D3", "E3",
        "A2", "B2", "C2", "D2", "E2",
        "A1", "B1", "C1", "D1", "E1"
    };
    QString SideToManual[2] = {"R", "B"};//0为红方R,1为蓝方B
    QString TextWhichWin;//"先手胜"或"后手胜"的字符串
    QString Player_address = "重庆";

    int MaxRound_CanRedo = 0;//最大能重做到的回合数
    //以下数据在每次棋子移动时储存（不包括放回原位），都用于悔棋，注意务必在gamewidget构析时delete
    int *LOGmovechess = new int[100];//移动棋子记录，参数为回合,注意记录时要是正数，用于棋谱
    int *LOGmoveplace = new int[100];//移动到的位置记录，参数为回合，用于棋谱
    int *LOGmovepoint = new int[100];//随机数点数记录，参数为回合
    int *LOGbeeaten = new int[100];//被吃棋子记录，参数为回合
    int *LOGbemove = new int[100];//移动的棋子原位置记录，参数为回合

    //原rule.h文件的内容

    int GameModel = 1;//预设游戏模式,0为测试模式，1为比赛模式，2为试玩模式

    int Layout_Status = -2;//布局状态，-2为交换棋子阶段，-1为交换棋子提起，0为行棋阶段，1为提起棋子
    int ChessBoard[25] = {0};//棋盘对应棋子，0为没有棋子，1~6为己方，7~12为对方
    //显示和保存时，加上上一步位置显示

    int Round = 1;//回合
    int Takeup_Place = -1;//拿起棋子的位置,-1代表没有提起
    int Takeup_Chess = -1;//拿起棋子的编号,-1代表没有提起
    int Rnd_color = 1;//随机数颜色，0为红，1为蓝
    int Rnd_Point = 0;//随机数点数，1~6
    int ActSide = 0;//行动方，0为对方，1为己方
    int Numb_Calculagraph[2] = {0};//双方的计时，0为红，1为蓝
    bool isRun_Calculagraph = false;//是否在计时的标志

    int ControlSide = 0;//算法控制方，0为红方，1为蓝方，2为不控制
    int ChessPlaceT[13];//1~6为己方，7~12为对方,用于传导数据进入对象计算,不用于实际记录局面

    void LayoutOfPlace()//位置布局
    {
        ChessBoard[0]=6,    ChessBoard[1]=2,    ChessBoard[2]=4,
        ChessBoard[5]=1,    ChessBoard[6]=5,
        ChessBoard[10]=3;
                                                ChessBoard[14]=9,
                            ChessBoard[18]=11,  ChessBoard[19]=7,
        ChessBoard[22]=10,  ChessBoard[23]=8,  ChessBoard[24]=12;
    }

    void setChessPlaceT(int actside){//算法执行前的转换，主要是ChessPlaceT的传递,参数为行动方
        //以算法为基准，参数则为ControlSide，以回合为基准，参数则为(Round + 1) % 2)
        for(int point = 1; point <= 12; point++){
            ChessPlaceT[point] = 25;
        }//清空棋子位置数组设为被吃

        //如果红方为行动方
        if(actside == 0){
            for(int place = 0; place < 25; place++){
                if(ChessBoard[place] > 0){
                    ChessPlaceT[ChessBoard[place]] = place;//正常获取棋子位置
                }
            }
        }
        //如果蓝方为行动方
        else{
            for (int place = 0; place < 25; place++){
                if(ChessBoard[place] > 0){
                    ChessPlaceT[ChessBoard[place]] = 24 - place;//对换获取棋子位置
                }
            }
            for (int point = 1, exch; point <= 6; point++) {//颜色互换
                exch = ChessPlaceT[point];
                ChessPlaceT[point] = ChessPlaceT[point + 6];
                ChessPlaceT[point + 6] = exch;
            }
        }
    }

    int IsGameover(){//判断是否对局结束条件达成，0为未达成，1为红方达成，2为蓝方达成
        bool alleaten_R = true;//红方全被吃，蓝胜
        bool alleaten_B = true;//蓝方全被吃，红胜
        if(ChessBoard[24] <= 6 && ChessBoard[24] >= 1){//蓝方角区为红方棋子
            return 1;//红方胜
        }
        if(ChessBoard[0] <= 12 && ChessBoard[0] >= 7){//红方角区为蓝方棋子
            return 2;//蓝方胜
        }
        for(int place = 0; place < 25; place++){
            if(ChessBoard[place] <= 6 && ChessBoard[place] >= 1){
                alleaten_R = false;
                break;
            }
        }
        if(alleaten_R == true){//如果红方全被吃，蓝方胜
            return 2;
        }
        for(int place = 0; place < 25; place++){
            if(ChessBoard[place] <= 12 && ChessBoard[place] >= 7){
                alleaten_B = false;
                break;
            }
        }
        if(alleaten_B == true){//如果蓝方全被吃，红方胜
            return 1;
        }
        return 0;//否则游戏结束条件未达成
    }

    int IsLegalTakeup(int pointin) {//判断行棋阶段提子是否合法，1为合法，-1为还未掷出本回合骰子，-2为提子颜色不合法，-3为提子点数不合法
        if (GameModel == 0) {//测试模式不受限制，认为合法
            return 1;
        }
        int back = 1;//预设合法
        int pointnc = (pointin - 1) % 6 + 1;//no color没有颜色的点数
        setChessPlaceT((Round + 1) % 2);//设定ChessPlaceT，主要是ChessPlaceT的传递
        int uordchess[2];//参数为0是上子，参数为1是下子
        uordchess[0] = 7;//当前随机数的上子，包括等于当前随机数的情况，初始为不存在时的值，基于1~6
        uordchess[1] = 0;//当前随机数的下子，初始为不存在时的值，基于1~6
        for (int point = Rnd_Point; point <= 6; point++) {//对于己方棋子，计算基于当前随机数的上下子
            if(ChessPlaceT[point] < 25){//若棋子存活,计算当前随机数的上子
                uordchess[0] = point;
                break;
            }
        }
        if(uordchess[0] != Rnd_Point){//上子不为当前随机数才存在下子
            for (int point = Rnd_Point - 1; point >= 1; point--) {//对于己方棋子，计算基于当前随机数的上下子
                if(ChessPlaceT[point] < 25){//若棋子存活,计算当前随机数的下子
                    uordchess[1] = point;
                    break;
                }
            }
        }

        if (Rnd_color != (Round + 1) % 2) {//如果随机数颜色和回合数不匹配，即本回合没有掷骰子
            back = -1;
            QMessageBox::information(NULL, "提子不合法", "行棋前请先掷骰子（点击产生随机数）");
        }else if ((pointin - 1) / 6 != (Round + 1) % 2) {//如果提子和回合数不匹配,即提子颜色不合法
            back = -2;
            QString colorname[2] = {"红", "蓝"};
            QMessageBox::information(NULL, "提子不合法", "现在为" + colorname[(Round + 1) % 2] + "方回合");
        }else if ((pointnc != uordchess[0] && pointnc != uordchess[1])) {//如果走的棋子既不是上子也不是下子
            back = -3;
            if (uordchess[1] == 0){//如果不存在下子
                QMessageBox::information(NULL, "提子不合法", "你只能走棋子" + QString::number(uordchess[0], 10));
            }else if(uordchess[0] == 7){//如果不存在上子
                QMessageBox::information(NULL, "提子不合法", "你只能走棋子" + QString::number(uordchess[1], 10));
            }else {//上下子都存在
                QMessageBox::information(NULL, "提子不合法", "你只能走棋子" + QString::number(uordchess[0], 10) + "或" + QString::number(uordchess[1], 10));
            }
        }
        return back;
    }

    int IsLegalMove(int pointin, int place){//判断行棋是否合法，这个判断只会在提子后阶段出现,参数为落子位置
        if (GameModel == 0) {//测试模式不受限制，认为合法
            return 1;
        }
        int back = 0;//返回值，0代表不合法，1代表合法
        int pointnc = (pointin - 1) % 6 + 1;//no color没有颜色的点数
        setChessPlaceT((Round + 1) % 2);//设定ChessPlaceT，主要是ChessPlaceT的传递
        if ((Round + 1) % 2 == 1) {//若为蓝方
            place = 24 - place;//对落子位置互换
        }
        if ((ChessPlaceT[pointnc] != 4 && ChessPlaceT[pointnc] + 1 == place)
            ||(ChessPlaceT[pointnc] <= 19 && ChessPlaceT[pointnc] + 5 == place)
            ||(ChessPlaceT[pointnc] != 4 && ChessPlaceT[pointnc] <= 18 && ChessPlaceT[pointnc] + 6 == place)){
            back = 1;
        }else {

            QMessageBox::information(NULL, "落子不合法", "这个棋子不能落于此处");
        }
        return back;
    }



signals:
    //void Signal_LogOutput(QString); // 发出记录信号

public slots:
    void Do_LabelClick();//棋盘位置点击
    void Do_Calculagraph();//计时器
    void SwichRnd_Changed(int);


 private:
    QPushButton Button_SwichControl_R;
    QPushButton Button_SwichControl_B;
    QPushButton Button_SwichControl_N;
    QPushButton Button_AIconrolMove;
    QPushButton Button_CreateMannual;
    QPushButton Button_ProduceRandom;
    QPushButton Button_RetractMove;
    QPushButton Button_RedoMove;
    QPushButton Button_SwichGameModel;
    QComboBox ComboBox_SwichRnd;
    QLineEdit LineEdit_ShowRnd;
    QLineEdit LineEdit_WayWinrate[6];//不同走法的胜率
    QLabel Label_WayWinrate[6];//不同走法的胜率文本
    QLineEdit LineEdit_Calculagraph[2];//参数0为红方计时，参数2为蓝方计时
    QLabel Label_Calculagraph[2];//显示计时器框上方文本
    QLineEdit LineEdit_allSeachCountValue;//搜索节点总和
    QLabel Label_allSeachCountValue;//搜索末节点总和文本
    QLineEdit LineEdit_allUnSureValue;//不确定末节点总和
    QLabel Label_allUnSureValue;//不确定末节点总和文本
    QLineEdit LineEdit_SureValueRate;//不确定末节点总和
    QLabel Label_SureValueRate;//确切末节点比率
    QLineEdit LineEdit_SeachStep;//搜索层数文本
    QLabel Label_SeachStep;//搜索层数文本标签
    QLineEdit LineEdit_SeachtoReading;//搜索到棋谱数量文本
    QLabel Label_SeachtoReading;//搜索到棋谱数量文本标签


    QPixmap pixmap_Chessimg[14];//棋子图片
    Clickedlabel Label_Chessimg[25];//棋子位置框

    QTimer Timer_Calculagraph;//计时器
};
#endif // GAMEWIDGET_H
