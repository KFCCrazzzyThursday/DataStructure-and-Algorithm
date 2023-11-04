#include "hash.h"

//����ȡ��
Key Valtokey(Val str) {  //ȡ�ַ�ascii��ĺ�  ע�����ĵ�ascii�벿���Ǹ���
	Key hash = 0;
	for (int i = 0; i < str.length(); i++) {
		hash += toascii(str[i]); 
	}
	return hash;
}
//�����ã�
//Key Valtokey(Val str) {
//	Key hash = toascii(str[0]);
//	return hash;
//}


int stringsize(string str) {         //��ɽ��ѧ
	int count = 0;                   //aaaaaaaa    �ɼ���ӡʱ,�����ַ��ĳ���������Ӣ���ַ��൱ 
	for (int i = 0; str[i]; ++i) {   //            ��string.size()�ķ���ֵ�������ַ��ı����йأ�����ʹ��
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
			cout << "�Ƿ��Ƴ�ȫ����Ϊ" << str << "��Ԫ�أ�Y/N��" << endl;
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
			cout << "���˳�����" << endl;
			cout << "-------------------------------------------------------" << endl;
			cout << "�����棺" << endl << "����1����������ɵ�30������" << endl << "����2���Ա����е�30������" << endl << "����3���Թ�ϣ����ӡ��Ƴ�Ԫ�ع���" << endl << "����-1�˳�����" << endl << "-------------------------------------------------------" << endl;
			break;
		}
		else {
			cout << "�������" << endl;
		}
		cout << "��ǰ��ϣ��:" << endl;
		h->print(COMPELETE);
	}
}

void Insert_Remove_Search_Clear_Test(void) {
	cout << "ʹ��̽�ⷨ��" << endl << "1��α���̽����ɢ��" << endl << "2: ����̽����ɢ��" << endl << "3������̽����ɢ��" << endl;
	int control;
	cin >> control;
	cout << "����\"add Ԫ��\"���Ԫ�أ�����\"rem Ԫ��\"ɾ��Ԫ��,����\"find Ԫ��\"����Ԫ�أ�����\"clear\"��չ�ϣ������\"exit\"�˳�" << endl;
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



//���ࣺ
int HashMap::hash(Key key) {
	return (key % this->size + this->size) % this->size; //��ֹkeyΪ������%�޷�������ת��Ϊ��
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
}; //װ������

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
	cout << "װ������ :  " << loadFactor() << endl;
	cout << "ƽ�����ҳ��ȣ�" << averageSearchLength() << endl;
	cout << "ƫ�����У�" << endl;
	for (int i = 0; i < bias.size(); ++i) cout << bias[i] << ' ';
	cout << endl;
	if (control != ONLY_BASIC_INFO) {
		cout << "��ϣ��" << endl;
		cout << "_____________________________________________________" << endl;
		cout << "                      Ԫ��" << "             "<< " ��־   "  << "Ƶ��" << "  " << endl;
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
		cout << "error:δ�ҵ�"<<name << endl;
		return;
	}
	cout << "����Ԫ��\"" << name << "\"�ɹ�" << endl;
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
	while (map[new_index].flag && map[new_index].value != str) {  //�ҵ�val��������cellֹͣ
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
	bool FULL = false;  //ƽ��̽�ⷨ���ܲ���ʧ�ܣ���ʱӦ����
a:
	if (loadFactor() > MAX_LOAD_FACTOR || FULL) {  //װ�����Ӵ���0.5ʱ����
		int new_size = prime(size * 2);
		int tmp_size = size;
		size = new_size;
		Pair* temp = map;  //����ɱ�
		map = new Pair[new_size];  //rehash
		set_bias();
		count = 0;
		count_all = 0;
		for (int i = 0; i < tmp_size; ++i) {
			if (temp[i].flag) {  //���ǿ�cell
				for (int j = 0; j < temp[i].freq; j++) insert(temp[i].value);
			}
		}
		//rehash
		delete[] temp; //�ͷžɱ�
	}

	int index = hash(Valtokey(value));
	int new_index = index;
	int i = 0;
	bool flag = false;
	while (map[new_index].flag) {  //�ҵ�val��������cellֹͣ
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
		new_index = ((index + bias[i]) % size + size) % size;  //��ֹ����
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

//α���̽�� Pseudo��
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


//����̽�ⷨ Linear��
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


//ƽ��̽�ⷨ Quadratic��
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


