#include "Graph.cpp"
using namespace std;
//连通分量查询
class CC{
	bool * marked;
	int * connected;//数组，只一样事表示这两个索引对应的节点是连通的
	int flag; 

	void dfs(Graph&g,int n){
		connected[n] = flag;
		marked[n] = true;
		for (std::list<AdjList>::iterator i = g.getAdj(n)->begin(); i != g.getAdj(n)->end(); i++){
			if (!marked[i->value])
				dfs(g, i->value);
		}
	}
public:
	CC(Graph&g){
		marked = new bool[g.getV()];
		memset(marked, 0, g.getV()*sizeof(bool));
		connected = new int[g.getV()];
		flag = 0;
		for (int node = 0; node < g.getV(), node++){
			if (!marked[node]){
				dfs(g, node);
				flag++;
			}
		}

		for (int i = 0, i <g.getV(); i++){
			cout << i << " " << connected[i] << endl;
		}
	}


	bool isConnected(int v, int w){
		return connected[v] == connected[w];
	}
};


int main(){

}