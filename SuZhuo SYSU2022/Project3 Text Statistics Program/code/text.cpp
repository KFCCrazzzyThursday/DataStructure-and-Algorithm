#include"text.h"
int ch[N][100], tag[N], tot;
int vis[N];
int cnt1, cnt2, cnt3;
vector<vector<int>> row;
vector<string> words;
vector<int> counts;
void read(vector<vector<string>>& label, string filename, vector<string>& lines) {
	string sys = "start ";
	sys += filename;
	system(sys.c_str());
	ifstream ifs;
	ifs.open(filename);
	string str;
	int i;

	while (getline(ifs, str)) {
		lines.push_back(str);
		vector<string> tmp;
		string temp;
		for (i = 0; i < str.size(); ++i) {
			if (str[i] == ' ' || str[i] == '\t') {
				cnt3++;
				if (!temp.empty()) tmp.push_back(temp);
				temp = "";
			}
			else if (i == str.size() - 1 && !issym(str[i])) {
				cnt1++;
				temp.push_back(str[i]);
				if (!temp.empty()) tmp.push_back(temp);
				temp = "";
			}
			else if (issym(str[i])) {
				cnt2++;
				if (!temp.empty()) tmp.push_back(temp);
				temp = str[i];
				tmp.push_back(temp);
				temp = "";
			}
			else if (str[i] != ' ' && str[i] != '\t') {
				if (str[i] == '-')	cnt2++;
				else cnt1++;
				temp.push_back(str[i]);
			}
		}
		label.push_back(tmp);
	}
}

void create(vector<vector<string>>& label) {              //创建字典树
	int i, j, k;
	for (i = 0; i < label.size(); ++i) {
		for (j = 1; j <= label[i].size(); ++j) {
			string tmp;
			tmp.push_back(' ');
			tmp += label[i][static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(j) - 1];
			int u = 1;
			for (k = 1; k < tmp.size(); ++k) {
				int c = 0;
				c = chtoi(tmp[k]);
				if (!ch[u][c])
					ch[u][c] =
					++tot;     // 如果子节点中没有这个字符，添上并将该字符的节点号记录为++tot
				u = ch[u][c];  // 往更深一层搜索
				if (k == tmp.size() - 1 && tag[u]) {
					tag[u]++;
				}
			}
			if (!tag[u]) tag[u] = 1;  // 最后一个字符为节点 u 的名字未被访问到记录为 1
		}
	}
}


void print(vector<vector<string>> label, string filename, vector<string> lines) {
	cout << "---------------------------------------------------------------------" << endl << endl;
	cout << "文档统计信息：" << endl;
	int i, j, k;
	for (i = 0; i < label.size(); ++i) {
		for (j = 0; j < label[i].size(); ++j) {
			int p = 1;
			for (int k = 0; k < label[i][j].size(); ++k) {
				int c = 0;
				c = chtoi(label[i][j][k]);
				p = ch[p][c];
			}
			if (tag[p]) {
				if (!vis[p]) {
					words.push_back(label[i][j]);
					row.push_back({ i + 1 });
					counts.push_back(tag[p]);
					vis[p] = 1;
					tag[p]--;
				}
				else {
					int m;
					for (m = 0; m < words.size(); ++m) {
						if (words[m] == label[i][j]) break;
					}
					row[m].push_back(i + 1);
					tag[p]--;
				}
			}
		}
	}

	cout << "全文 共" << label.size() << "行" << endl;
	cout << "     共" << cnt1 + cnt2 << "个字符（不含空格）" << endl;
	cout << "     共" << cnt3 << "个空格和制表符" << endl;
	cout << "     共" << cnt2 << "个半角符号" << endl << endl;
	if (isc(filename)) {
		cout << "此文件为c++文件，将额外统计保留字符集" << endl;
		cout << "保留字符集统计：" << endl;
		int cnt = 0;
		vector<string> preserved = { "int","long","short","float","double","char","unsigned","signed","const","void","volatile","enum","struct","union","if","else","goto","switch","case","while","for","continue","break","return","default","typedef","auto","register","extern","static","sizeof","%c","%d","%f","%o","%s","%u","%x","%%" };
		for (i = 0; i < preserved.size(); ++i) {
			bool flag = true;
			for (j = 1; j <= lines.size(); ++j) {
				vector<int> col = KMP(lines[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(j) - 1], preserved[i]);
				if (!col.empty()) {
					if (flag == true) {
						cout << '\"' << preserved[i] << '\"' << " : " << endl;
						flag = false;
					}
					cout << "第 " << j << " 行  " << "第 ";
					for (k = 0; k < col.size(); ++k) {
						cout << col[k] + 1 << ' ';
						cnt++;
					}
					cout << "列" << endl;
				}
			}
			if (cnt) cout << "共" << cnt << "个" << endl << endl;
			cnt = 0;
		}
		cout << "---------------------------------------------------------------------" << endl << endl;
	}
	cout << "按首次出现行数排序:" << endl;
	for (i = 0; i < words.size(); ++i) {
		cout << '\"' << words[i] << '\"' << " : " << "共出现" << counts[i] << "次" << endl;
		cout << "出现在第 ";
		for (j = 0; j < row[i].size(); ++j) {
			if (j >= 1 && row[i][j] != row[i][static_cast<std::vector<int, std::allocator<int>>::size_type>(j) - 1]) {
				if (j != 0) cout << ',';
				cout << row[i][j];
			}
			else if (j == 0) {
				if (j != 0) cout << ',';
				cout << row[i][j];
			}
		}
		cout << " 行" << endl << endl;
	}
	for (i = 0; i < words.size(); ++i) {
		for (j = i; j < words.size(); ++j) {
			if (counts[i] < counts[j]) {
				int tmp1 = counts[i];
				vector<int> tmp2 = row[i];
				string tmp3 = words[i];
				counts[i] = counts[j];
				row[i] = row[j];
				words[i] = words[j];
				counts[j] = tmp1;
				row[j] = tmp2;
				words[j] = tmp3;
			}
		}
	}
	cout << "---------------------------------------------------------------------" << endl << endl;
	cout << "按词频排序:" << endl;
	for (i = 0; i < words.size(); ++i) {
		cout << '\"' << words[i] << '\"' << " : " << "共出现" << counts[i] << "次" << endl;
		cout << "出现在第 ";
		for (j = 0; j < row[i].size(); ++j) {
			if (j >= 1 && row[i][j] != row[i][static_cast<std::vector<int, std::allocator<int>>::size_type>(j) - 1]) {
				if (j != 0) cout << ',';
				cout << row[i][j];
			}
			else if (j == 0) {
				if (j != 0) cout << ',';
				cout << row[i][j];
			}
		}
		cout << " 行" << endl << endl;
	}
	cout << "文本分析已结束" << endl;
	cout << "---------------------------------------------------------------------" << endl;
}

vector<int> profix(string& mode) {
	int i;
	int n = (int)mode.size();
	vector<int> pro(n);
	for (i = 1; i < n; ++i) {
		int j = pro[static_cast<std::vector<int, std::allocator<int>>::size_type>(i) - 1];
		while (j > 0 && mode[i] != mode[j]) {
			j = pro[static_cast<std::vector<int, std::allocator<int>>::size_type>(j) - 1];
		}
		if (mode[i] == mode[j]) {
			j += 1;
		}
		pro[i] = j;
	}
	return pro;
}

vector<int> KMP(string& desk, string& mode) {
	int i;
	string mode_ = mode + "$";
	int l = (int)mode_.size();
	int l_ = (int)desk.size();
	vector<int> pro = profix(mode_);
	for (i = 0; i < desk.size(); ++i) {
		int j = pro[static_cast<std::vector<int, std::allocator<int>>::size_type>(l) - 1 + i];
		while (j > 0 && desk[i] != mode_[j]) {
			j = pro[static_cast<std::vector<int, std::allocator<int>>::size_type>(j) - 1];
		}
		if (desk[i] == mode_[j]) {
			j += 1;
		}
		pro.push_back(j);
	}
	vector<int>res;
	for (i = l; i < pro.size(); ++i) {
		if (pro[i] == l - 1) res.push_back(i - 2 * l + 2);
	}
	return res;
}

void search(vector<string> lines) {
	int i, j;
	int cnt = 0;
	while (1) {
		cout << "请输入要查找的字符串" << endl;
		string find;
		cin >> find;
		if (find == "end_this_search123") break;
		for (i = 1; i <= lines.size(); ++i) {
			vector<int> col = KMP(lines[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) - 1], find);
			if (!col.empty()) {
				cout << "第 " << i << " 行  " << "第 ";
				for (j = 0; j < col.size(); ++j) {
					cout << col[j] + 1 << ' ';
					cnt++;
				}
				cout << "列" << endl;
			}
		}
		if (cnt) cout << "共" << cnt << "个" << endl << endl;
		else cout << "字符串未找到" << endl << endl;
		cnt = 0;

	}
}

bool issym(char ch) {
	if (ch == '!' || ch == '@' || ch == '#' || ch == '%' || ch == '^' || ch == '&' || ch == '*' || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == ';' || ch == ':' || ch == '\'' || ch == '\"' || ch == '\\' || ch == '<' || ch == '>' || ch == '?' || ch == ',' || ch == '.' || ch == '=') return true;
	return false;
}

inline bool isc(string name)
{
	int l = name.size() - 1;
	if ((name[l - 3] == '.' && name[l - 2] == 'c' && name[l - 1] == 'c' && name[l] == 'p') || (name[l - 1] == '.' && name[l] == 'c') || (name[l - 3] == '.' && name[l - 2] == 'h' && name[l - 1] == 'p' && name[l] == 'p') || (name[l - 1] == '.' && name[l] == 'h')) {
		return true;
	}
	return false;
}


int chtoi(char ch) {
	int c = 0;
	if (ch >= 'a' && ch <= 'z') {
		c = ch - 'a';
	}
	else if (ch >= 'A' && ch <= 'Z') {
		c = ch - 'A' + 26;
	}
	else if (ch >= '0' && ch <= '9') {
		c = ch - '0' + 52;
	}
	else {
		switch (ch) {
		case '!': {
			c = 63;
			break;
		}
		case'@': {
			c = 64;
			break;
		}
		case'#': {
			c = 65;
			break;
		}
		case'$': {
			c = 66;
			break;
		}
		case'%': {
			c = 67;
			break;
		}
		case'^': {
			c = 68;
			break;
		}
		case '&': {
			c = 69;
			break;
		}
		case'*': {
			c = 70;
			break;
		}
		case'(': {
			c = 71;
			break;
		}
		case')': {
			c = 72;
			break;
		}
		case'[': {
			c = 73;
			break;
		}
		case']': {
			c = 74;
			break;
		}
		case'{': {
			c = 75;
			break;
		}
		case'}': {
			c = 76;
			break;
		}
		case';': {
			c = 77;
			break;
		}
		case':': {
			c = 78;
			break;
		}
		case'\'': {
			c = 79;
			break;
		}
		case'\"': {
			c = 80;
			break;
		}
		case'\\': {
			c = 81;
			break;
		}
		case'<': {
			c = 82;
			break;
		}
		case'>': {
			c = 83;
			break;
		}
		case'?': {
			c = 84;
			break;
		}
		case',': {
			c = 85;
			break;
		}
		case'.': {
			c = 86;
			break;
		}
		case'=': {
			c = 87;
			break;
		}
		default: {
			c = 99;
			break;
		}
		}
	}
	return c;
}

void clear()
{
	tot = 1;
	cnt1 = 0;
	cnt2 = 0;
	cnt3 = 0;
	row.clear();
	words.clear();
	counts.clear();
	int i, j;
	for (i = 0; i < N; ++i) {
		tag[i] = 0;
		vis[i] = 0;
	}
	for (i = 0; i < N; ++i) {
		for (j = 0; j < 100; ++j) {
			ch[i][j] = 0;
		}
	}
}
