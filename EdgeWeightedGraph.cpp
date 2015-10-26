// 加权无向图
#include<iostream>
#include <list>
#include <fstream>
#include <queue>
#include <functional>
class Edge{
	//该重载用于建立优先队列
	friend bool operator>(Edge a, Edge b){
		return a.weight > b.weight;
	}
public:
	Edge(){}
	Edge(int v, int w, double weight){
		this->v = v;
		this->w = w;
		this->weight = weight;
	}
	double getWeight(){ return weight; }
	int either(){ return v; };
	int other(int vertex){ 
		if (vertex == v)return w;
		else if (vertex == w)return v;
		//else  throw
	}
	int compareTo(Edge &that){
		if (this->weight < that.weight)return -1;
		if (this->weight > that.weight)return 1;
		else return 0;
	}
	
private:
	int v;
	int w;
	double weight;
};



class EdgeWeightedGraph{
private:
	int v;
	int e;
	std::list<Edge>*adj;
public:
	EdgeWeightedGraph(int v){
		this->v = v;
		this->e = 0;
		adj = new std::list<Edge>[v];
	}

	EdgeWeightedGraph(std::ifstream &in){
		if (!in){
			std::cout << "can't open file";
			exit(-1);
		}
		int n; in >> n;
		new (this) EdgeWeightedGraph(n);
		in >> n;
		for (int i = 0; i < n; i++){
			int v, w;
			double weight;
			in >> v >> w >> weight;
			addEdge(Edge(v, w, weight));
		}
	}
	//添加边
	void addEdge(Edge ed){
		int v = ed.either(), w = ed.other(v);
		adj[v].push_front(ed);
		adj[w].push_front(ed);
		e++;
	}

	int getV(){
		return v;
	}
	int getE(){
		return e;
	}
	//返会和i节点相连的边
	std::list<Edge>* getAdj(int i){
		return &adj[i];
	}
	//返回所有边集合
	std::list<Edge> *getEdges(){
		std::list<Edge> * p = new std::list<Edge>;
		for (int i = 0; i < v; i++){
			for (auto it:adj[i]){
				if (it.other(i)>i)p->push_back(it);
			}
		}
		return p;
	}
	
};

//延时Prim算法实现minimum spanning tree
class LazyPrimeMST{
private:
	bool *marked;
	std::queue<Edge> *mst;//最小生产树；
	std::priority_queue<Edge,std::vector<Edge>,std::greater<Edge>>*pq;//小顶优先队列
	void visit(EdgeWeightedGraph &g, int v){
		marked[v] = true; //标记v点;
		for (auto i = g.getAdj(v)->begin(); i != g.getAdj(v)->end();i++){
			if (!marked[i->other(v)]) pq->push(*i); //把和v点相连的边加入到pq优先队列中；
		}
	}
public:
	LazyPrimeMST(EdgeWeightedGraph &g){
		pq = new std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>>;
		marked = new bool[g.getV()];
		memset(marked, 0, sizeof(bool)*g.getV());
		mst = new std::queue<Edge>;

		//访问第一个节点 0，把和0点相连的边加入到pq优先队列中，这时候队列的顶部是距离0点最近的；
		visit(g, 0);
		while (!pq->empty()){

			//每次栈顶的元素会变，最小的那条边，并不是沿着一个点一个点走下去，而是一个区域一个区域的走，具体见图
			Edge e = pq->top();
			pq->pop();
			int v = e.either(), w = e.other(v);
			if (marked[v]&&marked[w])continue;
			mst->push(e);

			if (!marked[v])visit(g, v);
			if (!marked[w])visit(g, w);
		}
	}
	std::queue<Edge>*getMST(){
		return mst;
	}
	double getLength(){
		double sum = 0;
		std::queue<Edge> p(*mst);
		while (!p.empty()){
			Edge e = p.front();
			sum += e.getWeight();
			p.pop();
		}
		return sum;
	}
};

//即时遍历 Prim
//class PrimeMST{
//private:
//	Edge *edgeTo;			//距离树最近的边
//	double *distTo;			//distTo[w] = edgeTo[w].weight
//	bool *marked;		//											
//	std::priority_queue<double, std::vector<double>, std::greater<double>>*pq;
//public:
//	PrimeMST(EdgeWeightedGraph &g){
//		edgeTo = new Edge[g.getV()];
//		distTo = new double[g.getV()];
//		marked = new bool[g.getV()];
//		memset(marked, 0, sizeof(bool)*g.getV());
//		memset(distTo, 0, sizeof(double)*g.getV());
//		pq = new std::priority_queue<double, std::vector<double>, std::greater<double>>;
//
//		distTo[0] = 0.0;
//		pq->push()
//	}
//};


//int main(){
//	std::ifstream in("c:\\t\\tinyEWG.txt");
//	EdgeWeightedGraph te(in);
//	LazyPrimeMST a(te);
//	std::queue<Edge> * p = a.getMST();
//	while (!p->empty()){
//		Edge a = p->front();
//		std::cout << a.either() << " " << a.other(a.either()) << "\n";
//		p->pop();
//	}
//


	//std::list<Edge>* p = te.getEdges();
	//for (auto i : *p){
	//	std::cout << i.either() << " " << i.other(i.either()) << " " << i.getWeight() << "\n";
	//}
	//std :: cout << "\n";
	//stl中的优先队列，具体见笔记
	//std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> edge_queue;
	//for (auto i : *p){
	//	edge_queue.push(i);
	//}
	//while (!edge_queue.empty()){
	//	Edge t = edge_queue.top();
	//	std::cout << t.either() << " " << t.other(t.either()) << " " << t.getWeight() << "\n";
	//	edge_queue.pop();
	//}
	
	
//}  