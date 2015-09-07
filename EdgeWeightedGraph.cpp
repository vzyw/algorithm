// 加权无向图
#include<iostream>
#include <list>
#include <fstream>
class Edge{
public:
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

	bool operator>(const Edge &that){
		return this->weight > that.weight;
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

//延时Prim算法实现
class LazyPrimeMST{

};
int main(){
	std::ifstream in("c:\\t\\tinyEWG.txt");
	EdgeWeightedGraph te(in);
	std::list<Edge>* p = te.getEdges();
	/*for (auto i:*p){
		std::cout << i.either() << " " << i.other(i.either()) <<" "<<i.getWeight()<< "\n";
	}*/
}