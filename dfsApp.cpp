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

//检测是否是无环图
class Cycle{
private:
	bool *marked;
	bool cycle;
	//v表示起点，n表示终点，
	void dfs(Graph&g, int v, int n){
		marked[v] = true;
		for (std::list<AdjList>::iterator i = g.getAdj(v)->begin(); i != g.getAdj(v)->end(); i++){
			//递归，把与起点的相邻的下一个点作为起点，起点作为终点。 如果找到了与当前起点相邻的下一个点被标记过了，说明之前经过这点，一定能构成环。
			if (!marked[i->value])
				dfs(g, i->value,v); 
			else if (i->value != n) cycle = true;
		}

	}
public:
	Cycle(Graph&g){
		cycle = false;
		marked = new bool[g.getV()];
		for (int n = 0; n < g.getV(); n++){
			if (!marked[n]){
				dfs(g, n, n);
			}
		}
	}
	bool hasCycle(){
		return cycle;
	}
};

//检测是否是二分图，用染色法，即从其中一个顶点开始，将跟它邻接的点染成与其不同的颜色，如果邻接的点有相同颜色的，则说明不是二分图，每次用bfs遍历即可。
class bipartiteGraph{
private:
	bool *marked;
	bool *color;//true 和false 示不同的两种颜色；
	bool isBip;
	void dfs(Graph&g, int node){
		marked[node] = true;
		for (std::list<AdjList>::iterator i = g.getAdj(node)->begin(); i != g.getAdj(node)->end(); i++){
			if (!marked[i->value]){
				color[i->value] = !color[node];
				dfs(g, i->value);
			}
			else if (color[i->value] == color[node])isBip= false;  //已经判断过的点和当前点颜色一样说明不是二分图

		}
		
	}
public:
	bipartiteGraph(Graph&g){
		isBip= true;
		color = new bool[g.getV()];
		marked = new bool[g.getV()];
		memset(marked, 0, g.getV()*sizeof(bool));
		memset(color, 0, g.getV()*sizeof(bool));
		dfs(g, 0);
	}
	bool isBipartite(){
		return isBip;
	}

};
//int main(){
//	
//	std::ifstream in("c:\\t\\g.txt");
//	Graph p(in);
//	CC c(p);
//	std::cout<<c.isConnected(1, 9);
//}