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




//前序递归；
void BTree::preOrder(R r){
	if (r)
	{
		cout << r->data << " ";
		preOrder(r->lChild);
		preOrder(r->rChild);
	}
}
//中序递归
void BTree::inOrder(R r)
{
	if (r)
	{
		inOrder(r->lChild);
		cout << r->data << " ";
		inOrder(r->rChild);
	}
}

//后序递归
void BTree::postOrder(R r)
{
	if (r)
	{
		postOrder(r->lChild);
		postOrder(r->rChild);
		cout << r->data << " ";

	}
}


//中序遍历(非递归)
// 利用堆栈 一直向堆栈里压入左节点，无法压入时进行抛出，并把抛出的节点的右节点继续压入堆栈
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
//前序遍历(非递归)
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
//后序遍历(非递归)

//要保证根结点在左孩子和右孩子访问之后才能访问，因此对于任一结点P，先将其入栈。
//如果P不存在左孩子和右孩子，则可以直接访问它；或者P存在左孩子或者右孩子，
//但是其左孩子和右孩子都已被访问过了，则同样可以直接访问该结点。若非上述两种情况，
//则将P的右孩子和左孩子依次入栈，这样就保证了每次取栈顶元素的时候，左孩子在右孩子前面被访问，
//左孩子和右孩子都在根结点前面被访问。
void BTree::NotRePostOrder(R r)
{


	vector<R> nodeVec;
	R cur = 0; //当前结点
	R pre = 0;//前一次访问的结点 
	nodeVec.push_back(r);
	
	while (!nodeVec.empty())
	{
		cur = nodeVec.back();

		//如果当前结点没有孩子结点或者孩子节点都已被访问过 
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

