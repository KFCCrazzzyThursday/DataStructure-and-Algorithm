#include"zip.h"

extern string INPUT_PATH;
extern string OUTPUT_PATH;

bool SameColor(int* c1, int* c2)
{
	if (c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2]) return true;
	return false;
}

vector<int> stringtoint(string& str)   //带空格string拆分成vector<int>
{
	int l = str.size();
	vector<int> res;
	int i;
	int num = 0;
	for (i = 0; i < l; ++i) {
		if (str[i] == ' ' && str[i + 1] != ' ') {
			res.push_back(num);
			num = 0;
		}
		else if (str[i] == ' ' && str[i + 1] == ' ') {
			res.push_back(num);
			num = 0;
			i += 1;
		}
		else if (i == l - 1) {
			num *= 10;
			num += (str[i] - '0');
			res.push_back(num);
		}
		else {
			num *= 10;
			num += (str[i] - '0');
		}
	}
	return res;
}

bool zip(Mat& pic,string& filename)
{
	int i, j;
	vector<pixiv> sparse;
	vector<pixiv>comp;
	vector<compress> zip;

	int dim = pic.channels();
	int w = pic.cols;
	int h = pic.rows;
	if (dim == 3) {
		for (i = 0; i < h; ++i) {
			for (j = 0; j < w; ++j) {
				Vec3b rgb = pic.at<Vec3b>(i, j);
				pixiv tmp(i, j, rgb);
				sparse.push_back(tmp);
			}
		}
	}

	bool flag = false;
	for (i = 0; i < sparse.size(); ++i) {
		for (j = 0; j < zip.size(); ++j) {
			if (SameColor(sparse[i].RGB, zip[j].RGB)) {
				flag = true;
				zip[j].count++;
				break;
			}
		}
		if (!flag) {
			compress tmp(sparse[i].RGB);
			zip.push_back(tmp);
		}
		flag = false;
	}

	for (i = 0; i < zip.size(); ++i) {
		for (j = i + 1; j < zip.size(); ++j) {
			if (zip[i].count < zip[j].count) {
				int counttmp = zip[i].count;
				int rtmp = zip[i].RGB[0];
				int gtmp = zip[i].RGB[1];
				int btmp = zip[i].RGB[2];
				zip[i].count = zip[j].count;
				zip[i].RGB[0] = zip[j].RGB[0];
				zip[i].RGB[1] = zip[j].RGB[1];
				zip[i].RGB[2] = zip[j].RGB[2];

				zip[j].count = counttmp;
				zip[i].RGB[0] = rtmp;
				zip[i].RGB[1] = gtmp;
				zip[i].RGB[2] = btmp;
			}
		}
	}


	for (i = 0; i < sparse.size(); ++i) {
		if (!SameColor(zip[0].RGB, sparse[i].RGB)) {
			comp.push_back(sparse[i]);
		}
	}


	string outname1 = filename+"_tride1.txt";
	string outname2 = filename + "_tride2.txt";
	ofstream outputf1(OUTPUT_PATH+outname1, ios::out);   //储存原三元组
	for (i = 0; i < sparse.size(); ++i) {
		outputf1 << sparse[i].x << ' ' << sparse[i].y << ' ' << sparse[i].RGB[0] << ' ' << sparse[i].RGB[1] << ' ' << sparse[i].RGB[2] << endl;
	}

	ofstream outputf2(OUTPUT_PATH+outname2, ios::out);   //储存压缩三元组
	outputf2 << w << ' ' << h << endl;
	outputf2 << zip[0].RGB[0] << ' ' << zip[0].RGB[1] << ' ' << zip[0].RGB[2] << endl;
	for (i = 0; i < comp.size(); ++i) {
		if (i >= 1) {
			if (comp[i].x != comp[i - 1].x) {
				outputf2 << comp[i].x << ' ' << comp[i].y << ' ' << ' ';
			}
			else {
				if (comp[i].y != (comp[i - 1].y) + 1) {
					outputf2 << comp[i].y << ' ' << ' ';
				}
			}
		}
		else {
			outputf2 << comp[i].x << ' ' << comp[i].y << ' ' << ' ';
		}
		if (comp[i].RGB[0] == comp[i].RGB[1] && comp[i].RGB[0] == comp[i].RGB[2]) {
			outputf2 << comp[i].RGB[0] << endl;
		}
		else {
			outputf2 << comp[i].RGB[0] << ' ' << comp[i].RGB[1] << ' ' << comp[i].RGB[2] << endl;
		}
	}
	if (outputf1 && outputf2)	return true;
	return false;
}

bool unzip(string& zipname) {
	int i, j;
	ifstream input1(OUTPUT_PATH+zipname, ios::in);//解压
	vector<pixiv> decode;
	if (!input1.is_open()) {
		cout << "读取文件失败" << endl;
		return 1;
	}
	string buf;
	getline(input1, buf);
	vector<int>SIZE = stringtoint(buf);
	Mat dec = Mat::zeros(Size(SIZE[1], SIZE[0]), CV_8UC3);  //空图
	getline(input1, buf);
	vector<int>backgroudcolor = stringtoint(buf);   
	for (i = 0; i < SIZE[1]; ++i) {
		for (j = 0; j < SIZE[0]; ++j) {
			dec.at<Vec3b>(i, j)[0] = backgroudcolor[0];
			dec.at<Vec3b>(i, j)[1] = backgroudcolor[1];
			dec.at<Vec3b>(i, j)[2] = backgroudcolor[2];
		}
	}
	int x = 0, y = 0;
	while (getline(input1, buf)) {
		bool doubleblank = false;
		int blank = 0;
		for (i = 0; i < buf.size(); ++i) {
			if (buf[i] == ' ') blank++;
			if (i < buf.size() - 1 && buf[i] == ' ' && buf[i + 1] == ' ') doubleblank = true;
		}
		vector<int> p = stringtoint(buf);
		vector<int> pivixcolor(3);
		switch (blank) {     //对每一行数据中的空格数计数 判断是何种压缩数据 还原原数据
		case 5: {
			x = p[0];
			y = p[1];
			pivixcolor[0] = p[2];
			pivixcolor[1] = p[3];
			pivixcolor[2] = p[4];
			break;
		}
		case 4: {
			y = p[0];
			pivixcolor[0] = p[1];
			pivixcolor[1] = p[2];
			pivixcolor[2] = p[3];
			break;
		}
		case 3: {
			x = p[0];
			y = p[1];
			pivixcolor[0] = p[2];
			pivixcolor[1] = p[2];
			pivixcolor[2] = p[2];
			break;
		}
		case 2: {
			if (doubleblank) {
				y = p[0];
				pivixcolor[0] = p[1];
				pivixcolor[1] = p[1];
				pivixcolor[2] = p[1];
			}
			else {
				y = y + 1;
				pivixcolor[0] = p[0];
				pivixcolor[1] = p[1];
				pivixcolor[2] = p[2];
			}
			break;
		}
		case 0: {
			y = y + 1;
			pivixcolor[0] = p[0];
			pivixcolor[1] = p[0];
			pivixcolor[2] = p[0];
			break;
		}
		default: {
			break;
		}
		}
		{
			dec.at<Vec3b>(x, y)[0] = pivixcolor[0];
			dec.at<Vec3b>(x, y)[1] = pivixcolor[1];
			dec.at<Vec3b>(x, y)[2] = pivixcolor[2];
		}
	}
	string unzipname;
	for (i = 0; i < zipname.size(); ++i) {
		if (zipname[i] == '_' && zipname[i + 1] == 't') {
			break;
		}
		unzipname += zipname[i];
	}
	imwrite(OUTPUT_PATH+"unzip_"+unzipname, dec);
}
