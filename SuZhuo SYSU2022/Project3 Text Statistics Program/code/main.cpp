#include "text.h"
extern int ch[N][100], tag[N], tot;
extern int vis[N];
extern int cnt1, cnt2, cnt3;
extern vector<vector<int>> row;
extern vector<string> words;
extern vector<int> counts;
int main() {
	string filename;
	cout << "����1���ļ���ͳ��" << endl << "����2ʹ����������" << endl << "����0�˳�����" << endl << "---------------------------------------------------------------------" << endl;
	string c;
	vector<vector<string>> label;  //�ִʣ�����Ȼ��Ϊ����
	vector<string> lines;      //����
	while (cin >> c) {
		if (c == "1") {
			label.clear();
			lines.clear();
			clear();                 //ÿ�ζ�ȡǰ���ǰ�ζ�ȡ����
			cout << "������Ҫ�򿪵��ļ���: " << endl;
			cin >> filename;
			read(label, filename, lines);   //��ȡ�ļ����ִʣ�����
			create(label);           //�����ֵ���
			print(label, filename, lines);    //ͳ�ƣ�����ӡͳ����Ϣ
		}
		else if (c == "2") {
			cout << "����\"end_this_search123\"" << "��ֹ����" << endl;
			char control;
			cout << "�Ƿ��ڸ��ļ������� Y/N" << endl;
			cin >> control;
			if (control == 'Y') {
				search(lines);           //����
			}
			else if (control == 'N') {
				cout << "����������ҵ��ļ���" << endl;
				label.clear();
				lines.clear();
				clear();
				cin >> filename;
				read(label, filename, lines);
				create(label);                      //��ȡ��һ�ļ�
				search(lines);
			}
			cout << "��������" << endl;
			cout << "---------------------------------------------------------------------" << endl;
		}
		else if (c == "0") {
			cout << "Done" << endl;
			system("pause");
			break;
		}
		else {
			cout << "Wrong input, please check" << endl;
		}
	}
}