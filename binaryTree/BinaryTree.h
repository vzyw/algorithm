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

	//�������(�ݹ�)
	void inOrder(R);
	//�������(�ǵݹ�)
	void NotReInOrder(R);
	

	//ǰ�����(�ݹ�)
	void preOrder(R);
	//ǰ�����(�ǵݹ�)
	void NotRePreOrder(R);

	//�������(�ݹ�)
	void postOrder(R);

	//�������(�ǵݹ�)
	void NotRePostOrder(R);

	//�������
	int BTreeSize();
	//��Ҷ�ӽ�����
	int BTreeLeaves();

	//������
	int BTreeHeight();
	//��η�������
	int layerHeight();//����

private:
	R root;
};

#endif