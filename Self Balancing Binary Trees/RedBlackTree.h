#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node_RB
{
    int data;
    Node_RB *parent;
    Node_RB *left;
    Node_RB *right;
    int color;
};

typedef Node_RB *NodePtr_RB;

class RedBlackTree
{
private:
    NodePtr_RB root;
    NodePtr_RB TNULL;
    int count_RB_Insert = 0, count_RB_Delete = 0;
    void initializeNULLNode(NodePtr_RB node, NodePtr_RB parent);
    void preOrderHelper(NodePtr_RB node);
    void inOrderHelper(NodePtr_RB node);
    void postOrderHelper(NodePtr_RB node);
    NodePtr_RB searchTreeHelper(NodePtr_RB node, int key);
    void deleteFix(NodePtr_RB x);
    void rbTransplant(NodePtr_RB u, NodePtr_RB v);
    void deleteNodeHelper(NodePtr_RB node, int key);
    void insertFix(NodePtr_RB k);
    void printHelper(NodePtr_RB root, string indent, bool last);

public:
    RedBlackTree()
    {
        TNULL = new Node_RB;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }
    void preorder();
    void inorder();
    void postorder();
    NodePtr_RB searchTree(int k);
    NodePtr_RB minimum(NodePtr_RB node);
    NodePtr_RB maximum(NodePtr_RB node);
    NodePtr_RB successor(NodePtr_RB x);
    NodePtr_RB predecessor(NodePtr_RB x);
    void leftRotate(NodePtr_RB x);
    void rightRotate(NodePtr_RB x);
    void insert(int key);
    NodePtr_RB getRoot();
    void deleteNode(int data);
    void printTree();
    int countInsert(); 
    int countDelete();
};
