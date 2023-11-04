#pragma once
#include<vector>
#include<string>
#include "MySTL.h"
 
#define MAXVSIZE 30  //最大点集大小
typedef string Vertex;

int to_int(string num) {   //string to int
	int l =(int) num.size();
	int i;
	int number = 0;
	for (i = 0; i < l; ++i) {
		number *= 10;
		number += num[i] - '0';
	}
	return number;
}

int stringsize(string str) {   //输出string类型尺寸，std::string::size()在字符串中有中文时会+2
	int count = 0;
	for (int i = 0; str[i]; ++i) {
		if (str[i] < 0) i++;
		count++;
	}
	return count;
}

typedef struct TreeEdge {
	Vertex nextvex;
	struct TreeEdge* nextedge;
	int power;
}TreeEdge;

typedef struct TreeVertex
{
	Vertex vex;
	TreeEdge* FirstEdge;
}TreeVertexes[MAXVSIZE];

typedef struct
{
	bool powered;
	TreeVertexes vertexes;
	int size_of_vex;
	int size_of_arc;
}AdjList;

int Index(const AdjList& G, Vertex vex)
{
	for (int i = 0; i < G.size_of_vex; i++)
	{
		if (G.vertexes[i].vex == vex)
		{
			return i;
		}
	}
	return -1;
}

void Create(AdjList& G, vector<string>vertex, vector<string> edge, bool powered) {
	int i;
	G.powered = powered;
	G.size_of_vex = (int)vertex.size();
	if (powered) {
		G.size_of_arc = edge.size() / 3;
		for (i = 0; i < vertex.size(); ++i) {
			G.vertexes[i].vex = vertex[i];
			G.vertexes[i].FirstEdge = nullptr;
		}
		for (i = 0; i < edge.size(); ++i) {
			if (i % 3 == 0) {
				int ind = Index(G, edge[i]);
				TreeEdge* arc = new TreeEdge;
				arc->nextvex = edge[i + 1];
				arc->nextedge = nullptr;
				arc->power = to_int(edge[i + 2]);
				TreeEdge* p = G.vertexes[ind].FirstEdge;
				if (p == nullptr) {
					G.vertexes[ind].FirstEdge = arc;
				}
				else {
					while (p->nextedge != nullptr) {
						p = p->nextedge;
					}
					p->nextedge = arc;
				}
				i += 2;
			}
		}
	}
	else {
		G.size_of_arc = (int)edge.size() / 2;
		for (i = 0; i < vertex.size(); ++i) {
			G.vertexes[i].vex = vertex[i];
			G.vertexes[i].FirstEdge = nullptr;
		}
		for (i = 0; i < edge.size(); ++i) {
			if (i % 2 == 0) {
				int ind = Index(G, edge[i]);
				TreeEdge* arc = new TreeEdge;
				arc->nextvex = edge[i + 1];
				arc->nextedge = nullptr;
				TreeEdge* p = G.vertexes[i].FirstEdge;
				if (p == nullptr) {
					G.vertexes[ind].FirstEdge = arc;
				}
				else {
					while (p->nextedge != nullptr) {
						p = p->nextedge;
					}
					p->nextedge = arc;
				}
				i += 1;
			}
		}
	}
}















void print(AdjList& G, Vertex V, int depth, int power, int S, int N, int pre) {  //S是上一个顶点造成的偏移 //N是累积偏移
	int ind = Index(G, V);
	TreeEdge* p = G.vertexes[ind].FirstEdge;
	int count = 0;
	if (depth > 0) {
		//cout << '|';
		if (depth > 1 && G.powered) {
			for (int i = 0; i < N; ++i) {//边权数字造成的偏移
				count++;
				//if (flag && count == pre) cout << '|';
				cout << ' ';
			}
		}
		for (int i = 0; i < depth - 1; ++i) {
			count += 5;
			cout << "     ";
		}
		for (int i = 0; i < S / 2; ++i) {
			count++;
			//if (flag && count == pre) cout << ' ';
			cout << ' ';
		}
		cout << '|' << endl;
	}
	int this_b = N + (5 * (depth - 1) > 0 ? (depth - 1) : 0) + S / 2;
	for (int i = 0; i < depth - 1; ++i) cout << "     ";
	if (depth > 0) {
		if (depth > 1 && G.powered) {
			for (int i = 0; i < N; ++i)
				cout << ' ';
		}
		for (int i = 0; i < S / 2; ++i) cout << ' ';
		if (G.powered) cout << "`--" << power << "--";
		else cout << "`----";
	}
	cout << G.vertexes[ind].vex << endl;
	while (p != nullptr) {
		bool flag = true;
		if (p->nextedge == nullptr) flag = false;
		print(G, p->nextvex, depth + 1, p->power, stringsize(V), stringsize(V) / 2 + N + (int)to_string(power).size(), this_b);
		p = p->nextedge;
	}
}

