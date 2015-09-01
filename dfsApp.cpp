#include "Graph.cpp"
//连通分量检测 节点a和节点b是否连通
#pragma once;
class CC{
	bool * marked;
	int * connected;//数组，连通的节点其值都是一样的
	int flag; 

	void dfs(Graph&g,int n){
		connected[n] = flag;
		marked[n] = true;
		for (std::list<AdjList>::iterator i = g.getAdj(n)->begin(); i != g.getAdj(n)->end(); i++){
			if (!marked[i->value])
				dfs(g, i->value);//递归，直到所有相连的节点被标记。
		}
	}
public:
	CC(Graph&g){
		marked = new bool[g.getV()];
		memset(marked, 0, g.getV()*sizeof(bool));
		connected = new int[g.getV()];
		flag = 0;
		for (int node = 0; node < g.getV(); node++){
			if (!marked[node]){
				dfs(g, node);
				flag++;
			}
		}

	}


	bool isConnected(int v, int w){
		return connected[v] == connected[w];
	}
};


int main(){
	
	std::ifstream in("c:\\t\\g.txt");
	Graph p(in);
	CC c(p);
	std::cout<<c.isConnected(1, 9);
}