#pragma once
#include"Tree.h"
#include "MySTL.h"

typedef struct EdgeNode
{
	//bool visited;
	int ivex;
	int jvex;
	struct EdgeNode* ilink;
	struct EdgeNode* jlink;
	int power;
}EdgeNode;    //边结点

typedef struct VertexNode
{
	Vertex vex;
	EdgeNode* FirstEdge;
}Vex[MAXVSIZE];  //顶点结点数组

typedef struct
{
	Vex vertexes;
	bool powered;
	int size_of_vex;
	int size_of_arc;
}MultiAdjList;   //多重邻接表

int Index(const MultiAdjList& G, Vertex vex)
{
	for (int i = 0; i < G.size_of_vex; i++)
	{
		if (G.vertexes[i].vex == vex)
		{
			return i;
		}
	}
	return -1;
};


bool Create(MultiAdjList& G)
{
	cout << "请输入顶点集和边集大小" << endl;
	cin >> G.size_of_vex >> G.size_of_arc;
	if (G.size_of_vex == 0) return false;
	for (int i = 0; i < G.size_of_vex; i++)
	{
		cout << "请输入第" << i + 1 << "个结点名" << endl;
		cin >> G.vertexes[i].vex;
		G.vertexes[i].FirstEdge = NULL;
	}
	cout << "选择输入边的端点编号（从0开始计数）键入0，选择输入端点名键入1" << endl;
	int control = 0;
	cin >> control;
	cout << "是否为带权图Y/N" << endl;
	char p;
	cin >> p;
	if (p == 'Y') G.powered = true;
	else G.powered = false;
	for (int k = 0; k < G.size_of_arc; k++)
	{
		if (control == 1)	cout << "请输入第" << k + 1 << "条边的两个端点名：" << endl;
		else if (control == 0) cout << "请输入第" << k + 1 << "条边的两个端点编号：" << endl;
		Vertex ctemp1;
		Vertex ctemp2;
		int i = 0, j = 0;
		if (control == 1) {
			cin >> ctemp1 >> ctemp2;
			i = Index(G, ctemp1);
			j = Index(G, ctemp2);
		}
		else if (control == 0) {
			cin >> i >> j;
		}
		EdgeNode* arcNode = new EdgeNode;
		if (G.powered) {
			cout << "请输入边权：" << endl;
			cin >> arcNode->power;
		}
		//arcNode->visited = false;
		arcNode->ivex = i;
		arcNode->ilink = G.vertexes[i].FirstEdge;
		G.vertexes[i].FirstEdge = arcNode;

		arcNode->jvex = j;
		arcNode->jlink = G.vertexes[j].FirstEdge;
		G.vertexes[j].FirstEdge = arcNode;
	}
	return true;
}

void DFS(const MultiAdjList& G, Vertex V) {
	cout << "DFS:" << endl;
	Stack<Vertex> s;
	vector<string> Edge;
	int* visit = new int[G.size_of_vex]();
	s.push(V);
	while (!s.isempty()) {
		int i = Index(G, s.top());
		visit[i] = 1;
		cout << "当前遍历顶点：" << s.top() << endl;
		Vertex temp = s.top();
		s.pop();
		EdgeNode* ptemp = G.vertexes[i].FirstEdge;
		while (ptemp!=nullptr) {
			if (ptemp->ivex == i) {
				if (visit[ptemp->jvex] == 0) {
					s.push(G.vertexes[ptemp->jvex].vex);
					Edge.push_back(temp);
					Edge.push_back(G.vertexes[ptemp->jvex].vex);
					if (G.powered) {
						Edge.push_back(to_string((int)ptemp->power));
					}

					visit[ptemp->jvex] = 1;
				}
				ptemp = ptemp->ilink;
			}
			else {
				if (visit[ptemp->ivex] == 0) {
					s.push(G.vertexes[ptemp->ivex].vex);
					Edge.push_back(temp);
					Edge.push_back(G.vertexes[ptemp->ivex].vex);
					if (G.powered) {
						Edge.push_back(to_string((int)ptemp->power));
					}

					visit[ptemp->ivex] = 1;
				}
				ptemp = ptemp->jlink;
			}
		}
	}
	cout << "DFS遍历树的边集：" << endl;
	for (int i = 0; i < Edge.size(); ++i) { 
		if (G.powered) {
			cout << Edge[i]<<"-->"<<Edge[i+1]<<" 边权：" << Edge[i+2] << endl;
			i += 2;
		}
		else {
			cout << Edge[i] << "-->" << Edge[i+1]<< endl;
			i += 1;
		}
	}
	cout << endl;
	vector<string> vert;
	for (int i = 0; i < G.size_of_vex; ++i) {
		vert.push_back(G.vertexes[i].vex);
	}
	AdjList* Tree = new AdjList;
	Create(*Tree, vert, Edge, G.powered);
	print(*Tree, V, 0, 0, 0, 0, 0);
}
//

void BFS(const MultiAdjList& G, Vertex V) {
	cout << "BFS:" << endl;
	Queue<Vertex> q;
	vector<string> Edge;
	int* visit = new int[G.size_of_vex]();
	q.push(V);
	while (!q.isempty()) {
		int i = Index(G, q.front());
		visit[i] = 1;
		cout << "当前遍历顶点：" << q.front() << endl;
		Vertex temp = q.front();
		q.pop();
		EdgeNode* ptemp = G.vertexes[i].FirstEdge;
		while (ptemp) {
			if (ptemp->ivex == i) {
				if (visit[ptemp->jvex] == 0) {
					q.push(G.vertexes[ptemp->jvex].vex);
					Edge.push_back(temp);
					Edge.push_back(G.vertexes[ptemp->jvex].vex);
					if (G.powered) {
						Edge.push_back(to_string((int)ptemp->power));
					}

					visit[ptemp->jvex] = 1;
				}
				ptemp = ptemp->ilink;
			}
			else {
				if (visit[ptemp->ivex] == 0) {
					q.push(G.vertexes[ptemp->ivex].vex);
					Edge.push_back(temp);
					Edge.push_back(G.vertexes[ptemp->ivex].vex);
					if (G.powered) {
						Edge.push_back(to_string((int)ptemp->power));
					}

					visit[ptemp->ivex] = 1;
				}
				ptemp = ptemp->jlink;
			}
		}
	}
	cout << "BFS遍历树的边集：" << endl;
	for (int i = 0; i < Edge.size(); ++i) {
		if (G.powered) {
			cout << Edge[i] << "-->" << Edge[i+1] << " 边权：" << Edge[i+2] << endl;
			i += 2;
		}
		else {
			cout << Edge[i] << "-->" << Edge[i+1]  << endl;
			i += 1;
		}
	}
	cout << endl;
	vector<string> vert;
	for (int i = 0; i < G.size_of_vex; ++i) {
		vert.push_back(G.vertexes[i].vex);
	}
	AdjList* Tree = new AdjList;
	Create(*Tree, vert, Edge, G.powered);
	print(*Tree,V,0,0,0,0,0);
}