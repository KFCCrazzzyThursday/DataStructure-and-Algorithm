#pragma once
#include"stringtreat.h"
#include "GUI.h"

bool issym(const char);   //�ж��������or����
bool issym2(const char);  //�ж��Ƿ�Ϊ˫Ŀ�����
bool isnum(const vector<char>);
bool isnum(const char); 

void posfix(string&, vector<vector<char>>&); //��׺���ʽת��׺������vector<vector<char>>&
int calc(vector<vector<char>>&,string);   //�Ժ�׺���ʽ���м��㣬�õ����

void change0();    //����������
void change1();
void change2();
void change3();
void change4();
void change5();
void change6();
