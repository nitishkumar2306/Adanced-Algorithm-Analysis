#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node
{
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};

int count_RB_Insert = 0, count_RB_Delete = 0;
typedef Node *NodePtr;

class RedBlackTree
{
private:
    NodePtr root;
    NodePtr TNULL;
    void initializeNULLNode(NodePtr node, NodePtr parent);
    void preOrderHelper(NodePtr node);
    void inOrderHelper(NodePtr node);
    void postOrderHelper(NodePtr node);
    NodePtr searchTreeHelper(NodePtr node, int key);
    void deleteFix(NodePtr x);
    void rbTransplant(NodePtr u, NodePtr v);
    void deleteNodeHelper(NodePtr node, int key);
    void insertFix(NodePtr k);
    void printHelper(NodePtr root, string indent, bool last);

public:
    RedBlackTree()
    {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
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
    void deleteNode(int data);
    void printTree();
};