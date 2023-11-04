#pragma once
#include"myrand.h"
#include"prime.h"
#include <string>
#include<iostream>
using namespace std;


#define Val std::string
#define Key int  

#define ALL 0    //remove all
#define ONE 1    //remove once

#define COMPELETE 0  //print all
#define NOT_EMPTY 1  //print not-empty cells
#define ONLY_BASIC_INFO 2  //print only basic info

#define MAX_LOAD_FACTOR 0.5  //max load factor



//����ȡ��
int Valtokey(Val);

//�����ĵ��ַ��������ʱ�ĳ��ȣ����ַ����ڴ�ӡʱռ�ĳ��ȣ�һ�������ַ������൱������Ӣ���ַ���
int stringsize(string str);



//��ϣ
struct Pair {
	Val value;
	int freq;
	bool flag;
	Pair() :value(""), freq(0), flag(false) {};  //�յ�Ԫ��Ϊfalse
};

class HashMap {
protected:
	int size;   //��ϣ���С
	int count;  //�Ѵ洢��Ԫ�ظ��� ����ֻ��һ��
	int count_all; //���� ����Ҳ�Ƕ��
	Pair* map;
	vector<int> bias;
	
	int hash(Key key); //��ϣ���� ����������
	
public:
	virtual void set_bias()=0;
	HashMap();
	virtual ~HashMap();
	HashMap(HashMap& h); //���

	double loadFactor();//װ������

	int Getindex(Val str);//��ȡ�������±�
	Val Getvalue(Key key);//����������keyֵ��ͬ���ҵ�һ����

	bool insert(Val value);  //����
	bool remove(Val name, int control); //ɾ��Ԫ�� ������

	int getSize();
	int getCount();
	int getCount_all();
	//��ӡ
	void print(int control);
	//ƽ�����ҳ���
	double averageSearchLength();
	void search(Val);
	void clear();
	Pair& operator[](int index); //������
	virtual HashMap& operator=(HashMap& h); //��ֵ���������
};

class HashMap_Pseudo :public HashMap {
public:
	virtual void set_bias();
	HashMap_Pseudo();
	virtual ~HashMap_Pseudo();
	HashMap_Pseudo(HashMap_Pseudo& h);
};

class HashMap_Linear :public HashMap {
public:
	virtual void set_bias();
	HashMap_Linear();
	~HashMap_Linear();
	HashMap_Linear(HashMap_Linear& h);
};

class HashMap_Quadratic :public HashMap {
public:
	virtual void set_bias();
	HashMap_Quadratic();
	~HashMap_Quadratic();
	HashMap_Quadratic(HashMap_Quadratic& h);
};

void Insert_Remove_Search_Clear_Test(void);//����ɾ������
void Insert_Remove_Search_Clear_Test(HashMap*&);