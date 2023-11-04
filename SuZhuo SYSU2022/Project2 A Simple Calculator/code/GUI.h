#pragma once
#include<iostream>

#include<string>
#include<vector>
#include<stack>

#include<easyx.h>
#include<graphics.h>

#include <time.h>
#include <conio.h>
#include<cmath>
#include<Windows.h>

using namespace std;

void create(void);    //创建计算器界面，同时在控制台界面输出
void button(int x, int y, int w, int h, string p);   //创建按钮图像
string calculate(void);    //读取鼠标键盘输入 返回为string类型
void output(int,string);  //图形化输出
