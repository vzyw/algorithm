#ifndef BTREE_H
#define BTREE_H

struct BTreeNode
{
	int data;
	BTreeNode *lChild, *rChild;
};

typedef BTreeNode* R;
class BTree
{
public:
	void setRoot(R);
	R getRoot();
	R createBTree();

	//中序遍历(递归)
	void inOrder(R);
	//中序遍历(非递归)
	void NotReInOrder(R);
	

	//前序遍历(递归)
	void preOrder(R);
	//前序遍历(非递归)
	void NotRePreOrder(R);

	//后序遍历(递归)
	void postOrder(R);

	//后序遍历(非递归)
	void NotRePostOrder(R);

	//求结点个数
	int BTreeSize();
	//求叶子结点个数
	int BTreeLeaves();

	//求树高
	int BTreeHeight();
	//层次法求树高
	int layerHeight();//队列

private:
	R root;
};

#endif