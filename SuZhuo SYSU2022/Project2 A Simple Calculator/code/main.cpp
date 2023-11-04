#include "calc.h"

int main() {
	string p;
	create();		//创建窗口，同时保留控制台界面
	while (1) {
		p = calculate();                   //读取输入。 **其中"(/)键"， 鼠标左键单击为'(' ，右键单击为 ')'。
		if (p == "#") break;               //终止计算
		if (compare(p)) {                  //判断输入合法性
			string p_ = p;                
			pretreat(p_);				   //预处理，将-a转为-1*a，否则-2^2计算得4而非-4
			vector<vector<char>> posf;
			posfix(p_, posf);          //将p_转为后缀表达式并存在posf中
			cout << endl;
			int res = calc(posf, p);     //计算后缀表达式posf的值
			cout << res << endl;
			cout << "-------------------------------------------" << endl;
			output(res,p);                 //输出
		}
	}
	//system("pause");                        //防止误操作
}



