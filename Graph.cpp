#include <iostream>
#include <fstream>
#include <list>
#include <stack>
#include <queue>
#pragma once;
//�ڽӱ�����ڵ�
struct AdjList
{
	AdjList(int v){
		value = v;
	}
	int value;
};

class Graph{
private:
	int v;//������Ŀ
	int e;//����
	std::list<AdjList> * adj;
public:
	//��ʼ��graph
	Graph(int v){
		this->v = v;
		e = 0;
		adj = new std::list<AdjList>[v];
	}
	//�����ı��ļ��� ��ʼ��
	Graph(std::ifstream &in){
		if (!in){
			std::cout << "can't open file";
			exit(-1);
		}
		int n; in >> n;
		new (this) Graph(n);//���ù��캯��������thisָ����ڴ�
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
//�����������
class DepthFirstSearch{
private:
	bool* marked;//һ��ָ���СΪgraph.v �����ָ�롣
	int count;
public:
	//��ʼ��������һ��g����ʼ��
	DepthFirstSearch(Graph &g, int start){
		marked = new bool[g.getV()];
		memset(marked, 0, g.getV()*sizeof(bool));
		count = 0;
		dfs(g, start);
	}
	//����һ��G�ͽڵ�ֵ
	void dfs(Graph&g, int node){
		marked[node] = true;
		count++;
		//������ӱ�û�б���ǵĽڵ�����ݹ�
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
//�����������·��
class DepthFirstPaths{
private:
	bool* marked;//һ��ָ���СΪgraph.v �����ָ�롣
	int *edgeTo;//��������n��ʾ�ڵ�n��ֵ��ʾ��ýڵ����ӵĽڵ�
	int s;

	void dfs(Graph&g, int node){
		marked[node] = true;
		//�˴�����  �����Ƿ��ܷ��ʵ����������д���֤
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
	//����һ��G�ͽڵ�ֵ
	
	bool hasPathTo(int w){
		return marked[w];
	}

	//����·������
	std::stack<int>* pathTo(int v){
		if (!hasPathTo(v))return NULL;
		std::stack<int> * p = new std::stack<int>;
		for (int x = v; x != s; x = edgeTo[x]){
			p->push(x);
		}
		p->push(s);
		return p;//p pop�����ľ���·��˳��
	}
	
};
//�����������
class BreadthFirstPaths{
private:
	bool *marked;//���
	int *edgeTo;//���ӵ��ı�
	int s;//���

	void bfs(Graph&g, int start){
		std::queue<int> que;
		marked[start] = true;
		que.push(start);
		while (!que.empty())
		{
			int v = que.front(); 
			que.pop();	//��ȡ������ǰ���һ��Ԫ�غ�ɾȥ
			//std::cout << v<<std::endl;
			for (std::list<AdjList>::iterator i = g.getAdj(v)->begin(); i != g.getAdj(v)->end(); i++){
				//std::cout << i->value<<std::endl;
				if (!marked[i->value]){
					edgeTo[i->value] = v;//����������ڵĵ����·
					marked[i->value] = true;//����������ڵ��
					que.push(i->value);//�Ѹõ��������
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

	//����·������
	std::stack<int>* pathTo(int v){
		if (!hasPathTo(v))return NULL;
		std::stack<int> * p = new std::stack<int>;
		for (int x = v; x != s; x = edgeTo[x]){
			p->push(x);
		}
		p->push(s);
		return p;//p pop�����ľ���·��˳��
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