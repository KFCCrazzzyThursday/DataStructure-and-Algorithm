#include"gray.h"
#include"resize.h"
#include"zip.h"

string INPUT_PATH = "C:/Users/lenovo/Desktop/Inputs/";
string OUTPUT_PATH = "C:/Users/lenovo/Desktop/Outputs/";

int main() {
	create();
	int i;
	string filename[6] = { "color-block.png","color-block.ppm","lena-128-gray.png","lena-128-gray.ppm","lena-512-gray.png","lena-512-gray.ppm" };
	int control;
	
	while (cin >> control) {
		switch (control) {
		case 1: {
			cout << "演示：读取Inputs文件夹中的图片并保存到Outputs文件夹中" << endl;
			for (i = 0; i < 6; ++i) {
				string filepath = INPUT_PATH;
				filepath += filename[i];
				string storepath = OUTPUT_PATH+"Write_";
				storepath += filename[i];
				Mat src1 = imread(filepath);
				imshow(filename[i], src1);
				imwrite(storepath, src1);
				waitKey(2000);
			}
			cout << "读取写入演示完毕，将关闭所有图片" << endl;
			waitKey(1000);
			destroyAllWindows();
			break;
		}
		case 2: {
			cout << "tride1.txt文件为原始三元组，tride2.txt文件为压缩后的三元组" << endl;
			for (i = 0; i < 6; ++i) {
				string filepath = INPUT_PATH;
				filepath += filename[i];
				Mat src2 = imread(filepath);
				if (zip(src2, filename[i])) {
					string zipname = filename[i];
					zipname += "_tride2.txt";
					unzip(zipname);
				}
			}
			break;
		}
		case 3: {
			Mat src3 = imread(INPUT_PATH+"color - block.ppm");
			imshow("INPUT", src3);
			waitKey(1500);
			destroyWindow("INPUT");
			Mat Grey = gray(src3);
			imshow("GREY_LEVEL",Grey);
			waitKey(3000);
			destroyAllWindows();
			cout << "灰度演示完毕" << endl;
			break;
		}
		case 4: {
			Mat src4 = imread(INPUT_PATH+"lena-128-gray.ppm");
			Mat res=enlarge(src4, 256, 256);
			//namedWindow("256*256", WINDOW_AUTOSIZE);
			imshow("256*256_1", res);
			waitKey(2000);
			imwrite(OUTPUT_PATH+"resize_lena_128_256256.ppm", res);

			
			res=enlarge(src4, 256, 512);
			//namedWindow("256*512", WINDOW_AUTOSIZE);
			imshow("256*512_1", res);
			waitKey(2000);
			imwrite(OUTPUT_PATH+"resize_lena_128_256512.ppm", res);
			
			res = imread(INPUT_PATH+"lena-512-gray.ppm");
			imshow("256*256_2", res);
			waitKey(2000);
			imwrite(OUTPUT_PATH+"resize_lena_512_256256.ppm", res);
			res=enlarge(src4,128, 128);
			imshow("128*128_2", res);
			waitKey(2000);
			imwrite(OUTPUT_PATH+"resize_lena_512_128128.ppm", res);
			break;
		}
		case 0: {
			goto a;
			break;
		}
		default: {
			goto a;
			break;
		}
		}
	}
	a:
	destroyAllWindows();
	return 0;
}



