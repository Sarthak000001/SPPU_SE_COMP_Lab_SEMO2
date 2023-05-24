// ==============================================================
// Assignment No : 2
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================

// Problem Statement :
// Beginning with an empty binary tree, Construct binary tree by inserting
// the values in the order given. After constructing a binary tree perform
// following operations on it-  Perform inorder, preorder and post order
// traversal  Change a tree so that the roles of the left and right pointers
// are swapped at every node  Find the height of tree  Copy this tree to
// another [operator=]  Count number of leaves, number of internal nodes.
// Erase all nodes in a binary tree.
// (Implement both recursive and non-recursive methods)

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
  int data;
  Node *left;
  Node *right;
  Node()
  {
    left = NULL;
    right = NULL;
  }
  Node(int d)
  {
    data = d;
    left = NULL;
    right = NULL;
  }
  friend class BST;
};

class BST
{
public:
  Node *root;
  BST() { root = NULL; }

  BST(const BST &src)
  {
    root = NULL;
    operator=(src);
  }

  void insert(int val)
  {
    if (root == NULL)
    {
      root = new Node(val);
      return;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
      Node *curr = q.front();
      q.pop();
      if (curr->left == NULL)
      {
        curr->left = new Node(val);
        break;
      }
      else
      {
        q.push(curr->left);
      }
      if (curr->right == NULL)
      {
        curr->right = new Node(val);
        break;
      }
      else
      {
        q.push(curr->right);
      }
    }
  }

  void preorder(Node *node)
  {
    if (node != NULL)
    {
      cout << node->data << " ";
      preorder(node->left);
      preorder(node->right);
    }
  }

  void printpreorder()
  {
    preorder(root);
    cout << endl;
  }

  void inorder(Node *node)
  {
    if (node != NULL)
    {
      inorder(node->left);
      cout << node->data << " ";
      inorder(node->right);
    }
  }

  void printinorder()
  {
    inorder(root);
    cout << endl;
  }

  void postorder(Node *node)
  {
    if (node != NULL)
    {
      postorder(node->left);
      postorder(node->right);
      cout << node->data << " ";
    }
  }

  void printpostorder()
  {
    postorder(root);
    cout << endl;
  }

  void SwapNode(Node *node)
  {
    if (node == NULL)
    {
      return;
    }
    swap(node->left, node->right);
    SwapNode(node->left);
    SwapNode(node->right);
  }

  void SwapNodeInBST()
  {
    SwapNode(root);
  }

  int height(Node *node)
  {
    if (node == NULL)
    {
      return 0;
    }
    int left = height(node->left);
    int right = height(node->right);
    return max(left, right) + 1;
  }

  int heightInBST()
  {
    return height(root);
  }

  int getLeafnode(Node *node)
  {
    if (node == NULL)
    {
      return 0;
    }
    if (node->left == NULL && node->right == NULL)
    {
      return 1;
    }

    return getLeafnode(node->left) + getLeafnode(node->right);
  }

  int countleaf()
  {
    return getLeafnode(root);
  }

  int countNode(Node *node)
  {
    int count = 1;
    if (node == NULL)
    {
      return 0;
    }
    count += countNode(node->left);
    count += countNode(node->right);
    return count;
  }
  // void count_internal_lead(node *p,int &internal,int &leaf){
	// 	if(p){
	// 		if(p->left || p->right){
	// 			internal++;
	// 		}
	// 		else{
	// 			leaf++;
	// 		}
	// 		count_internal_lead(p->left,internal,leaf);
	// 		count_internal_lead(p->right,internal,leaf);
	// 	}
	// }

  int countTotalNode()
  {
    if (root == NULL)
    {
      return 0;
    }
    return countNode(root);
  }

  void removeAll(Node *&node)
  {
    if (node == NULL)
    {
      return;
    }
    removeAll(node->left);
    removeAll(node->right);
    delete node;
    node = NULL;
  }

  void RemoveAllNode()
  {
    removeAll(root);
  }

  void copyTree(Node *&dest, Node *src)
  {
    if (src == NULL)
    {
      dest = NULL;
    }
    else
    {
      dest = new Node();
      dest->data = src->data;
      copyTree(dest->left, src->left);
      copyTree(dest->right, src->right);
    }
  }

  void operator=(BST *&src)
  {

    if (root != NULL)
    {
      removeAll(root);
    }
    copyTree(root, src->root);
  }
//  BST(const BST &src)
//   {
//     root = NULL;
//     operator=(src);
//   }

  void preorderIterative(Node *node)
  {
    stack<Node *> st;
    if (node == NULL)
    {
      return;
    }
    st.push(node);
    while (!st.empty())
    {
      Node *curr = st.top();
      st.pop();
      cout << curr->data << " ";
      if (curr->right != NULL)
      {
        st.push(curr->right);
      }
      if (curr->left != NULL)
      {
        st.push(curr->left);
      }
    }
  }

  void printPreorderIterative()
  {
    preorderIterative(root);
    cout << endl;
  }

  void postorderIterative(Node *node)
  {
    stack<Node *> s1;
    stack<Node *> s2;
    if (node == NULL)
    {
      cout << "Empty\n";
      return;
    }

    s1.push(node);
    while (1)
    {
      Node *curr = s1.top();
      s1.pop();
      s2.push(curr);
      if (curr->left != NULL)
      {
        s1.push(curr->left);
      }
      if (curr->right != NULL)
      {
        s1.push(curr->right);
      }
      if (s1.empty())
      {
        while (!s2.empty())
        {
          Node *temp = s2.top();
          s2.pop();
          cout << temp->data << " ";
        }
        if (s2.empty() && s1.empty())
        {
          return;
        }
      }
    }
  }

  void printPostorderIterative()
  {
    postorderIterative(root);
    cout << endl;
  }

  void inorderIterative(Node *node)
  {
    stack<Node *> st;
    if (node == NULL)
    {
      return;
    }
    Node *curr = node;
    int run = 1;
    while (run)
    {
      while (curr)
      {
        st.push(curr);
        curr = curr->left;
      }
      if (!st.empty())
      {
        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        curr = curr->right;
      }
      else
      {
        run = 0;
        return;
      }
    }
  }

  void printInorderIterative()
  {
    inorderIterative(root);
    cout << endl;
  }
};

int main()
{
  BST tree;

  int run = 1;
  while (run)
  {
    cout << "_________________Menu Bar_______________\n";
    cout << "||        1.Insert                      || \n";
    cout << "||        2.Display Inorder recursive   ||\n";
    cout << "||        3.Display Inorder Iterative   ||\n";
    cout << "||        4.Display Preorder recursive  ||\n";
    cout << "||        5.Display Preoder Iterative   ||\n";
    cout << "||        6.Display Postorder recursive ||\n";
    cout << "||        7.Display Postorder Iterative ||\n";
    cout << "||        8.Height                      ||\n";
    cout << "||        9.Total no. of internal Node  ||\n";
    cout << "||        10.Total no. of leaf Node     ||\n";
    cout << "||        11.Swap left and right Node   ||\n";
    cout << "||        12.Copy oldtree to newtree    ||\n";
    cout << "||        13.Exit                       || \n";
    cout << "___________________________________________ \n";
    int ch;
    cout << "Enter your Choice : " ;
    cin >> ch;
    cout << endl;
    if (ch == 1)
    {

      cout << "Enter no. of element : " << endl;
      int n;
      cin >> n;
      cout << "Enter value : ";
      while (n)
      {
        int val;
        cin >> val;
        tree.insert(val);
        n--;
      }
    }
    else if (ch == 2)
    {
      tree.printinorder();
    }
    else if (ch == 3)
    {
      tree.printInorderIterative();
    }
    else if (ch == 4)
    {
      tree.printpreorder();
    }
    else if (ch == 5)
    {
      tree.printPreorderIterative();
    }
    else if (ch == 6)
    {
      tree.printpostorder();
    }
    else if (ch == 7)
    {
      tree.printPostorderIterative();
    }
    else if (ch == 8)
    {
      int h = tree.heightInBST();
      cout << "Height of Binary tree : " << h << endl;
    }
    else if (ch == 9)
    {
      int c = tree.countTotalNode();
      int l = tree.countleaf();
      cout << "No. of internal node : " << c - l << endl;
    }
    else if (ch == 10)
    {
      int l = tree.countleaf();
      cout << "No. of leaf : " << l << endl;
    }
    else if (ch == 11)
    {
      tree.SwapNodeInBST();
      cout << "Inorder traversal of BInary Tree after swaping nodes : " << endl;
      tree.printinorder();
    }
    else if (ch == 12)
    {
      BST newtree;
      newtree = tree;
      cout << "New tree is created: " << endl;
      cout << "Inorder of New tree : " << endl;
      newtree.printinorder();
      cout << endl;
    }
    else if (ch == 13)
    {
      cout << "\tThank You !\t" << endl;
      run = 0;
      break;
    }
  }

  //  tree.insert(2);
  //  tree.insert(3);
  //  tree.insert(1);
  //  tree.insert(9);
  //  tree.insert(5);
  //  tree.insert(10);
  //  tree.insert(15);
  //  tree.printpreorder();
  //  tree.printPreorderIterative();
  //  tree.printpostorder();
  //  tree.printPostorderIterative();
  //  tree.printinorder();
  //  tree.printInorderIterative();

  //   tree.SwapNodeInBST();
  //   tree.printinorder();
  //   cout << "Height : " << tree.heightInBST() << endl;
  //   cout << "Count Leaf : " << tree.countleaf() << endl;
  //   int c = tree.countTotalNode();
  //   cout << "No. of Node : " << c - tree.countleaf() << endl;
  // tree.RemoveAllNode(); // erasing tree
  // tree.printinorder();
  // cout << "No. of Node : " << tree.countTotalNode() << endl;

  //   BST newtree;
  //   newtree.insert(100);
  //   newtree = tree;
  //   newtree.printinorder();
  return 0;
}
