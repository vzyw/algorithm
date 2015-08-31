#include<iostream>
using namespace std;
#define RED true;
#define  BLACK false ;

//����������Ժ�ڵ���в��룬֮���������״̬��������ת��������ת��������ɫת��

//ÿ��node ����key��value��num��ʾ�����Լ������Լ�Ϊ���ڵ�Ķ������ܽڵ���������һ��boolֵ��ʾ�Ӹ��ڵ�ָ�������Ǻ�ɫ���ɫ
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
	//����ת
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
	//����ת
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
	//��ɫ�仯�������ҽڵ㶼�Ǻ���ʱ��ɺ�ɫ�����ڵ��ɺ�ɫ
	void flipColors(Node *p){
		p->color = RED;
		p->left->color = BLACK;
		p->right->color = BLACK;
	}
	//���롣�������ݺ���ܳ�������������ڵ㣬�������ҹյĺ�ڵ㣬���������Ӧ�仯��
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