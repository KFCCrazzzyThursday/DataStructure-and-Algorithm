//随机读取姓.txt 与 名.txt 生成NAME_SIZE个随机姓名
#include "test_name.h"
#define NAME_SIZE 30

vector<vector<string>> readfile(string filename) {
	ifstream file(filename);
	vector<vector<string>> v;
	vector<string> v1(2);
	string s;
	while (getline(file, s)) {
		int i=0;
		while (s[i] != ' ' && s[i] != ',' && s[i] != '\0') {
			v1[0].push_back(s[i]);
			++i;
		}
		for (int j = i + 1; j < s.size(); ++j) {
			v1[1].push_back(s[j]);
		}
		v.push_back(v1);
		v1[0].clear();
		v1[1].clear();
	}
	return v;
}

vector<vector<string>> test_name(vector<vector<string>> First_name, vector<vector<string>> Last_name) {
	vector<vector<string>> v;
	vector<string> tmp(2);
	
	myRandom r;
	r.mySrand();
	for (int i = 0; i < NAME_SIZE; ++i) {
		int x = r.myRand() % First_name.size();
		int y = r.myRand() % Last_name.size();
		string s = First_name[x][0] + Last_name[y][0];
		string c = First_name[x][1] + Last_name[y][1];
		tmp[0] = s;
		tmp[1] = c;
		v.push_back(tmp);
		tmp[0].clear();
		tmp[1].clear();
	}
	return v;
}

vector<vector<string>> test_name(string First_name, string Last_name) {
	vector<vector<string>> v = test_name(readfile(First_name), readfile(Last_name));
	ofstream file;
	file.open("test_name.txt", ios::out);
	for (int i = 0; i < v.size(); ++i) { 
		file.write(v[i][0].c_str(), v[i][0].size()); 
		file.write(" ", 1);
		file.write(v[i][1].c_str(), v[i][1].size());
		file.write("\n", 1);
	}
	file.close();
	return v;
}

void hashtest(vector<vector<string>>&name){
	HashMap* h1 = new HashMap_Pseudo();
	HashMap* h2 = new HashMap_Linear;
	HashMap* h3 = new HashMap_Quadratic();
	for (int i = 0; i < name.size(); ++i) {
		h1->insert(name[i][0] + ", " + name[i][1]);
		h2->insert(name[i][0] + ", " + name[i][1]);
		h3->insert(name[i][0] + ", " + name[i][1]);
	}

	//ONLY_BASIC_INFO:只打印表的基本信息
	//COMPELETE:打印表的所有信息
	//NOT_EMPTY:打印表中非空单元的信息
	cout << "h1（伪随机探测再散列):" << endl;
	char c;
	cout << "是否只打印表的基本信息？（Y/N）" << endl;
	cin >> c;
	if (c == 'Y') {
		h1->print(ONLY_BASIC_INFO);
	}
	else {
		cout << "是否只打印非空单元的信息？（Y/N)" << endl;
		cin >> c;
		if (c == 'Y') {
			h1->print(NOT_EMPTY);
		}
		else {
			h1->print(COMPELETE);
		}
	}
	cout << "进行查找测试：" << endl;
	while (1) {
		cout << "请输入要查找的姓名：" << endl;
		string s;
		//getline(cin, s);
		cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
		getline(cin, s);
		h1->search(s);
		cout << "是否继续查找？（Y/N）" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}
	cout << endl;

	cout << "h2（线性探测再散列）:" << endl;
	cout << "是否只打印表的基本信息？（Y/N）" << endl;
	cin >> c;
	if (c == 'Y') {
		h2->print(ONLY_BASIC_INFO);
	}
	else {
		cout << "是否只打印非空单元的信息？（Y/N)" << endl;
		cin >> c;
		if (c == 'Y') {
			h2->print(NOT_EMPTY);
		}
		else {
			h2->print(COMPELETE);
		}
	}
	cout << "进行查找测试：" << endl;
	while (1) {
		cout << "请输入要查找的姓名：" << endl;
		string s;
		//getline(cin, s);
		cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
		getline(cin, s);
		h2->search(s);
		cout << "是否继续查找？（Y/N）" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}
	cout << endl;

	cout << "h3 （二次探测再散列）: " << endl;
	cout << "是否只打印表的基本信息？（Y/N）" << endl;
	cin >> c;
	if (c == 'Y') {
		h3->print(ONLY_BASIC_INFO);
	}
	else {
		cout << "是否只打印非空单元的信息？（Y/N)" << endl;
		cin >> c;
		if (c == 'Y') {
			h3->print(NOT_EMPTY);
		}
		else {
			h3->print(COMPELETE);
		}
	}
	cout << "进行查找测试：" << endl;
	while (1) {
		cout << "请输入要查找的姓名：" << endl;
		string s;
		//getline(cin, s);
		cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
		getline(cin, s);
		h3->search(s);
		cout << "是否继续查找？（Y/N）" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}
	delete h1;
	delete h2;
	delete h3;
	cout << "输出结束" << endl << "-------------------------------------------------------" << endl;
	cout << "主界面:" << endl << "输入1测试随机生成的30个姓名" << endl << "输入2测试本班中的30个姓名" << endl << "输入3测试哈希表添加、移除元素功能" << endl << "输入-1退出程序" << endl << "-------------------------------------------------------" << endl;
}
