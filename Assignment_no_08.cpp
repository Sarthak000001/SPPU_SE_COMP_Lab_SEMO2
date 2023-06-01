// ==============================================================
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// Assignment No : 8
// ==============================================================

// Problem Statement :
// Given sequence k = k1 <k2 < ... < kn of n sorted keys, with a search
// probability pi for each key ki . Build the Binary search tree that has
// the least search cost given the access probability for each key.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int MAX = 200;

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
    Node(int data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
    friend class OBST;
};

class OBST
{
public:
    int cost[MAX][MAX];
    int root[MAX][MAX];
    int *key;
    int *freq;
    int size;
    Node *start, *start2;
    OBST()
    {
        start = NULL;
        start2 = NULL;
    }
    OBST(int n)
    {
        start = NULL;
        start2 = NULL;
        this->size = n;
        key = new int[size];
        freq = new int[size];
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                cost[i][j] = 0;
                root[i][j] = 0;
            }
        }
    }
    void getValue()
    {
        int k_, f_;
        for (int i = 0; i < this->size; i++)
        {
            cout << "\nEnter value of key : ";
            cin >> k_;
            key[i] = k_;
            cout << "\nEnter frequency of {" << k_ << "} : ";
            cin >> f_;
            freq[i] = f_;
        }
    }
    int getSum(int i, int j)
    {
        int s = 0;
        for (int k = i; k <= j; k++)
            s += freq[k];
        return s;
    }

    int optCost(int i, int j)
    {

        if (j < i)
        {
            return 0;
        }

        if (cost[i][j])
        {
            return cost[i][j];
        }

        int f_sum = getSum(i, j);

        int mini = INT_MAX;

        for (int k = i; k <= j; k++)
        {
            int c = optCost(i, k - 1) + optCost(k + 1, j) + f_sum;
            if (c < mini)
            {
                mini = c;
                root[i][j] = k;
                cost[i][j] = c;
            }
        }

        return cost[i][j];
    }
    void getCost(int n)
    {
        cout << optCost(0, n - 1) << endl;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                cout << cost[i][j] << "," << root[i][j] << "\t";
            }
            cout << "\n";
        }
    }

     //recursively
    void buildTreeUtil(Node *&currNode, int i, int j) 
    {
        if (i > j)
            return;

        int l = root[i][j];
        currNode = new Node(root[l][j]);

        buildTreeUtil(currNode->left, i, l - 1);
        buildTreeUtil(currNode->right, l + 1, j);
    }

    void buildStart()
    {
        buildTreeUtil(start2, 0, size - 1);
    }

    void buildTree()
    {

        stack<pair<Node *, pair<int, int>>> st;
        if (start == NULL)
        {
            start = new Node(root[0][size - 1]);
            st.push(make_pair(start, make_pair(0, size - 1)));
        }
        while (!st.empty())
        {
            pair<Node *, pair<int, int>> val = st.top();
            st.pop();
            int i = val.second.first;
            int j = val.second.second;
            int l = root[i][j];
            Node *u = val.first;
            if (l < j)
            {
                // build the right subtree
                Node *v = new Node(root[l + 1][j]);
                u->right = v;
                st.push(make_pair(v, make_pair(l + 1, j)));
            }
            if (i < l)
            {
                // build left tree
                Node *v = new Node(root[i][l - 1]);
                u->left = v;
                st.push(make_pair(v, make_pair(i, l - 1)));
            }
        }
    }

    void printLevelOrder(Node *root)
    {
        if (root == NULL)
            return;
        queue<Node *> q;

        q.push(root);

        while (q.empty() == false)
        {

            Node *node = q.front();
            cout << key[node->data] << " ";
            q.pop();

            if (node->left != NULL)
                q.push(node->left);

            if (node->right != NULL)
                q.push(node->right);
        }
    }
    void printlevel1()
    {
        printLevelOrder(start);
    }
    void printlevel2()
    {
        printLevelOrder(start2);
    }
};

int main()
{

    int n;
    cout << "Enter the no. of keys: ";
    cin >> n;
    OBST tree(n);
    tree.getValue();
    tree.getCost(n);
    cout << "First \n";
    tree.buildTree();
    tree.printlevel1();
    cout << "\nSecond \n";
    tree.buildStart();
    tree.printlevel2();
    return 0;
}

// ex1
//  keys[] = {10, 12}, freq[] = {34, 50}
//  The cost of tree I is 34*1 + 50*2 = 134
//  The cost of tree II is 50*1 + 34*2 = 118
// ex2
//  keys[] = {10, 12, 20}, freq[] = {34, 8, 50}
//  1*50 + 2*34 + 3*8 = 142