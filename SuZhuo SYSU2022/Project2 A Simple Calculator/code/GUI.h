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

void create(void);    //�������������棬ͬʱ�ڿ���̨�������
void button(int x, int y, int w, int h, string p);   //������ťͼ��
string calculate(void);    //��ȡ���������� ����Ϊstring����
void output(int,string);  //ͼ�λ����
