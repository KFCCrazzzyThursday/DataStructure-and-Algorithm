#pragma once
#ifndef TEXT_H
#define TEXT_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<Windows.h>
#define N 500010
using namespace std;


void read(vector<vector<string>>&, string, vector<string>&);  //��ȡ�ļ�
void create(vector<vector<string>>&);                //�����ֵ���
void print(vector<vector<string>>, string, vector<string>lines);
void clear();

vector<int> profix(string& mode);   //ǰ׺���� ����next����
vector<int> KMP(string& desk, string& mode);  //KMP


void search(vector<string>);

bool issym(char);
bool isc(string);
int chtoi(char);
#endif // !