#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"hash.h"

using namespace std;
vector<vector<string>> readfile(string filename);//��ȡ�ļ� ��������ƴ���ֱ���� vector<vector<string>[i][0]��[i][1]��

vector<vector<string>> test_name(vector<vector<string>> First_name, vector<vector<string>> Last_name);  //������ ��������

vector<vector<string>> test_name(string First_name = "First_name.txt", string Last_name = "Last_name.txt"); //��������������������ȡ�ļ���������������Ͷ�Ӧƴ��
                                                                                                            //�ֱ����vector<vector<string>>[i][0]��[i][1]��
                                                                                                            //��д�뵽test_name.txt��

void hashtest(vector<vector<string>>& name); //���Ժ���                                                     