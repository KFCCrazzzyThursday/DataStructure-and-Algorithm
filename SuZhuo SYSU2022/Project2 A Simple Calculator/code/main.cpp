#include "calc.h"

int main() {
	string p;
	create();		//�������ڣ�ͬʱ��������̨����
	while (1) {
		p = calculate();                   //��ȡ���롣 **����"(/)��"�� ����������Ϊ'(' ���Ҽ�����Ϊ ')'��
		if (p == "#") break;               //��ֹ����
		if (compare(p)) {                  //�ж�����Ϸ���
			string p_ = p;                
			pretreat(p_);				   //Ԥ������-aתΪ-1*a������-2^2�����4����-4
			vector<vector<char>> posf;
			posfix(p_, posf);          //��p_תΪ��׺���ʽ������posf��
			cout << endl;
			int res = calc(posf, p);     //�����׺���ʽposf��ֵ
			cout << res << endl;
			cout << "-------------------------------------------" << endl;
			output(res,p);                 //���
		}
	}
	//system("pause");                        //��ֹ�����
}



