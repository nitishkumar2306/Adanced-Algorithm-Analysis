// Source: https://www.programiz.com/dsa/red-black-tree
// source: https://www.guru99.com/avl-tree.html

#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

struct AVL_Node {
  struct AVL_Node *left;
  int data;
  int height;
  struct AVL_Node *right;
};
// ------------------------Red Black Tree--------------------------------

typedef Node *NodePtr;

class RedBlackTree {
   private:
  NodePtr root;
  NodePtr TNULL;

  void initializeNULLNode(NodePtr node, NodePtr parent) {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
  void preOrderHelper(NodePtr node) {
    if (node != TNULL) {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void inOrderHelper(NodePtr node) {
    if (node != TNULL) {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void postOrderHelper(NodePtr node) {
    if (node != TNULL) {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr searchTreeHelper(NodePtr node, int key) {
    if (node == TNULL || key == node->data) {
      return node;
    }

    if (key < node->data) {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = root;
        }
      }
    }
    x->color = 0;
  }

  void rbTransplant(NodePtr u, NodePtr v) {
    if (u->parent == nullptr) {
      root = v;
    } else if (u == u->parent->left) {
      u->parent->left = v;
    } else {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void deleteNodeHelper(NodePtr node, int key) {
    NodePtr z = TNULL;
    NodePtr x, y;
    while (node != TNULL) {
      if (node->data == key) {
        z = node;
      }

      if (node->data <= key) {
        node = node->right;
      } else {
        node = node->left;
      }
    }

    if (z == TNULL) {
      cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL) {
      x = z->right;
      rbTransplant(z, z->right);
    } else if (z->right == TNULL) {
      x = z->left;
      rbTransplant(z, z->left);
    } else {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z) {
        x->parent = y;
      } else {
        rbTransplant(y, y->right);
        y->right = z->right;
        y->right->parent = y;
      }

      rbTransplant(z, y);
      y->left = z->left;
      y->left->parent = y;
      y->color = z->color;
    }
    delete z;
    if (y_original_color == 0) {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == 1) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == 1) {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root) {
        break;
      }
    }
    root->color = 0;
  }

  void printHelper(NodePtr root, string indent, bool last) {
    if (root != TNULL) {
      cout << indent;
      if (last) {
        cout << "R----";
        indent += "   ";
      } else {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

   public:
  RedBlackTree() {
    TNULL = new Node;
    TNULL->color = 0;
    TNULL->left = nullptr;
    TNULL->right = nullptr;
    root = TNULL;
  }

  void preorder() {
    preOrderHelper(this->root);
  }

  void inorder() {
    inOrderHelper(this->root);
  }

  void postorder() {
    postOrderHelper(this->root);
  }

  NodePtr searchTree(int k) {
    return searchTreeHelper(this->root, k);
  }

  NodePtr minimum(NodePtr node) {
    while (node->left != TNULL) {
      node = node->left;
    }
    return node;
  }

  NodePtr maximum(NodePtr node) {
    while (node->right != TNULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr successor(NodePtr x) {
    if (x->right != TNULL) {
      return minimum(x->right);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->right) {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr predecessor(NodePtr x) {
    if (x->left != TNULL) {
      return maximum(x->left);
    }

    NodePtr y = x->parent;
    while (y != TNULL && x == y->left) {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void leftRotate(NodePtr x) {
    NodePtr y = x->right;
    x->right = y->left;
    if (y->left != TNULL) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void rightRotate(NodePtr x) {
    NodePtr y = x->left;
    x->left = y->right;
    if (y->right != TNULL) {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      this->root = y;
    } else if (x == x->parent->right) {
      x->parent->right = y;
    } else {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void insert(int key) {
    NodePtr node = new Node;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr y = nullptr;
    NodePtr x = this->root;

    while (x != TNULL) {
      y = x;
      if (node->data < x->data) {
        x = x->left;
      } else {
        x = x->right;
      }
    }

    node->parent = y;
    if (y == nullptr) {
      root = node;
    } else if (node->data < y->data) {
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr) {
      return;
    }

    insertFix(node);
  }

  NodePtr getRoot() {
    return this->root;
  }

  void deleteNode(int data) {
    deleteNodeHelper(this->root, data);
  }

  void printTree() {
    if (root) {
      printHelper(this->root, "", true);
    }
  }
};


// -------------------------AVL Tree-------------------------

class AVL {
private:
public:
  struct AVL_Node *root;
  AVL() { this->root = NULL; }

  int calheight(struct AVL_Node *p) {

    if (p->left && p->right) {
      if (p->left->height < p->right->height)
        return p->right->height + 1;
      else
        return p->left->height + 1;
    } else if (p->left && p->right == NULL) {
      return p->left->height + 1;
    } else if (p->left == NULL && p->right) {
      return p->right->height + 1;
    }
    return 0;
  }

  int bf(struct AVL_Node *n) {
    if (n->left && n->right) {
      return n->left->height - n->right->height;
    } else if (n->left && n->right == NULL) {
      return n->left->height;
    } else if (n->left == NULL && n->right) {
      return -n->right->height;
    }
  }

  struct AVL_Node *llrotation(struct AVL_Node *n) {
    struct AVL_Node *p;
    struct AVL_Node *tp;
    p = n;
    tp = p->left;

    p->left = tp->right;
    tp->right = p;

    return tp;
  }

  struct AVL_Node *rrrotation(struct AVL_Node *n) {
    struct AVL_Node *p;
    struct AVL_Node *tp;
    p = n;
    tp = p->right;

    p->right = tp->left;
    tp->left = p;

    return tp;
  }

  struct AVL_Node *rlrotation(struct AVL_Node *n) {
    struct AVL_Node *p;
    struct AVL_Node *tp;
    struct AVL_Node *tp2;
    p = n;
    tp = p->right;
    tp2 = p->right->left;

    p->right = tp2->left;
    tp->left = tp2->right;
    tp2->left = p;
    tp2->right = tp;

    return tp2;
  }

  struct AVL_Node *lrrotation(struct AVL_Node *n) {
    struct AVL_Node *p;
    struct AVL_Node *tp;
    struct AVL_Node *tp2;
    p = n;
    tp = p->left;
    tp2 = p->left->right;

    p->left = tp2->right;
    tp->right = tp2->left;
    tp2->right = p;
    tp2->left = tp;

    return tp2;
  }

  struct AVL_Node *insert(struct AVL_Node *r, int data) {

    if (r == NULL) {
      struct AVL_Node *n;
      n = new struct AVL_Node;
      n->data = data;
      r = n;
      r->left = r->right = NULL;
      r->height = 1;
      return r;
    } else {
      if (data < r->data)
        r->left = insert(r->left, data);
      else
        r->right = insert(r->right, data);
    }

    r->height = calheight(r);

    if (bf(r) == 2 && bf(r->left) == 1) {
      r = llrotation(r);
    } else if (bf(r) == -2 && bf(r->right) == -1) {
      r = rrrotation(r);
    } else if (bf(r) == -2 && bf(r->right) == 1) {
      r = rlrotation(r);
    } else if (bf(r) == 2 && bf(r->left) == -1) {
      r = lrrotation(r);
    }

    return r;
  }

  void levelorder_newline() {
    if (this->root == NULL) {
      cout << "\n"
           << "Empty tree"
           << "\n";
      return;
    }
    levelorder_newline(this->root);
  }

  void levelorder_newline(struct AVL_Node *v) {
    queue<struct AVL_Node *> q;
    struct AVL_Node *cur;
    q.push(v);
    q.push(NULL);

    while (!q.empty()) {
      cur = q.front();
      q.pop();
      if (cur == NULL && q.size() != 0) {
        cout << "\n";

        q.push(NULL);
        continue;
      }
      if (cur != NULL) {
        cout << " " << cur->data;

        if (cur->left != NULL) {
          q.push(cur->left);
        }
        if (cur->right != NULL) {
          q.push(cur->right);
        }
      }
    }
  }

  struct AVL_Node *deleteAVL_Node(struct AVL_Node *p, int data) {

    if (p->left == NULL && p->right == NULL) {
      if (p == this->root)
        this->root = NULL;
      delete p;
      return NULL;
    }

    struct AVL_Node *t;
    struct AVL_Node *q;
    if (p->data < data) {
      p->right = deleteAVL_Node(p->right, data);
    } else if (p->data > data) {
      p->left = deleteAVL_Node(p->left, data);
    } else {
      if (p->left != NULL) {
        q = inpre(p->left);
        p->data = q->data;
        p->left = deleteAVL_Node(p->left, q->data);
      } else {
        q = insuc(p->right);
        p->data = q->data;
        p->right = deleteAVL_Node(p->right, q->data);
      }
    }

    if (bf(p) == 2 && bf(p->left) == 1) {
      p = llrotation(p);
    } else if (bf(p) == 2 && bf(p->left) == -1) {
      p = lrrotation(p);
    } else if (bf(p) == 2 && bf(p->left) == 0) {
      p = llrotation(p);
    } else if (bf(p) == -2 && bf(p->right) == -1) {
      p = rrrotation(p);
    } else if (bf(p) == -2 && bf(p->right) == 1) {
      p = rlrotation(p);
    } else if (bf(p) == -2 && bf(p->right) == 0) {
      p = llrotation(p);
    }

    return p;
  }

  struct AVL_Node *inpre(struct AVL_Node *p) {
    while (p->right != NULL)
      p = p->right;
    return p;
  }

  struct AVL_Node *insuc(struct AVL_Node *p) {
    while (p->left != NULL)
      p = p->left;

    return p;
  }

  ~AVL() {}
};

// -------------------------------------------------------



int main() {
  RedBlackTree bst;
  AVL avltree;

   cout<<"-----------AVL Tree------------"<<endl;

  avltree.root = avltree.insert(avltree.root, 50);
  avltree.root = avltree.insert(avltree.root, 40);
  avltree.root = avltree.insert(avltree.root, 60);
  avltree.root = avltree.insert(avltree.root, 45);
  avltree.root = avltree.insert(avltree.root, 55);

  cout << "Before Delete" << endl;
  avltree.levelorder_newline();

  avltree.root =  avltree.deleteAVL_Node( avltree.root,45);
  
  cout<<endl;
  cout <<endl<<"After Delete" << endl;
  avltree.levelorder_newline();

  cout<<endl<<"---------Red Black Tree----------"<<endl;
  bst.insert(55);
  bst.insert(40);
  bst.insert(65);
  bst.insert(60);
  bst.insert(75);
  bst.insert(57);

  bst.printTree();
  cout << endl
     << "After deleting" << endl;
  bst.deleteNode(40);
  bst.printTree();
}