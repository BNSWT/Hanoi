/* 班级 学号 姓名 */
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include "hanoi.h"
#define maxn 10
using namespace std;

/* -----------------------------------------

     本文件功能：
	1、放被 hanoi_main.cpp/hanoi_menu.cpp 中的各函数调用的菜单各项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------- */
int pa, pb, pc;
char a[maxn], b[maxn], c[maxn];
int step = 0;
int pause;

/***************************************************************************
  函数名称：hanoi
  功    能：实现汉诺塔问题中的递归
  输入参数：int n: 汉诺塔总层数n
		  char src: 起始柱编号
		  char tmp: 中间柱编号
		  char dst: 终点柱编号
		  int choose: 选择的展示方式
  返 回 值：无
  说    明：
***************************************************************************/
void Hanoi(int n, char src, char tmp, char dst, int choose, int size, const HANDLE hout)
{
	if (n == 0)
		return;
	Hanoi(n - 1, src, dst, tmp, choose, size, hout);
	show(n, src, dst, choose, size, hout);
	Hanoi(n - 1, tmp, src, dst, choose, size, hout);
}

/***************************************************************************
  函数名称：show
  功    能：实现汉诺塔问题中某一步的移动过程
  输入参数：int n: 盘子编号
		  char from: 起始柱编号
		  char to: 终点柱编号
		  choose: 选择的展示方式
  返 回 值：无
  说    明：
***************************************************************************/
void show(int n, char from, char to, int choose, int size, const HANDLE hout)
{
	switch (choose) {
		case 8:
		case 7:
		case 6:
		case 5:
		case 4:
			print_col(n, from, to, size, hout);
		case 3:
			print_row(n, from, to, size);
		case 2:
			print_step(n, from, to); break;
		case 1:
			basic(n, from, to);
	}
}



/***************************************************************************
  函数名称：print_col
  功    能：按列打印步骤
  输入参数：	int n: 盘子编号n
			char src: 本次移动的起始柱
			char dst: 本次移动的目标柱
			int size: 汉诺塔总层数（即汉诺塔盘子元素数组的大小）
			HANDLE hout：输出设备句柄
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void print_col(int n, char src, char dst, int size, const HANDLE hout)
{
	set_pause();
	gotoxy(hout, 0, 16);
	set_pause();
	print_row(n, src, dst, size);
	
	int yp;
	switch (src) {
		case 'A':
			yp = 11 - pa; break;
		case 'B':
			yp = 11 - pb; break;
		case 'C':
			yp = 11 - pc; break;
	}
	gotoxy(hout, 10 * (src - 'A') + 11, yp);
	cout << ' ';

	switch (dst) {
		case 'A':
			yp = 12 - pa; break;
		case 'B':
			yp = 12 - pb; break;
		case 'C':
			yp = 12 - pc; break;
	}
	gotoxy(hout, 10 * (dst - 'A') + 11, yp);
	cout << n;
}

/***************************************************************************
  函数名称：set_pause
  功    能：将光标移动到指定位置
  输入参数：无
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void set_pause()
{
	if (pause == 0) {
		char c;
		while (1) {
			c = getchar();
			if (c == '\n')
				break;
		}
	}
	else
		Sleep(1500 / pause);
}

/***************************************************************************
  函数名称：gotoxy
  功    能：将光标移动到指定位置
  输入参数：HANDLE hout：输出设备句柄
			int X      ：指定位置的x坐标
			int Y      ：指定位置的y坐标
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  函数名称：print_row
  功    能：求基本解，打印汉诺塔的移动步数，以及横向打印移动时每个柱子上的盘子情况
  输入参数：int n: 盘子编号
		  char src: 本次移动中的起始柱编号
		  char dst: 本次移动中的终点柱编号
		  int size: 汉诺塔总层数（即汉诺塔盘子元素数组的大小）
  返 回 值：无
  说    明：
***************************************************************************/
void print_row(int n, char src, char dst, int size)
{
	cout << "第" << setw(4) << ++step << " 步:";
	cout << "(" << setw(2) << n << "):" << src << "-->" << dst;
	switch (src) {
		case 'A':
			pa--;
			a[pa] = ' ';
			break;
		case 'B':
			pb--;
			b[pb] = ' ';
			break;
		case 'c':
			pc--;
			c[pc] = ' ';
			break;
	}
	switch (dst) {
		case 'A':
			a[pa++] = n + '0'; break;
		case 'B':
			b[pb++] = n + '0'; break;
		case 'C':
			c[pc++] = n + '0'; break;
	}
	cout << " A:";
	print_array(a, size);
	cout << " B:";
	print_array(b, size);
	cout << " C:";
	print_array(c, size);
	cout << endl;
}

/***************************************************************************
  函数名称：init
  功    能：初始化横向数组
  输入参数：char src: 起始位置
		  int n: 汉诺塔层数
  返 回 值：无
  说    明：
***************************************************************************/
void init(char src, int n)
{
	pa = pb = pc = 0;
	for (int i = 0; i < n; i++) {
		a[i] = b[i] = c[i] = ' ';
	}
	switch (src) {
		case 'A':
			pa = n;
			for (int i = 0; i < n; i++)
				a[i] = n - i + '0';
			break;
		case 'B':
			pb = n;
			for (int i = 0; i < n; i++)
				b[i] = n - i + '0';
			break;
		case 'C':
			pc = n;
			for (int i = 0; i < n; i++)
				c[i] = n - i + '0';
	}
	return;
}

/***************************************************************************
  函数名称：print_array
  功    能：横向打印每个柱子上的盘子编号
  输入参数：char *p: 数组名
		  int size: 数组大小
  返 回 值：无
  说    明：
***************************************************************************/
void print_array(char* p, int size)
{
	for (int i = 0; i < size; i++) {
		cout << *(p + i) << " ";
	}
	return;
}

/***************************************************************************
  函数名称：print_step
  功    能：求基本解，打印汉诺塔的移动步数，以及移动过程中的每一步
  输入参数：int n: 盘子编号
		  char from: 起始柱编号
		  char to: 终点柱编号
  返 回 值：无
  说    明：
***************************************************************************/
void print_step(int n, char from, char to)
{
	cout << "第";
	cout << setw(5) << ++step << " 步";
	cout << "(";
	cout << setw(2) << n << "#: " << from << "-->" << to << endl;
	cout << ")";
}

/***************************************************************************
  函数名称：basic
  功    能：求基本解，打印汉诺塔移动过程中的每一步
  输入参数：int n: 盘子编号
		  char from: 起始柱编号
		  char to: 终点柱编号
  返 回 值：无
  说    明：
***************************************************************************/
void basic(int n, char from, char to)
{
	cout << n << "# " << from << "-->" << to << endl;
}



