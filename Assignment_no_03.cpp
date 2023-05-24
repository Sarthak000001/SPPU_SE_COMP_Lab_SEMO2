// ==============================================================
// Assignment No : 3
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================


// Problem Statement :
//  Create an inordered threaded binary search tree. Perform inorder,
//  preorder traversals without recursion and deletion of a node. Analyze
//  time and space complexity of the algorithm.


#include <iostream>
using namespace std;


class Node
{
public:
   int data;
   Node *left, *right;
   bool lthread, rthread;
   Node()
   {
       data = -1;
       left = right = NULL;
       lthread = rthread = false; // false means thread is present
   }
   Node(int val)
   {
       data = val;
       left = right = NULL;
       lthread = rthread = false;
   }
};


class Bthread
{
public:
   Node *root, *dummy;
   Bthread()
   {
       root = NULL;
       dummy = NULL;
   }
   void create()
   {
       int n, val;
       cout << "Enter the Number of node : " << endl;
       cin >> n;
       for (int i = 0; i < n; i++)
       {
           cout << "Value : ";
           cin >> val;
           this->createBtree(val);
       }
   }
   void createBtree(int d)
   {
       if (root == NULL)
       {
           dummy = new Node(1234);
           dummy->right = dummy;
           root = new Node(d);
           root->lthread = false;
           root->rthread = false;
           dummy->left = root;
           root->left = dummy;
           root->right = dummy;
           return;
       }
       else
       {
           Node *temp = new Node(d);
           Node *ptr = root;
           while (1)
           {
               if (ptr->data > d)
               {
                   if (ptr->lthread == true)
                   {
                       ptr = ptr->left;
                   }
                   else
                   {
                       ptr->lthread = true;
                       temp->left = ptr->left;
                       temp->right = ptr;
                       temp->lthread = false;
                       temp->rthread = false;
                       ptr->left = temp;
                       return;
                   }
               }
               else
               {
                   if (ptr->rthread == true)
                   {
                       ptr = ptr->right;
                   }
                   else
                   {
                       ptr->rthread = true;
                       temp->right = ptr->right;
                       temp->left = ptr;
                       temp->rthread = false;
                       temp->lthread = false;
                       ptr->right = temp;
                       return;
                   }
               }
           }
       }
   }


   Node *inoderSuccessor(Node *temp)
   {
       if (temp->rthread == false)
       {
           return temp->right;
       }
       temp = temp->right;
       while (temp->lthread == true)
       {
           temp = temp->left;
       }
       return temp;
   }
   Node *inpre(Node *temp)
   {
       if (temp->lthread == 0)
       {
           return temp->left;
       }
       temp = temp->left;
       while (temp->rthread == 1)
       {
           temp = temp->right;
       }
       return temp;
   }
   void inorder()
   {
       if (root == NULL)
       {
           cout << "tree is empty \n";
           return;
       }
       Node *p = root;
       while (p->lthread == true)
       {
           p = p->left;
       }
       while (p != dummy)
       {
           cout << p->data << " ";
           p = inoderSuccessor(p);
       }
       cout << endl;
   }


   void preoder()
   {
       if (root == NULL)
       {
           cout << "Tree is emtpy\n";
           return;
       }
       Node *p = root;
       while (p != dummy)
       {
           cout << p->data << " ";
           if (p->lthread == true)
           {
               p = p->left;
           }
           else if (p->rthread == true)
           {
               p = p->right;
           }
           else
           {
               while (p != dummy && p->rthread != 1)
               {
                   p = p->right;
               }
               if (p != dummy)
               {
                   p = p->right;
               }
           }
       }
       cout << endl;
   }


   void del()
   {
       int key;
       cout << "\nEnter key you want to delete : ";
       cin >> key;
       del_logic(root, dummy, key);
   }


   void del_logic(Node *root, Node *dummy, int key)
   {
       Node *par = dummy;
       Node *ptr = root;


       bool found = false;


       while (ptr != NULL)
       {
           if (key == ptr->data)
           {
               found = true;
               break;
           }
           par = ptr;
           if (key < ptr->data)
           {
               if (ptr->lthread == true)
               {
                   ptr = ptr->left;
               }
               else
               {
                   break;
               }
           }
           else
           {
               if (ptr->rthread == true)
               {
                   ptr = ptr->right;
               }
               else
               {
                   break;
               }
           }
       }


       if (!found)
       {
           cout << "\nKey is not present " << endl;
       }
       else if (ptr->lthread == 0 && ptr->rthread == 0)
       {
           no_child(root, par, ptr);
       }
       else if (ptr->lthread == 0 || ptr->rthread == 0)
       {
           one_child(root, par, ptr);
       }
       else
       {
           two_child(root, par, ptr);
       }
   }


   void no_child(Node *root, Node *par, Node *ptr)
   {
       if (par == NULL)
       {
           root = NULL;
       }
       else if (ptr == par->left)
       {
           par->lthread = 0;
           par->left = ptr->left;
       }
       else
       {
           par->rthread = 0;
           par->right = ptr->right;
       }
       delete ptr;
   }


   void one_child(Node *root, Node *par, Node *ptr)
   {
       Node *child, *s, *p;
       if (ptr->lthread == 1)
       {
           child = ptr->left;
       }
       else
       {
           child = ptr->right;
       }
       if (par == NULL)
       {
           root = child;
       }
       else if (ptr == par->left)
       {
           par->left = child;
       }
       else
       {
           par->right = child;
       }
       s = inoderSuccessor(ptr);
       p = inpre(ptr);
       if (ptr->lthread == 1)
       {
           p->right = s;
       }
       else if (ptr->rthread == 1)
       {
           s->left = p;
       }
       delete ptr;
   }


   void two_child(Node *root, Node *par, Node *ptr)
   {
       Node *s, *pars;
       pars = ptr;
       s = ptr->right;
       ptr->data = s->data;


       if (s->lthread == 0 && s->rthread == 0)
       {
           no_child(root, pars, s);
       }
       else if (s->lthread == 0 || s->rthread == 0)
       {
           one_child(root, pars, s);
       }
       else
       {
           two_child(root, pars, s);
       }
   }
};
int main()
{
   Bthread tree;
   // tree.create();
   // cout << "Inorder : " << endl;
   // tree.inorder();
   // cout << "Preorder : " << endl;
   // tree.preoder();


   while (1)
   {
       cout << "________________Menu Bar________________\n";
       cout << "\n\t1.Insert \n\t2.Display \n\t3.Delete \n\t4.Exit \n";
       int go;
       cout << "\tEnter your choice : ";
       cin >> go;
       cout << "_________________________________________" << endl;
       if (go == 1)
       {
           tree.create();
       }
       else if (go == 2)
       {
           cout << "Inorder : " << endl;
           tree.inorder();
           cout << "Preorder : " << endl;
           tree.preoder();
       }
       else if (go == 3)
       {
           tree.del();
       }
       else if (go == 4)
       {
           cout << "Thank You...!!\n";
           break;
       }
       else
       {
           cout << "Invalid Input \n";
       }
   }
   return 0;
}

