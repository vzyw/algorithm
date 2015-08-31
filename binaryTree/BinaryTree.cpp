#include "BinaryTree.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void BTree::setRoot( R r)
{
	root = r;
}

R BTree::getRoot()
{
	return root;
}

R BTree::createBTree()
{
	R current = NULL;
	int val = 0;	
	
	cin >> val;

	
	if (!val)
		return NULL;
	else
	{
		current = new BTreeNode;
		current->data = val;
		current->lChild = createBTree();
		current->rChild = createBTree();
		return current;
	}

}




//ǰ��ݹ飻
void BTree::preOrder(R r){
	if (r)
	{
		cout << r->data << " ";
		preOrder(r->lChild);
		preOrder(r->rChild);
	}
}
//����ݹ�
void BTree::inOrder(R r)
{
	if (r)
	{
		inOrder(r->lChild);
		cout << r->data << " ";
		inOrder(r->rChild);
	}
}

//����ݹ�
void BTree::postOrder(R r)
{
	if (r)
	{
		postOrder(r->lChild);
		postOrder(r->rChild);
		cout << r->data << " ";

	}
}


//�������(�ǵݹ�)
// ���ö�ջ һֱ���ջ��ѹ����ڵ㣬�޷�ѹ��ʱ�����׳��������׳��Ľڵ���ҽڵ����ѹ���ջ
void BTree::NotReInOrder(R r){
	vector<R> nodeVec;
	R Ptr = r;
	while (Ptr||!nodeVec.empty()){
		while (Ptr)
		{
			nodeVec.push_back(Ptr);
			Ptr = Ptr->lChild;
		}
		if (!nodeVec.empty()){
			Ptr = nodeVec.back();
			nodeVec.pop_back();
			cout << Ptr->data<<" ";
			Ptr = Ptr->rChild;
		}
	}
}
//ǰ�����(�ǵݹ�)
void BTree::NotRePreOrder(R r)
{
	vector<R> nodeVec;
	R Ptr = r;
	while (Ptr || !nodeVec.empty()){
		while (Ptr)
		{
			nodeVec.push_back(Ptr);
			cout << Ptr->data << " ";
			Ptr = Ptr->lChild;
		}
		if (!nodeVec.empty()){
			Ptr = nodeVec.back();
			nodeVec.pop_back();
			Ptr = Ptr->rChild;
		}
	}
}
//�������(�ǵݹ�)

//Ҫ��֤����������Ӻ��Һ��ӷ���֮����ܷ��ʣ���˶�����һ���P���Ƚ�����ջ��
//���P���������Ӻ��Һ��ӣ������ֱ�ӷ�����������P�������ӻ����Һ��ӣ�
//���������Ӻ��Һ��Ӷ��ѱ����ʹ��ˣ���ͬ������ֱ�ӷ��ʸý�㡣�����������������
//��P���Һ��Ӻ�����������ջ�������ͱ�֤��ÿ��ȡջ��Ԫ�ص�ʱ���������Һ���ǰ�汻���ʣ�
//���Ӻ��Һ��Ӷ��ڸ����ǰ�汻���ʡ�
void BTree::NotRePostOrder(R r)
{


	vector<R> nodeVec;
	R cur = 0; //��ǰ���
	R pre = 0;//ǰһ�η��ʵĽ�� 
	nodeVec.push_back(r);
	
	while (!nodeVec.empty())
	{
		cur = nodeVec.back();

		//�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ� 
		if (  (cur->lChild == 0 && cur->rChild == 0) || (pre != 0 && (pre == cur->lChild || pre == cur->rChild))){
			cout << cur->data << " ";
			nodeVec.pop_back();
			pre = cur;
		}
		else{
			if (cur->rChild != NULL)
				nodeVec.push_back(cur->rChild);
			if (cur->lChild != NULL)
				nodeVec.push_back(cur->lChild);

		}
	}
}

