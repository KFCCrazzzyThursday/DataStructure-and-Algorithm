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


void read(vector<vector<string>>&, string, vector<string>&);  //读取文件
void create(vector<vector<string>>&);                //创建字典树
void print(vector<vector<string>>, string, vector<string>lines);
void clear();

vector<int> profix(string& mode);   //前缀函数 生成next数组
vector<int> KMP(string& desk, string& mode);  //KMP


void search(vector<string>);

bool issym(char);
bool isc(string);
int chtoi(char);
#endif // !