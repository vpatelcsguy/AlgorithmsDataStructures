
#ifndef __RBTree__
#define __RBTree__
#include <iostream>
#include <cstring>
using namespace std;

enum Color {R, B};

template <typename E>
class RBTree {
private:
	class TreeNode
	{
	public:
		E element;
		bool color;
		TreeNode *left;
		TreeNode * right;
		TreeNode * parent;

		TreeNode(E element): left(nullptr), right(nullptr), parent(nullptr), element(element){}
	};
	void copyTree(TreeNode *& r, TreeNode * cr) {
		if (cr) {
			r = createNode(cr->element);
			copyTree(r->left, cr->left);
			copyTree(r->right, cr->right);
		}
	}

	void releaseNode(TreeNode *& r) {
		r->left = r->right = nullptr;
		delete r;
		r = nullptr;
	}

	void makeEmpty(TreeNode *& r) {
		if (r) {
			makeEmpty(r->left);
			makeEmpty(r->right);
			releaseNode(r);
		}
	}
	TreeNode* createNode(const E& e) {
		return new TreeNode(e);
	}
	TreeNode * BSTInsert(TreeNode * root, TreeNode * newItem)
	{
		if (root == nullptr) { return newItem; }

		if (newItem->element < root->element) {
			root->left = BSTInsert(root->left, newItem);
			root->left->parent = root;
		}
		else if (newItem->element > root->element) {
			root->right = BSTInsert(root->right, newItem);
			root->right->parent = root;
		}
		return root;
	}

	void RBTree::rotateLeft(TreeNode *& root, TreeNode *& newItem)
	{
		TreeNode * newItemRight = newItem->right;
		newItem->right = newItemRight->left;

		if (newItem->right != nullptr) { newItem->right->parent = newItem; }

		newItemRight->parent = newItem->parent;

		if (newItem->parent == nullptr){ root = newItemRight; }
		else if (newItem == newItem->parent->left){ newItem->parent->left = newItemRight; }
		else { newItem->parent->right = newItemRight; }
		newItemRight->left = newItem;
		newItem->parent = newItemRight;
	}

	void RBTree::rotateRight(TreeNode *& root, TreeNode *& newItem)
	{
		TreeNode *newItemLeft = newItem->left;
		newItem->left = newItemLeft->right;

		if (newItem->left != nullptr) { newItem->left->parent = newItem; }

		newItemLeft->parent = newItem->parent;

		if (newItem->parent == nullptr) { root = newItemLeft; }
		else if (newItem == newItem->parent->left){	newItem->parent->left = newItemLeft;}
		else { newItem->parent->right = newItemLeft; }
		newItemLeft->right = newItem;
		newItem->parent = newItemLeft;
	}

	void RBTree::fixViolation(TreeNode *& root, TreeNode *& newItem) {
		TreeNode * newParent = nullptr;
		TreeNode * grandPa = nullptr;

		while ((newItem != root) && (newItem->color != B) && (newItem->parent->color == R)) {
			newParent = newItem->parent;
			grandPa = newItem->parent->parent;

			if (newParent == grandPa->left) {
				TreeNode *uncle = grandPa->right;
				if (uncle != NULL && uncle->color == R)	{
					grandPa->color = R;
					newParent->color = B;
					uncle->color = B;
					newItem = grandPa;
				}
				else {
					if (newItem == newParent->right) {
						rotateLeft(root, newParent);
						newItem = newParent;
						newParent = newItem->parent;
					}

					rotateRight(root, grandPa);
					swap(newParent->color, grandPa->color);
					newItem = newParent;
				}
			}
			else {
				TreeNode *uncle = grandPa->left;

				if ((uncle != NULL) && (uncle->color == R))	{
					grandPa->color = R;
					newParent->color = B;
					uncle->color = B;
					newItem = grandPa;
				}
				else {
					if (newItem == newParent->left)	{
						rotateRight(root, newParent);
						newItem = newParent;
						newParent = newItem->parent;
					}
					rotateLeft(root, grandPa);
					swap(newParent->color, grandPa->color);
					newItem = newParent;
				}
			}
		}
		root->color = B;
	}

protected:
	TreeNode *root;
	template<typename Functor> void DoTraverse(Functor search, TreeNode* root);

public:
	RBTree() : root(nullptr) {}

	RBTree(const RBTree& o) : root(nullptr) { copyTree(root, o.root); }

	~RBTree() { makeEmpty(root); }
	const RBTree& operator =(const RBTree& o) {
		if (this != &o) {
			makeEmpty(root);
			copyTree(root, o.root);
		}

		return *this;
	}

	virtual void makeEmpty() { makeEmpty(root); }

	template<typename Functor> void traverse(Functor search);
	void RBTree::insert(const E &element)
	{
		TreeNode *newItem = new TreeNode(element);
		root = BSTInsert(root, newItem);
		fixViolation(root, newItem);
	}
};

template<typename T> template<typename Functor> inline void RBTree<T>::traverse(Functor search) {
	DoTraverse(search, root);
}
template<typename T> template<typename Functor> inline void RBTree<T>::DoTraverse(Functor search, TreeNode* root)
{
	if (root) {
		DoTraverse(search, root->left);
		search(root->element);
		DoTraverse(search, root->right);
	}
}
#endif 