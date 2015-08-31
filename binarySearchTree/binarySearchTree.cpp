#include<iostream>
using namespace std;

class Node
{
public:
	Node(){
	}
	Node(char k,int v, Node *l, Node *r, int n){
		key = k;
		value = v;
		left = l;
		right = r;
		num = n;
	}
	Node(const Node&n){
		key = n.key;
		value = n.value;
		left = n.left;
		right = n.right;
		num = n.num;
	}
	char key;
	int value;
	Node * left, *right;
	int num;
};

class BST{
private:
	Node *root;
	int get(Node *x, char k){
		if (!x) return -1;

		if (k> x->key) return get(x->right,k);
		else if (k < x->key)return get(x->left,k);
		else return x->value;
	}
	Node* put(Node *x,char k, int v){
		if (!x) return new Node(k, v, NULL, NULL, 1);
		if (k>x->key)			x->right = put(x->right, k, v);
		else if (k < x->key)	x->left = put(x->left, k, v);
		else					x->value = v;
		x->num = size(x->left) + size(x->right)+1;
		return x;
	}
	int size(Node *x){
		if (!x) return 0;
		return x->num;
	}
	 Node * min(Node *x){
		if (!x->left)return x;
		return min(x->left);
	}
	 Node* max(Node*x){
		if (!x->right)return x;
		else return max(x->right);
	}
	const Node * select(Node *x, int k){
		if (!x) return NULL;
		int t = size(x->left);
		if (t > k) return select(x->left, k);
		else if (t < k) return select(x->right, k - t - 1);//t<k时 说明当前节点的左边的t个节点加上当前节点这个都是小于要查找的节点，接下来就往右边去，找到右边某个节点，这个节点有（k-t-1)个节点小于他。
		else return x;
	}
	int rank(Node *x, char k){
		if (!x)return 0;
		if		(k < x->key)return rank(x->left, k);
		else if (k > x->key)return 1 + size(x->left) + rank(x->right, k);//当前节点1 加上当前节点的左边所有节点，向右走
		else	return size(x->left);
	}
	Node *delMin(Node*x){
		if (!x->left){
			Node * p = x->right;
			delete x;
			return p;
		}
		x->left = delMin(x->left);
		x->num = size(x->left) + size(x->right) + 1;
		return x;
	}
	Node *delMax(Node*x){
		if (!x->right) {
			Node * p = x->left;
			delete x;
			return p;
		}
		x->right = delMin(x->right);
		x->num = size(x->left) + size(x->right) + 1;
		return x;
	}

	Node *del(Node*x, char k){
		if (!x)return NULL;
		if		(k < x->key) x->left = del(x->left, k);
		else if (k>x->key) x->right = del(x->right, k);
		else{
			if (x->right == NULL) return x->left;
			if (x->left == NULL) return x->right;
			Node *t = x;
			x = new Node(*min(t->right));
			x->right = delMin(t->right);
			x->left = t->left;
			delete t;
		}
		x->num = size(x->left) + size(x->right) + 1;
		return x;
	}
public:
	BST(){}
	BST(char k, int v, Node *l, Node*r, int n){
		root = new Node(k, v, l, r, n);
	}
	int size(){
		return size(root);
	}
	void put(char k,int v){
		put(root,k, v);
	}
	int get(char k){
		return get(root, k);
	}
	const Node* max(){
		return max(root);
	}
	const Node* min(){
		return min(root);
	}

	//查找 查找排名为k的节点（树中有k个小于他的节点）
	const Node * select(int k){
		return select(root, k);
	}
	//返回给定键的排名
	int rank(char k){
		return rank(root,k);
	}
	
	void delMin(){
		root = delMin(root);
	}
	void delMax(){
		root = delMax(root);
	}
	void del(char k){
		del(root, k);
	}
};
int main(){
	BST a('t', 10, NULL, NULL, 1);
	a.put('b', 10);
	a.put('a', 1);
	a.put('u', 3);
	a.put('o', 3);
	a.put('c', 3);
	a.put('s', 3);
	a.put('x', 3);
	
	a.del('b');

}