#include"pixiv.h"

void create(void) {
	cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_SILENT);  //停止输出日志信息
	cout << "输入1演示图像的读取、写入与展示，读取Inputs文件夹中的图片并保存到Outputs文件夹中" << endl;
	cout << "输入2演示图像的压缩储存,tride1.txt文件为原始三元组，tride2.txt文件为压缩后的三元组" << endl;
	cout << "输入3演示彩色图像转换为灰度图像，使用加权法" << endl;
	cout << "输入4演示图像尺寸的缩放，128*128放大到256*256和256*512,512*512缩小到256*256和128*128，使用双线性插值" << endl;
	cout << "输入0退出程序" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl << endl;
}