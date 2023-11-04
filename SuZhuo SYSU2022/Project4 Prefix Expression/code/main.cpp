#include "GUI.h"
#include "Tree.h"

extern bool flag;

int main() {
	create();  //��������
	map<string, Tree> trees; //������ʽ
	string control;  //���ܿ��Ʒ�
	while (cin >> control) {  //switch case��֧��string���ͣ��Ƿ����������д
		if (control == "1") {
			cout << "����Ϸ���ǰ׺���ʽ������Done��������" << endl;
			string p_name;
			while (1) {
			b:
				cout << "��������ʽ��:" << endl;
				cin >> p_name;
				if (p_name == "Done") {
					cout << "�������" << endl;
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}
				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it != trees.end()) {
						cout << "���ʽ�Ѵ���" << endl;
						goto b;
					}
					cout << "������" << p_name << ": ";
					Tree E = ReadExpr(p_name);
					if (flag) {
						trees.insert(pair<string, Tree>(p_name, E));
						cout << "���ʽ�Ѵ���" << endl << endl;
						tempinit(E.root);
						cleardevice();
						GUIprint(E.root, 500, 100);
					}
				}
			}
		}

		else if (control == "2") {
			cout << "������Ҫ��ӡ�ı��ʽ��������Done��ֹ��ӡ" << endl;
			while (1) {
				string p_name;
				cin >> p_name;

				if (p_name == "Done") {
					cout << "��ӡ���" << endl;
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}

				else {
					map<string, Tree>::iterator it = trees.find(p_name);
					if (it == trees.end()) {
						cout << "�ñ��ʽ�����ڣ�����������" << endl;
					}
					else {
						WriteExpr(it->second);
						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						cout << endl << endl;
					}
					cout << "������Ҫ��ӡ�ı��ʽ��: ";
				}
			}

		}
		else if (control == "3") {
			cout << "������Ҫ��ֵ�ı��ʽ��������Done����" << endl;
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
						cout << "�ñ��ʽ�����ڣ�����������" << endl;
					}
					else {
						cout << "������Ҫ��ֵ�ı�������ֵ" << endl;
						char variable;
						double value;
						cin >> variable >> value;
						it->second.Assign(variable, value);
						cout << "��ֵ��ɣ���ֵ��ñ��ʽΪ:" << endl;
						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						Value(it->second);
						cout << endl << endl;
					}
					cout << "������Ҫ��ֵ�ı��ʽ��: ";
				}
			}
		}
		else if (control == "4") {
			cout << "������Ҫ��ֵ�ı��ʽ��������Done��ֹ" << endl;
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
						cout << "�ñ��ʽ�����ڣ�����������" << endl;
					}
					else {
						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						Value(it->second);
						cout << endl << endl;
					}
					cout << "������Ҫ��ֵ�ı��ʽ��: ";
				}
			}
		}

		else if (control == "5") {
			cout << "������Ҫ���ϵı��ʽ��������Done��ֹ" << endl;
			while (1) {
				string res_name;
				cout << "�����븴�ϱ��ʽ��:" << endl;
				cin >> res_name;
				if (res_name == "Done") {
					cout << "------------------------------------------------------------------" << endl << endl;
					break;
				}
				map<string, Tree>::iterator it = trees.find(res_name);
				if (it == trees.end()) {
					string p1_name, p2_name;
					cout << "�������踴�ϵ��������ʽ" << endl;
				a:
					cin >> p1_name;
					if (p1_name == "Done") {
						cout << "------------------------------------------------------------------" << endl << endl;
						break;
					}

					else {
						cin >> p2_name;
						cout << "������Ҫ���е�����P:" << endl;
						char P;
						cin >> P;
						map<string, Tree>::iterator it_1 = trees.find(p1_name);
						map<string, Tree>::iterator it_2 = trees.find(p2_name);
						if (it_1 == trees.end() || it_2 == trees.end()) {
							cout << "���ʽ�����ڣ�����������" << endl;
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
					cout << "�ñ��ʽ���Ѵ��ڣ���ʹ���������ʽ��" << endl;
				}
			}
		}

		else if (control == "6") {
			cout << "������Ҫ�ϲ��ı��ʽ��������Done��ֹ" << endl;
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
						cout << "�ñ��ʽ�����ڣ�����������" << endl;
					}
					else {
						MergeConst(it->second);
						WriteExpr(it->second);

						tempinit(it->second.root);
						cleardevice();
						GUIprint(it->second.root, 500, 100);
						cout << endl << endl;
					}
					cout << "������Ҫ��ӡ�ı��ʽ��: ";
				}
			}
		}

		else if (control == "0") {
			cout << "�˳�����" << endl;
			cout << "------------------------------------------------------------------" << endl << endl;
			break;
		}
		else {
			cout << "���Ϸ��Ŀ����ַ�" << endl;
		}
	}
}








