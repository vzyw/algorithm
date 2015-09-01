#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
#pragma once;
//邻接表链表节点
struct AdjList
{
	AdjList(int v){
		value = v;
	}
	int value;
};

class Graph{
private:
	int v;//顶点数目
	int e;//边数
	std::list<AdjList> * adj;
public:
	//初始化graph
	Graph(int v){
		this->v = v;
		e = 0;
		adj = new std::list<AdjList>[v];
	}
	//读入文本文件后 初始化
	Graph(std::ifstream &in){
		if (!in){
			std::cout << "can't open file";
			exit(-1);
		}
		int n; in >> n;
		new (this) Graph(n);//调用构造函数，覆盖this指向的内存
		in >> n;
		for (int i = 0; i < n; i++){
			int v, w;
			in >> v;in >> w;
			addEdge(v, w);
		}
	}

	int getV(){ return v; }
	int getE(){ return e; }

	void addEdge(int v, int w){
		adj[v].push_back(w);
		adj[w].push_back(v);
		e++;
	}

	std::list<AdjList> * getAdj(int n){
		return &adj[n];
	}

};
//深度优先搜索
class DepthFirstSearch{
private:
	bool* marked;//一个指向大小为graph.v 数组的指针。
	int count;
public:
	//初始化，传入一个g和起始点
	DepthFirstSearch(Graph &g, int start){
		marked = new bool[g.getV()];
		memset(marked, 0, g.getV()*sizeof(bool));
		count = 0;
		dfs(g, start);
	}
	//传入一个G和节点值
	void dfs(Graph&g, int node){
		marked[node] = true;
		count++;
		//遍历领接表，没有被标记的节点继续递归
		for (std::list<AdjList>::iterator i = g.getAdj(node)->begin(); i != g.getAdj(node)->end(); i++){
			if (!marked[i->value])dfs(g, i->value);
		}
	}
	bool isMarked(int w){
		return marked[w];
	}
	int getCount(){
		return count;
	}
};
//深度优先搜索路径
class DepthFirstPaths{
private:
	bool* marked;//一个指向大小为graph.v 数组的指针。
	int *edgeTo;//数组索引n表示节点n，值表示与该节点连接的节点
	int s;

	void dfs(Graph&g, int node){
		marked[node] = true;
		//此处存疑  这样是否能访问到整个链表有待验证
		for (std::list<AdjList>::iterator i = g.getAdj(node)->begin(); i != g.getAdj(node)->end(); i++){
			if (!marked[i->value]){
				edgeTo[i->value] = node;
				dfs(g, i->value);
			}
		}
	}
public:
	DepthFirstPaths(Graph &g, int start){
		marked = new bool[g.getV()];
		memset(marked, 0, g.getV() - 1);
		edgeTo = new int[g.getV()];
		memset(edgeTo, 0, g.getV() - 1);
		s = start;
		dfs(g, start);
	}
	//传入一个G和节点值
	
	bool hasPathTo(int w){
		return marked[w];
	}

	//返回路径链表
	std::stack<int>* pathTo(int v){
		if (!hasPathTo(v))return NULL;
		std::stack<int> * p = new std::stack<int>;
		for (int x = v; x != s; x = edgeTo[x]){
			p->push(x);
		}
		p->push(s);
		return p;//p pop出来的就是路径顺序
	}
	
};
//广度优先搜索
class BreadthFirstPaths{
private:
	bool *marked;//标记
	int *edgeTo;//连接到的边
	int s;//起点

	void bfs(Graph&g, int start){
		std::queue<int> que;
		marked[start] = true;
		que.push(start);
		while (!que.empty())
		{
			int v = que.front(); 
			que.pop();	//获取队列最前面的一个元素后删去
			//std::cout << v<<std::endl;
			for (std::list<AdjList>::iterator i = g.getAdj(v)->begin(); i != g.getAdj(v)->end(); i++){
				//std::cout << i->value<<std::endl;
				if (!marked[i->value]){
					edgeTo[i->value] = v;//标记所有相邻的点的来路
					marked[i->value] = true;//标记所有相邻点的
					que.push(i->value);//把该点推入队列
				}
			}
		}
	}
	
public:
	BreadthFirstPaths(Graph&g, int start){
		s = start;
		marked = new bool[g.getV()];
		edgeTo = new int[g.getV()];
		memset(marked, 0, g.getV()*sizeof(bool));
		bfs(g, s);
	}
	bool hasPathTo(int v){
		return marked[v];
	}

	//返回路径链表
	std::stack<int>* pathTo(int v){
		if (!hasPathTo(v))return NULL;
		std::stack<int> * p = new std::stack<int>;
		for (int x = v; x != s; x = edgeTo[x]){
			p->push(x);
		}
		p->push(s);
		return p;//p pop出来的就是路径顺序
	}


};

//int main(){
//	std::ifstream in("c:\\t\\g2.txt");
//	Graph p(in);
//	BreadthFirstPaths s(p, 0);
//	std::stack<int> *ptr = s.pathTo(3);
//	while (ptr&&!ptr->empty())
//	{
//		int q = ptr->top();
//		std::cout << q << " ";
//		ptr->pop();
//
//	}
//	//std::list<AdjList>*q = p.getAdj(3);
//	/*for (std::list<AdjList>::iterator i = p.getAdj(3)->begin(); i != p.getAdj(3)->end(); i++){
//		std::cout << i->value << " ";
//	}*/
//}