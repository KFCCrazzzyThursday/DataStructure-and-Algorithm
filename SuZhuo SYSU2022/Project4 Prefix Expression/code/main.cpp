#include "GUI.h"
#include "Tree.h"

extern bool flag;

int main() {
	create();  //创建窗口
	map<string, Tree> trees; //储存表达式
	string control;  //功能控制符
	while (cin >> control) {  //switch case不支持string类型，非法输出处理不好写
		if (control == "1") {
			cout << "输入合法的前缀表达式，键入Done结束输入" << endl;
			string p_name;
			while (1) {
			b:
				cout << "请输入表达式名:" << endl;
				cin >> p_name;
				if (p_name == "Done") {
					cout << "输入结束" << endl;
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}
				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it != trees.end()) {
						cout << "表达式已存在" << endl;
						goto b;
					}
					cout << "请输入" << p_name << ": ";
					Tree E = ReadExpr(p_name);
					if (flag) {
						trees.insert(pair<string, Tree>(p_name, E));
						cout << "表达式已储存" << endl << endl;
						tempinit(E.root);
						cleardevice();
						GUIprint(E.root, 500, 100);
					}
				}
			}
		}

		else if (control == "2") {
			cout << "请输入要打印的表达式名，输入Done终止打印" << endl;
			while (1) {
				string p_name;
				cin >> p_name;

				if (p_name == "Done") {
					cout << "打印完成" << endl;
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}

				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it == trees.end()) {
						cout << "该表达式不存在，请重新输入" << endl;
					}
					else {
						WriteExpr(it->second);
						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						cout << endl << endl;
					}
					cout << "请输入要打印的表达式名: ";
				}
			}

		}
		else if (control == "3") {
			cout << "请输入要赋值的表达式名，输入Done结束" << endl;
			while (1) {
				string p_name;
				cin >> p_name;

				if (p_name == "Done") {
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}
				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it == trees.end()) {
						cout << "该表达式不存在，请重新输入" << endl;
					}
					else {
						cout << "请输入要赋值的变量名和值" << endl;
						char variable;
						double value;
						cin >> variable >> value;
						it->second.Assign(variable, value);
						cout << "赋值完成，赋值后该表达式为:" << endl;
						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						Value(it->second);
						cout << endl << endl;
					}
					cout << "请输入要赋值的表达式名: ";
				}
			}
		}
		else if (control == "4") {
			cout << "请输入要求值的表达式名，输入Done终止" << endl;
			while (1) {
				string p_name;
				cin >> p_name;

				if (p_name == "Done") {
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}
				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it == trees.end()) {
						cout << "该表达式不存在，请重新输入" << endl;
					}
					else {
						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						Value(it->second);
						cout << endl << endl;
					}
					cout << "请输入要求值的表达式名: ";
				}
			}
		}

		else if (control == "5") {
			cout << "请输入要复合的表达式名，输入Done终止" << endl;
			while (1) {
				string res_name;
				cout << "请输入复合表达式名:" << endl;
				cin >> res_name;
				if (res_name == "Done") {
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}
				map<string, Tree>::iterator it = trees.find(res_name);
				if (it == trees.end()) {
					string p1_name, p2_name;
					cout << "请输入需复合的两个表达式" << endl;
				a:
					cin >> p1_name;
					if (p1_name == "Done") {
						cout << "------------------------------------------------------------------" << endl << endl;
						break;
					}

					else {
						cin >> p2_name;
						cout << "请输入要进行的运算P:" << endl;
						char P;
						cin >> P;
						map<string, Tree>::iterator it_1 = trees.find(p1_name);
						map<string, Tree>::iterator it_2 = trees.find(p2_name);
						if (it_1 == trees.end() || it_2 == trees.end()) {
							cout << "表达式不存在，请重新输入" << endl;
							goto a;
						}
						else {
							Tree res = CompoundExpr(P, it_1->second, it_2->second);
							tempinit(it_1->second.root);
							cleardevice();
							GUIprint(it_1->second.root, 500, 100);
							system("pause");
							tempinit(it_2->second.root);
							cleardevice();
							GUIprint(it_2->second.root, 500, 100);
							system("pause");
							res.name = res_name;
							tempinit(res.root);
							cleardevice();
							GUIprint(res.root, 500, 100);

							trees.insert(pair<string, Tree>(res_name, res));
							WriteExpr(res);
							cout << endl << endl;
						}
					}
				}
				else {
					cout << "该表达式名已存在，请使用其他表达式名" << endl;
				}
			}
		}

		else if (control == "6") {
			cout << "请输入要合并的表达式名，输入Done终止" << endl;
			while (1) {
				string p_name;
				cin >> p_name;

				if (p_name == "Done") {
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}

				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it == trees.end()) {
						cout << "该表达式不存在，请重新输入" << endl;
					}
					else {
						MergeConst(it->second);
						WriteExpr(it->second);

						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						cout << endl << endl;
					}
					cout << "请输入要打印的表达式名: ";
				}
			}
		}

		else if (control == "0") {
			cout << "退出程序" << endl;
			cout << "------------------------------------------------------------------" << endl << endl;
			break;
		}
		else {
			cout << "不合法的控制字符" << endl;
		}
	}
}








