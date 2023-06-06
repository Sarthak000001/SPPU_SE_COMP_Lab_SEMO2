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
    int data;
    Node *left, *right;
    int lbit, rbit; // 0->thread present,1->link present
    friend class BT;

public:
    Node(int data = 0)
    {
        this->data = data;
        left = right = NULL;
        lbit = rbit = 0;
    }
};

class BT
{
    Node *root, *head;

public:
    BT()
    {
        root = NULL;
        head = NULL; // used as dummey node
    }
    void create()
    {
        char ch;
        do
        {
            Node *temp = new Node(); 
            cout << "Enter the Node value : " << endl;
            cin >> temp->data;

            if (root == NULL)
            {
                root = temp;
                head = new Node(9999);
                head->right = head;
                head->left = root;
                root->left = head;
                root->right = head;
            }
            else
            {
                insert(temp, root);
            }
            cout << "Do you want to continue : (y/n)" << endl;
            cin >> ch;

        } while (ch == 'y' || ch == 'Y');
    }
    void insert(Node *temp, Node *node)
    {
        if (temp->data < node->data)
        {
            if (node->lbit == 0)
            {
                temp->left = node->left;
                node->left = temp;
                node->lbit = 1;
                temp->right = node;
            }
            else
            {
                node = node->left;
                insert(temp, node);
            }
        }
        if (temp->data > node->data)
        {
            if (node->rbit == 0)
            {
                temp->right = node->right;
                node->right = temp;
                node->rbit = 1;
                temp->left = node;
            }
            else
            {
                node = node->right;
                insert(temp, node);
            }
        }
    }
    void inorder()
    {
        if (root == NULL)
        {
            return;
        }
        Node *t = root;
        do
        {
            while (t->lbit != 0)
            {
                t = t->left;
            }

            cout << t->data << " ";

            while (t->rbit == 0)
            {
                t = t->right;
                if (t == head)
                {
                    return;
                }
                cout << t->data << " ";
            }
            t = t->right;
        } while (t != head);
    }
    void preorder()
    {
        if (root == NULL)
        {
            return;
        }
        Node *t = root;
        do
        {
            while (t->lbit != 0)
            {
                cout << t->data << " ";
                t = t->left;
            }
            cout << t->data << " ";
            while (t->rbit == 0)
            {
                t = t->right;
                if(t == head){return;}
            }
            t = t->right;
        } while (t != head);
    }
    Node *inSucc(Node *temp)
    {
        if (temp->rbit == 0)
        {
            return temp->right;
        }

        temp = temp->right;
        while (temp->lbit != 0)
        {
            temp = temp->left;
        }
        return temp;
    }
    Node *inPres(Node *temp)
    {
        if (temp->lbit == 0)
        {
            return temp->left;
        }

        temp = temp->left;
        while (temp->rbit != 0)
        {
            temp = temp->right;
        }
        return temp;
    }
    void deleteBT(int key)
    {
        if (root == NULL)
        {
            return;
        }
        Node *par = head; // parent initially pointing to dummey node
        Node *ptr = root; // ptr pointing to root of tree

        int found = false;

        while (!found)
        {
            if (ptr->data == key)
            {
                found = true;
                break;
            }
            par = ptr;

            if (key < ptr->data)
            {
                if (ptr->lbit == 1)
                {  //if link is present on left side
                    ptr = ptr->left;
                }
                else
                {
                  //no link is present on left side i.e.thread is present
                    break;
                }
            }
            else
            {
                if (ptr->rbit == 1)
                {
                    //if link is present on righ side
                    ptr = ptr->right;
                }
                else
                {
                    //no link is present on right side i.e.thread is present
                    break;
                }
            }
        }

        if (!found)
        {
            cout << "key does not found " << endl;
            return;
        }
        else if (ptr->lbit == 0 && ptr->rbit == 0)
        {
            // no child case
            noChild(ptr, par);
        }else if(ptr->lbit == 0 || ptr->rbit == 0)
        {
            //one child case
            oneChild(ptr,par);
        }else{
            //two child case
            twoChild(ptr,par);
        }
    }
    void noChild(Node *ptr, Node *par)
    {
        if (par->left == ptr)
        {
            //node to be delete is present on left side of parent
            par->left = ptr->left;
            par->lbit = ptr->lbit;
        }
        else
        {
            //node to be delete is present on right side of parent
            par->right = ptr->right;
            par->rbit = ptr->rbit;
        }
       delete ptr;
    }
    void oneChild(Node *ptr, Node *par)
    {
        Node *child,*s,*p;
        //child position respective to the ptr position
        if(ptr->lbit == 1)
        {
            child = ptr->left;
        }else{
            child = ptr->right;
        }
     
        //ptr position respective to the par position   
        if(par->left == ptr)
        {
            par->left = child;
        }else{
            par->right = child;
        }

        //adjust thread of ptr
        s = inSucc(ptr);
        p = inPres(ptr);
        
        if(ptr->lbit == 1)
        {
            p->right = s;
        }else{
            s->left = p;
        }

        delete ptr;
    }
    void twoChild(Node *ptr, Node *par)
    {
        Node* pars,*s;
        pars = ptr; 
        s = ptr->right;
        ptr->data = s->data;
       
       if(s->lbit == 0 && s->rbit == 0)
       {
          //No child case
          noChild(s,pars);
       }else if(s->lbit == 0 || s->rbit == 0)
       {
          //One child case
          oneChild(s,pars);
       }else{
          //Two child case
          twoChild(s,pars);
       }

    }
};

int main()
{

    BT tree;
    while (1)
    {
        cout << "\n1.Insert \n2.Inorder \n3.Preoder \n4.Delete";
        cout << "\nEnter your Option :" << endl;
        int c;
        cin >> c;
        if (c == 1)
        {
            tree.create();
        }
        else if (c == 2)
        {
            tree.inorder();
        }
        else if (c == 3)
        {
            tree.preorder();
        }else if(c == 4)
        {
            cout << "Enter the value you want to delete : " << endl;
            int k_; cin >> k_;
            tree.deleteBT(k_);
        }
        else
        {
            cout << "Thank You !" << endl;
            break;
        }
    }
    return 0;
}