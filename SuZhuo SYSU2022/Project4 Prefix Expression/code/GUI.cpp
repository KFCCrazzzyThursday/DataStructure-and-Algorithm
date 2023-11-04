#include "GUI.h"
#include"Tree.h"
int GUIsize;

int temp;


int deep(TreeNode*& root) {
	int dl, dr;
	if (root == NULL) return 0;
	else {
		dl = deep(root->lchild);
		dr = deep(root->rchild);
		return (dl > dr) ? (dl + 1) : (dr + 1);
	}
}

void create() {
	cout << "键入1以输入前缀表达式" << endl;
	cout << "键入2以打印中缀表达式" << endl;
	cout << "键入3以赋值" << endl;
	cout << "键入4以求值" << endl;
	cout << "键入5以构建复合表达式" << endl;
	cout << "键入6以合并常数项" << endl;
	cout << "键入0以退出" << endl << endl;
	cout << "------------------------------------------------------------------" << endl;
	initgraph(1000, 700, EX_SHOWCONSOLE);      //创建图形窗

	setfillcolor(RED);       //设置填充色
	setbkcolor(RGB(238, 238, 238));
	settextcolor(BLACK);       //设置文本颜色
	setlinecolor(BLACK);           //画线的颜色
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "黑体");
	cleardevice();
	Sleep(50);
}

void draw(int x, int y, TreeNode*& s) {
	circle(x, y, 20); Sleep(100);//画圈并暂停100ms
	RECT r = { x-10, y-10, x+10, y+10 };
	if (s->v[0] == 1) {
		outtextxy(x - 4, y - 8, s->sym);
	}
	else if (s->v[1] == 1) {
		if (s->v[2] == 1) {
			outtextxy(x - 15, y - 8, s->vari);
			outtextxy(x - 3, y - 8, "=");
			string num;
			if (s->number - (double)((int)s->number) <= 0.000001 && s->number - (double)((int)s->number) >= -0.000001) {
				num = to_string((int)s->number);
			}
			else {
				num = to_string(s->number);
			}
			string num_;
			int i;
			for (i = 0; i < num.size(); ++i) {
				num_.push_back(num[i]);
				if (num[i] == '.') {
					num_.push_back(num[i + 1]);
					break;
				}
			}
			outtextxy(x + 5, y - 8, num_.c_str());
		}
		else outtextxy(x - 4, y - 8, s->vari);
	}
	else if (s->v[2] == 1) {
		string num;
		if (s->number - (double)((int)s->number) <= 0.000001 && s->number - (double)((int)s->number) >= -0.000001) {
			num = to_string((int)s->number);
		}
		else {
			num = to_string(s->number);
		}
		string num_;
		int i;
		for (i = 0; i < num.size(); ++i) {
			num_.push_back(num[i]);
			if (num[i] == '.') {
				num_.push_back(num[i + 1]);
				break;
			}
		}

		outtextxy(x - 6, y - 8, num_.c_str());
	}
}


void tempinit(TreeNode*& root) {
	GUIsize = 1;
	temp = 1000 / deep(root);
}

void GUIprint(TreeNode* s, int x, int y) {
	if (s != NULL)
		draw(x, y, s);
	if (s != NULL && s->lchild != NULL) {
		GUIsize++;
		line(x - 14, y + 14, x - temp / GUIsize, y + 100 - 20);
		Sleep(50);
		GUIprint(s->lchild, x - temp / GUIsize, y + 100);
	}
	if (s != NULL && s->rchild != NULL) {
		GUIsize++;
		line(x + 14, y + 14, x + temp / GUIsize, y + 100 - 20);
		Sleep(50);
		GUIprint(s->rchild, x + temp / GUIsize, y + 100);
	}
	GUIsize--;
}
