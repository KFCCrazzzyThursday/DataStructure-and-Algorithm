#pragma once
#undef UNICODE
#include "Tree.h"
#include<easyx.h>
#include<graphics.h>

#include <time.h>
#include <conio.h>

void create();   //��������

int deep(TreeNode*& root); //������ȣ���������

void draw(int x, int y, TreeNode*& c); //���Ƶ������

void tempinit(TreeNode*& root); //��temp��GUIsizeֵ���г�ʼ��

void GUIprint(TreeNode* s, int x, int y);//������

