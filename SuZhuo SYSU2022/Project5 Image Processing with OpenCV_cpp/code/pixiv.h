#pragma once
#include<opencv2\opencv.hpp>
#include<opencv2/core/utils/logger.hpp>
#include<iostream>
#include<fstream>
#include<vector>
using namespace cv;
using namespace std;

void create(void);

struct pixiv {
	int x;
	int y;
	int* RGB;

	pixiv() :x(0), y(0), RGB(new int[3]()) {};
	pixiv(int x_, int y_, Vec3b rgb) :x(x_), y(y_) {
		RGB = new int[3];
		RGB[0] = rgb[0];
		RGB[1] = rgb[1];
		RGB[2] = rgb[2];
	}
	pixiv(const pixiv& p) {
		x = p.x;
		y = p.y; 
		RGB = new int[3];
		RGB[0] = p.RGB[0];
		RGB[1] = p.RGB[1];
		RGB[2] = p.RGB[2];
	}
	pixiv(const pixiv&& p) noexcept {
		x = p.x;
		y = p.y;
		RGB = new int[3];
		RGB[0] = p.RGB[0];
		RGB[1] = p.RGB[1];
		RGB[2] = p.RGB[2];
	}
};

struct compress {
	int* RGB;
	int count;
	compress() :RGB(new int[3]), count(1) {};
	compress(Vec3b rgb, int count_ = 1) :count(count_) {
		RGB = new int[3];
		RGB[0] = rgb[0];
		RGB[1] = rgb[1];
		RGB[2] = rgb[2];
	}
	compress(int* rgb, int count_ = 1) :count(count_) {
		RGB = new int[3];
		RGB[0] = rgb[0];
		RGB[1] = rgb[1];
		RGB[2] = rgb[2];
	}
};

