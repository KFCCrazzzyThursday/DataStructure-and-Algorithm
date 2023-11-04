#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"hash.h"

using namespace std;
vector<vector<string>> readfile(string filename);//读取文件 将姓名和拼音分别存入 vector<vector<string>[i][0]和[i][1]中

vector<vector<string>> test_name(vector<vector<string>> First_name, vector<vector<string>> Last_name);  //随机组合 生成姓名

vector<vector<string>> test_name(string First_name = "First_name.txt", string Last_name = "Last_name.txt"); //调用上面两个函数，读取文件，返回随机姓名和对应拼音
                                                                                                            //分别存在vector<vector<string>>[i][0]和[i][1]中
                                                                                                            //并写入到test_name.txt中

void hashtest(vector<vector<string>>& name); //测试函数                                                     