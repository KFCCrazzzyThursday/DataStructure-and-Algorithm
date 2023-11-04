#include "Arithmetic.h"


int main() {
	cout << "�밴 1 �������ʽ" << endl;
	cout << "�밴 2 ��������" << endl;
	cout << "�밴 3 ��ӡ��ǰȫ������ʽ" << endl;
	cout << "�밴 4 �޸ĵ�ǰ����ʽ" << endl;
	cout << "�밴 5 ��յ�ǰ���ж���ʽ" << endl;
	cout << "�밴 6 ��ֵ" << endl;
	cout << "�밴 0 �˳�����" << endl;
	cout << "_______________________________________________________________________________" << endl << endl;
	string control;
	int flag;            //������Ʒ�
	int total = 0;       //����ʽ����
	vector<List*> polynomial;  //�������ж���ʽ
	vector<string> names;     //�������ж���ʽ������������map��������vector
	while (cin >> control) {
		if (control.size() == 1 && control[0] >= '0' && control[0] <= '9') {
			flag = control[0] - '0';
		}
		else {
			cout << "������������" << endl << endl;
			continue;
		}
		switch (flag) {
			//���룺
		case 1: {
			cout << "������ʹ�����빦��" << endl;
			cout << "����ʾ���� p1: 3x^3+2x^-2+3" << endl << "           p2:-2x^-2.5+3x-1" << endl << "           p3:Done" << endl;
			cout << "�����Զ���������Ķ���ʽ" << endl;
			cout << "��������Ϻ���� \"Done\" " << endl << endl;
			system("pause");
			string poly;

		f:while (cout << "p" << total + 1 << " = " && (cin >> poly) && poly != "Done") {
			string name = "p";
			int i;
			for (i = 0; i < poly.size(); ++i) {
				if (poly[i] == '^' && ((i == poly.size() - 1) || ((poly[i + 1] != '-') && (poly[i + 1] > '9' || poly[i + 1] < '0')))) {
					cout << "�����������룬\'^\'���Ƿ��������" << endl << endl;
					goto f;
				}
				else if (poly[i] != 'x' && poly[i] != '^' && poly[i] != '+' && poly[i] != '-' && poly[i] != '.' && (poly[i] > '9' || poly[i] < '0')) {
					cout << "�����������룬����Ķ���ʽֻ�ܰ��� 0-9 \' + \'\' - \'\' ^ \'\' . \'\' x \'" << endl << endl;
					goto f;
				}
			}
			name += to_string((total + 1));
			names.push_back(name);

			List* pol = new List;
			vector<string> poly_;
			poly_ = pretreat(poly, poly_); //Ԥ����
			for (i = 0; i < poly_.size(); i += 2) {
				pol->push_back(strtod(poly_[i]), strtod(poly_[i + 1]));
			}
			//pol->print();
			polynomial.push_back(pol);
			total++;
			cout << endl;
		}
		if (poly == "Done") cout << "�������" << endl << "_______________________________________________________________________________" << endl << endl;
		break;
		}
			  //�������㣺
		case 2: {
			cout << "������ʹ�����㹦��" << endl;
			cout << "����ʾ���� p1+p2   p3-p1  p3*p2   p4'" << endl;
			cout << "������Ϻ������ \"Done\" " << endl << endl;
			system("pause");
			string contr;      //����
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
							cout << "�����������룬�����������˲����ڵĶ���ʽ����" << endl << endl;
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
							cout << "�����������룬�����������˲����ڵĶ���ʽ����" << endl << endl;
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
							cout << "�����������룬�����������˲����ڵĶ���ʽ����" << endl << endl;
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
							cout << "�����������룬�����������˲����ڵĶ���ʽ����" << endl << endl;
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
			if (contr == "Done") cout << "�������" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}

		case 3: {
			int i;
			for (i = 0; i < total; ++i) {
				cout << names[i] << " = ";
				polynomial[i]->print();
				cout << endl;
			}
			cout << "�����ȫ������ʽ����" << total << "��" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}

		case 4: {
			cout << "�������޸Ķ���ʽ" << endl;
			cout << "�޸���Ϻ�����\"Done\"�˳�����" << endl << endl;
			string p;
			cout << "������Ҫ�޸ĵĶ���ʽ���ƣ�" << endl;
			while (cin >> p && p != "Done") {
				int ind = findp(names, p);
				if (ind == -1) {
					cout << "�����������룬�����������˲����ڵĶ���ʽ����" << endl << endl;
				}
				else {
					cout << "�������޸ĺ�Ķ���ʽ:" << endl;
					cout << p << " = ";
					string poly;
					cin >> poly;
					int i;
					List* pol = new List;
					vector<string> poly_;
					poly_ = pretreat(poly, poly_); //Ԥ����
					for (i = 0; i < poly_.size(); i += 2) {
						pol->push_back(strtod(poly_[i]), strtod(poly_[i + 1]));
					}
					polynomial[ind] = pol;
					cout << "����ʽ" << p << "�޸ĳɹ�" << endl;
				}
			}
			cout << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}

		case 5: {
			int i;
			for (i = 0; i < polynomial.size(); ++i) {   //�ͷ��ڴ�
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
			cout << "��������ж���ʽ" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}
		case 6: {
			cout << "������x" << endl << "x = ";
			string x_;
			while (cin >> x_ && x_ != "Done") {
				string p;
				cout << "������Ҫ����Ķ���ʽ���ƣ�" << endl;
				cin >> p;
				int ind = findp(names, p);
				double res = 0;
				double x = strtod(x_);
				if (ind == -1) {
					cout << "�����������룬�����������˲����ڵĶ���ʽ����" << endl << endl;
				}
				else {
					Node* p = polynomial[ind]->head;
					while (p != nullptr) {
						res += p->coeff * pow(x, p->index);
						p = p->next;
					}
					cout << "�����" <<fixed<<std::setprecision(2)<< res << endl<<endl;
					system("pause");
					cout << "������x" << endl << "x = ";
				}
			}
			cout << "��ֵ���" << endl << "_______________________________________________________________________________" << endl << endl;
			break;
		}
		case 0: {
			cout << "Clearing" << endl;
			int i;
			for (i = 0; i < polynomial.size(); ++i) {   //�ͷ��ڴ�
				polynomial[i]->clear();
			}
			system("pause");
			return 0;
			break;
		}

		default: {
			cout << "������������" << endl;
			break;
		}
		}

	}
}
