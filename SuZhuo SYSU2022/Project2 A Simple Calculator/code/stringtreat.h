#pragma once
#include"GUI.h"

int chartoi(vector<char>);     //int及vector<char>互相转换
vector<char> itochar(int);

void pretreat(string&);   //字符串预处理函数 将-a转为-1*a，否则-2^2计算得4而非-4

bool compare(string);            //括号匹配以及非法字符报错


void print(vector<vector<char>>);//三个打印函数

template<typename T>
void print(vector<T> desk) {
	int len = desk.size();
	if (len == 0) cout << "Empty";
	int i = 0;
	for (i = 0; i < len; ++i) cout << desk[i] << ' ';
	cout << endl;
}

template<typename T>
void print(stack<T> desk) {
	stack<T> cpy = desk;
	stack<T> inverse;
	if (desk.size() == 0) cout << "Empty";
	while (!cpy.empty()) {
		inverse.push(cpy.top());
		cpy.pop();
	}
	while (!inverse.empty()) {
		cout << inverse.top() << ' ';
		inverse.pop();
	}
	cout << endl;
}

