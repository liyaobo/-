#define _CRT_SECURE_NO_WARNINGS 1
#pragma   warning(push)
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
//����������easyX��չ
//��������ͼ���ö�ά��������ͼ
// 0#�յ� 1#ǽ 3#Ŀ�ĵ� 4#���� 5#��  7#������Ŀ�ĵص����
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

//���������ݴ���
IMAGE img[6];//��ʼ��img��ʽ����Դ,[6]������6��
int imgIndex[6] = { 0,1,3,4,5,7 };//���������Դ���±� 0��1��2��3��4��5��6
//�ؿ����Ʊ���
int cos = 0;
//������Դ ----�������ĳ�ʼ��|| ��ѧ��loadimage ��ʼ��IMAGE���� 
//loadimage ��������ʼ��ͼ���
void loadResource() 
{
	for (int i = 0; i < 6; i++) 
	{	
		char filename[20] = "";//��ʽ�����֡�(ע��ÿһ�ε�ѭ�������ĸ�ʽ���ڱ�)
		sprintf(filename, "%d.jpg", imgIndex[i]);//�ַ�����ʽ������Ҫ����Ϊ�Ѹ�ʽ��Ϊ��%d.jpg��������д��filename�����С�imageIdex[i]��37���Ѿ���������±�
		loadimage(img + i, filename,64,64);//64,64���������õ�ͼƬ��С����С64*64��imgԭ�����±�ֵ+i����imgIndex�е�ֵһһ��Ӧ����ص�filename���������
	}
}

void drawmap()//����ַ��ͼ
{
	int x, y;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//����ƽ����Ҫ��������x,y
			x = 64 * j;//����ͼƬ��64*64�ģ�������64*����������
			y = 64 * i;
			switch (map[cos][i][j])//��Ϸ״̬�ķ���������ÿ��λ��Ӧ��չ�ֳ�������ʲôͼ��
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
			case 8:				//��վ��Ŀ�ĵ���
				putimage(x, y, img + 4);
				break;
			case 7:				//���ӵ���Ŀ�ĵ�
				putimage(x, y, img + 5);
				break;
			}
		}
	}
}

void keyDown()
{
//����״��������Ŀ�ĵ����˱���
	int i, j;
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (map[cos][i][j] == 5 || map[cos][i][j] == 8)
				break;//����breakֻ������һ��ѭ����������for(j=0;j<8;j++)֮���ټ�һ��ifʹ�ÿ�����ȫ�˳�
		}
		if (map[cos][i][j] == 5 || map[cos][i][j] == 8)//�ڶ�������
			break;
	}
		/*��������
				I
				I
				I
				V
		*/
		char userKey/*��Ұ���*/ = _getch();//���ɼ����루��ѧ��
		switch (userKey)
		{//С�����������Ҽ���ֵ72  80  75  77
		case'W':
		case'w':
		case 72:
			//��һ����������Ա��ǿյػ�Ŀ�ĵ�
			if (map[cos][i - 1][j] == 0 || map[cos][i - 1][j] == 3)
			{
				map[cos][i - 1][j] += 5;
				map[cos][i][j] -= 5;
			}
			//�ڶ�����������Ա�������
			else if (map[cos][i - 1][j] == 4 || map[cos][i - 1][j] == 7)
			{//�ж������Ա����߲����յغ�Ŀ�ĵء�
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
			{//�ж������Ա����߲����յغ�Ŀ�ĵء�
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
			{//�ж������Ա����߲����յغ�Ŀ�ĵء�
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
			{//�ж������Ա����߲����յغ�Ŀ�ĵء�
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
	printf("Ը�漲��ǰ�У���Լ���ɣ���������");
	IMAGE ����;
	loadimage(&����, "��������.jpg", 550, 700);
	initgraph(550, 700);
	putimage(0, 0, &����);
	getchar();
	closegraph();//�ر�ͼ��ϵͳ
}

void menu()
{
	printf("-------������--------\n");
	printf("�밴�س���������Ϸ��ҳ\n");
	printf("---------------------\n");
	printf("------0.��ʼ��Ϸ-------\n");
	printf("------1.�˳�--------------\n");
	while (1)
	{
		printf("��ѡ�����������\n");
		int item;
		scanf_s("%d", &item);
		switch (item)
		{
		case 0:
			//��ʼ��Ϸ
			break;
		case 1://�˳�
			exit(0);
		}
		break;
	}
	gameOverLayout();
}
int main()
{	
	menu();
	initgraph(64 * 8, 64 * 7);//initgraph��ʼ��ͼ��ϵͳ������ǰΪ�У����ź�Ϊ��,64���ڿ������п�Ĵ�СΪ64*64
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
	printf("�밴������˳���Ϸ");
	return 0;
}
