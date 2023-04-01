#include "loadwidget.h"

Reading LoadWidget::reading123;//静态全局初始化

LoadWidget::LoadWidget(QWidget *parent)
    : QFrame(parent)
{
    resize(LoadWidgetXsize,LoadWidgetYsize);
    setFrameShape(Panel);//边框形状为盒子
    setFrameShadow(Raised);//边框阴影为沉没
    setLineWidth(LineWidth);//设定边框大小
    //setFocusPolicy()
    //setAcceptDrops(true);

    Button_LoadWinrateFile.setParent(this);
    Button_LoadWinrateFile.setText(" 加载胜率库文件");
    Button_LoadWinrateFile.move(30, 40);
    Button_LoadWinrateFile.resize(325, 30);

    Button_ViewWinrateFilePath.setParent(this);
    Button_ViewWinrateFilePath.setText(" 浏览");
    Button_ViewWinrateFilePath.move(300, 13);
    Button_ViewWinrateFilePath.resize(55, 28);


    LineEdit_WinrateFilePath.setParent(this);
    LineEdit_WinrateFilePath.move(100, 15);
    LineEdit_WinrateFilePath.resize(200,25);
    LineEdit_WinrateFilePath.setText("non--");
    LineEdit_WinrateFilePath.setReadOnly(true);

    Label_WinrateFilePath.setParent(this);
    Label_WinrateFilePath.move(30, 15);
    Label_WinrateFilePath.resize(70,25);
    Label_WinrateFilePath.setText("胜率库路径：");

    TextEdit_LogOutput.setParent(this);
    TextEdit_LogOutput.move(600 - LineWidth *2, LineWidth *2);
    TextEdit_LogOutput.resize(400 - LineWidth,LoadWidgetYsize - LineWidth * 2*2);
    TextEdit_LogOutput.setFrameShape(Panel);//边框形状为盒子
    TextEdit_LogOutput.setFrameShadow(Sunken);//边框阴影为沉没
    TextEdit_LogOutput.setLineWidth(3);//设定边框大小
    //下面保持在最后一行添加(自动滚屏)
    TextEdit_LogOutput.setReadOnly(true);
    LogOutput("+程序已启动");


    //载入配置文件
    QSettings config_winrate(":/config/config_winrate.ini",QSettings::IniFormat);
    config_winrate.beginGroup("MAIN"); //可以理解为进入到 节 MAIN
    if(!config_winrate.childKeys().contains("file_path")){//判断节中是否存在键
        config_winrate.setValue("file_path","non"); //若不存在则创建并赋值为空
        LogOutput("|-胜率库路径键值不存在");
    }
    else{
        file_path = config_winrate.value("file_path").toString(); //存在则取出键值
        LineEdit_WinrateFilePath.setText(file_path);
    }
    config_winrate.endGroup();//beginGroup后必须endGroup ，可以理解为退出
    if(isFileExist(file_path)){//如果文件存在
        LogOutput("|+存在胜率库默认路径");
        LogOutput(" |-胜率库文件自动选择：" + file_path);
        LogOutput(" |-胜率库文件等待加载");
    }else{
        LogOutput("|+该文件不存在请重新选择");
        LogOutput(" |-需要浏览选择胜率库文件WinrateStorage.bin");
    }



   //信号槽
   connect(&Button_LoadWinrateFile, &QPushButton::pressed, this, &LoadWidget::Do_LoadWinrateFile);
   connect(&Button_ViewWinrateFilePath, &QPushButton::pressed, this, &LoadWidget::Do_ViewWinrateFilePath);
}

void LoadWidget::Do_LoadWinrateFile(){//按下后加载胜率库文件
    std::string cstr = Reading::QStrToCStr(file_path);
    replace(cstr.begin(), cstr.end(), '/', '\\'); //替换'/'为'\'
    QString qstr = Reading::CStrToQStr(cstr);
    //qDebug()<< qstr;
    LogOutput("|-路径已转译：" + qstr);
    LogOutput("|+正在加载中......");
    if((reading123.Bin_WinrateFile = fopen(cstr.c_str(),"rb")) == NULL){//如果不存在文件  备用isFileExist(file_path)
        LogOutput("|+该文件不存在请重新选择");
        LogOutput(" |-错误加载");
        LogOutput(" |-错误路径：" + file_path);
    }else{//如果存在路径
        for(long long i = 0;i < ALLsituation ;i++){
            fread(&reading123.Winrate[i], sizeof(double), 1, reading123.Bin_WinrateFile);
            //如果以后发现耗时太长可尝试每隔一定执行次数跳出一次显示a%b ==c cout
        }
        LogOutput("|-文件已成功加载");
        LogOutput("|-可以开始对局");
        qDebug()<<"Winrate72385 = "<< reading123.Winrate[72386] <<endl;//0.861111 4子
        qDebug()<<"Winrate72386 = "<< reading123.Winrate[72386] <<endl;//-1 4子
        qDebug()<<"Winrate72384 = "<< reading123.Winrate[72384] <<endl;//0.91358 4子
        qDebug()<<"Winrate184855190 = "<< reading123.Winrate[184855190] <<endl;//0.792018 6子
        qDebug()<<"Winrate25659607 = "<< reading123.Winrate[25659607] <<endl;//1.0 6子
        reading123.isLoad = true;//标志已加载
    }
    fclose(reading123.Bin_WinrateFile);
    reading123.Bin_WinrateFile = NULL;
}

void LoadWidget::Do_ViewWinrateFilePath(){//按下后浏览选择胜率库文件
    file_path = QFileDialog::getOpenFileName(this, "选择胜率库文件", "./","*.bin");
    config_winrate.beginGroup("MAIN"); //可以理解为进入到 节 MAIN
    if(file_path != NULL){//如果选择了路径
        config_winrate.setValue("file_path",file_path);
        LineEdit_WinrateFilePath.setText(file_path);
        LogOutput("|-胜率库文件选择：" + file_path);
        LogOutput("|-胜率库文件等待加载");
    }
    config_winrate.endGroup();//beginGroup后必须endGroup ，可以理解为退出
}

void LoadWidget::LogOutput(QString output){
    QTextCursor Cursor_LogOutput = TextEdit_LogOutput.textCursor();
    Cursor_LogOutput.movePosition(QTextCursor::End);
    TextEdit_LogOutput.setTextCursor(Cursor_LogOutput);
    TextEdit_LogOutput.append(output);
}


bool LoadWidget::isFileExist(QString fullfileName){//判断文件是否存在

    QFileInfo fileInfo(fullfileName);
    if(fileInfo.isFile()){
        return true;
    }
    return false;
}

LoadWidget::~LoadWidget()
{
}

