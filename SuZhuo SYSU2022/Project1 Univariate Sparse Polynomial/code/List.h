#pragma once
#define _CRT_SECURE_NO_WARNINGS //��ֹsize_tתint����

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
string cut(string, string);  //��string aǰ��ȥ��string b�������豣֤b��a��ǰ׺�Ӵ�

void sprint(string); //������

//bool notaply(string); ������
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
	List(List&); //������캯��
public:
	List* push_back(double co_, double in_);
	List* sort(void);            //����
	List* deri(void);            //��

	void print(void);
	void clear(void);			 //�ͷ��ڴ�
};