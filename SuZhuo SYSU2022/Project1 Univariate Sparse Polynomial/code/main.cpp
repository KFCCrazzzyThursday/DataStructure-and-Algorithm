#include "Arithmetic.h"


int main() {
	cout << "请按 1 输入多项式" << endl;
	cout << "请按 2 进行运算" << endl;
	cout << "请按 3 打印当前全部多项式" << endl;
	cout << "请按 4 修改当前多项式" << endl;
	cout << "请按 5 清空当前所有多项式" << endl;
	cout << "请按 6 求值" << endl;
	cout << "请按 0 退出程序" << endl;
	cout << "_______________________________________________________________________________" << endl << endl;
	string control;
	int flag;            //输入控制符
	int total = 0;       //多项式总数
	vector<List*> polynomial;  //储存所有多项式
	vector<string> names;     //储存所有多项式的命名，可用map代替两个vector
	while (cin >> control) {
		if (control.size() == 1 && control[0] >= '0' && control[0] <= '9') {
			flag = control[0] - '0';
		}
		else {
			cout << "请检查您的输入" << endl << endl;
			continue;
		}
		switch (flag) {
			//输入：
		case 1: {
			cout << "您正在使用输入功能" << endl;
			cout << "输入示例： p1: 3x^3+2x^-2+3" << endl << "           p2:-2x^-2.5+3x-1" << endl << "           p3:Done" << endl;
			cout << "程序将自动保存输入的多项式" << endl;
			cout << "请输入完毕后键入 \"Done\" " << endl << endl;
			system("pause");
			string poly;

		f:while (cout << "p" << total + 1 << " = " && (cin >> poly) && poly != "Done") {
			string name = "p";
			int i;
			for (i = 0; i < poly.size(); ++i) {
				if (poly[i] == '^' && ((i == poly.size() - 1) || ((poly[i + 1] != '-') && (poly[i + 1] > '9' || poly[i + 1] < '0')))) {
					cout << "请检查您的输入，\'^\'后是否输入错误？" << endl << endl;
					goto f;
				}
				else if (poly[i] != 'x' && poly[i] != '^' && poly[i] != '+' && poly[i] != '-' && poly[i] != '.' && (poly[i] > '9' || poly[i] < '0')) {
					cout << "请检查您的输入，输入的多项式只能包含 0-9 \' + \'\' - \'\' ^ \'\' . \'\' x \'" << endl << endl;
					goto f;
				}
			}
			name += to_string((total + 1));
			names.push_back(name);

			List* pol = new List;
			vector<string> poly_;
			poly_ = pretreat(poly, poly_); //预处理
			for (i = 0; i < poly_.size(); i += 2) {
				pol->push_back(strtod(poly_[i]), strtod(poly_[i + 1]));
			}
			//pol->print();
			polynomial.push_back(pol);
			total++;
			cout << endl;
		}
		if (poly == "Done") cout << "输入完毕" << endl << "_______________________________________________________________________________" << endl << endl;
		break;
		}
			  //代数运算：
		case 2: {
			cout << "您正在使用运算功能" << endl;
			cout << "输入示例： p1+p2   p3-p1  p3*p2   p4'" << endl;
			cout << "运算完毕后请键入 \"Done\" " << endl << endl;
			system("pause");
			string contr;      //输入
			while (cin >> contr && contr != "Done") {
				int length = contr.size();
				int i;
				for (i = 0; i < length; ++i) {
					if (contr[i] == '+') {
						string a, b;
						int j;
						for (j = 0; j < i; ++j) a.push_back(contr[j]);
						for (j = i + 1; j < contr.size(); ++j) b.push_back(contr[j]);
						int ina = 0, inb = 0;
						ina = findp(names, a);
						inb = findp(names, b);
						if (ina == -1 || inb == -1) {
							cout << "请检查您的输入，您可能输入了不存在的多项式名称" << endl << endl;
						}
						else {
							List* res = new List((List&)(*polynomial[ina] + *polynomial[inb]));
							res->sort();
							polynomial.push_back(res);
							total++;
							string name = "p";
							name += to_string(total);
							names.push_back(name);
							cout << name << " = " << a << " + " << b << " = ";
							res->print();
							cout << endl;
						}
					}
				}
				for (i = 0; i < length; ++i) {
					if (contr[i] == '-') {
						string a, b;
						int j;
						for (j = 0; j < i; ++j) a.push_back(contr[j]);
						for (j = i + 1; j < contr.size(); ++j) b.push_back(contr[j]);
						int ina = 0, inb = 0;
						ina = findp(names, a);
						inb = findp(names, b);
						if (ina == -1 || inb == -1) {
							cout << "请检查您的输入，您可能输入了不存在的多项式名称" << endl << endl;
						}
						else {
							List* res = new List((List&)(*polynomial[ina] - *polynomial[inb]));
							res->sort();
							polynomial.push_back(res);
							total++;
							string name = "p";
							name += to_string(total);
							names.push_back(name);
							cout << name << " = " << a << " - " << b << " = ";
							res->print();
							cout << endl;
						}

					}
				}
				for (i = 0; i < length; ++i) {
					if (contr[i] == '*') {
						string a, b;
						int j;
						for (j = 0; j < i; ++j) a.push_back(contr[j]);
						for (j = i + 1; j < contr.size(); ++j) b.push_back(contr[j]);
						int ina = 0, inb = 0;
						ina = findp(names, a);
						inb = findp(names, b);
						if (ina == -1 || inb == -1) {
							cout << "请检查您的输入，您可能输入了不存在的多项式名称" << endl << endl;
						}
						else {
							List* res = new List((List&)(*polynomial[ina] * *polynomial[inb]));
							res->sort();
							polynomial.push_back(res);
							total++;
							string name = "p";
							name += to_string(total);
							names.push_back(name);
							cout << name << " = " << a << " * " << b << " = ";
							res->print();
							cout << endl;
						}

					}
				}

				for (i = 0; i < length; ++i) {
					if (contr[i] == '\'') {
						string a;
						int j;
						for (j = 0; j < i; ++j) a.push_back(contr[j]);
						int ind = 0;
						ind = findp(names, a);
						if (ind == -1) {
							cout << "请检查您的输入，您可能输入了不存在的多项式名称" << endl << endl;
						}
						else {
							List* res = (polynomial[ind]->deri())->sort();
							polynomial.push_back(res);
							total++;
							string name = "p";
							name += to_string(total);
							names.push_back(name);
							cout << name << " = " << a << "' = ";
							res->print();
							cout << endl;
						}

					}
				}

			}
			if (contr == "Done") cout << "输入完毕" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}

		case 3: {
			int i;
			for (i = 0; i < total; ++i) {
				cout << names[i] << " = ";
				polynomial[i]->print();
				cout << endl;
			}
			cout << "已输出全部多项式，共" << total << "个" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}

		case 4: {
			cout << "您正在修改多项式" << endl;
			cout << "修改完毕后输入\"Done\"退出功能" << endl << endl;
			string p;
			cout << "请输入要修改的多项式名称：" << endl;
			while (cin >> p && p != "Done") {
				int ind = findp(names, p);
				if (ind == -1) {
					cout << "请检查您的输入，您可能输入了不存在的多项式名称" << endl << endl;
				}
				else {
					cout << "请输入修改后的多项式:" << endl;
					cout << p << " = ";
					string poly;
					cin >> poly;
					int i;
					List* pol = new List;
					vector<string> poly_;
					poly_ = pretreat(poly, poly_); //预处理
					for (i = 0; i < poly_.size(); i += 2) {
						pol->push_back(strtod(poly_[i]), strtod(poly_[i + 1]));
					}
					polynomial[ind] = pol;
					cout << "多项式" << p << "修改成功" << endl;
				}
			}
			cout << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}

		case 5: {
			int i;
			for (i = 0; i < polynomial.size(); ++i) {   //释放内存
				polynomial[i]->clear();
			}
			vector<List*>::iterator iter1 = polynomial.begin();
			while (iter1 != polynomial.end()) {
				iter1 = polynomial.erase(iter1);
			}
			vector<string>::iterator iter2 = names.begin();
			while (iter2 != names.end()) {
				iter2 = names.erase(iter2);
			}
			total = 0;
			cout << "已清空所有多项式" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}
		case 6: {
			cout << "请输入x" << endl << "x = ";
			string x_;
			while (cin >> x_ && x_ != "Done") {
				string p;
				cout << "请输入要计算的多项式名称：" << endl;
				cin >> p;
				int ind = findp(names, p);
				double res = 0;
				double x = strtod(x_);
				if (ind == -1) {
					cout << "请检查您的输入，您可能输入了不存在的多项式名称" << endl << endl;
				}
				else {
					Node* p = polynomial[ind]->head;
					while (p != nullptr) {
						res += p->coeff * pow(x, p->index);
						p = p->next;
					}
					cout << "结果是" <<fixed<<std::setprecision(2)<< res << endl<<endl;
					system("pause");
					cout << "请输入x" << endl << "x = ";
				}
			}
			cout << "求值完毕" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}
		case 0: {
			cout << "Clearing" << endl;
			int i;
			for (i = 0; i < polynomial.size(); ++i) {   //释放内存
				polynomial[i]->clear();
			}
			system("pause");
			return 0;
			break;
		}

		default: {
			cout << "请检查您的输入" << endl;
			break;
		}
		}

	}
}
