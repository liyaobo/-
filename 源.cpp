#define _CRT_SECURE_NO_WARNINGS 1
#pragma   warning(push)
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
//运行徐下载easyX拓展
//首先做地图，用二维数组描绘地图
// 0#空地 1#墙 3#目的地 4#箱子 5#人  7#箱子在目的地的情况
int map[3][7][8] =
{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 3, 4, 0, 0, 4, 3, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 1, 1, 0, 1,
		1, 0, 0, 5, 0, 0, 0, 1,
		1, 3, 4, 0, 0, 4, 3, 1,
		1, 1, 1, 1, 1, 1, 1, 1,

		1, 1, 1, 1, 1, 1, 1, 1,
		1, 3, 4, 0, 0, 4, 3, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 3, 4, 0, 0, 4, 3, 1,
		1, 0, 1, 5, 0, 1, 0, 1,
		1, 3, 4, 0, 0, 4, 3, 1,
		1, 1, 1, 1, 1, 1, 1, 1,

		1, 1, 1, 1, 1, 1, 1, 1,
		1, 3, 4, 0, 0, 4, 3, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 5, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 1, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
};

//批量化数据处理
IMAGE img[6];//初始化img格式的资源,[6]代表共有6个
int imgIndex[6] = { 0,1,3,4,5,7 };//定义各个资源的下标 0，1，2，3，4，5，6
//关卡控制变量
int cos = 0;
//加载资源 ----》变量的初始化|| 才学的loadimage 初始化IMAGE变量 
//loadimage 是用来初始化图像的
void loadResource() 
{
	for (int i = 0; i < 6; i++) 
	{	
		char filename[20] = "";//格式化名字。(注：每一次的循环，它的格式都在变)
		sprintf(filename, "%d.jpg", imgIndex[i]);//字符串格式化，主要功能为把格式化为“%d.jpg”的数据写入filename变量中。imageIdex[i]在37行已经定义过了下标
		loadimage(img + i, filename,64,64);//64,64表明将引用的图片缩小至大小64*64，img原本的下标值+i后与imgIndex中的值一一对应后加载到filename数组变量中
	}
}

void drawmap()//给地址附图
{
	int x, y;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//贴出平面需要横纵坐标x,y
			x = 64 * j;//由于图片是64*64的，所以是64*。。。。。
			y = 64 * i;
			switch (map[cos][i][j])//游戏状态的分析，就是每个位置应该展现出来的是什么图像
			{
			case 0:
				putimage(x, y, img + 0);
				break;
			case 1:
				putimage(x, y, img + 1);
				break;
			case 3:
				putimage(x, y, img + 2);
				break;
			case 4:
				putimage(x, y, img + 3);
				break;
			case 5:
			case 8:				//人站在目的地上
				putimage(x, y, img + 4);
				break;
			case 7:				//箱子到达目的地
				putimage(x, y, img + 5);
				break;
			}
		}
	}
}

void keyDown()
{
//特殊状况：人在目的地与人本身
	int i, j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (map[cos][i][j] == 5 || map[cos][i][j] == 8)
				break;//由于break只能跳出一层循环，所以在for(j=0;j<8;j++)之外再加一个if使得可以完全退出
		}
		if (map[cos][i][j] == 5 || map[cos][i][j] == 8)//第二次跳出
			break;
	}
		/*按键部分
				I
				I
				I
				V
		*/
		char userKey/*玩家按键*/ = _getch();//不可见输入（刚学）
		switch (userKey)
		{//小键盘上下左右键的值72  80  75  77
		case'W':
		case'w':
		case 72:
			//第一种情况：人旁边是空地或目的地
			if (map[cos][i - 1][j] == 0 || map[cos][i - 1][j] == 3)
			{
				map[cos][i - 1][j] += 5;
				map[cos][i][j] -= 5;
			}
			//第二种情况：人旁边是箱子
			else if (map[cos][i - 1][j] == 4 || map[cos][i - 1][j] == 7)
			{//判断箱子旁边能走不。空地和目的地。
				if (map[cos][i - 2][j] == 0 || map[cos][i - 2][j] == 3)
				{
					map[cos][i - 2][j] += 4;
					map[cos][i - 1][j] += 1;
					map[cos][i][j] -= 5;
				}
			}
			break;
		case's':
		case'S':
		case 80:
			if (map[cos][i + 1][j] == 0 || map[cos][i + 1][j] == 3)
			{
				map[cos][i + 1][j] += 5;
				map[cos][i][j] -= 5;
			}
			else if (map[cos][i + 1][j] == 4 || map[cos][i + 1][j] == 7)
			{//判断箱子旁边能走不。空地和目的地。
				if (map[cos][i + 2][j] == 0 || map[cos][i + 2][j] == 3)
				{
					map[cos][i + 2][j] += 4;
					map[cos][i + 1][j] += 1;
					map[cos][i][j] -= 5;
				}
			}
			break;
		case'a':
		case'A':
		case 75:
			if (map[cos][i][j - 1] == 0 || map[cos][i][j - 1] == 3)
			{
				map[cos][i][j - 1] += 5;
				map[cos][i][j] -= 5;
			}
			else if (map[cos][i][j - 1] == 4 || map[cos][i][j - 1] == 7)
			{//判断箱子旁边能走不。空地和目的地。
				if (map[cos][i][j - 2] == 0 || map[cos][i][j - 2] == 3)
				{
					map[cos][i][j - 2] += 4;
					map[cos][i][j - 1] += 1;
					map[cos][i][j] -= 5;
				}
			}
			break;
		case'd':
		case'D':
		case 77:
			if (map[cos][i][j + 1] == 0 || map[cos][i][j + 1] == 3)
			{
				map[cos][i][j + 1] += 5;
				map[cos][i][j] -= 5;
			}
			else if (map[cos][i][j + 1] == 4 || map[cos][i][j + 1] == 7)
			{//判断箱子旁边能走不。空地和目的地。
				if (map[cos][i][j + 2] == 0 || map[cos][i][j + 2] == 3)
				{
					map[cos][i][j + 2] += 4;
					map[cos][i][j + 1] += 1;
					map[cos][i][j] -= 5;
				}
			
			}
			break;
		}
}
int gameOver()
{
	int  count = 1;
	for (int i = 0; i < 7; i++)
	{
		for (int j=0; j < 8; j++)
		{
			if (map[cos][i][j] == 4)
			{
				count = 0;
				return count;
			}
		}
		}
	return count;
}


void gameOverLayout()
{
	printf("愿随疾风前行，面对疾风吧！哈撒给！");
	IMAGE 结束;
	loadimage(&结束, "结束画面.jpg", 550, 700);
	initgraph(550, 700);
	putimage(0, 0, &结束);
	getchar();
	closegraph();//关闭图形系统
}

void menu()
{
	printf("-------推箱子--------\n");
	printf("请按回车键进入游戏首页\n");
	printf("---------------------\n");
	printf("------0.开始游戏-------\n");
	printf("------1.退出--------------\n");
	while (1)
	{
		printf("请选择操作的命令\n");
		int item;
		scanf_s("%d", &item);
		switch (item)
		{
		case 0:
			//开始游戏
			break;
		case 1://退出
			exit(0);
		}
		break;
	}
	gameOverLayout();
}
int main()
{	
	menu();
	initgraph(64 * 8, 64 * 7);//initgraph初始化图像系统，逗号前为列，逗号后为行,64用于控制运行框的大小为64*64
	while (1)
	{
		loadResource();
		drawmap();
		if (gameOver())
		{
			cos++;
			if (cos == 3)
				break;
		}
		keyDown();
	}
	gameOverLayout();
	closegraph();
	printf("请按任意键退出游戏");
	return 0;
}
