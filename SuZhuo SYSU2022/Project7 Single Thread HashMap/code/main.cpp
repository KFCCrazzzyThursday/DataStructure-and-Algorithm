#include"test_name.h"

using namespace std;


int main() {
	int control;
	cout <<"������:"<<endl << "����1����������ɵ�30������" << endl << "����2���Ա����е�30������" << endl << "����3���Թ�ϣ����ӡ��Ƴ�Ԫ�ع���" << endl << "����-1�˳�����" << endl << "-------------------------------------------------------" << endl;
	while (cin >> control) {
		switch (control)
		{
		case 1: {
			cout << "���������������" << endl << endl;
			vector<vector<string>> name = test_name();
			hashtest(name);
			break;
		}
		case 2: {
			cout << "��������" << endl << endl;
			vector<vector<string>> name = readfile("test_name_1.txt");
			hashtest(name);
			break;
		}
		case 3: {
			cout << "��ϣ�����" << endl << endl;
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