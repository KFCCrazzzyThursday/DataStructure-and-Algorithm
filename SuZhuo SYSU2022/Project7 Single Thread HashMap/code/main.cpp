#include"test_name.h"

using namespace std;


int main() {
	int control;
	cout <<"主界面:"<<endl << "输入1测试随机生成的30个姓名" << endl << "输入2测试本班中的30个姓名" << endl << "输入3测试哈希表添加、移除元素功能" << endl << "输入-1退出程序" << endl << "-------------------------------------------------------" << endl;
	while (cin >> control) {
		switch (control)
		{
		case 1: {
			cout << "随机生成姓名测试" << endl << endl;
			vector<vector<string>> name = test_name();
			hashtest(name);
			break;
		}
		case 2: {
			cout << "特例测试" << endl << endl;
			vector<vector<string>> name = readfile("test_name_1.txt");
			hashtest(name);
			break;
		}
		case 3: {
			cout << "哈希表测试" << endl << endl;
			Insert_Remove_Search_Clear_Test();
			break;
		}
		case -1: {
			return 0;
		}
		default:
			break;
		}
	}
}