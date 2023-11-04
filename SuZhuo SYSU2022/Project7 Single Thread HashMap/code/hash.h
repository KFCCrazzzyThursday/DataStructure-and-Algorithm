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



//姓名取码
int Valtokey(Val);

//含中文的字符串在输出时的长度（即字符串在打印时占的长度，一个中文字符长度相当于两个英文字符）
int stringsize(string str);



//哈希
struct Pair {
	Val value;
	int freq;
	bool flag;
	Pair() :value(""), freq(0), flag(false) {};  //空单元记为false
};

class HashMap {
protected:
	int size;   //哈希表大小
	int count;  //已存储的元素个数 重名只记一次
	int count_all; //总数 重名也记多次
	Pair* map;
	vector<int> bias;
	
	int hash(Key key); //哈希函数 除留余数法
	
public:
	virtual void set_bias()=0;
	HashMap();
	virtual ~HashMap();
	HashMap(HashMap& h); //深拷贝

	double loadFactor();//装载因子

	int Getindex(Val str);//获取姓名的下标
	Val Getvalue(Key key);//查找姓名（key值相同查找第一个）

	bool insert(Val value);  //插入
	bool remove(Val name, int control); //删除元素 测试用

	int getSize();
	int getCount();
	int getCount_all();
	//打印
	void print(int control);
	//平均查找长度
	double averageSearchLength();
	void search(Val);
	void clear();
	Pair& operator[](int index); //测试用
	virtual HashMap& operator=(HashMap& h); //赋值运算符重载
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

void Insert_Remove_Search_Clear_Test(void);//插入删除测试
void Insert_Remove_Search_Clear_Test(HashMap*&);