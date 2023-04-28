#include "RedBlackTree.h"

void RedBlackTree::initializeNULLNode(NodePtr_RB node, NodePtr_RB parent)
  {
    node->data = 0;
    node->parent = parent;
    node->left = nullptr;
    node->right = nullptr;
    node->color = 0;
  }

  // Preorder
  void RedBlackTree::preOrderHelper(NodePtr_RB node)
  {
    if (node != TNULL)
    {
      cout << node->data << " ";
      preOrderHelper(node->left);
      preOrderHelper(node->right);
    }
  }

  // Inorder
  void RedBlackTree::inOrderHelper(NodePtr_RB node)
  {
    if (node != TNULL)
    {
      inOrderHelper(node->left);
      cout << node->data << " ";
      inOrderHelper(node->right);
    }
  }

  // Post order
  void RedBlackTree:: postOrderHelper(NodePtr_RB node)
  {
    if (node != TNULL)
    {
      postOrderHelper(node->left);
      postOrderHelper(node->right);
      cout << node->data << " ";
    }
  }

  NodePtr_RB RedBlackTree:: searchTreeHelper(NodePtr_RB node, int key)
  {
    if (node == TNULL || key == node->data)
    {
      if (key == node->data)
      {
        cout << "Key Found" << endl;
      }
      else
      {
        cout << "Key Not Found" << endl;
      }
      return node;
    }

    if (key < node->data)
    {
      return searchTreeHelper(node->left, key);
    }
    return searchTreeHelper(node->right, key);
  }

  // For balancing the tree after deletion
  void RedBlackTree::deleteFix(NodePtr_RB x)
  {
    NodePtr_RB s;
    while (x != root && x->color == 0)
    {
      if (x == x->parent->left)
      {
        s = x->parent->right;
        if (s->color == 1)
        {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->right->color == 0)
          {
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
      }
      else
      {
        s = x->parent->left;
        if (s->color == 1)
        {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->right->color == 0)
        {
          s->color = 1;
          x = x->parent;
        }
        else
        {
          if (s->left->color == 0)
          {
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

  void RedBlackTree::rbTransplant(NodePtr_RB u, NodePtr_RB v)
  {
    if (u->parent == nullptr)
    {
      root = v;
    }
    else if (u == u->parent->left)
    {
      u->parent->left = v;
    }
    else
    {
      u->parent->right = v;
    }
    v->parent = u->parent;
  }

  void RedBlackTree::deleteNodeHelper(NodePtr_RB node, int key)
  {
    
    NodePtr_RB z = TNULL;
    NodePtr_RB x, y;
    count_RB_Delete++;
    while (node != TNULL)
    {
      if (node->data == key)
      {
        z = node;
        count_RB_Delete++;
      }

      if (node->data <= key)
      {
        node = node->right;
        count_RB_Delete++;
      }
      else
      {
        node = node->left;
      }
    }

    if (z == TNULL)
    {
      // cout << "Key not found in the tree" << endl;
      return;
    }

    y = z;
    int y_original_color = y->color;
    if (z->left == TNULL)
    {
      x = z->right;
      rbTransplant(z, z->right);
    }
    else if (z->right == TNULL)
    {
      x = z->left;
      rbTransplant(z, z->left);
    }
    else
    {
      y = minimum(z->right);
      y_original_color = y->color;
      x = y->right;
      if (y->parent == z)
      {
        x->parent = y;
      }
      else
      {
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
    if (y_original_color == 0)
    {
      deleteFix(x);
    }
  }

  // For balancing the tree after insertion
  void RedBlackTree::insertFix(NodePtr_RB k)
  {
    NodePtr_RB u;
    while (k->parent->color == 1)
    {
      if (k->parent == k->parent->parent->right)
      {
        u = k->parent->parent->left;
        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->left)
          {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          leftRotate(k->parent->parent);
        }
      }
      else
      {
        u = k->parent->parent->right;

        if (u->color == 1)
        {
          u->color = 0;
          k->parent->color = 0;
          k->parent->parent->color = 1;
          k = k->parent->parent;
        }
        else
        {
          if (k == k->parent->right)
          {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = 0;
          k->parent->parent->color = 1;
          rightRotate(k->parent->parent);
        }
      }
      if (k == root)
      {
        break;
      }
    }
    root->color = 0;
  }

  void RedBlackTree::printHelper(NodePtr_RB root, string indent, bool last)
  {
    if (root != TNULL)
    {
      cout << indent;
      if (last)
      {
        cout << "R----";
        indent += "   ";
      }
      else
      {
        cout << "L----";
        indent += "|  ";
      }

      string sColor = root->color ? "RED" : "BLACK";
      cout << root->data << "(" << sColor << ")" << endl;
      printHelper(root->left, indent, false);
      printHelper(root->right, indent, true);
    }
  }

  void RedBlackTree::preorder()
  {
    preOrderHelper(this->root);
  }

  void RedBlackTree::inorder()
  {
    inOrderHelper(this->root);
  }

  void RedBlackTree::postorder()
  {
    postOrderHelper(this->root);
  }

  NodePtr_RB RedBlackTree::searchTree(int k)
  {
    return searchTreeHelper(this->root, k);
  }

  NodePtr_RB RedBlackTree::minimum(NodePtr_RB node)
  {
    while (node->left != TNULL)
    {
      node = node->left;
    }
    return node;
  }

  NodePtr_RB RedBlackTree::maximum(NodePtr_RB node)
  {
    while (node->right != TNULL)
    {
      node = node->right;
    }
    return node;
  }

  NodePtr_RB RedBlackTree::successor(NodePtr_RB x)
  {
    if (x->right != TNULL)
    {
      return minimum(x->right);
    }

    NodePtr_RB y = x->parent;
    while (y != TNULL && x == y->right)
    {
      x = y;
      y = y->parent;
    }
    return y;
  }

  NodePtr_RB RedBlackTree::predecessor(NodePtr_RB x)
  {
    if (x->left != TNULL)
    {
      return maximum(x->left);
    }

    NodePtr_RB y = x->parent;
    while (y != TNULL && x == y->left)
    {
      x = y;
      y = y->parent;
    }

    return y;
  }

  void RedBlackTree::leftRotate(NodePtr_RB x)
  {
    NodePtr_RB y = x->right;
    x->right = y->left;
    if (y->left != TNULL)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }

  void RedBlackTree::rightRotate(NodePtr_RB x)
  {
    NodePtr_RB y = x->left;
    x->left = y->right;
    if (y->right != TNULL)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
      this->root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  // Inserting a node
  void RedBlackTree::insert(int key)
  {
    count_RB_Insert++;
    NodePtr_RB node = new Node_RB;
    node->parent = nullptr;
    node->data = key;
    node->left = TNULL;
    node->right = TNULL;
    node->color = 1;

    NodePtr_RB y = nullptr;
    NodePtr_RB x = this->root;

    while (x != TNULL)
    {
      y = x;
      if (node->data < x->data)
      {
        x = x->left;
        count_RB_Insert++;
      }
      else
      {
        x = x->right;
        count_RB_Insert++;
      }
    }

    node->parent = y;
    if (y == nullptr)
    {
      root = node;
    }
    else if (node->data < y->data)
    {
      y->left = node;
    }
    else
    {
      y->right = node;
    }

    if (node->parent == nullptr)
    {
      node->color = 0;
      return;
    }

    if (node->parent->parent == nullptr)
    {
      return;
    }

    insertFix(node);
  }

  NodePtr_RB RedBlackTree::getRoot()
  {
    return this->root;
  }

  void RedBlackTree::deleteNode(int data)
  {
    deleteNodeHelper(this->root, data);
  }

  void RedBlackTree::printTree()
  {
    if (root)
    {
      printHelper(this->root, "", true);
    }
  }

 int RedBlackTree::countInsert()
  {
    return count_RB_Insert;
  }

  int RedBlackTree::countDelete()
  {
    return count_RB_Delete;
  }


