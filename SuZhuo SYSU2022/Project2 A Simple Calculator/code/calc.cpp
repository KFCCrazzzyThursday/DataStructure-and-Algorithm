#include "calc.h"
bool issym(const char ch) {
	if ((ch == '+' || ch == '-' || ch == '(' || ch == ')' || ch == '*' || ch == '/' || ch == '^')) return true;
	return false;
}
bool issym2(const char ch) {
	if ((ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')) return true;
	return false;
}
bool isnum(const vector<char> num) {
	if (num[0] >= '0' && num[0] <= '9') return true;
	else if (num.size() > 1 && num[0] == '-' && num[1] >= '0' && num[1] <= '9') return true;
	return false;
}

bool isnum(const char ch) {
	if (ch >= '0' && ch <= '9') return true;
	return false;
}
void posfix(string& p, vector<vector<char>>& pos) {
	cout << "中缀表达式转后缀过程:"<<endl;
	int length = (int)p.size();
	int i;
	stack<char> sym;
	for (i = 0; i < length; ++i) {
		if (!pos.empty()&&(i >= 1 && p[i] >= '0' && p[i] <= '9' && p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] >= '0' && p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] <= '9')) {
			int num = chartoi(pos.back());
			pos.pop_back();
			num = num * 10 + (p[i] - '0');
			vector<char> res = itochar(num);
			pos.push_back(res);
			cout << "后缀表达式：";
			print(pos);
			cout << "运算符栈：";
			print(sym);
		}
		else if (p[i] >= '0' && p[i] <= '9') {
			vector<char> res;
			
			if (!pos.empty()&&pos.back().back() == '$') {
				pos.pop_back();
				res.push_back('-');
			}
			res.push_back(p[i]);
			pos.push_back(res);
			cout << "后缀表达式：";
			print(pos);
			cout << "运算符栈：";
			print(sym);
		}
		else if ((i == 0 && p[i] == '-') || (i >= 1 && p[i] == '-' && (p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '+' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '-' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i)) - 1] == '*' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '/' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '('))) {
			vector<char>res;
			res.push_back('$');
			pos.push_back(res);
		}
		else if (issym(p[i])) {
			if (p[i] == ')') {
				while (sym.top() != '(') {
					vector<char> res;
					res.push_back(sym.top());
					pos.push_back(res);
					sym.pop();
				}
				sym.pop();
				cout << "后缀表达式：";
				print(pos);
				cout << "运算符栈：";
				print(sym);
			}
			else if (p[i] == '^') {
				while (!sym.empty() && sym.top() != '+' && sym.top() != '-' && sym.top() != '*' && sym.top() != '/' && sym.top() != '(') {
					if (sym.top() != '(') {
						vector<char> res;
						res.push_back(sym.top());
						pos.push_back(res);
					}
					sym.pop();
				}
				sym.push(p[i]);
				cout << "后缀表达式：";
				print(pos);
				cout << "运算符栈：";
				print(sym);
			}
			else if (p[i] == '*' || p[i] == '/') {
				while (!sym.empty() && sym.top() != '+' && sym.top() != '-' && sym.top() != '(') {
					if (sym.top() != '(') {
						vector<char> res;
						res.push_back(sym.top());
						pos.push_back(res);
					}
					sym.pop();
				}
				sym.push(p[i]);
				cout << "后缀表达式：";
				print(pos);
				cout << "运算符栈：";
				print(sym);
			}
			else if (p[i] == '+' || p[i] == '-') {
				while (!sym.empty() && sym.top() != '(') {
					if (sym.top() != '(') {
						vector<char> res;
						res.push_back(sym.top());
						pos.push_back(res);
					}
					sym.pop();
				}
				sym.push(p[i]);
				cout << "后缀表达式：";
				print(pos);
				cout << "运算符栈：";
				print(sym);
			}
			else if (p[i] == '(') {
				sym.push(p[i]);
				cout << "后缀表达式：";
				print(pos);
				cout << "运算符栈：";
				print(sym);
			}

		}
	}
	while (!sym.empty()) {
		vector<char> res;
		res.push_back(sym.top());
		pos.push_back(res);
		sym.pop();
		cout << "后缀表达式：";
		print(pos);
		cout << "运算符栈：";
		print(sym);
	}
	cout << endl;
	cout << "最终的后缀表达式：";
	print(pos);
}

int calc(vector<vector<char>>& pos,string p_) {
	cout << "后缀表达式运算过程：" << endl;
	int length = (int)pos.size();
	stack<int> nums;
	int i;
	for (i = 0; i < length; ++i) {
		if (isnum(pos[i])) {
			nums.push(chartoi(pos[i]));
			cout << "运算数栈：";
			print(nums);
		}
		else if (pos[i][0] == '+') {
			int a = nums.top();
			nums.pop();
			int b = nums.top();
			nums.pop();
			nums.push(a + b);
			cout << "运算数栈：";
			print(nums);
		}
		else if (pos[i][0] == '-') {
			int a = nums.top();
			nums.pop();
			int b = nums.top();
			nums.pop();
			nums.push(b - a);
			cout << "运算数栈：";
			print(nums);
		}
		else if (pos[i][0] == '*') {
			int a = nums.top();
			nums.pop();
			int b = nums.top();
			nums.pop();
			nums.push(a * b);
			cout << "运算数栈：";
			print(nums);
		}
		else if (pos[i][0] == '/') {
			int a = nums.top();
			nums.pop();
			int b = nums.top();
			nums.pop();
			if (a == 0) {
				change0();
				system("pause");
				return -1;
			}
			else if (b % a != 0) {
				change3();
				nums.push(b / a);
				cout << "运算数栈：";
				print(nums);
			}
			else {
				nums.push(b / a);
				cout << "运算数栈：";
				print(nums);
			}
		}
		else if (pos[i][0] == '^') {
			double a = nums.top();
			nums.pop();
			double b = nums.top();
			nums.pop();
			nums.push((int)pow(b, a));
			cout << "运算数栈：";
			print(nums);
		}
	}
	cout << endl;
	cout << p_ << '=';
	return nums.top();
}

void change0(){
	MessageBox(NULL, "Devided by 0, check your input. 按任意键继续","Error", MB_OK);
}
void change1() {
	MessageBox(NULL, "Wrong input, please check.", "Error", MB_OK);
}
void change2() {
	MessageBox(NULL, "括号不匹配，请重新输入", "Error", MB_OK);
}
void change3() {
	MessageBox(NULL, "仅支持整数除法，您输入的表达式无法整除，输出为向下取整的结果", "Error", MB_OK);
}
void change4() {
	MessageBox(NULL, "您没有输入内容", "Error", MB_OK);
}
void change5() {
	MessageBox(NULL, "不支持负指数", "Error", MB_OK);
}
void change6() {
	MessageBox(NULL, "请在括号前输入运算符", "Error", MB_OK);
}

void pretreat(string& p) {
	int i = 0,j=0;
	int len = (int)p.size();
	for (i = 0; i < len; ++i) {
		if (i == 0 && p[i] == '-') {
			string p_;
			p_ += "-1*";
			for (j = 1; j < len ; ++j) {
				p_.push_back(p[j]);
			}
			p = p_;
			len += 2;
		}
		else if (i >= 1 && p[i] == '-' && (p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '+' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '-' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i)) - 1] == '*' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '/' || p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] == '(')) {
			string p_;
			for (j = 0; j <= i; ++j) {
				p_.push_back(p[j]);
			}
			p_ += "1*";
			for (j = i+1; j <len; ++j) {
				p_.push_back(p[j]);
			}
			p = p_;
			len += 2;
		}
	}
}