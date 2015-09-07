#include <iostream>
#include <list>
#include <fstream>
struct AdjList
{
	AdjList(int v){
		value = v;
	}
	int value;
};
class DirectedGraph{
private:
	int v;
	int e;
	std::list<AdjList> * adj;

	void addEdge(int v, int w){
		adj[v].push_front(w);
		e++;
	}
public:
	DirectedGraph(int v){
		this->v = v;
		e = 0;
		adj = new std::list<AdjList>[v];
	}
	DirectedGraph(std::ifstream &in){
		if (!in){
			std::cout << "can't open file";
			exit(-1);
		}
		int n; in >> n;
		new (this) DirectedGraph(n);
		in >> n;
		for (int i = 0; i < n; i++){
			int v, w;
			in >> v>> w;
			addEdge(v, w);
		}

		
	}
	std::list<AdjList>*getAdj(int n){
		return &adj[n];
	}
	int getV(){
		return v;
	}
	int getE(){
		return e;
	}

	DirectedGraph*reverse(){
		DirectedGraph *p = new DirectedGraph(v);
		for (int i = 0; i < v; i++){
			for (std::list<AdjList>::iterator t = getAdj(i)->begin();
				t != getAdj(i)->end(); t++){
				p->addEdge(t->value, i);
			}
		}
		return p;
	}

	void d(){
		for (int i = 0; i < this->v; i++){
			std::cout << i << "  ";
			for (std::list<AdjList>::iterator t = adj[i].begin();
				t != adj[i].end(); t++)
				std::cout << t->value << " ";
			std::cout << "\n";
		}
	}
};
//
//int main(){
//	std::ifstream in("c:\\t\\directed.txt");
//	DirectedGraph di(in);
//	DirectedGraph *q = di.reverse();
//	di.d();
//	std::cout << "\n";
//	q->d();
//
//}