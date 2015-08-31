#include<iostream>
using namespace std;
#define RED true;
#define  BLACK false ;

//红黑树总是以红节点进行插入，之后根据树的状态进行左旋转或者右旋转，或者颜色转换

//每个node 都有key和value，num表示包括自己，以自己为根节点的二叉树总节点数，还有一个bool值表示从父节点指过来的是黑色或红色
class Node
{
public:
	Node(){
	}
	Node(char k, int v, Node *l, Node *r, int n,bool c){
		key = k;
		value = v;
		left = l;
		right = r;
		num = n;
		color = c;
	}
	char key;
	int value;
	Node * left, *right;
	int num;
	bool color;
};


class RedBlackBST{
private:
	Node *root;
	bool isRed(Node *p){
		if (!p)return false;
		return p->color == RED;
	}
	int size(Node *x){
		if (!x) return 0;
		return x->num;
	}
	//左旋转
	Node * rotateLeft(Node*p){
		Node*x = p->right;
		p->right = x->left;
		x->left = p;
		x->color = p->color;
		p->color = RED;
		x->num = p->num;
		p->num = 1 + size(p->left) + size(p->right);
		return x;
		
	}
	//右旋转
	Node * rotateRight(Node*p){
		Node*x = p->left;
		p->left = x->right;
		x->right = p;
		x->color = p->color;
		p->color = RED;
		x->num = p->num;
		p->num = 1 + size(p->left) + size(p->right);
		return x;
	}
	//颜色变化，当左右节点都是红树时变成黑色，父节点变成红色
	void flipColors(Node *p){
		p->color = RED;
		p->left->color = BLACK;
		p->right->color = BLACK;
	}
	//插入。插入数据后可能出现连续两个红节点，或者向右拐的红节点，对其进行相应变化。
	Node* put(Node *x, char k, int v){
		if		(!x)			return new Node(k, v, NULL, NULL, 1,1);
		if		(k > x->key)	x->right = put(x->right, k, v);
		else if (k < x->key)	x->left = put(x->left, k, v);
		else					x->value = v;

		if (isRed(x->right) && !isRed(x->left)) rotateLeft(x);
		if (isRed(x->left) && isRed(x->left->left)) rotateRight(x);
		if (isRed(x->left) && isRed(x->right)) flipColors(x);
		x->num = size(x->left) + size(x->right) + 1;
		return x;
	}
public:

};

int main(){

}