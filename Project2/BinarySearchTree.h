
#ifndef __BinarySearchTree__
#define __BinarySearchTree__

#include <iostream>
using namespace std;

template <typename E>
class BinarySearchTree {

private:
   class TreeNode {
   public:
      TreeNode * left;
      E element;
      TreeNode * right;
      
      TreeNode(TreeNode* const left, const E& e, TreeNode* const right): left(left), element(e), right(right){}
   };

   void copyTree(TreeNode *& r, TreeNode * cr) {
      if (cr) {
         r = createNode(nullptr, cr->element, nullptr);
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
   TreeNode* createNode(TreeNode * const left, const E& e, TreeNode * const right) {
      return new TreeNode(left, e, right);
   }
   void insert(TreeNode *& r, const E& e) {
      if (r == nullptr)          { r = createNode(nullptr, e, nullptr); }
      else if (e < r->element)   { insert(r->left, e);                  }
      else                       { insert(r->right, e);                 }
   }

protected:
   TreeNode * root;
   template<typename Functor> void DoTraverse(Functor search, TreeNode *root);

public:
   BinarySearchTree() : root(nullptr){}

   BinarySearchTree(const BinarySearchTree& o) : root(nullptr) { copyTree(root, o.root); }

   ~BinarySearchTree() { makeEmpty(root); }

   template<typename Functor> void traverse(Functor search);

   const BinarySearchTree& operator =(const BinarySearchTree& o) {
      if (this != & o) {
         makeEmpty(root);
         copyTree(root, o.root);
      }
      
      return *this;
   }

   virtual void makeEmpty() { makeEmpty(root); }
   virtual void insert(const E& e) { insert(root, e); }
};

template<typename K> template<typename Functor> inline void BinarySearchTree<K>::traverse(Functor search) {
	DoTraverse(search, root);
}
template<typename E> template<typename Functor> inline void BinarySearchTree<E>::DoTraverse(Functor search, TreeNode* root)
{
	if (root) {
		DoTraverse(search, root->left);
		search(root->element);
		DoTraverse(search, root->right);
	}
}
#endif 
