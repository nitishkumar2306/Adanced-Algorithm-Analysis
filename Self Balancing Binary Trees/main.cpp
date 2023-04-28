#include "AVLTree.h"
#include "RedBlackTree.h"
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  RedBlackTree bst;
  AVLTree bst_avl;
  ifstream ifile_AVL, ifile_RB;
  int temp, delTemp = 0;
  double duration_Insert_AVL = 0, duration_Insert_RB = 0;
  double duration_Delete_AVL = 0, duration_Delete_RB = 0;
  clock_t start;
  ofstream ofile;

  ofile.open("array_data.dat");

  srand(time(0));
  int upper = 500, lower = 10;
  delTemp = (rand() % (upper - lower + 1)) + lower;
  cout << "Random Variable to be deleted is: " << delTemp << endl;

  for (int i = 0; i < 200; i++) {
    int num = (rand() % (upper - lower + 1)) + lower;
    // cout << num << " ";
    ofile << num << endl;
  }

  cout << "-------------Red Black Tree-------------" << endl;

  start = clock();

  ifile_RB.open("array_data.dat");

  for (int i = 0; i < 200; i++) {
    ifile_RB >> temp;
    bst.insert(temp);
  }

  duration_Insert_RB = (clock() - start) / (double)CLOCKS_PER_SEC;
  cout << "Duration for Insertion into Red Black tree: " << duration_Insert_RB
       << endl;

  // bst.printTree();
  // cout << endl
  //  << "After deleting" << endl;

  start = clock();

  bst.deleteNode(delTemp);

  duration_Delete_RB = (clock() - start) / (double)CLOCKS_PER_SEC;

  // bst.printTree();
  cout << "Duration to delete an element in AVL tree: " << duration_Delete_RB
       << endl;

  cout << "Count for Insertion: " << bst.countInsert() << endl;
  cout << "Count for Deletion: " << bst.countDelete() << endl;

  cout << endl;
  cout << "-------------------AVL Tree--------------------" << endl;
  ifile_AVL.open("array_data.dat");

  // start the timer
  start = clock();

  for (int i = 0; i < 200; i++) {
    ifile_AVL >> temp;
    bst_avl.insert(temp);
  }

  duration_Insert_AVL = (clock() - start) / (double)CLOCKS_PER_SEC;

  cout << "Duration for Insertion into AVL tree: " << duration_Insert_AVL
       << endl;

  // bst.prettyPrint();

  // start the timer
  start = clock();
  bst_avl.deleteNode(21);

  duration_Delete_AVL = (clock() - start) / (double)CLOCKS_PER_SEC;

  // bst.printTree();
  cout << "Duration to delete an element in AVL tree: " << duration_Delete_AVL
       << endl;
  // bst.prettyPrint();
  cout << "Count for Insertion: " << bst_avl.countInsert() << endl;
  cout << "Number of Comparisons Before Variable found for Deletion: "
       << bst_avl.countDelete() << endl;
  return 0;
}