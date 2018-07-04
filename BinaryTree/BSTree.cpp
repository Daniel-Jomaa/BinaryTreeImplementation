
#include "BSTree.h"

template <typename DataType, class KeyType>
BSTree<DataType, KeyType>::BSTreeNode::BSTreeNode(const DataType &nodeDataItem, BSTreeNode *leftPtr, BSTreeNode *rightPtr)
{
	dataItem = nodeDataItem;
	left = leftPtr;
	right = rightPtr;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree()
{
	root = NULL;
}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::BSTree(const BSTree<DataType, KeyType>& other)
{	
	copyTree(other);

}

template < typename DataType, class KeyType >
BSTree<DataType, KeyType>& BSTree<DataType, KeyType>:: operator= (const BSTree<DataType, KeyType>& other)
{
	copyTree(other);

	return this;
}
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyTree(const BSTree<DataType, KeyType> &otherTree)
{
	copyTreeHelper(root, otherTree.root);
}
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::copyTreeHelper(BSTreeNode *&p, const BSTreeNode *otherPtr)
{
	
	//immiates the inorder traversal method, however it copies the pointer 
	//instead of say printing it.
	if (otherPtr == NULL)
		return;

	copyTreeHelper(p->left, otherPtr->left);//goo alllll the way to the left

	p = otherPtr; // copy the pointer

	copyTreeHelper(p->right, otherPtr->right);//then go allll the way to the right
		//and copy the pointer

}
template < typename DataType, class KeyType >
BSTree<DataType, KeyType>::~BSTree()
{
	clear();
}

template < typename DataType, class KeyType >
//EXTRA POINT===
void BSTree<DataType, KeyType>::insert(const DataType& newDataItem)
{
	insertHelper(root, newDataItem);
}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::insertHelper(BSTreeNode *&p, const DataType &newDataItem)
{

	if (p == NULL)
		p = new BSTreeNode(newDataItem, NULL, NULL);
	//if the node data is smaller move to the right
	else if (p->dataItem.getKey() < newDataItem.getKey())
		insertHelper(p->right, newDataItem);
	//if the node data is smaller move to the right
	else if (p->dataItem.getKey() > newDataItem.getKey())
		insertHelper(p->left, newDataItem);
	else
		p->dataItem = newDataItem;
	
}
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieve(const KeyType& searchKey, DataType& searchDataItem) const
{
	return retrieveHelper(root, searchKey, searchDataItem);
}
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::retrieveHelper(BSTreeNode *p, const KeyType& searchKey, DataType &searchDataItem) const
{
   if (p == NULL) return false;
	if (p->dataItem.getKey() < searchKey)
		return retrieveHelper(p->right, searchKey, searchDataItem);

	else if (p->dataItem.getKey() > searchKey)
		return retrieveHelper(p->left, searchKey, searchDataItem);

	else if (p->dataItem.getKey() == searchKey){
	searchDataItem.setKey(searchKey);
	return true;
	}
}
//END EXTRA POINT====
//REMOVE A KEY=======
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::remove(const KeyType& deleteKey)
{
	return removeHelper(root, deleteKey);	
}
template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::removeHelper(BSTreeNode *&p, const KeyType& deleteKey)
{
	BSTreeNode *temp;

	if (p == NULL)
		return false;
	else if (p->dataItem.getKey() > deleteKey) //if larger go left
		removeHelper(p->left, deleteKey);

	else if (p->dataItem.getKey() < deleteKey) //if smaller go right
		removeHelper(p->right, deleteKey); 

	else if (p->dataItem.getKey() == deleteKey) {
		//if it is a leaf node its an easy delete
		if (p->left == NULL && p->right == NULL) {
			temp = p;
			delete temp;
			p = NULL;
			return true;
		}
		//case where there is only one child to the right
		else if (p->right != NULL && p->left == NULL)
		{
			temp = p;
			p = p->right;
			delete temp;
			return true;
		}
		//case where there is one child to the left
		else if (p->left != NULL && p->right == NULL)
		{
			temp = p;
			p = p->left;
			delete temp;
			return true;
		}
		//case where there two children
		else if (p->left != NULL && p->right != NULL)
		{
			temp = p->right;
			//recurse to find the leftmost node, copy it, and replace the current node with it
			cutRightmost(p, temp);
			return true;
		}
	}	

}
//this will be the helper that finds a replacement for the current nodeto be removed
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::cutRightmost(BSTreeNode *&r, BSTreeNode *&delPtr)
{
	//delPtr;
	//BSTreeNode *temp;

	while (delPtr->left != NULL)
	{
		delPtr = delPtr->left;
	}
	r->dataItem = delPtr->dataItem;
	removeHelper(r->right, delPtr->dataItem.getKey());
}
//END REMOVE A KEY======
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeys() const
{
	writeKeysHelper(root); 
}
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeKeysHelper(BSTreeNode *p) const
{
	if (p == NULL)
		return;
		writeKeysHelper(p->left);

		cout << p->dataItem.getKey() << " ";

		writeKeysHelper(p->right);

}

template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clear()
{
	clearHelper(root);
	root = NULL;
}
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::clearHelper(BSTreeNode *p)
{
	if (p == NULL)
		return;
	if (p->left != NULL) clearHelper(p->left);
	if (p->right != NULL) clearHelper(p->right);
	delete p;
}

template < typename DataType, class KeyType >
bool BSTree<DataType, KeyType>::isEmpty() const
{
	if (root == NULL)
		return true;
	else
		return false;
}

template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeight() const
{
	int left = getHeightHelper(root->left);
	int right = getHeightHelper(root->right);

	if (left > right)
		return left;
	else
		return right + 1;

}
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getHeightHelper(BSTreeNode *p) const
{
	if (p == NULL)
		return 0;
	
	return getHeightHelper(p->left) + getHeightHelper(p->right) + 1;
}
//max of left or right + 1
//go left and right, choose the highest, then add one
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCount() const
{
	return getCountHelper(root);
}
template < typename DataType, class KeyType >
int BSTree<DataType, KeyType>::getCountHelper(BSTreeNode *p) const
{
	if (p == NULL)
		return 0;

	return getHeightHelper(p->left) + getHeightHelper(p->right) + 1;
}
//recusive, number of nodes in left plus right plus one
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLessThan(const KeyType& searchKey) const
{
	writeLTHelper(root, searchKey);
}
template < typename DataType, class KeyType >
void BSTree<DataType, KeyType>::writeLTHelper(BSTreeNode *p, const KeyType& searchKey) const
{
	if (p == NULL)
		return;
	writeLTHelper(p->left, searchKey);

	if (p->dataItem.getKey() < searchKey) {
		cout << p->dataItem.getKey() << " ";
	}

	writeLTHelper(p->right, searchKey);
}
//print the items that are lesss than the search key
//siimilar t writekey but you need to compare


#include "show9.cpp"