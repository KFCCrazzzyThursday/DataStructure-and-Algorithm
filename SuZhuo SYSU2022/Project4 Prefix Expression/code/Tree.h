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
	char sym;   //���������
	char vari;  //���������
	double number;//���渡������ֵ
	int* v;  //int[3]���飬ÿλΪ0��1��ʾ�ý���Ƿ���������������͡��磺{1,0,0}��ʾ�ý������������{0,1,1}��ʾ�ý�����һ���Ѹ�ֵ�ı���

	TreeNode* lchild;
	TreeNode* rchild;

	TreeNode() :sym('\0'), vari('\0'), number(0), v(new int[3]()), lchild(NULL), rchild(NULL) {};  //�޲ι��캯��
	TreeNode(TreeNode*& node);//���ƹ��캯��

	TreeNode(double x);//�������number�Ĺ��캯��
	TreeNode(char ch);//����vari����sym�Ĺ��캯��(��Ϊchar����)
};

class Tree {
public:
	TreeNode* root;  //�����
	string name;  //���ʽ��

	Tree() :root(new TreeNode()) {};  //�޲ι��캯�� 
	Tree(Tree& tree);    //��ֵ���ø��ƹ��캯��
	Tree(Tree&& tree) noexcept;//��ֵ���ø��ƹ��캯��

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






