#pragma once
#include"GUI.h"

int chartoi(vector<char>);     //int��vector<char>����ת��
vector<char> itochar(int);

void pretreat(string&);   //�ַ���Ԥ������ ��-aתΪ-1*a������-2^2�����4����-4

bool compare(string);            //����ƥ���Լ��Ƿ��ַ�����


void print(vector<vector<char>>);//������ӡ����

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

