#pragma once
#include"stringtreat.h"
#include "GUI.h"

bool issym(const char);   //判断是运算符or数字
bool issym2(const char);  //判断是否为双目运算符
bool isnum(const vector<char>);
bool isnum(const char); 

void posfix(string&, vector<vector<char>>&); //中缀表达式转后缀，存入vector<vector<char>>&
int calc(vector<vector<char>>&,string);   //对后缀表达式进行计算，得到结果

void change0();    //报错弹窗函数
void change1();
void change2();
void change3();
void change4();
void change5();
void change6();
