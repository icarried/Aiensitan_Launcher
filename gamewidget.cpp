//该程序由 哈尔滨理工大学测控18-6陈泳吉 独立制作
#include "gamewidget.h"

#include <QString>
#include<QPainter>

bool GameWidget::isWindow_GameOpen = false;

GameWidget::GameWidget(QWidget *parent)
    : QWidget(parent)
{
    GameWidget::isWindow_GameOpen = true;
    //窗口设置
    //setWindowTitle("HRBUST");
    resize(1000, 550);

    //设置一个控件包括在whidget.h的声明、父对象和位置和尺寸的设置、信号槽、槽函数

    //按钮
    Button_SwichControl_R.setParent(this);
    Button_SwichControl_R.setText(" 程序控制红方");
    Button_SwichControl_R.move(ButtonXline + ButtonXlength * 0, ButtonYline + ButtonYlength * 0);
    Button_SwichControl_R.resize(ButtonXsize, ButtonYsize);

    Button_SwichControl_B.setParent(this);
    Button_SwichControl_B.setText(" 程序控制蓝方");
    Button_SwichControl_B.move(ButtonXline + ButtonXlength * 1, ButtonYline + ButtonYlength * 0);
    Button_SwichControl_B.resize(ButtonXsize, ButtonYsize);

    Button_SwichControl_N.setParent(this);
    Button_SwichControl_N.setText(" 程序不控制");
    Button_SwichControl_N.move(ButtonXline + ButtonXlength * 2, ButtonYline + ButtonYlength * 0);
    Button_SwichControl_N.resize(ButtonXsize, ButtonYsize);

    Button_CreateMannual.setParent(this);
    Button_CreateMannual.setText(" 生成棋谱");
    Button_CreateMannual.move(ButtonXline + ButtonXlength * 0, ButtonYline + ButtonYlength * 1);
    Button_CreateMannual.resize(ButtonXsize, ButtonYsize);


    Button_RetractMove.setParent(this);
    Button_RetractMove.setText(" 悔棋");
    Button_RetractMove.move(ButtonXline + ButtonXlength * 2, ButtonYline + ButtonYlength * 1);
    Button_RetractMove.resize(ButtonXsize, ButtonYsize);

    Button_RedoMove.setParent(this);
    Button_RedoMove.setText(" 重做");
    Button_RedoMove.move(ButtonXline + ButtonXlength * 2, ButtonYline + ButtonYlength * 3);
    Button_RedoMove.resize(ButtonXsize, ButtonYsize);

    Button_AIconrolMove.setParent(this);
    Button_AIconrolMove.setText("AI移动");
    Button_AIconrolMove.move(ButtonXline + ButtonXlength * 0, ButtonYline + ButtonYlength * 2);
    Button_AIconrolMove.resize(ButtonXsize, ButtonYsize);

    Button_ProduceRandom.setParent(this);
    Button_ProduceRandom.setText(" 生成随机数");
    Button_ProduceRandom.move(ButtonXline + ButtonXlength * 2, ButtonYline + ButtonYlength * 2);
    Button_ProduceRandom.resize(ButtonXsize, ButtonYsize);



    Button_SwichGameModel.setParent(this);
    Button_SwichGameModel.setText(" 切换模式");
    Button_SwichGameModel.move(ButtonXline + ButtonXlength * 1, ButtonYline + ButtonYlength * 1);
    Button_SwichGameModel.resize(ButtonXsize, ButtonYsize);


    //下拉列表框
    ComboBox_SwichRnd.setParent(this);//随机数选择框
    ComboBox_SwichRnd.move(ButtonXline + ButtonXlength * 1, ButtonYline + ButtonYlength * 3);
    ComboBox_SwichRnd.resize(ButtonXsize,20);
    for (int point = 0; point <= 6; point++) {
            ComboBox_SwichRnd.addItem(QString::number(point, 10));
    }

    //文本输入框
    LineEdit_ShowRnd.setParent(this);//随机数显示框
    LineEdit_ShowRnd.move(ButtonXline + ButtonXlength * 1, ButtonYline + ButtonYlength * 2);
    LineEdit_ShowRnd.resize(ButtonXsize,ButtonYsize);
    LineEdit_ShowRnd.setTextMargins(25,5,25,5);
    LineEdit_ShowRnd.setText("0");
    LineEdit_ShowRnd.setFont(QFont("timers", 50, QFont::Bold));
    LineEdit_ShowRnd.setReadOnly(true);

    QString WordOfWayWinrate[6] = {"上子横走", "上子竖走", "上子斜走", "下子横走", "下子竖走", "下子斜走"};
    for (int order = 0, xline =ButtonXline + ButtonXlength * 0, yline = LabelYline + LabelYlength * 1 ,xlength = ButtonXlength, ylength = 50; order < 6; order++){//各走法胜率显示
        LineEdit_WayWinrate[order].setParent(this);
        LineEdit_WayWinrate[order].resize(100,20);
        LineEdit_WayWinrate[order].move(xline + order % 3 * xlength, yline + order / 3 * ylength + 20);//比文本低20像素
        LineEdit_WayWinrate[order].setText("NULL");
        LineEdit_WayWinrate[order].setReadOnly(true);

        Label_WayWinrate[order].setParent(this);
        Label_WayWinrate[order].resize(100,20);
        Label_WayWinrate[order].move(xline + order % 3 * xlength, yline + order / 3 * ylength);
        Label_WayWinrate[order].setText(WordOfWayWinrate[order]);
    }

    //计时器
    LineEdit_Calculagraph[0].setParent(this);//红方计时器显示
    LineEdit_Calculagraph[0].move(ButtonXline + ButtonXlength * 0, 65);
    LineEdit_Calculagraph[0].resize(ButtonXsize,20);
    LineEdit_Calculagraph[0].setText("0");
    LineEdit_Calculagraph[0].setReadOnly(true);

    Label_Calculagraph[0].setParent(this);//红方计时器文本
    Label_Calculagraph[0].move(ButtonXline + ButtonXlength * 0, 45);
    Label_Calculagraph[0].resize(ButtonXsize,20);
    Label_Calculagraph[0].setText("红方计时器");

    LineEdit_Calculagraph[1].setParent(this);//蓝方计时器显示
    LineEdit_Calculagraph[1].move(ButtonXline + ButtonXlength * 2, 65);
    LineEdit_Calculagraph[1].resize(ButtonXsize,20);
    LineEdit_Calculagraph[1].setText("0");
    LineEdit_Calculagraph[1].setReadOnly(true);

    Label_Calculagraph[1].setParent(this);//蓝方计时器文本
    Label_Calculagraph[1].move(ButtonXline + ButtonXlength * 2, 45);
    Label_Calculagraph[1].resize(ButtonXsize,20);
    Label_Calculagraph[1].setText("蓝方计时器");

    //搜索数值记录
    LineEdit_allSeachCountValue.setParent(this);//搜索节点总和，比文本低20像素
    LineEdit_allSeachCountValue.move(ButtonXline + ButtonXlength * 0, LabelYline + LabelYlength * 0 + SpaceUnderLabel);
    LineEdit_allSeachCountValue.resize(ButtonXsize,20);
    LineEdit_allSeachCountValue.setText("NULL");
    LineEdit_allSeachCountValue.setReadOnly(true);

    Label_allSeachCountValue.setParent(this);//搜索末节点总和文本
    Label_allSeachCountValue.move(ButtonXline + ButtonXlength * 0, LabelYline + LabelYlength * 0);
    Label_allSeachCountValue.resize(ButtonXsize,20);
    Label_allSeachCountValue.setText("<搜索总末节点数>");

    LineEdit_allUnSureValue.setParent(this);//不确定末节点总和，比文本低20像素
    LineEdit_allUnSureValue.move(ButtonXline + ButtonXlength * 1, LabelYline + LabelYlength * 0 + SpaceUnderLabel);
    LineEdit_allUnSureValue.resize(ButtonXsize,20);
    LineEdit_allUnSureValue.setText("NULL");
    LineEdit_allUnSureValue.setReadOnly(true);

    Label_allUnSureValue.setParent(this);//不确定末节点总和文本
    Label_allUnSureValue.move(ButtonXline + ButtonXlength * 1, LabelYline + LabelYlength * 0);
    Label_allUnSureValue.resize(ButtonXsize,20);
    Label_allUnSureValue.setText("<不确定末节点数>");

    LineEdit_SureValueRate.setParent(this);//比文本低20像素
    LineEdit_SureValueRate.move(ButtonXline + ButtonXlength * 2, LabelYline + LabelYlength * 0 + SpaceUnderLabel);
    LineEdit_SureValueRate.resize(ButtonXsize,20);
    LineEdit_SureValueRate.setText("NULL");
    LineEdit_SureValueRate.setReadOnly(true);

    Label_SureValueRate.setParent(this);//确切末节点比率文本
    Label_SureValueRate.move(ButtonXline + ButtonXlength * 2, LabelYline + LabelYlength * 0);
    Label_SureValueRate.resize(ButtonXsize,20);
    Label_SureValueRate.setText("<确切末节点比率>");

    LineEdit_SeachStep.setParent(this);//比文本低20像素
    LineEdit_SeachStep.move(ButtonXline + ButtonXlength * 0, LabelYline + LabelYlength * 3 + SpaceUnderLabel);
    LineEdit_SeachStep.resize(ButtonXsize,20);
    LineEdit_SeachStep.setText("NULL");
    LineEdit_SeachStep.setReadOnly(true);

    Label_SeachStep.setParent(this);//搜索层数
    Label_SeachStep.move(ButtonXline + ButtonXlength * 0, LabelYline + LabelYlength * 3);
    Label_SeachStep.resize(ButtonXsize,20);
    Label_SeachStep.setText("<搜索层数>");

    LineEdit_SeachtoReading.setParent(this);//比文本低20像素
    LineEdit_SeachtoReading.move(ButtonXline + ButtonXlength * 1, LabelYline + LabelYlength * 3 + SpaceUnderLabel);
    LineEdit_SeachtoReading.resize(ButtonXsize,20);
    LineEdit_SeachtoReading.setText("NULL");
    LineEdit_SeachtoReading.setReadOnly(true);

    Label_SeachtoReading.setParent(this);//搜索到残局库数
    Label_SeachtoReading.move(ButtonXline + ButtonXlength * 1, LabelYline + LabelYlength * 3);
    Label_SeachtoReading.resize(ButtonXsize,20);
    Label_SeachtoReading.setText("<搜索到残局库数>");



    //棋子图片
    pixmap_Chessimg[0].load(":/chessimg/img/0.jpg");
    pixmap_Chessimg[1].load(":/chessimg/img/1.jpg");
    pixmap_Chessimg[2].load(":/chessimg/img/2.jpg");
    pixmap_Chessimg[3].load(":/chessimg/img/3.jpg");
    pixmap_Chessimg[4].load(":/chessimg/img/4.jpg");
    pixmap_Chessimg[5].load(":/chessimg/img/5.jpg");
    pixmap_Chessimg[6].load(":/chessimg/img/6.jpg");
    pixmap_Chessimg[7].load(":/chessimg/img/-1.jpg");
    pixmap_Chessimg[8].load(":/chessimg/img/-2.jpg");
    pixmap_Chessimg[9].load(":/chessimg/img/-3.jpg");
    pixmap_Chessimg[10].load(":/chessimg/img/-4.jpg");
    pixmap_Chessimg[11].load(":/chessimg/img/-5.jpg");
    pixmap_Chessimg[12].load(":/chessimg/img/-6.jpg");
    pixmap_Chessimg[13].load(":/chessimg/img/f.jpg");

    //棋盘
    for (int i = 0, xline = BoardXline, yline = BoardYline ,length = BoardLength; i < 25; i++) {
        Label_Chessimg[i].setParent(this);
        Label_Chessimg[i].setText(QString(i));
        Label_Chessimg[i].move(xline + i % 5 * length, yline + i / 5 * length);
        Label_Chessimg[i].lower();
    }


    //计时器
    Timer_Calculagraph.setParent(this);
    Timer_Calculagraph.setTimerType(Qt::VeryCoarseTimer);//设置为非常粗糙的计时器，减少CPU占用

    //信号槽
    connect(&Button_SwichControl_R, &QPushButton::pressed, this, &GameWidget::Do_SwichControl_R);
    connect(&Button_SwichControl_B, &QPushButton::pressed, this, &GameWidget::Do_SwichControl_B);
    connect(&Button_SwichControl_N, &QPushButton::pressed, this, &GameWidget::Do_SwichControl_N);
    connect(&Button_AIconrolMove, &QPushButton::pressed, this, &GameWidget::Do_AIconrolMove);
    connect(&Button_CreateMannual, &QPushButton::pressed, this, &GameWidget::Do_CreateMannual);
    connect(&Button_ProduceRandom, &QPushButton::pressed, this, &GameWidget::Do_ProduceRandom);
    connect(&Button_RetractMove, &QPushButton::pressed, this, &GameWidget::Do_RetractMove);
    connect(&Button_RedoMove, &QPushButton::pressed, this, &GameWidget::Do_RedoMove);
    connect(&Button_SwichGameModel, &QPushButton::pressed, this, &GameWidget::Do_SwichGameModel);
    connect(&ComboBox_SwichRnd, SIGNAL(currentIndexChanged(int)), this, SLOT(SwichRnd_Changed(int)));
    for(int place = 0; place <25; place++){//建立每个棋位的连接
        connect(&Label_Chessimg[place], SIGNAL(clicked()), this, SLOT(Do_LabelClick()));
    }
    connect(&Timer_Calculagraph, SIGNAL(timeout()), this, SLOT(Do_Calculagraph()));//通过start函数调用计时

    /* &Button_SwichControl_R: 信号的发出者，指针的类型  或  &发送的对象名
     * &QPushButton::pressed： 处理的信号，&发送的类名::信号的名字
     * this： 信号的接收者
     * &GameWidget::Do_SwichControl_R：槽函数，信号处理函数，&接收的类名::槽函数名字
     */

    //Lambda表达式，匿名函数对象

    //棋局初始设置
    LayoutOfPlace();//位置布局
    Refurbish();//刷新显示
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//随机数初始化

    //按钮隐藏
    Button_AIconrolMove.hide();
    Button_CreateMannual.hide();
    Button_ProduceRandom.hide();
    Button_RetractMove.hide();
    Button_RedoMove.hide();
    ComboBox_SwichRnd.hide();
    LineEdit_ShowRnd.hide();
    LineEdit_Calculagraph[0].hide();
    LineEdit_Calculagraph[1].hide();
    Label_Calculagraph[0].hide();
    Label_Calculagraph[1].hide();
    LineEdit_allSeachCountValue.hide();
    LineEdit_allUnSureValue.hide();
    Label_allSeachCountValue.hide();
    Label_allUnSureValue.hide();
    LineEdit_SureValueRate.hide();
    Label_SureValueRate.hide();
    LineEdit_SeachStep.hide();
    Label_SeachStep.hide();
    LineEdit_SeachtoReading.hide();
    Label_SeachtoReading.hide();

    for (int order = 0; order < 6; order++) {
        LineEdit_WayWinrate[order].hide();
        Label_WayWinrate[order].hide();
    }
}

//对局开始布置
void GameWidget::EndLayout(){//结束布局，对局正式开始前的设置
    //按键状态
    Button_SwichControl_R.hide();
    Button_SwichControl_B.hide();
    Button_SwichControl_N.hide();

    Button_CreateMannual.show();
    Button_ProduceRandom.show();
    Button_RetractMove.show();
    ComboBox_SwichRnd.show();
    LineEdit_ShowRnd.show();
    LineEdit_Calculagraph[0].show();
    LineEdit_Calculagraph[1].show();
    Label_Calculagraph[0].show();
    Label_Calculagraph[1].show();

    if (ControlSide == 1 || ControlSide == 0) {//若为程序控制
        LineEdit_allSeachCountValue.show();
        LineEdit_allUnSureValue.show();
        Label_allSeachCountValue.show();
        Label_allUnSureValue.show();
        LineEdit_SureValueRate.show();
        Label_SureValueRate.show();
        LineEdit_SeachStep.show();
        Label_SeachStep.show();
        LineEdit_SeachtoReading.show();
        Label_SeachtoReading.show();
        for (int order = 0; order < 6; order++) {
            LineEdit_WayWinrate[order].show();
            Label_WayWinrate[order].show();
        }
    }

    //还原特殊状态
    Takeup_Chess = -1;//变回未提状态
    Takeup_Place = -1;//变回未提状态
    Layout_Status = 0;//转为行棋阶段

    //信息记录
    for (int order = 0; order < 12; order++) {//记录初始布局，用于棋谱
        LOGlayout[order] = ChessBoard[LayoutToPlace[order]];
    }
    //试玩模式红方控制开局走子
    if (GameModel == 2 && ControlSide == 0) {//试玩模式开局红方控制中帮程序掷骰子走子一气呵成
        Do_ProduceRandom();//掷骰子
        Do_AIconrolMove();//走子
    }
}

// 槽函数
void GameWidget::Do_SwichControl_R()
{
    ControlSide = 0;//设置程序控制方
    EndLayout();//结束布局，对局正式开始前的设置
    Button_AIconrolMove.show();
}

void GameWidget::Do_SwichControl_B()
{
    ControlSide = 1;//设置程序控制方
    EndLayout();//结束布局，对局正式开始前的设置
    Button_AIconrolMove.show();
}

void GameWidget::Do_SwichControl_N()
{
    ControlSide = 2;//设置为无程序控制方
    EndLayout();//结束布局，对局正式开始前的设置
}

void GameWidget::Do_LabelClick(){//检查是哪个棋位被点击了
    for (int place = 0; place <25; place++) {
        if((Clickedlabel*) sender() == &Label_Chessimg[place])
        {
            switch (Layout_Status) {
            case -2://交换棋子阶段
                if(ChessBoard[place]){//如果该棋位不为0，即有棋子
                    Layout_Status = -1;//转为提起状态
                    Takeup_Place = place;//记下提起位置
                    Takeup_Chess = ChessBoard[place];//记下提起棋子
                    Refurbish();//刷新显示
                }
                break;
            case -1://交换棋子提起
                if(ChessBoard[place]){//如果该棋位不为0，即有棋子
                    Layout_Status = -2;//转为未提状态
                    ChessBoard[Takeup_Place] = ChessBoard[place];//交换棋子位置
                    ChessBoard[place] = Takeup_Chess;//交换棋子位置
                    Takeup_Chess = -1;//变回未提状态
                    Takeup_Place = -1;//变回未提状态
                    Refurbish();//刷新显示
                }
                break;
            case 0://行棋阶段
                if (ChessBoard[place] && GameModel != 0 && IsGameover()) {//如果不为测试模式且已游戏结束，则不能移动
                    QMessageBox::information(NULL, "提子不合法", "对局已结束");
                }
                else if(ChessBoard[place] && IsLegalTakeup(ChessBoard[place]) == 1){//如果该棋位不为0，即有棋子,且须提子合法
                    Layout_Status = 1;//转为提起状态
                    Takeup_Place = place;//记下提起位置
                    Takeup_Chess = ChessBoard[place];//记下提起棋子
                    Refurbish();//刷新显示
                }
                break;
            case 1://棋子提起
                if(place !=Takeup_Place && IsLegalMove(ChessBoard[Takeup_Place], place) == 1){//如果不是放回原位，则进行记录
                    //%如果不是放回原位，则进行记录
                    ChessMoveTo(place);
                    if (GameModel == 2 && (ControlSide == 1 || ControlSide == 0) && !IsGameover()) {//试玩模式中帮程序掷骰子走子一气呵成
                        Do_ProduceRandom();//掷骰子
                        Do_AIconrolMove();//走子
                    }
                }else{//如果是放回原位，不需要推移回合(落子不合法也放回原位)
                    Layout_Status = 0;//转为未提状态
                    Takeup_Chess = -1;//变回未提状态
                    Takeup_Place = -1;//变回未提状态
                    Refurbish();//刷新显示
                }
                break;
            default:
                break;
            }
            break;
        }
    }
}

void GameWidget::Do_AIconrolMove(){//AI移动
    if (GameModel != 0 && ControlSide != (Round + 1) % 2 ) {
        return;
    }
    if (Rnd_Point == 0) {//如果未掷骰子，则函数调用无效
        return;
    }
    setChessPlaceT(ControlSide);//进入算法操作前的准备，包括了操作蓝方时程序换方，主要是ChessPlaceT的传递
    int ordertodrift[3] = {1, 5, 6};//序号转偏移。偏移指横走+1，竖走+5，斜走+6
    int uordchess[2];//参数为0是上子，参数为1是下子
    uordchess[0] = 7;//当前随机数的上子，包括等于当前随机数的情况，初始为不存在时的值，基于1~6
    uordchess[1] = 0;//当前随机数的下子，初始为不存在时的值，基于1~6
    for (int point = 1; point <= 6; point++) {//对于己方棋子，计算基于当前随机数的上下子
        if(ChessPlaceT[point] < 25){//若棋子存活
            if(point >= Rnd_Point && point < uordchess[0]){//计算当前随机数的上子
                uordchess[0] = point;
            }else if(point < Rnd_Point && point > uordchess[1]){//计算当前随机数的下子
                uordchess[1] = point;
            }
        }
    }
    //20220713重新将各走法层数统一
    //以下直接计算层数后，生成对象再加给其层数
    int chessnumb = 0;
    int addSeachStep = 0;
    for (int point = 1; point <= 12; point++) {
        if(ChessPlaceT[point] < 25){//若棋子存活
            chessnumb++;
        }
    }
    if (chessnumb <= 8){
        addSeachStep += 1;
    }
    if (chessnumb <= 6){
        addSeachStep += 1;
    }
    if (chessnumb <= 5){
        addSeachStep += (6 - chessnumb);
    }

    if(uordchess[0] == Rnd_Point){
        //上子等于点数时，下子不存在
        uordchess[1] = 0;
    }
    Algorithm MoveWay[6];//定义6个算法对象，对应至多六种走法
    bool isExist[6];//某个对象是否存在
    int maxOrder = 0;//记录最大的走法胜率对应的走法次序
    double maxWinrate = 0;//记录最大的走法胜率
    for (int order = 0; order < 6; order++) {//将对象不存在的情况排除
        isExist[order] = 1;
        if(uordchess[0] == 7 && order / 3 == 0){//如果没有上子,用到了上子的对象不存在
            isExist[order] = 0;
        }else if(uordchess[1] == 0 && order / 3 == 1){//如果没有下子,用到了下子的对象不存在
            isExist[order] = 0;
        }else if(order == 0 && uordchess[0] > 0 && !(ChessPlaceT[uordchess[0]] % 5 != 4)){//上子横走但右边没位置，且上子存在
            isExist[order] = 0;
        }else if(order == 1 && uordchess[0] > 0 && !(ChessPlaceT[uordchess[0]] < 20)){//上子竖走但下边没位置，且上子存在
            isExist[order] = 0;
        }else if(order == 2 && uordchess[0] > 0 && !(ChessPlaceT[uordchess[0]] < 20 && ChessPlaceT[uordchess[0]] % 5 != 4)){//上子斜走但斜边没位置，且上子存在
            isExist[order] = 0;
        }else if(order == 3 && uordchess[1] < 7 && !(ChessPlaceT[uordchess[1]] % 5 != 4)){//下子横走但右边没位置，且上子存在
            isExist[order] = 0;
        }else if(order == 4 && uordchess[1] < 7 && !(ChessPlaceT[uordchess[1]] < 20)){//下子竖走但下边没位置，且上子存在
            isExist[order] = 0;
        }else if(order == 5 && uordchess[1] < 7 && !(ChessPlaceT[uordchess[1]] < 20 && ChessPlaceT[uordchess[1]] % 5 != 4)){//下子斜走但斜边没位置，且上子存在
            isExist[order] = 0;
        }
    }
    long long allSeachCountValue = 0;
    long long allUnSureValue = 0;
    long long allSeachtoReading = 0;
    int firstsign = -1;//存在的第一个走法的标志,将分配给主线程
    for (int order = 0; order < 6; order++) {//对每个对象进行计算
        if (isExist[order]){
            MoveWay[order].setAlgWay(ChessPlaceT, uordchess[order / 3], ordertodrift[order % 3]);//对对象设定其走法
            MoveWay[order].SeachStep += addSeachStep;//20220713修改统一加层
            if (firstsign == -1){
                firstsign = order;//分配存在的第一个走法给主线程
                LineEdit_SeachStep.setText(QString::number( MoveWay[order].SeachStep, 10));//用主进程取出搜索层数用于显示
            }else{
                MoveWay[order].start();//计算对象的胜率保存在AlgWinrate,分配给子线程
            }
        }
    }
    MoveWay[firstsign].CalWinrate();//分配完子线程后，对主线程进行计算

    while(1){//等待所有子线程执行完毕
        bool breakflag = true;
        for (int order = 0; order < 6; order++) {//对每个对象进行检验是否计算完成
            if(order != firstsign && isExist[order] && MoveWay[order].isFinished() == false){//如果存在的线程没有运行完,去除了主线程
                breakflag = false;
                break;
            }
        }
        if (breakflag == true){
            break;
        }
    }

    for (int order = 0; order < 6; order++) {//对每个对象进行处理
        if(isExist[order]){
            if(MoveWay[order].AlgWinrate >= maxWinrate){//取得最大胜率走法对应次序, 大于等于是为了防止胜率都是0就不走了
                maxOrder = order;
                maxWinrate = MoveWay[order].AlgWinrate;
            }
            LineEdit_WayWinrate[order].setText(QString::number(MoveWay[order].AlgWinrate));//用文本框显示胜率
            allSeachCountValue += MoveWay[order].SeachCountValue;//搜索总节点数计总
            allUnSureValue += MoveWay[order].UnSureValue;//不确定末节点计总
            allSeachtoReading += MoveWay[order].SeachtoReading;//搜索到棋谱数加总
        }else{
            LineEdit_WayWinrate[order].setText("NULL");//用文本框显示胜率
        }
    }
    LineEdit_allSeachCountValue.setText(QString::number( allSeachCountValue, 10));
    LineEdit_allUnSureValue.setText(QString::number( allUnSureValue, 10));
    LineEdit_SeachtoReading.setText(QString::number( allSeachtoReading, 10));
    if(allSeachCountValue != 0)
        LineEdit_SureValueRate.setText(QString::number( double(allSeachCountValue-allUnSureValue) / allSeachCountValue * 100) + '%');
    else
        LineEdit_SureValueRate.setText("NULL");
    Layout_Status = 1;//移动前先转为提起状态
    int movetoplace;//移动到位置
    if(!ControlSide){//如果红方为控制方
        Takeup_Chess = uordchess[maxOrder / 3];//取得这个走法是上子还是下子，进而取得移动棋子的编号
        Takeup_Place = ChessPlaceT[Takeup_Chess];
        movetoplace = Takeup_Place + ordertodrift[maxOrder % 3];//移动的到的位置为加上偏移量
    }else{//如果蓝方为控制方
        Takeup_Chess = 6 + uordchess[maxOrder / 3];//取得这个走法是上子还是下子，进而换为蓝方取得移动棋子的编号
        Takeup_Place = 24 - ChessPlaceT[Takeup_Chess - 6 ];//由于ChessPlaceT未换回颜色因此取红方的位置，取得后再换回位置
        movetoplace = Takeup_Place - ordertodrift[maxOrder % 3];//移动的到的位置为减去偏移量
    }
    ChessMoveTo(movetoplace);//调用位置移动函数
}

void GameWidget::Do_ProduceRandom(){
    RefurColor();//刷新随机数颜色显示
    Rnd_Point = Random6();//设置随机数点数
    LineEdit_ShowRnd.setText(QString::number(Rnd_Point));//设置显示随机数点数
}

void GameWidget::SwichRnd_Changed(int arg){//当随机数选择改变时,参数为0~5
    if(arg != 0){//清除默认选中不带操作
        RefurColor();//刷新随机数颜色显示
        Rnd_Point = arg;//设置随机数点数
        ComboBox_SwichRnd.setCurrentIndex(0);//清除默认选中
        LineEdit_ShowRnd.setText(QString::number(Rnd_Point));//设置显示随机数点数
    }
}

void GameWidget::Do_CreateMannual(){//生成棋谱按钮按下后
    if(Round <= 1){
        //%输出不可产生棋谱
    }
    else{
        QTextCodec *pCodec = QTextCodec::codecForName("GB2312");
        QTextCodec::setCodecForLocale(pCodec);
        //QString outwrite;
        //outwrite += (char)0xA3A3;
        //outwrite += (char)0xDECF30;
        //%打开模态窗口，输入数据
        //%输出数据
        QInputDialog inputfirsthand;//输入先手
        QString textfirsthand = QInputDialog::getText(this, "棋谱内容输入", "输入先手：");
        if(textfirsthand == NULL)
            return;

        QInputDialog inputlasthand;//输入后手
        QString textlasthand = QInputDialog::getText(this, "棋谱内容输入", "输入后手：");
        if(textlasthand == NULL)
            return;

        if(TextWhichWin == NULL){//由于游戏胜利会自动记录先手或后手胜，所以当已经记录时则跳过
            QInputDialog inputwhichwin;//输入先手胜或后手胜
            TextWhichWin = QInputDialog::getText(this, "棋谱内容输入", "输入先手胜或后手胜：");
        }

        QDateTime curdatetime = QDateTime::currentDateTime();//获取当前时间

        //%文件流产生文件
        QString manualpath = QFileDialog::getExistingDirectory(this, "选择保存到的路径", "/");
        if(manualpath != NULL){//如果选择了路径
            QFile manualfile;//创建文件对象
            QTextStream stream_manualfile(&manualfile);
            stream_manualfile.setCodec("GB2312");
            manualfile.setFileName(manualpath + "/" + "WTN-" + textfirsthand + "vs" + textlasthand + "-" + TextWhichWin + curdatetime.toString("yyyyMMddhhmm") + ".txt");
            bool isOK = manualfile.open((QIODevice::WriteOnly));
            if(isOK == true){


                //生成棋谱是生成之前回合的数据，不包括当前回合
                stream_manualfile << "#[" << textfirsthand << "][" << textlasthand << "][" << TextWhichWin << "]["
                        << curdatetime.toString("yyyy.MM.dd hh:mm") << " " << Player_address << "][" << curdatetime.toString("yyyy") << " CCGC];\n";
                //把记录数据输入棋谱
                stream_manualfile << "R:";
                for (int order = 0; order < 12; order ++) {
                    stream_manualfile << PlaceToManual[LayoutToPlace[order]] << "-" << QString::number(Poi(LOGlayout[order]), 10);
                    if(order == 5 || order == 11)
                        stream_manualfile << "\n";
                    else
                        stream_manualfile << ";";
                    if(order == 5)
                        stream_manualfile << "B:";
                }
                for (int theround = 1; theround < Round; theround ++) {
                    stream_manualfile << QString::number(theround, 10) << ":" << QString::number(LOGmovepoint[theround], 10)
                            << ";(" << SideToManual[((theround + 1) % 2)] << QString::number(Poi(LOGmovechess[theround]), 10)
                            << "," << PlaceToManual[LOGmoveplace[theround]] << ")\n";
                }
                /*
                 * setCodeforCString
                QByteArray array_outwrite;
                array_outwrite = outwrite.toUtf8();
                std::string str_outwrite = outwrite.toStdString();
                char* char_outwrite = (char*) str_outwrite.c_str();
                //outwrite = utf8ToGB2312(char_outwrite);
                array_outwrite = utf8ToGB2312(char_outwrite);
                manualfile.write(array_outwrite);
                */
                //stream_manualfile << 0xDECF30;
                //manualfile.write(pCodec->fromUnicode(outwrite));
                //stream_manualfile << pCodec->fromUnicode(outwrite);
                //stream_manualfile << pCodec->fromUnicode(outwrite);
            }
            manualfile.close();
        }
    }

}

void GameWidget::Do_RetractMove(){//悔棋
    if(Round < 2){//第一回合不能悔棋
        //%输出不能悔棋
    }else{
        Round--;//回到上一回合
        ChessBoard[LOGbemove[Round]] = LOGmovechess[Round];
        ChessBoard[LOGmoveplace[Round]] = LOGbeeaten[Round];
        Refurbish();//刷新显示

        //随机数显示
        Rnd_Point = LOGmovepoint[Round];
        RefurColor();//刷新随机数颜色显示
        LineEdit_ShowRnd.setText(QString::number(Rnd_Point));//设置显示随机数点数
        Button_RedoMove.show();//悔棋后可重做
    }
}

void GameWidget::Do_RedoMove(){
    if(Round + 1 > MaxRound_CanRedo){//有效防止移动后的还能重做的错误
        //%输出不能重做
    }else{
        ChessBoard[LOGbemove[Round]] = 0;//被移动的地方变为0
        ChessBoard[LOGmoveplace[Round]] = LOGmovechess[Round];//移到的地方棋子变为移动的棋子
        Rnd_Point = LOGmovepoint[Round];
        Round++;//回到下一回合
        Refurbish();//刷新显示

        //随机数显示
        RefurColor();//刷新随机数颜色显示
        LineEdit_ShowRnd.setText(QString::number(Rnd_Point));//设置显示随机数点数
    }
    if(Round == MaxRound_CanRedo){//达到最大可重做回合则隐藏
        Button_RedoMove.hide();
    }
}

void GameWidget::Do_SwichGameModel(){//切换模式,0为测试模式，1为比赛模式，2为试玩模式
    GameModel++;
    if (GameModel > 2) {//循环切换
        GameModel = 0;
    }
    switch (GameModel) {
        case 0:
            Button_SwichGameModel.setText("切换模式\n(当前为测试模式)");
        break;
        case 1:
            Button_SwichGameModel.setText("切换模式\n(当前为比赛模式)");
        break;
        case 2:
            Button_SwichGameModel.setText("切换模式\n(当前为试玩模式)");
        break;
        default:
        break;

    }

}

void GameWidget::Do_Calculagraph(){//计时，每满一秒调用一次
    int actside = (Round + 1) % 2;
    Numb_Calculagraph[actside]++;//记满一秒
    LineEdit_Calculagraph[actside].setText(QString::number(Numb_Calculagraph[actside], 10));
}


//非槽函数

void GameWidget::Refurbish(){//刷新显示
    for(int place = 0; place < 25; place ++){
        if(Takeup_Place == place){//如果是提起棋子的位置，显示上做个标记
            Label_Chessimg[place].setPixmap(pixmap_Chessimg[13]);//用纽扣图做标记
        }else{
            Label_Chessimg[place].setPixmap(pixmap_Chessimg[ChessBoard[place]]);//正常显示棋子
        }
    }
    if (isRun_Calculagraph == true){
        Timer_Calculagraph.stop();//暂停计时器
        isRun_Calculagraph = false;
    }
}

void GameWidget::ChessMoveTo(int place){//参数为棋子移动到的位置
    //为悔棋与棋谱功能做记录
    LOGmovechess[Round] = Takeup_Chess;
    LOGbemove[Round] = Takeup_Place;//提起的位置即为原位置
    LOGbeeaten[Round] = ChessBoard[place];//被吃棋子可以指“0”
    LOGmoveplace[Round] = place;
    LOGmovepoint[Round] = Rnd_Point;
    Layout_Status = 0;//转为未提状态
    ChessBoard[Takeup_Place] = 0;//从原位置离开
    ChessBoard[place] = Takeup_Chess;//到新的棋子位置,同时也替换掉了原棋子，相当于“吃”
    Takeup_Chess = -1;//变回未提状态
    Takeup_Place = -1;//变回未提状态
    Round++;//到下一回合
    MaxRound_CanRedo = Round;//用于回合重做的截止
    Button_RedoMove.hide();
    Refurbish();//刷新显示

    //对局结束执行
    int isgameover = IsGameover();//是否达成对局结束条件，1为红胜，2为蓝胜
    if(isgameover != 0){//如果游戏结束
        if(GameModel == 1){//如果为比赛模式
            if(isgameover == 1){//如果红胜
                TextWhichWin = "先手胜";
            }else{//如果蓝胜
                TextWhichWin = "后手胜";
            }
            Do_CreateMannual();//比赛模式下对局结束自动打开棋谱生成功能，防止忘记生成棋谱
        }else if(GameModel == 2){//如果为试玩模式
            if(isgameover == 1){//如果红胜
                TextWhichWin = "先手胜";
                QMessageBox::information(NULL, "对局结束", "红方胜");
            }else{//如果蓝胜
                TextWhichWin = "后手胜";
                QMessageBox::information(NULL, "对局结束", "蓝方胜");
            }

        }

    }
}

void GameWidget::RefurColor(){//刷新随机数颜色
    if(!((Round + 1) % 2)){//固定先手的单数回合为红色点数
        Rnd_color = 0;//随机数颜色变为红
        LineEdit_ShowRnd.setStyleSheet("color:red");//设为红色
    }else{//固定后手的双数回合为蓝色点数
        Rnd_color = 1;//随机数颜色变为蓝
        LineEdit_ShowRnd.setStyleSheet("color:blue");//设为蓝色
    }

    if (isRun_Calculagraph == false){
        Timer_Calculagraph.start(1000);//设定为每秒调用一次计时器槽函数
        isRun_Calculagraph = true;
    }
}


GameWidget::~GameWidget()
{
    delete [] LOGmovechess;
    delete [] LOGmoveplace;
    delete [] LOGmovepoint;
    delete [] LOGbeeaten;
    delete [] LOGbemove;
    GameWidget::isWindow_GameOpen = false;
}


