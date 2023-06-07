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


#include <iostream>
#include <queue>
#include <stack>
using namespace std;

class Node
{
    int data;
    Node *left, *right;
    friend class BT;

public:
    Node(int d = 0)
    {
        data = d;
        left = right = NULL;
    }
};

class BT
{
    Node *root;

public:
    BT() : root(NULL) {}

    void insertLevelwise()
    {
        int d;
        if (root == NULL)
        {
            cout << "Enter the data for creation of root " << endl;
            cin >> d;
            root = new Node(d);
        }
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();

            cout << "Enter data for inserting in left of " << curr->data << endl;
            cin >> d;
            cout << endl;
            if (d != -1)
            {
                Node *newNode = new Node(d);
                curr->left = newNode;
                q.push(newNode);
            }

            cout << "Enter data for inserting in right of " << curr->data << endl;
            cin >> d;
            cout << endl;
            if (d != -1)
            {
                Node *newNode = new Node(d);
                curr->right = newNode;
                q.push(newNode);
            }
        }
    }
    // level wise traversal
    void levelTraversal()
    {
        if (root == NULL)
        {
            return;
        }
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int lvl = q.size();
            for (int i = 0; i < lvl; i++)
            {
                Node *curr = q.front();
                q.pop();
                cout << curr->data << " ";

                if (curr->left)
                {
                    q.push(curr->left);
                }
                if (curr->right)
                {
                    q.push(curr->right);
                }
            }
        }
    }
    // recursive travesal
    void inorderR(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        inorderR(node->left);
        cout << node->data << " ";
        inorderR(node->right);
    }
    void printinorderR()
    {
        cout << "Inorder Recursively " << endl;
        inorderR(root);
    }
    void preorderR(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        cout << node->data << " ";
        preorderR(node->left);
        preorderR(node->right);
    }
    void printpreorderR()
    {
        cout << "Preoder Recursively " << endl;
        preorderR(root);
    }
    void postorderR(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        postorderR(node->left);
        postorderR(node->right);
        cout << node->data << " ";
    }
    void printpostorderR()
    {
        cout << "Postorder Recursively " << endl;
        postorderR(root);
    }
    // iterative traversal
    void inorderI(Node *node)
    {
        if (node == NULL)
        {
            return;
        }

        stack<Node *> st;
        Node *curr = node;

        while (1)
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
                break;
                return;
            }
        }
    }
    void printinorderIter()
    {
        cout << "Inorder Iteratively " << endl;
        inorderI(root);
    }
    void preoderI(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        stack<Node *> st;
        st.push(node);

        while (!st.empty())
        {
            Node *curr = st.top();
            st.pop();
            cout << curr->data << " ";

            if (curr->right)
            {
                st.push(curr->right);
            }
            if (curr->left)
            {
                st.push(curr->left);
            }
        }
    }
    void printpreoderIter()
    {
        cout << "Preoder Iteratively " << endl;
        preoderI(root);
    }
    void postorderI(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        stack<Node *> s1;
        stack<Node *> s2;
        s1.push(node);
        while (!s1.empty())
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
        }
        while (!s2.empty())
        {
            Node *temp = s2.top();
            s2.pop();
            cout << temp->data << " ";
        }
    }
    void printposterorderiter()
    {
        cout << "Postorder Iteratively " << endl;
        postorderR(root);
    }

    Node *copytree(Node *t)
    {
        Node *cp = NULL;
        if (t != NULL)
        {
            cp = new Node(t->data);
            cp->left = copytree(t->left);
            cp->right = copytree(t->right);
        }
        return cp;
    }
    void operator=(BT &obj)
    {
        root = copytree(obj.root);
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

        return 1 + max(left, right);
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

    int countNonLeafNodes(Node *node)
    {

        if (node == NULL)
            return 0;
        if (node->left == NULL && node->right == NULL)
            return 0;

        int l = countNonLeafNodes(node->left);
        int r = countNonLeafNodes(node->right);

        return 1 + l + r;
    }

    int getInternalNode()
    {
        return countNonLeafNodes(root);
    }
};

int main()
{
    BT tree;

    int run = 1;
    while (run)
    {
        cout << "\n_________________Menu Bar_______________\n";
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
        cout << "Enter your Choice : ";
        cin >> ch;
        cout << endl;
        if (ch == 1)
        {

            tree.insertLevelwise();
        }
        else if (ch == 2)
        {
            tree.printinorderR();
        }
        else if (ch == 3)
        {
            tree.printinorderIter();
        }
        else if (ch == 4)
        {
            tree.printpreorderR();
        }
        else if (ch == 5)
        {
            tree.printpreoderIter();
        }
        else if (ch == 6)
        {
            tree.printpostorderR();
        }
        else if (ch == 7)
        {
            tree.printposterorderiter();
        }
        else if (ch == 8)
        {
            int h = tree.heightInBST();
            cout << "Height of Binary tree : " << h << endl;
        }
        else if (ch == 9)
        {
            int internal = tree.getInternalNode();
            cout << "Total no. of internal Node " << internal << endl;
        }
        else if (ch == 10)
        {
            int l = tree.countleaf();
            cout << "Total no. of leaf node: " << l << endl;
        }
        else if (ch == 11)
        {
            tree.SwapNodeInBST();
            cout << "level traversal of Binary Tree after swaping nodes : " << endl;
            tree.levelTraversal();
        }
        else if (ch == 12)
        {
            BT newtree;
            newtree = tree;
            cout << "New tree is created: " << endl;
            cout << "levelTraversal of New tree : " << endl;
            newtree.levelTraversal();
            cout << endl;
        }
        else if (ch == 13)
        {
            cout << "\tThank You !\t" << endl;
            run = 0;
            break;
        }
        else
        {
            cout << "\tInvalid Input \t" << endl;
        }
    }
    return 0;
}