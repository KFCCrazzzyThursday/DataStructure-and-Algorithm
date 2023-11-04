//�����ȡ��.txt �� ��.txt ����NAME_SIZE���������
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

	//ONLY_BASIC_INFO:ֻ��ӡ��Ļ�����Ϣ
	//COMPELETE:��ӡ���������Ϣ
	//NOT_EMPTY:��ӡ���зǿյ�Ԫ����Ϣ
	cout << "h1��α���̽����ɢ��):" << endl;
	char c;
	cout << "�Ƿ�ֻ��ӡ��Ļ�����Ϣ����Y/N��" << endl;
	cin >> c;
	if (c == 'Y') {
		h1->print(ONLY_BASIC_INFO);
	}
	else {
		cout << "�Ƿ�ֻ��ӡ�ǿյ�Ԫ����Ϣ����Y/N)" << endl;
		cin >> c;
		if (c == 'Y') {
			h1->print(NOT_EMPTY);
		}
		else {
			h1->print(COMPELETE);
		}
	}
	cout << "���в��Ҳ��ԣ�" << endl;
	while (1) {
		cout << "������Ҫ���ҵ�������" << endl;
		string s;
		//getline(cin, s);
		cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
		getline(cin, s);
		h1->search(s);
		cout << "�Ƿ�������ң���Y/N��" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}
	cout << endl;

	cout << "h2������̽����ɢ�У�:" << endl;
	cout << "�Ƿ�ֻ��ӡ��Ļ�����Ϣ����Y/N��" << endl;
	cin >> c;
	if (c == 'Y') {
		h2->print(ONLY_BASIC_INFO);
	}
	else {
		cout << "�Ƿ�ֻ��ӡ�ǿյ�Ԫ����Ϣ����Y/N)" << endl;
		cin >> c;
		if (c == 'Y') {
			h2->print(NOT_EMPTY);
		}
		else {
			h2->print(COMPELETE);
		}
	}
	cout << "���в��Ҳ��ԣ�" << endl;
	while (1) {
		cout << "������Ҫ���ҵ�������" << endl;
		string s;
		//getline(cin, s);
		cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
		getline(cin, s);
		h2->search(s);
		cout << "�Ƿ�������ң���Y/N��" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}
	cout << endl;

	cout << "h3 ������̽����ɢ�У�: " << endl;
	cout << "�Ƿ�ֻ��ӡ��Ļ�����Ϣ����Y/N��" << endl;
	cin >> c;
	if (c == 'Y') {
		h3->print(ONLY_BASIC_INFO);
	}
	else {
		cout << "�Ƿ�ֻ��ӡ�ǿյ�Ԫ����Ϣ����Y/N)" << endl;
		cin >> c;
		if (c == 'Y') {
			h3->print(NOT_EMPTY);
		}
		else {
			h3->print(COMPELETE);
		}
	}
	cout << "���в��Ҳ��ԣ�" << endl;
	while (1) {
		cout << "������Ҫ���ҵ�������" << endl;
		string s;
		//getline(cin, s);
		cin.ignore(std::numeric_limits< streamsize >::max(), '\n');
		getline(cin, s);
		h3->search(s);
		cout << "�Ƿ�������ң���Y/N��" << endl;
		cin >> c;
		if (c == 'N') {
			break;
		}
	}
	delete h1;
	delete h2;
	delete h3;
	cout << "�������" << endl << "-------------------------------------------------------" << endl;
	cout << "������:" << endl << "����1����������ɵ�30������" << endl << "����2���Ա����е�30������" << endl << "����3���Թ�ϣ����ӡ��Ƴ�Ԫ�ع���" << endl << "����-1�˳�����" << endl << "-------------------------------------------------------" << endl;
}
