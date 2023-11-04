#include "calc.h"
int chartoi(vector<char> num) {
	int sum = 0;
	int i = 0;
	for (i = 0; i < num.size(); ++i) {
		if (i == 0 && num[i] == '-') {
			continue;
		}
		else {
			sum *= 10;
			sum += (num[i] - '0');
		}
	}
	if (!num.empty() && num[0] == '-') sum *= -1;
	return sum;
}

vector<char> itochar(int num) {
	vector<char> res;
	stack<char> res_;
	int num_ = num;
	if (num < 0) {
		res.push_back('-');
		num_ = -num;
	}
	else if (num == 0) {
		res.push_back('0');
		return res;
	}
	while (num_ > 0) {
		res_.push((num_ % 10) + '0');
		num_ /= 10;
	}
	while (!res_.empty()) {
		res.push_back(res_.top());
		res_.pop();
	}
	return res;
}


void print(vector<vector<char>> pos) {
	int len = pos.size();
	if (len == 0) cout << "Empty";
	int i = 0;
	for (i = 0; i < len; ++i) {
		int lenth = pos[i].size();
		int j = 0;
		for (j = 0; j < lenth; ++j) cout << pos[i][j];
		cout << ' ';
	}
	cout << endl;
}

bool compare(string p) {
	int i = 0;
	int len = p.size();
	if (len == 0) {
		change4();
		cout << "-------------------------------------------" << endl;
		return false;
	}
	if ((p[0] == '-' && (len == 1 || !isnum(p[1]))) || (issym2(p[0])&&p[0]!='-' && p[0] != '(')) {
		change1();
		cout << "-------------------------------------------" << endl;
		return false;
	}
	for (i = 0; i < len; ++i) {
		if (i < len - 1 && p[i] == '^' && p[i + 1] == '-') {
			change5();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		if (p[i] != '+' && p[i] != '-' && p[i] != '*' && p[i] != '/' && p[i] != '^' && p[i] != '(' && p[i] != ')' && (p[i] > '9' || p[i] < '0')) {
			change1();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if (i >= 1 && issym2(p[i]) && issym2(p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1]) && p[i] != '-' && p[i] != '(') {
			change1();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if (i < len - 1 && issym2(p[i]) && p[i] != ')' && p[i] != '(' && !isnum(p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1]) && p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1] != '-' && p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1] != '(') {
			change1();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if (i == len - 1 && issym2(p[i]) && p[i] != ')') {
			change1();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if (i > 1 && (p[i] == '+' || p[i] == '*' || p[i] == '/' || p[i] == '^') && !isnum(p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1]) && p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1] != ')') {
			change1();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if (i >= 1 && p[i] == '(' && isnum(p[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) - 1])) {
			change6();
			cout << "-------------------------------------------" << endl;
			return false;
		}
	}

	stack<char> cmp;
	for (i = 0; i < len; ++i) {
		if (p[i] == '(') cmp.push(p[i]);
		else if (p[i] == ')' && cmp.empty()) {
			change2();
			cout << "-------------------------------------------" << endl;
			return false;
		}
		else if (!cmp.empty() && p[i] == ')') cmp.pop();
	}
	if (!cmp.empty()) {
		change2();
		cout << "-------------------------------------------" << endl;
		return false;
	}
	return true;
}

