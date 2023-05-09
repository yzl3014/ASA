#pragma once
//以下宏定义值均*不可*为负数，否则会报错或崩溃。
#define	WIDTH	1000	//窗口宽度
#define	HEIGHT	600		//窗口高度
#define	SIDE	2		//方块长度

#define WAIT 0 //每次刷新显示间隔，单位ms。
#define NO_BORDER_MAX 300 //如果数据量超过此设定值，方块将无边框。反之则有
#define ONE_BY_ONE 1 //在生成数据时缓慢显示，以表现动画感觉。1打开，0关闭。
const int BLOCKS_NUM = WIDTH / SIDE; //方块总个数（根据窗口宽度计算得出）