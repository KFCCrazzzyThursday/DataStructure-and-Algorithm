#pragma once
#define _CRT_SECURE_NO_WARNINGS //防止size_t转int报错

#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
using namespace std;
struct Node;
class List;
vector<string> pretreat(string, vector<string>);

int findp(vector<string>, string); 
double strtod(string p1); //string to double
string insert(string desk, string c, int k); //insert c into desk before index k
string cut(string, string);  //从string a前段去除string b，输入需保证b是a的前缀子串

void sprint(string); //调试用

//bool notaply(string); 调试用
struct Node {
	double coeff = 0;
	double index = 0;
	Node* next;

	Node() :coeff(0), index(0), next(nullptr) {};
	Node(double co_, double in_) :coeff(co_), index(in_), next(nullptr) {};
};

class List {
public:
	Node* head;
	List() :head(nullptr) {}
	List(List&); //深拷贝构造函数
public:
	List* push_back(double co_, double in_);
	List* sort(void);            //排序
	List* deri(void);            //求导

	void print(void);
	void clear(void);			 //释放内存
};