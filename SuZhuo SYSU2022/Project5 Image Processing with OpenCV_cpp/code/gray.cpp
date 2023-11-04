#include "gray.h"

extern string INPUT_PATH;
extern string OUTPUT_PATH;

Mat gray(Mat& src1){
	int dim = src1.channels();
	int i, j;
	int w = src1.cols;
	int h = src1.rows;
	Mat Gray = Mat::zeros(Size(h, w), CV_8UC3);
	if (dim == 3) {
		for (i = 0; i < h; ++i) {
			for (j = 0; j < w; ++j) {
				Vec3b rgb = src1.at<Vec3b>(i, j);
				int r = rgb[0];
				int g = rgb[1];
				int b = rgb[2];
				Gray.at<Vec3b>(i, j)[0] = (r * 299 + g * 587 + b * 114 + 500) / 1000;
				Gray.at<Vec3b>(i, j)[1] = (r * 299 + g * 587 + b * 114 + 500) / 1000;
				Gray.at<Vec3b>(i, j)[2] = (r * 299 + g * 587 + b * 114 + 500) / 1000;
			}
		}
	}
	imwrite(OUTPUT_PATH+"gray.ppm", Gray);
	//imshow("Grey_level", Gray);
	return Gray;
}
