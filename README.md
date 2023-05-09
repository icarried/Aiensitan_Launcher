# Aiensitan_Launcher
爱恩斯坦棋启动器，内置结合小型残局库的搜索算法

使用QT5，推荐QT5.14

请勿直接在未进行任何算法修改或改进的情况下使用本项目参与任何竞赛，任何竞赛都需要体现参赛者的算法的创新或改进。

如果你基于本项目创新或改进的算法在竞赛中获奖，希望在竞赛结束后将获奖算法进行开源，促进爱恩斯坦棋博弈项目发展（不作强制要求）。

使用三个线程进行计算，包括主进程，计算时主进程的界面也会暂停运作。

使用结合残局数据库的搜索算法，当前版本使用残局数据库为（0001110001110），即搜索到双方均剩编号余123的棋或更少时即触发直接获取准确胜率（即便如此，该小型残局库仍然占据了约2.3GB），release不支持2GB以上文件，因此请通过百度云盘下载链接：https://pan.baidu.com/s/1ZeUfGD7K8aFp--UTlSRdmA 提取码：i88a 

![image](https://user-images.githubusercontent.com/54706854/229297803-465d631a-8478-4814-bac8-7756d832425a.png)

请在开始新对局前加载残局库，一个6棋子残局库占据2.6GB内存，请确保内存充足。若未关闭启动器，通过左上角的“gmae->newgame”选项重新开始新游戏无需重新加载数据库，你可以通过该选项快速开始一局新游戏。

![image](https://user-images.githubusercontent.com/54706854/229297875-89072a7b-6d38-4140-a43b-a55d2abbb628.png)

对局有三种模式，包括1.“比赛模式”（默认），该模式下所有的操作都会经过合规性检查，并且会在对局结束弹出棋谱信息填写（棋谱目前编码问题尚未解决）；2.试玩模式，包括合规性检查，该模式下程序方自动摇骰子自动行棋，无需多余操作（试玩推荐）；3.测试模式，不含合规性检查，结束布局后即可随意移动。

![image](https://user-images.githubusercontent.com/54706854/229297907-eb29c678-cf8f-4334-ac06-72dad740a346.png)

程序控制有三种方式，当你选择自己作为红方与蓝方AI对局时，请选择蓝方程序控制，反之亦然。当进行非AI双人对局是，请选择程序不控制。在选中控制方前为布局阶段，先点击一个棋子，再点击另一个棋子，即可交换棋子位置，点击一个棋子后再点击原位置可放回原位。选中控制模式后即结束布局，进行行棋阶段。

![image](https://user-images.githubusercontent.com/54706854/229298137-17586e1c-ce0d-4a6b-add1-99351c1cd6a7.png)

每次行棋前需要产生新的随机数（摇骰子），依照生成的随机数决定可行棋的棋子，随机数的颜色为当前行棋方。

![image](https://user-images.githubusercontent.com/54706854/229298373-77bea016-bb1f-4b30-bcc0-cbf76c073d25.png)

在比赛模式和测试模式下，AI行棋须点击“AI移动”，AI会依照当前已生成的随机数计算移动；试玩模式下AI会自动行动。

![image](https://user-images.githubusercontent.com/54706854/229298642-22dd97c2-6e8c-4c97-92ee-2a6c035bb7bf.png)

程序计算得到的每种走法胜率和其他胜率计算参数都会显示。

![image](https://user-images.githubusercontent.com/54706854/229298798-c44cc3d3-e825-464e-9a54-b55b23b34064.png)

对局结束后点击“输出棋谱”并输入信息后可以把对局过程的棋谱输出（编码问题未解决），比赛模式下一方胜利达成时会自动触发输出棋谱。

对局完成后再次点击gmae->newgame选项开启新对局。

AI搜索层数由当前棋子数动态调整。



未解决问题：

生成棋谱的编码格式存在问题，无法以GB2312格式读取。棋谱部分的代码无法移植到QT6 。

加载任意残局库未完成，目前只能指定加载指定棋子次序的残局库。
