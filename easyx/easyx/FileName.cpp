#define _stprintf
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include <graphics.h>
#include <stdio.h>
#include <Windows.h>
#include <stdio.h>
#include <Windows.h>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#include<vector>
#include<ctime>
#include<conio.h>
#include<string>
#include<time.h>
#include <thread>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
int co = 0;
class Node
{
public:
	Node() :Node(0, 0, BLUE) {};
	Node(int x, int y, COLORREF color) :m_x(x), m_y(y), m_color(color) {};
	void draw()//画方块
	{
		setlinecolor(RED);
		setfillcolor(m_color);
		fillrectangle(m_x, m_y, m_x + 20, m_y + 10);
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);
		fillrectangle(m_x, m_y, m_x - 10, m_y + 10);
	}
	void clear()
	{
		clearrectangle(m_x, m_y, m_x + 20, m_y + 10);
		clearrectangle(m_x, m_y, m_x + 10, m_y + 10);
		clearrectangle(m_x, m_y, m_x - 10, m_y + 10);
	}

	//检查两个方块是否碰撞

	//方块位移
	void move(int dx, int dy)
	{
		m_x += dx;
		m_y += dy;
		if (m_x == -10)m_x = 490;
		if (m_x == 500)m_x = 0;
		if (m_y == -10)m_y = 490;
		if (m_y == 500)
			return;
	}
	int m_x;
	int m_y;
	COLORREF m_color;
};
ExMessage msg = { 0 };
using namespace std;
bool inarea(int x, int y, int w, int h, int mx, int my)
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}
bool button(int x, int y, int w, int h, const char* text)
{
	if (inarea(x, y, w, h, msg.x, msg.y))
	{
		setfillcolor(WHITE);
	}
	else
	{
		setfillcolor(WHITE);
	}
	fillroundrect(x, y, x + w, y + h, 5, 5);
	int rw = (w - textwidth(text)) / 2;
	int rh = (h - textheight(text)) / 2;
	outtextxy(x + rw, y + rh, text);
	if (inarea(x, y, w, h, msg.x, msg.y) && msg.message == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}
int gamestart()
{
	mciSendString(TEXT("open NULL type waveaudio alias audio"), NULL, 0, NULL);
	initgraph(640, 480, 1);
	setbkcolor(RGB(45, 204, 51));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	while (true)
	{
		peekmessage(&msg, EM_MOUSE);
		cleardevice();
		BeginBatchDraw();
		if (button(20, 20, 150, 35, "game start"))
		{
			cout << "gamestart";
			cleardevice();
			EndBatchDraw();
			msg = { 0 };
			return 1;
		}
		EndBatchDraw();
		msg = { 0 };
	}
	getchar();
}
int tab(int t, int n)
{
	int p = 0;
	char x = 0;
	switch (n)
	{
	case 1:
		x = 'A';
		p = 10;
		break;
	case 2:
		x = 'D';
		p = 213;
		break;
	case 3:
		x = 'J';
		p = 426;
		break;
	case 4:
		x = 'L';
		p = 620;
		break;
	}
	Node n1(p, 0, RED);
	Node n2(p, -10, WHITE);
	int i = 49;
	Sleep(t);
	while (i--)
	{
		n1.draw();
		n1.move(0, 10);
		n2.clear();
		n2.move(0, 10);
		if (i < 5 && (GetAsyncKeyState(x) & 0x8000))
		{
			co++;
			n2.clear();
			return 0;
		}
		Sleep(20);
		n2.clear();
	}
	return 0;
}

int game()
{
	setbkcolor(WHITE);
	initgraph(640, 480);
	IMAGE img;	//准备图片
	loadimage(&img, "pic.jpg");	//加载图片  L"背景.jpg"是图片的相对路径,也可以使用绝对路径
	putimage(0, 0, &img);
	//在指定位置贴图  前面的(0,0)是坐标
	int s = 1240;
	// 创建两个线程来运行tab函数
	mciSendString(_T("open music.mp3 alias bkmusic"), NULL, 100, NULL);
	setbkcolor(WHITE); 
	mciSendString(_T("play bkmusic "), NULL, 0, NULL);//循环播放
	std::thread t1(tab, 0, 1);
	std::thread t2(tab, s, 2);
	std::thread t3(tab, s*2, 3);
	std::thread t4(tab, s*3, 4);
	std::thread t5(tab, s*4, 1);
	std::thread t6(tab, s*5, 2);
	std::thread t7(tab, s * 6, 3);
	std::thread t8(tab, s * 7, 4);
	std::thread a1(tab, s*8, 2);
	std::thread a2(tab, s*9, 2);
	std::thread a3(tab, s * 10, 3);
	std::thread a4(tab, s * 11, 3);
	std::thread a5(tab, s* 12, 4);
	std::thread a6(tab, s * 13, 3);
	std::thread a7(tab, s * 14, 2);
	std::thread a8(tab, s * 15, 1);
	std::thread b1(tab, s * 16, 1);
	std::thread b2(tab, s * 17, 2);
	std::thread b3(tab, s * 18, 3);
	std::thread b4(tab, s * 19, 4);
	std::thread c1(tab, s * 20, 1);
	std::thread c2(tab, s * 21, 1);
	std::thread c3(tab, s * 22, 4);
	std::thread c4(tab, s * 23, 4);
	std::thread d1(tab, s * 24, 1);
	std::thread d2(tab, s * 25, 1);
	std::thread d3(tab, s * 26, 1);
	std::thread d4(tab, s * 27, 1);
	std::thread f1(tab, s * 28, 4);
	std::thread f2(tab, s * 29, 4);
	std::thread f3(tab, s * 30, 4);
	std::thread f4(tab, s * 31, 4);
	std::thread g1(tab, s * 32, 1);
	std::thread g2(tab, s * 33, 4);
	std::thread g3(tab, s * 34, 2);
	std::thread g4(tab, s * 35, 3);
	std::thread h1(tab, s * 36, 2);
	std::thread h2(tab, s * 37, 4);
	std::thread h3(tab, s * 38, 1);
	std::thread h4(tab, s * 39, 3);
	std::thread i1(tab, s * 40, 2);
	std::thread i2(tab, s * 41, 3);
	std::thread i3(tab, s * 42, 2);
	std::thread i4(tab, s * 43, 3);
	std::thread j1(tab, s * 44, 1);
	std::thread j2(tab, s * 45, 2);
	std::thread j3(tab, s * 46, 3);
	std::thread j4(tab, s * 47, 4);


	// 等待两个线程结束
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	a1.join();
	a2.join();
	a3.join();
	a4.join();
	a5.join();
	a6.join();
	a7.join();
	a8.join();
	b1.join();
	b2.join();
	b3.join();
	b4.join();
	c1.join();
	c2.join();
	c3.join();
	c4.join();
	d1.join();
	d2.join();
	d3.join();
	d4.join();
	f1.join();
	f2.join();
	f3.join();
	f4.join();
	g1.join();
	g2.join();
	g3.join();
	g4.join();
	h1.join();
	h2.join();
	h3.join();
	h4.join();
	i1.join();
	i2.join();
	i3.join();
	i4.join();
	j1.join();
	j2.join();
	j3.join();
	j4.join();

	mciSendString(_T("close bkmusic "), NULL, 0, NULL);
	return 0;
}
int main()
{
	if (gamestart() == 1)
	{
		if (game() == 0)
		{
			initgraph(500, 500);
			IMAGE img;	//准备图片
			loadimage(&img, "pic.jpg");
			putimage(0, 0, &img);
			TCHAR s[40];
			_stprintf(s, _T("你的分数:%d"), co);
			outtextxy(50, 50, s);
			getchar();
			// 关闭窗口
			closegraph();
			return 0;
		}
	}
}
