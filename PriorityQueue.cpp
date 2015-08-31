#include<iostream>
const int max = 20;
class MaxPQ{
private:
	int arr[max];
	int N = 0;
	bool less(int i, int j){
		return arr[i] < arr[j];
	}
	void exch(int i, int j){
		int t = arr[i];
		arr[i] = arr[j];
		arr[j] = t;
	}
	void swim(int n){
		while (n>1 && less(n/2, n)){
			exch(n / 2, n);//大于父节点则交换
			n /= 2;
		}
	}
	void sink(int n){
		while (2 * n <= N){
			int j = 2 * n;
			if (j < N&&!less(j, j+1))j++;//选取两个子节点中较的的一个，换到上面成为父节点之后才能比下面两个子节点都大
			if (!less(n, j))break;
			exch(n, j);
			n = j;
		}
	}
public:
	void insert(int n){
		arr[++N] = n;
		swim(N);
	}
	int delMax(){
		int max = arr[1];
		exch(1, N--);
		sink(1);
		return max;
	}
	void d(){
		for (int i = 1; i <= N; i++){
			std::cout << arr[i] << " ";
		}
		std::cout << "\n";
	}
};


int main(){
	MaxPQ p;
	p.insert(10);
	p.insert(3);
	p.insert(11);
	p.insert(6);
	p.insert(8);
	p.insert(12);
	p.insert(9);
	p.d();
	p.delMax();
	p.d();
}