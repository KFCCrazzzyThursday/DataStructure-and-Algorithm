#include "List.h"



//class函数
List::List(List& list) {
	Node* p = list.head;
	this->head = new Node(p->coeff, p->index);
	p = p->next;
	while (p != nullptr) {
		this->push_back(p->coeff, p->index);
		p = p->next;
	}
}

List* List::push_back(double co_, double in_) {
	Node* p = this->head;
	if (this->head == nullptr) {
		this->head = new Node(co_, in_);
	}
	else {
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = new Node(co_, in_);
	}
	return this;
}

List* List::sort(void) {
	Node* p = this->head;
	Node* q = p;
	for (; p != nullptr; p = p->next) {
		for (q = p->next; q != nullptr; q = q->next) {
			if (p->index == q->index) {
				p->coeff = p->coeff + q->coeff;
				q->coeff = 0;
			}
		}
	}
	for (p = this->head; p != nullptr; p = p->next) {
		for (q = p; q != nullptr; q = q->next) {
			if (p->index < q->index) {
				double tmp1 = p->coeff;
				double tmp2 = p->index;
				p->coeff = q->coeff;
				p->index = q->index;
				q->coeff = tmp1;
				q->index = tmp2;
			}
		}
	}
	return this;
}

List* List::deri(void) {
	List* res = new List;
	Node* p = this->head;
	while (p != nullptr) {
		if (p->index > 0.0000001 || p->index < -0.0000001) {
			res->push_back((p->coeff * p->index), (p->index - 1));
		}
		p = p->next;
	}
	return res;
}


void List::print(void) {
	Node* p = this->head;
	bool noinput = true;
	while (p != nullptr) {
		if (p->index<0.0000001 && p->index>-0.0000001) {
			if (p->coeff > 0.0000001) {
				if (p != this->head) {
					noinput = false;
					cout << '+';
				}
				noinput = false;
				cout << p->coeff;
			}
			else if (p->coeff < -0.0000001) {
				noinput = false;
				cout << p->coeff;
			}
		}
		else if (p->index - 1 < 0.0000001 && p->index - 1 > -0.0000001) {
			if (p->coeff > 0.0000001) {
				if (p != this->head) {
					noinput = false;
					cout << '+';
				}
				if (p->coeff - 1 > 0.0000001 || p->coeff - 1 < -0.0000001) {
					noinput = false;
					cout << p->coeff;
				}
				noinput = false;
				cout << 'x';
			}
			else if (p->coeff < -0.0000001) {
				if (p->coeff + 1 > 0.0000001 || p->coeff + 1 < -0.0000001) {
					noinput = false;
					cout << p->coeff;
				}
				else {
					noinput = false;
					cout << '-';
				}
				noinput = false;
				cout << 'x';
			}
		}
		else {
			if (p->coeff > 0.0000001) {
				if (p != this->head) {
					noinput = false;
					cout << '+';
				}
				if (p->coeff - 1 > 0.0000001 || p->coeff - 1 < -0.0000001) {
					noinput = false;
					cout << p->coeff;
				}
				cout << 'x' << '^' << p->index;
			}
			else if (p->coeff < -0.0000001) {
				noinput = false;
				cout << p->coeff << 'x' << '^' << p->index;
			}
		}
		p = p->next;
	}
	double zero = 0;
	if (noinput == true) cout << zero;
	cout << endl;
}

void List::clear(void) {
	Node* p = this->head;
	Node* q = p;
	while (p != nullptr) {
		q = p->next;
		delete p;
		p = q;
	}
	this->head = nullptr;
	delete this;
}


//字符串处理函数：
//输入预处理
vector<string> pretreat(string desk, vector<string> res) { 
	vector<string> mid;
	int length = desk.size();
	int i, j, k = 0;
	desk = insert(desk, "+", 0);
	for (i = 1; i < desk.size(); ++i) {
		if (desk[i] == '-' && desk[i - 1] != '+' && desk[i - 1] != '^') {
			desk = insert(desk, "+", i);
			++i;
		}
	}   //开头以及所有非^右边的-前加上'+'号，这样每个加号右侧可以切出一个子串

	

	//子串处理：
	for (i = 0; i < desk.size(); ++i) {
		if (desk[i] == '+') {
			string tmp;
			for (j = i + 1; desk[j] != '+' && j < desk.size(); ++j) {
				tmp.push_back(desk[j]);
			}
			mid.push_back(tmp);
		}
	}

	for (i = 0; i < mid.size(); ++i) {
		int len = mid[i].size();
		for (int j = 0; j < len; ++j) {
			if ((mid[i][j] == 'x' && j == 0) || (j >= 1 && mid[i][j] == 'x' && (mid[i][j - 1] > '9' || mid[i][j - 1] < '0'))) {
				mid[i] = insert(mid[i], "1", j);
			}
		}
	}   //若x左边不是数字 则加上1

	i = 0;
f:for (; i < mid.size(); ++i) {
	int l = mid[i].size();
	for (j = 0; j < l - 1; ++j) {
		if (mid[i][j] == 'x' && mid[i][j + 1] == '^') {
			string a, b;
			for (k = 0; k < j; ++k) a.push_back(mid[i][k]);
			for (k = j + 2; k < l; ++k) b.push_back(mid[i][k]);
			res.push_back(a);
			res.push_back(b);
			++i;
			goto f;
		}
	}  //对有x^结构的子串的处理
	for (j = 0; j < l; ++j) {
		if (mid[i][j] == 'x') {
			string a;
			for (k = 0; k < j; ++k) a.push_back(mid[i][k]);
			res.push_back(a);
			res.push_back("1");
			++i;
			goto f;
		}
	}  //对有x的子串的处理
	for (j = 0; j < l; ++j) {
		res.push_back(mid[i]);
		res.push_back("0");
		++i;
		goto f;
	} //对常数子串的处理
}

return res;
}

int findp(vector<string> names, string name){
	int i = 0;
	for (i = 0; i < names.size(); ++i) {
		if (names[i] == name) return i;
	}
	return -1;
}

double strtod(string p1) {
	int length = p1.size();
	int i;
	double sumi = 0;
	double sumd = 0;
	double count = 1;
	int inte = 0;
	bool intg = true;
	bool posi = true;
	for (i = 0; i < length; ++i) {
		if (p1[i] == '.') {
			intg = false;
			++i;
		}
		else if (p1[i] == '-') {
			posi = false;
			++i;
		}
		if (i < length) {
			if (intg == true) {
				sumi *= 10;
				sumi += (p1[i] - '0');
			}
			else if (intg == false) {
				sumd *= 10;
				sumd += (p1[i] - '0');
				count *= 10;
			}
		}

	}
	double b = sumi + (sumd / count);
	if (posi == false) b = -b;
	return b;
}

string insert(string desk, string c, int k){
	int i;
	int length = desk.size();
	string tail = c;
	string res;
	for (i = 0; i < k; ++i) {
		res.push_back(desk[i]);
	}
	for (i = k; i < length; ++i) {
		tail.push_back(desk[i]);
	}
	res += tail;
	return res;
}



string cut(string poly, string minus){
	int length1 = poly.size();
	int length2 = minus.size();
	string res;
	int i;
	for (i = 0; i < length1 - length2; ++i) {
		res.push_back(poly[i + length2]);
	}
	if (res[0] == ' ' || res[0] == '+') {
		res = cut(res, " ");
	}
	return res;
}

void sprint(string str){
	int length = str.size();
	int i;
	for (i = 0; i < length; ++i) {
		cout << str[i];
	}
	cout << endl;
}


