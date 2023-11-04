#pragma once
#undef UNICODE
#include "Tree.h"
#include<easyx.h>
#include<graphics.h>

#include <time.h>
#include <conio.h>

void create();   //创建界面

int deep(TreeNode*& root); //求树深度，用于缩放

void draw(int x, int y, TreeNode*& c); //绘制单个结点

void tempinit(TreeNode*& root); //对temp和GUIsize值进行初始化

void GUIprint(TreeNode* s, int x, int y);//绘制树

