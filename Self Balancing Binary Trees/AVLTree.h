#include <algorithm>
#include <iostream>

using namespace std;

// data structure that represents a Node_AVL in the tree
struct Node_AVL {
  int data;     // holds the key
  Node_AVL *parent; // pointer to the parent
  Node_AVL *left;   // pointer to left child
  Node_AVL *right;  // pointer to right child
  int bf;       // balance factor of the Node_AVL
};

typedef Node_AVL *NodePtr;

class AVLTree {
private:
  int count_AVL_Delete = 0, count_AVL_Insert = 0;
  NodePtr root;
  void initializeNode(NodePtr node, int key);
  void preOrderHelper(NodePtr node);
  void inOrderHelper(NodePtr node);
  void postOrderHelper(NodePtr node);
  NodePtr searchTreeHelper(NodePtr node, int key);
  NodePtr deleteNodeHelper(NodePtr node, int key);
  void updateBalance(NodePtr node);
  void rebalance(NodePtr node);
  void printHelper(NodePtr root, string indent, bool last);

public:
  AVLTree() { root = nullptr; }
  void preorder();
  void inorder();
  void postorder();
  NodePtr searchTree(int k);
  NodePtr minimum(NodePtr node);
  NodePtr maximum(NodePtr node);
  NodePtr successor(NodePtr x);
  NodePtr predecessor(NodePtr x);
  void leftRotate(NodePtr x);
  void rightRotate(NodePtr x);
  void insert(int key);
  NodePtr getRoot();
  NodePtr deleteNode(int data);
  void prettyPrint();
  int countInsert();
  int countDelete();
};