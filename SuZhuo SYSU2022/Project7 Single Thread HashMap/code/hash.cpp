#include "hash.h"

//姓名取码
Key Valtokey(Val str) {  //取字符ascii码的和  注意中文的ascii码部分是负数
	Key hash = 0;
	for (int i = 0; i < str.length(); i++) {
		hash += toascii(str[i]); 
	}
	return hash;
}
//测试用：
//Key Valtokey(Val str) {
//	Key hash = toascii(str[0]);
//	return hash;
//}


int stringsize(string str) {         //中山大学
	int count = 0;                   //aaaaaaaa    可见打印时,中文字符的长度与两个英文字符相当 
	for (int i = 0; str[i]; ++i) {   //            而string.size()的返回值与中文字符的编码有关，不宜使用
		if (str[i] < 0) {
			i++;
			count++;
		}
		count++;
	}
	return count;
}                                
	
void Insert_Remove_Search_Clear_Test(HashMap*& h) {
	string str;
	while (cin >> str) {
		if (str == "add") {
			cin >> str;
			h->insert(str);
		}
		else if (str == "rem") {
			cin >> str;
			cout << "是否移除全部名为" << str << "的元素（Y/N）" << endl;
			char c;
			cin >> c;
			if (c == 'Y') {
				h->remove(str, ALL);
			}
			else if (c == 'N') {
				h->remove(str, ONE);
			}
		}
		else if (str == "find") {
			cin >> str;
			h->search(str);
		}
		else if (str == "clear") {
			h->clear();
		}
		else if (str == "exit") {
			break;
		}
		else if (str == "exit") {
			delete h;
			cout << "已退出功能" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "主界面：" << endl << "输入1测试随机生成的30个姓名" << endl << "输入2测试本班中的30个姓名" << endl << "输入3测试哈希表添加、移除元素功能" << endl << "输入-1退出程序" << endl << "-------------------------------------------------------" << endl;
			break;
		}
		else {
			cout << "输入错误" << endl;
		}
		cout << "当前哈希表:" << endl;
		h->print(COMPELETE);
	}
}

void Insert_Remove_Search_Clear_Test(void) {
	cout << "使用探测法：" << endl << "1：伪随机探测再散列" << endl << "2: 线性探测再散列" << endl << "3：二次探测再散列" << endl;
	int control;
	cin >> control;
	cout << "输入\"add 元素\"添加元素，输入\"rem 元素\"删除元素,输入\"find 元素\"查找元素，输入\"clear\"清空哈希表，输入\"exit\"退出" << endl;
	switch (control) {
	case 1: {
		HashMap* h = new HashMap_Pseudo;
		h->set_bias();
		Insert_Remove_Search_Clear_Test(h);
		break;
	}
	case 2: {
		HashMap* h = new HashMap_Linear;
		h->set_bias();
		Insert_Remove_Search_Clear_Test(h);
		break;
	}
	case 3: {
		HashMap* h = new HashMap_Quadratic;
		h->set_bias();
		Insert_Remove_Search_Clear_Test(h);
		break;
	}
	default: {
		break;
	}
	}
}



//基类：
int HashMap::hash(Key key) {
	return (key % this->size + this->size) % this->size; //防止key为负数，%无法将负数转换为正
}

HashMap::HashMap() :size(7), count(0), count_all(0) {
	map = new Pair[size];
}


HashMap::HashMap(HashMap& h) {
	this->size = h.size;
	this->count = h.count;
	this->count_all = h.count_all;
	this->map = new Pair[size];
	for (int i = 0; i < size; i++) {
		this->map[i].value = h.map[i].value;
		this->map[i].freq = h.map[i].freq;
		this->map[i].flag = h.map[i].flag;
	}
}

HashMap::~HashMap() {
	delete[] map;
	size = 0;
	count = 0;
	count_all = 0;
}

Pair& HashMap::operator[](int index) {
	return map[index];
}

double HashMap::loadFactor() {
	return (double)count / size;
}; //装载因子

bool HashMap::remove(Val name, int control) {
	int index = Getindex(name);
	if (index == -1) return false;
	if (control == ONE) {
		if (map[index].freq > 0 && map[index].flag) {
			map[index].freq--;
			count_all--;
			if (map[index].freq == 0) {
				map[index].flag = false;
				count--;
			}
		}
	}
	else if (control == ALL) {
		map[index].flag = false;
		count_all -= map[index].freq;
		map[index].freq = 0;
		count--;
	}
	return true;
};

int HashMap::getSize() {
	return size;
};
int HashMap::getCount() {
	return count;
};
int HashMap::getCount_all() {
	return count_all;
};

void HashMap::print(int control = COMPELETE) {
	cout << "size:" << size << endl;
	cout << "count : " << count << endl;
	cout << "count_all : " << count_all << endl;
	cout << "装载因子 :  " << loadFactor() << endl;
	cout << "平均查找长度：" << averageSearchLength() << endl;
	cout << "偏置序列：" << endl;
	for (int i = 0; i < bias.size(); ++i) cout << bias[i] << ' ';
	cout << endl;
	if (control != ONLY_BASIC_INFO) {
		cout << "哈希表：" << endl;
		cout << "_____________________________________________________" << endl;
		cout << "                      元素" << "             "<< " 标志   "  << "频率" << "  " << endl;
		cout << "-----------------------------------------------------" << endl;
		for (int i = 0; i < size; ++i) {
			if (control == NOT_EMPTY) {
				if (map[i].flag) {
					cout << "Index " << i << (i >= 10 ? (":") : (" :")) << '[' << (map[i].value.empty() ? " " : (" \"" + (map[i].value)) + '\"');
					for (int j = 0; j < 25 - stringsize(map[i].value); ++j) cout << ' ';
					if (map[i].value == "") {
						cout << "  ";
					}
					cout << "," << boolalpha << map[i].flag << (map[i].flag ? ("  ,freq:") : (" ,freq:")) << map[i].freq << ']' << endl;
				}
			}
			else if (control == COMPELETE) {
				cout << "Index " << i << (i >= 10 ? (":") : (" :")) << '[' << (map[i].value.empty() ? " " : (" \"" + (map[i].value)) + '\"');
				for (int j = 0; j < 25 - stringsize(map[i].value); ++j) cout << ' ';
				if (map[i].value == "") {
					cout << "  ";
				}
				cout << "," << boolalpha << map[i].flag << (map[i].flag ? ("  ,freq:") : (" ,freq:")) << map[i].freq << ']' << endl;
			}
		}
		cout << "_____________________________________________________" << endl;
		cout << endl;
	}
};

void HashMap::search(Val name) {
	int i = Getindex(name);
	if ( i== -1) {
		cout << "error:未找到"<<name << endl;
		return;
	}
	cout << "查找元素\"" << name << "\"成功" << endl;
	cout << endl<<"Index " << i << (i >= 10 ? (":") : (" :")) << '[' << (map[i].value.empty() ? " " : (" \"" + (map[i].value)) + '\"');
	for (int j = 0; j < 25 - stringsize(map[i].value); ++j) cout << ' ';
	if (map[i].value == "") {
		cout << "  ";
	}
	cout << "," << boolalpha << map[i].flag << (map[i].flag ? ("  ,freq:") : (" ,freq:")) << map[i].freq << ']' << endl<<endl;
}

void HashMap::clear() {
	delete[] map;
	size = 7;
	count = 0;
	count_all = 0;
	map = new Pair[size];
}
HashMap& HashMap::operator=(HashMap& h) {
	if (this == &h) return *this;
	delete[] map;
	this->size = h.size;
	this->count = h.count;
	this->count_all = h.count_all;
	this->map = new Pair[size];
	this->bias = h.bias;
	for (int i = 0; i < size; i++) {
		this->map[i].value = h.map[i].value;
		this->map[i].freq = h.map[i].freq;
		this->map[i].flag = h.map[i].flag;
	}
	return *this;
}

int HashMap::Getindex(Val str) {
	int index = hash(Valtokey(str));
	int new_index = index;
	int i = 0;
	while (map[new_index].flag && map[new_index].value != str) {  //找到val或遇到空cell停止
		new_index = (index + bias[i]) % size;
		i++;
		if (i == bias.size()) break;
	}
	if (map[new_index].flag) return new_index;
	else return -1;
}

Val HashMap::Getvalue(Key key) {
	int index = hash(key);
	int new_index = index;
	int i = 0;
	while (map[new_index].flag) {
		if (Valtokey(map[new_index].value) == key) {
			return map[new_index].value;
		}
		new_index = (index + bias[i]) % size;
		i++;
	}
	return "";
}

bool HashMap::insert(Val value) {
	bool FULL = false;  //平方探测法可能插入失败，此时应扩容
a:
	if (loadFactor() > MAX_LOAD_FACTOR || FULL) {  //装载因子大于0.5时扩容
		int new_size = prime(size * 2);
		int tmp_size = size;
		size = new_size;
		Pair* temp = map;  //保存旧表
		map = new Pair[new_size];  //rehash
		set_bias();
		count = 0;
		count_all = 0;
		for (int i = 0; i < tmp_size; ++i) {
			if (temp[i].flag) {  //若非空cell
				for (int j = 0; j < temp[i].freq; j++) insert(temp[i].value);
			}
		}
		//rehash
		delete[] temp; //释放旧表
	}

	int index = hash(Valtokey(value));
	int new_index = index;
	int i = 0;
	bool flag = false;
	while (map[new_index].flag) {  //找到val或遇到空cell停止
		if (map[new_index].value == value) {
			map[new_index].freq++;
			count_all++;
			flag = true;
			break;
		}
		if (i == bias.size()) {
			FULL = true;
			goto a;
		}
		new_index = ((index + bias[i]) % size + size) % size;  //防止负数
		i++;

	}
	if (!flag) {
		map[new_index].value = value;
		map[new_index].freq = 1;
		map[new_index].flag = true;
		count++;
		count_all++;
	}
	return true;
}

double HashMap::averageSearchLength(void) {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		if (map[i].flag) {
			int index = hash(Valtokey(map[i].value));  //hash(x)
			int new_index = index;
			//cout << "finding:" << map[i].value << endl;
			//cout << "index:" << index << endl;
			int j = 0;
			while (new_index != i) {
				new_index = (index + bias[j]) % size;
				j++;
			}
			//cout <<"j:" << j << endl;
			sum += j;
		}
	}
	if (count == 0) return 0;
	return sum / count;
}

//伪随机探测 Pseudo类
void HashMap_Pseudo::set_bias() {
	if (!this->bias.empty()) this->bias.clear();
	myRandom r;
	r.mySrand();
	this->bias = r.myRand(1, size - 1);
}

HashMap_Pseudo::HashMap_Pseudo() :HashMap::HashMap() {
	set_bias();
};

HashMap_Pseudo::~HashMap_Pseudo() {}

HashMap_Pseudo::HashMap_Pseudo(HashMap_Pseudo& h) {
	this->size = h.size;
	this->count = h.count;
	this->count_all = h.count_all;
	this->map = new Pair[size];
	this->bias = h.bias;
	for (int i = 0; i < size; i++) {
		this->map[i].value = h.map[i].value;
		this->map[i].freq = h.map[i].freq;
		this->map[i].flag = h.map[i].flag;
	}
}


//线性探测法 Linear类
void HashMap_Linear::set_bias() {
	if (!this->bias.empty()) this->bias.clear();
	for (int i = 0; i < size - 1; ++i) {
		this->bias.push_back(i + 1);  //1~size-1
	}
}

HashMap_Linear::HashMap_Linear() :HashMap::HashMap() {
	set_bias();
}

HashMap_Linear::~HashMap_Linear() {}

HashMap_Linear::HashMap_Linear(HashMap_Linear& h) {
	this->size = h.size;
	this->count = h.count;
	this->count_all = h.count_all;
	this->map = new Pair[size];
	this->bias = h.bias;
	for (int i = 0; i < size; i++) {
		this->map[i].value = h.map[i].value;
		this->map[i].freq = h.map[i].freq;
		this->map[i].flag = h.map[i].flag;
	}
}


//平方探测法 Quadratic类
void HashMap_Quadratic::set_bias() {
	if (!this->bias.empty()) this->bias.clear();
	for (int i = 1; i <= size / 2; ++i) {
		this->bias.push_back(i * i);
		this->bias.push_back((-1) * i * i);
	}
}

HashMap_Quadratic::HashMap_Quadratic() :HashMap::HashMap() {
	set_bias();
}

HashMap_Quadratic::~HashMap_Quadratic() {}

HashMap_Quadratic::HashMap_Quadratic(HashMap_Quadratic& h) {
	this->size = h.size;
	this->count = h.count;
	this->count_all = h.count_all;
	this->map = new Pair[size];
	this->bias = h.bias;
	for (int i = 0; i < size; i++) {
		this->map[i].value = h.map[i].value;
		this->map[i].freq = h.map[i].freq;
		this->map[i].flag = h.map[i].flag;
	}
}


