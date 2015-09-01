#include "Graph.cpp"
using namespace std;
//��ͨ������ѯ
class CC{
	bool * marked;
	int * connected;//���飬ֻһ���±�ʾ������������Ӧ�Ľڵ�����ͨ��
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