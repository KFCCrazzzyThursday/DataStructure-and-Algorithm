#pragma once
#include<iostream>
#include<string>
#include<cmath>
#include<stack>
#include<map>
#include<vector>
#include<conio.h>
#include <time.h>
#include<Windows.h>
using namespace std;

struct TreeNode {
	char sym;   //储存运算符
	char vari;  //储存变量名
	double number;//储存浮点型数值
	int* v;  //int[3]数组，每位为0或1表示该结点是否存有以上三种类型。如：{1,0,0}表示该结点存有运算符，{0,1,1}表示该结点存有一个已赋值的变量

	TreeNode* lchild;
	TreeNode* rchild;

	TreeNode() :sym('\0'), vari('\0'), number(0), v(new int[3]()), lchild(NULL), rchild(NULL) {};  //无参构造函数
	TreeNode(TreeNode*& node);//复制构造函数

	TreeNode(double x);//输入参数number的构造函数
	TreeNode(char ch);//输入vari或者sym的构造函数(均为char类型)
};

class Tree {
public:
	TreeNode* root;  //根结点
	string name;  //表达式名

	Tree() :root(new TreeNode()) {};  //无参构造函数 
	Tree(Tree& tree);    //左值引用复制构造函数
	Tree(Tree&& tree) noexcept;//右值引用复制构造函数

	Tree operator =(Tree tree) {
		this->name = tree.name;
		this->root = new TreeNode(tree.root);
		return *this;
	}

	Tree operator+(Tree tree) {
		Tree res;
		res.root->sym = '+';
		res.root->v[0] = 1;
		res.root->lchild = new TreeNode(this->root);
		res.root->rchild = new TreeNode(tree.root);
		return res;
	}
	Tree operator-(Tree tree) {
		Tree res;
		res.root->sym = '-';
		res.root->v[0] = 1;
		res.root->lchild = new TreeNode(this->root);
		res.root->rchild = new TreeNode(tree.root);
		return res;
	}
	Tree operator*(Tree tree) {
		Tree res;
		res.root->sym = '*';
		res.root->v[0] = 1;
		res.root->lchild = new TreeNode(this->root);
		res.root->rchild = new TreeNode(tree.root);
		return res;
	}
	Tree operator /(Tree tree) {
		Tree res;
		res.root->sym = '/';
		res.root->v[0] = 1;
		res.root->lchild = new TreeNode(this->root);
		res.root->rchild = new TreeNode(tree.root);
		return res;
	}
	Tree operator^(Tree tree) {
		Tree res;
		res.root->sym = '^';
		res.root->v[0] = 1;
		res.root->lchild = new TreeNode(this->root);
		res.root->rchild = new TreeNode(tree.root);
		return res;
	}

	void Assign(char V, double c = 0);

	void print(void);


};
bool issym(char ch);
bool isvari(char ch);
bool isnum(char ch);
double chtodouble(char ch);


void WriteExpr(Tree& tree);
void print_node(TreeNode*&, int layer);
void print_node_by_value(TreeNode*&, int layer);


void Value(Tree&);
bool allvalued(TreeNode*&);
double value_node(TreeNode*&);

Tree MergeConst(Tree&);
TreeNode* MergeConst_node(TreeNode*&);

Tree CompoundExpr(char P, Tree E1, Tree E2);

Tree ReadExpr(string& name_);






