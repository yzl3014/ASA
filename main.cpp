/*       Animations of Sorting Algorithms     */
/*Programmer：Yzl3014[https://www.yuanzj.top/]*/
/*             2023.5.5-9 v0.1        (Age:14)*/
#include <stdio.h> //输入输出(控制台字符)
#include <conio.h> //键盘事件(控制台键盘)
#include <easyx.h> //画面绘制(基于EasyX)
#include <time.h>  //随机数和计时
#include <algorithm> //自带的各种算法
#include "configs.h" //必要的配置
using namespace std;


/*****各类定义*****/
int Nums[BLOCKS_NUM] = { 0 };//所有方块数值
int readNum = 0, moveNum = 0;//读取次数，操作次数。用于统计
double startClock, endClock;//开始计时时间，结束计时时间。字面意思：用于毫秒级计时。
wchar_t sortName[36] = L"未命名";//当前算法名称。用于在左上角显示信息，方便用户参考。

struct Block
{   /*状态：默认0，操作1,参考中2，完成10*/
	int status;
};
Block Blocks[BLOCKS_NUM];


/*****各类显示*****/
void showStatusText(TCHAR t[128])
{
	settextcolor(WHITE);//设置文字颜色：白色
	LOGFONT f;//定义字体配置
	gettextstyle(&f);
	f.lfHeight = 20;//字体大小
	wcscpy_s(f.lfFaceName, _T("微软雅黑"));//配置字体
	f.lfQuality = ANTIALIASED_QUALITY;//设置为抗锯齿效果
	settextstyle(&f);//设置文字输出字体为刚刚定义的字体
	outtextxy(10, 10, t);
	outtextxy(10, 30, L"By Yzl3014");
}
void makeBlocks()
{
	cleardevice();
	for (int a = 0; a <= BLOCKS_NUM - 1; a++)Nums[a] = a * (HEIGHT / BLOCKS_NUM) + 1;//将数组从小到大全部赋值，减一是为了防止缓冲区溢出
	srand(time(0) + rand());//置随机数种子（与易语言的一个函数名字一样）
	random_shuffle(Nums, Nums + BLOCKS_NUM - 1);//打乱数组
	for (int i = 0; i <= BLOCKS_NUM - 1; i++)//批量绘制柱子
	{
		int nowHeight = Nums[i] + 5;//当前绘制的柱子的高度
		fillrectangle(i * SIDE, HEIGHT - nowHeight, (i + 1) * SIDE, HEIGHT);//绘制方块
		/*绘制原理（按参数顺序解释）：左侧，即第i-1个方块的右侧，根据方块宽度易得；
		 * 高度，因为easyx是从上到下建立坐标系，所以需要减去；
		 * 右侧，即第i个方块左侧的位置加上方块宽度，所以只需要i+1即可得出；
		 * 底部，因为easyx是从上到下建立坐标系，所以最底部的坐标就是窗口高度。*/
		if (ONE_BY_ONE)Sleep(1);//逐个显示，更有动画的感觉
	}
	for (int i = 0; i <= BLOCKS_NUM - 1; i++)Blocks[i].status = 0;//重置所有方块状态为默认
}
void show()
{
	cleardevice();//清除画板
	if (BLOCKS_NUM <= NO_BORDER_MAX)setlinecolor(BLACK);//设置边框的线条颜色为黑色(方块填充默认有1像素的边框

	double nowLast = 0.0;//当前已消耗的时间
	if (endClock == 0)nowLast = (clock() - startClock) / 1000;
	else nowLast = (endClock - startClock) / 1000;
	for (int i = 0; i <= BLOCKS_NUM - 1; i++)//遍历所有数字，以此绘制方块
	{
		int nowHeight = Nums[i] + 5;
		switch (Blocks[i].status)
		{
		case 0://默认状态
			setfillcolor(WHITE); break;
		case 1://正在操作：读取
			setfillcolor(RED); break;
		case 2://正在参考（例如正在作为基准数）
			setfillcolor(YELLOW); break;
		case 10://已完成排序：方块/数值位置完全正确
			setfillcolor(GREEN); break;
		}
		if (BLOCKS_NUM <= NO_BORDER_MAX)fillrectangle(i * SIDE, HEIGHT - nowHeight, (i + 1) * SIDE, HEIGHT);
		else solidrectangle(i * SIDE, HEIGHT - nowHeight, (i + 1) * SIDE, HEIGHT);
	}
	TCHAR s[128];
	swprintf_s(s, _T("%s排序 | 数据量：%d | 移动次数：%d | 读取次数：%d | 耗时：%.3fs")
		, sortName, BLOCKS_NUM, moveNum, readNum, nowLast);
	//需要注意：上方函数中第二个参数需要传递[wchar_t]或者其指针，否则显示乱码或直接报错！
	showStatusText(s);
	FlushBatchDraw();
	Sleep(WAIT);
}


/*****数据操作*****/
void move(int a, int b)//移动数值/方块
{
	moveNum++;
	int temp = Nums[b];
	Nums[b] = Nums[a];
	Nums[a] = temp;
	Blocks[a].status = 1;
	Blocks[b].status = 1;
	show();//移动完之后显示该操作的结果
	Blocks[a].status = 0;
	Blocks[b].status = 0;
}
int read(int i)//读取数值/方块
{
	readNum++;
	Blocks[i].status = 1;
	show();
	Blocks[i].status = 0;
	//这里不显示(show函数)，因为下一次move或read操作会显示出来，并且这么快就变为默认，肉眼无法看出变化
	return Nums[i];
}


/*****排序算法*****/
void startBubbleSort()
{
	endClock = 0;
	_tcscpy_s(sortName, L"冒泡");//修改当前排序算法名称为冒泡排序。只能通过此函数赋值。
	startClock = clock();
	moveNum = 0;
	readNum = 0;

	for (int i = 0; i < BLOCKS_NUM - 1; i++) {
		for (int j = 0; j < BLOCKS_NUM - 1 - i; j++) {
			//这里判断时减去i，是因为每次遍历都会将剩余数值中的最大值“推”到最后，它也就到了正确位置无需再判断
			if (read(j) > read(j + 1))//本程序是按照从左到右，从小到大排列
				move(j, j + 1);
		}
		Blocks[BLOCKS_NUM - 1 - i].status = 10;//同上方注释理，这里将本此[遍历过的]最后一个数值设置为“完成”
	}
	Blocks[0].status = 10;

	endClock = clock();
	show();
}
void quickSort(int start, int end) {
	//默认数组为Nums
	if (start > end)return;//如果开始位置大于终止位置则本此排序完成
	int pivot = start, i = start, j = end;//进行左右指针和“基准”配置。
	//注意：本程序的基准在最左侧。这个小问题导致作者研究了近2小时。
	Blocks[pivot].status = 2;//设置“基准”，以便在show()中的显示时呈现黄色。
	while (i < j) {//在排序过程中j始终大于i，直到双指针在同一位置。
		while (Nums[j] >= Nums[pivot] && i < j)
		{//左侧为基准，则j从右侧先走，并且必须时刻注意i<j防止到达“指针碰撞”
			j--;
			readNum++;
		}
		while (Nums[i] <= Nums[pivot] && i < j) {
			//轮到i从左侧找了
			i++;
			readNum++;
		}
		if (i < j)move(i, j);//如果i<j则互换数值，然后重复上方操作，直到“指针碰撞”。
	}//此时i,j在同一位置，即基准值的正确位置。
	move(pivot, i);//按照算法，交换基准值和“碰撞”值。
	//本程序采用递归式快速排序！
	quickSort(start, i - 1);//首先排序本次已完成的数值（即基准值）左侧
	quickSort(i + 1, end);//然后是右侧的。
}
void startQuickSort()
{
	endClock = 0;
	_tcscpy_s(sortName, L"快速");//修改当前排序算法名称为冒泡排序。只能通过此函数赋值。
	startClock = clock();//开始计时

	quickSort(0, BLOCKS_NUM - 1);//本程序采用递归式快速排序，所以请到该函数查看算法

	endClock = clock();//结束计时
	for (int i = 0; i <= BLOCKS_NUM - 2; i = i + 2)
	{
		//排序已完成，将所有数值状态改为完成。
		Blocks[i].status = 10;
		Blocks[i + 1].status = 10;
		show();
	}
}
void startSelectionSort()//选择排序
{
	endClock = 0;
	_tcscpy_s(sortName, L"选择");//修改当前排序算法名称为冒泡排序。只能通过此函数赋值。
	startClock = clock();//开始计时

	for (int i = 0; i <= BLOCKS_NUM - 1; i++) {
		int min = i;
		Blocks[min].status = 2;
		for (int j = i + 1; j <= BLOCKS_NUM - 1; j++) {
			if (read(j) < Nums[min])
			{
				Blocks[min].status = 0;
				min = j;
				Blocks[min].status = 2;
			}
		}
		move(min, i);
		Blocks[i].status = 10;
	}

	endClock = clock();//结束计时
}
void startInsertionSort()//插入排序
{
	endClock = 0;
	_tcscpy_s(sortName, L"插入");//修改当前排序算法名称为冒泡排序。只能通过此函数赋值。
	startClock = clock();//开始计时

	int j, key;
	for (int i = 1; i <= BLOCKS_NUM - 1; i++)
	{
		key = Nums[i];//将i视为已完成值
		j = i - 1;//j从i-1开始向右扫描
		while (read(j) > key && j >= 0)
		{
			Nums[j + 1] = Nums[j];//如果read值比j大就一直向左移动 ；
			j--;
			show();
		}
		Nums[j + 1] = key;
	}

	endClock = clock();//结束计时
	for (int i = 0; i <= BLOCKS_NUM - 2; i = i + 2)
	{
		//排序已完成，将所有数值状态改为完成。
		Blocks[i].status = 10;
		Blocks[i + 1].status = 10;
		show();
	}
}

/*****主函数*****/
int main()
{
	initgraph(WIDTH, HEIGHT, EX_SHOWCONSOLE); //创建窗口
	makeBlocks();//生成由随机数组成的数组，并且以此绘制方块

	BeginBatchDraw();//开始批量绘制（提前准备）
INIT:
	/*显示左上角菜单*/
	TCHAR s[128];
	swprintf_s(s, _T("按键菜单：b冒泡排序 | s选择排序 | i插入排序 | q快速排序 | 0重置为最差情况"));
	showStatusText(s);
	FlushBatchDraw();//前面已经开始批量绘制，现在想显示必须flush
	char ch = _getch(), temp;
	if (ch == 'b') {
		startBubbleSort();//开始冒泡排序
	}
	else if (ch == 'q') {
		startQuickSort();//开始快速排序
	}
	else if (ch == 's')
	{
		startSelectionSort();//开始快速排序
	}
	else if (ch == 'i')
	{
		startInsertionSort();
	}
	else if (ch == '0') {
		EndBatchDraw();
		cleardevice();
		for (int a = 0; a <= BLOCKS_NUM - 1; a++)Nums[a] = (BLOCKS_NUM - a) * (HEIGHT / BLOCKS_NUM) - 5;
		for (int i = 0; i <= BLOCKS_NUM - 1; i++)//批量绘制柱子
		{
			int nowHeight = Nums[i] + 5;//当前绘制的柱子的高度
			fillrectangle(i * SIDE, HEIGHT - nowHeight, (i + 1) * SIDE, HEIGHT);//绘制方块
			if (ONE_BY_ONE)Sleep(1);
		}
		BeginBatchDraw();
		goto INIT;//如果输入的内容有误，直接重新获取
	}
	else goto INIT;//同上：如果输入的内容有误，直接重新获取

	while (TRUE)
	{
		show();//防止窗口被意外清除显示，如：窗口被拖拽到屏幕之外
		Sleep(1);
	}
	_getch();
	closegraph();//关闭窗口，结束程序
	return 0;
}