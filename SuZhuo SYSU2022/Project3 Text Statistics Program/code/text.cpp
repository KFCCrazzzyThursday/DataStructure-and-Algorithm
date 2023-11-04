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

void create(vector<vector<string>>& label) {              //�����ֵ���
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
					++tot;     // ����ӽڵ���û������ַ������ϲ������ַ��Ľڵ�ż�¼Ϊ++tot
				u = ch[u][c];  // ������һ������
				if (k == tmp.size() - 1 && tag[u]) {
					tag[u]++;
				}
			}
			if (!tag[u]) tag[u] = 1;  // ���һ���ַ�Ϊ�ڵ� u ������δ�����ʵ���¼Ϊ 1
		}
	}
}


void print(vector<vector<string>> label, string filename, vector<string> lines) {
	cout << "---------------------------------------------------------------------" << endl << endl;
	cout << "�ĵ�ͳ����Ϣ��" << endl;
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

	cout << "ȫ�� ��" << label.size() << "��" << endl;
	cout << "     ��" << cnt1 + cnt2 << "���ַ��������ո�" << endl;
	cout << "     ��" << cnt3 << "���ո���Ʊ��" << endl;
	cout << "     ��" << cnt2 << "����Ƿ���" << endl << endl;
	if (isc(filename)) {
		cout << "���ļ�Ϊc++�ļ���������ͳ�Ʊ����ַ���" << endl;
		cout << "�����ַ���ͳ�ƣ�" << endl;
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
					cout << "�� " << j << " ��  " << "�� ";
					for (k = 0; k < col.size(); ++k) {
						cout << col[k] + 1 << ' ';
						cnt++;
					}
					cout << "��" << endl;
				}
			}
			if (cnt) cout << "��" << cnt << "��" << endl << endl;
			cnt = 0;
		}
		cout << "---------------------------------------------------------------------" << endl << endl;
	}
	cout << "���״γ�����������:" << endl;
	for (i = 0; i < words.size(); ++i) {
		cout << '\"' << words[i] << '\"' << " : " << "������" << counts[i] << "��" << endl;
		cout << "�����ڵ� ";
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
		cout << " ��" << endl << endl;
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
	cout << "����Ƶ����:" << endl;
	for (i = 0; i < words.size(); ++i) {
		cout << '\"' << words[i] << '\"' << " : " << "������" << counts[i] << "��" << endl;
		cout << "�����ڵ� ";
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
		cout << " ��" << endl << endl;
	}
	cout << "�ı������ѽ���" << endl;
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
		cout << "������Ҫ���ҵ��ַ���" << endl;
		string find;
		cin >> find;
		if (find == "end_this_search123") break;
		for (i = 1; i <= lines.size(); ++i) {
			vector<int> col = KMP(lines[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(i) - 1], find);
			if (!col.empty()) {
				cout << "�� " << i << " ��  " << "�� ";
				for (j = 0; j < col.size(); ++j) {
					cout << col[j] + 1 << ' ';
					cnt++;
				}
				cout << "��" << endl;
			}
		}
		if (cnt) cout << "��" << cnt << "��" << endl << endl;
		else cout << "�ַ���δ�ҵ�" << endl << endl;
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
