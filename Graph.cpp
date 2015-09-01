#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
//邻接表链表
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
	Graph(std::ifstream in){
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
		memset(marked, 0, g.getV()-1);
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


	std::stack<AdjList>* pathTo(int v){
		if (!hasPathTo(v))return NULL;
		std::stack<AdjList> * p = new std::stack<AdjList>;
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

	void bfs(Graph&g, int node){
		std::queue<int> que;
		marked[node] = true;
		que.push(node);
		while (!que.empty())
		{
			int v = que.front();
			que.push();
			//std::list<AdjList> *p = g.getAdj(node);
			//此处存疑  这样是否能访问到整个链表有待验证
			for (std::list<AdjList>::iterator i = g.getAdj(node)->begin(); i != g.getAdj(node)->end(); i++){
				if (!marked[*i])
			}
		}
	}
public:
	BreadthFirstPaths(Graph&g, int start){
		s = start;
		marked = new bool[g.getV()];
		edgeTo = new int[g.getV()];
		memset(marked, 0, g.getV() - 1);
		//memset(marked, 0, g.getV() - 1);
		bfs(g, s);
	}



};

int main(){
	Graph p(std::ifstream("c:\\t\\g.txt"));
	std::list<AdjList>*q = p.getAdj(3);
	
}