#include"resize.h"

Mat enlarge(Mat& ori, int width, int height) {
	Mat res = Mat::zeros(Size(width, height), CV_8UC3);
	double w_ratio = (double)ori.cols / width;
	double h_ratio = (double)ori.rows / height;
	int i, j;
	for (i = 0; i < height; ++i) {
		for (j = 0; j < width; ++j) {
			double orix = (double)i * h_ratio;
			double oriy = (double)j * w_ratio;
			int px = (int)orix;
			int py = (int)oriy;
			int px2 = px + 1;
			int py2 = py + 1;
			if (px < ori.rows - 1 && py < ori.cols - 1) {
				Vec3b p11 = ori.at<Vec3b>(px, py);
				Vec3b p12 = ori.at<Vec3b>(px, py + 1);
				Vec3b p21 = ori.at<Vec3b>(px + 1, py);
				Vec3b p22 = ori.at<Vec3b>(px + 1, py + 1);
				res.at<Vec3b>(i, j)[0] = (int)((double)p11[0] * (px2 - orix) * (py2 - oriy) + p21[0] * (orix - px) * (py2 - oriy) + p12[0] * (px2 - orix) * (oriy - py) + p22[0] * (orix - px) * (oriy - py));
				res.at<Vec3b>(i, j)[1] = (int)((double)p11[1] * (px2 - orix) * (py2 - oriy) + p21[1] * (orix - px) * (py2 - oriy) + p12[1] * (px2 - orix) * (oriy - py) + p22[1] * (orix - px) * (oriy - py));
				res.at<Vec3b>(i, j)[2] = (int)((double)p11[2] * (px2 - orix) * (py2 - oriy) + p21[2] * (orix - px) * (py2 - oriy) + p12[2] * (px2 - orix) * (oriy - py) + p22[2] * (orix - px) * (oriy - py));
			}
			else {
				res.at<Vec3b>(i, j) = ori.at<Vec3b>(px, py);
			}
		}
	}
	return res;
}