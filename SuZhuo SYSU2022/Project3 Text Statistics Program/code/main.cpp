#include "text.h"
extern int ch[N][100], tag[N], tot;
extern int vis[N];
extern int cnt1, cnt2, cnt3;
extern vector<vector<int>> row;
extern vector<string> words;
extern vector<int> counts;
int main() {
	string filename;
	cout << "键入1打开文件并统计" << endl << "键入2使用搜索功能" << endl << "键入0退出程序" << endl << "---------------------------------------------------------------------" << endl;
	string c;
	vector<vector<string>> label;  //分词，以自然词为粒度
	vector<string> lines;      //分行
	while (cin >> c) {
		if (c == "1") {
			label.clear();
			lines.clear();
			clear();                 //每次读取前清除前次读取内容
			cout << "请输入要打开的文件名: " << endl;
			cin >> filename;
			read(label, filename, lines);   //读取文件，分词，分行
			create(label);           //创建字典树
			print(label, filename, lines);    //统计，并打印统计信息
		}
		else if (c == "2") {
			cout << "输入\"end_this_search123\"" << "终止搜索" << endl;
			char control;
			cout << "是否在该文件中搜索 Y/N" << endl;
			cin >> control;
			if (control == 'Y') {
				search(lines);           //搜索
			}
			else if (control == 'N') {
				cout << "输入你想查找的文件名" << endl;
				label.clear();
				lines.clear();
				clear();
				cin >> filename;
				read(label, filename, lines);
				create(label);                      //读取另一文件
				search(lines);
			}
			cout << "搜索结束" << endl;
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