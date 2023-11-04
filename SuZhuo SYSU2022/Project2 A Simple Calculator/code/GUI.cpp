#include "GUI.h"

void button(int x, int y, int w, int h, string p = " ") {
	setfillcolor(WHITE);    //填充颜色
	setlinecolor(RGB(238, 238, 238)); //轮廓颜色
	setlinestyle(PS_SOLID, 2);
	RECT r = { x,y,x + w,y + h };
	fillrectangle(x, y, x + w, y + h);  //创建按钮图形
	setbkmode(TRANSPARENT);    //背景透明化
	settextcolor(BLACK);
	settextstyle(20, 0, "黑体");
	drawtext((p.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);   //居中输出文字
}


string calculate() {
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 0, "宋体");
	string q;
	char ch = 0;
	RECT r = { 0,0,320,160 };
	ExMessage msg;
	while (1) {
		msg = getmessage(EX_MOUSE | EX_KEY | EX_CHAR);
		switch (msg.message) {
		case WM_LBUTTONDOWN: {
			if (msg.x >= 0 && msg.x <= 64) {
				if (msg.y >= 160 && msg.y <= 240) {
					q.push_back('7');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 240 && msg.y <= 320) {
					q.push_back('4');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 320 && msg.y <= 400) {
					q.push_back('1');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 400 && msg.y <= 480) {
					q.push_back('(');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			else if (msg.x >= 64 && msg.x <= 128) {
				if (msg.y >= 160 && msg.y <= 240) {
					q.push_back('8');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 240 && msg.y <= 320) {
					q.push_back('5');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 320 && msg.y <= 400) {
					q.push_back('2');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 400 && msg.y <= 480) {
					q.push_back('0');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			else if (msg.x >= 128 && msg.x <= 192) {
				if (msg.y >= 160 && msg.y <= 240) {
					q.push_back('9');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 240 && msg.y <= 320) {
					q.push_back('6');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 320 && msg.y <= 400) {
					q.push_back('3');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 400 && msg.y <= 480) {
					q.push_back('+');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
			}
			else if (msg.x >= 192 && msg.x <= 256) {
				if (msg.y >= 160 && msg.y <= 240) {
					q.push_back('/');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 240 && msg.y <= 320) {
					q.push_back('*');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 320 && msg.y <= 400) {
					q.push_back('-');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 400 && msg.y <= 480) {
					return q;
				}
			}
			else if (msg.x >= 256 && msg.x <= 320) {
				if (msg.y >= 160 && msg.y <= 240) {
					q.push_back('^');
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 240 && msg.y <= 320) {
					q = "";
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 320 && msg.y <= 400) {
					if (!q.empty()) q.pop_back();
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else if (msg.y >= 400 && msg.y <= 480) {
					q = "#";
					clearrectangle(0, 0, 320, 160);
					drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					//return q;
				}
			}
			break;
		}

		case WM_RBUTTONDOWN: {
			if (msg.x >= 0 && msg.x <= 64 && msg.y >= 400 && msg.y <= 480) {
				q.push_back(')');
				clearrectangle(0, 0, 320, 160);
				drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}

		case WM_CHAR: {
			char c = msg.ch;
			//printf("%d %c\n", c, c);
			if (c == 8) {
				if (!q.empty()) q.pop_back();
				BeginBatchDraw();
				clearrectangle(0, 0, 320, 160);
				drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				EndBatchDraw();
			}
			else if (c == 13||c=='=') {
				return q;
			}
			else if (c == '#') {
				q = "#";
				BeginBatchDraw();
				clearrectangle(0, 0, 320, 160);
				drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				EndBatchDraw();
			}
			else if (c >= 0 && c <= '9') {
				q.push_back(c);
				BeginBatchDraw();
				clearrectangle(0, 0, 320, 160);
				drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				EndBatchDraw();
			}
			else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^'  ) {
				q.push_back(c);
				BeginBatchDraw();
				clearrectangle(0, 0, 320, 160);
				drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				EndBatchDraw();
			}
			break;
		}
	
		default:
			break;
		}
	}
	return q;
}

void create() {
	cout << "输入示例：  3*(2+3^(4-1)/3)+1" << endl;
	cout << "            4/(9-8)*2" << endl;
	cout << "            \"(/)\"键用鼠标左键单击输入'(', 用鼠标右键单击输入')'" << endl;
	cout << "            左键单击'C'清空输入，单击\"<=\"回退一位" << endl;
	cout << "输入\"#\"结束计算" << endl;
	cout << "-------------------------------------------" << endl;

	initgraph(320, 480, EX_SHOWCONSOLE);
	setbkcolor(RGB(238, 238, 238));
	cleardevice();
	vector<string> cara = { "7","8","9","÷","^","4","5","6","x","C","1","2","3","-","<=","( / )","0","+","=","#" };
	int i = 0, j = 0;
	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 5; ++j) {
			button(0 + 64 * j, 160 + 80 * i, 64, 80, cara[i * 5 + j]);
		}
	}
}

void output(int res, string p) {
	RECT r = { 0, 0, 320, 160 };
	clearrectangle(0, 0, 320, 160);
	string q = p + "=" + (to_string(res));
	drawtext(_T(q.c_str()), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}