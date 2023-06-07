#include <iostream>
using namespace std;

class Node
{
    int data;
    Node *left, *right;
    friend class OBST;

public:
    Node()
    {
        left = right = NULL;
    }
    Node(int d)
    {
        this->data = d;
        left = right = NULL;
    }
};

class OBST
{
    Node *root;
    float *p, *q;
    int *key;
    double **w, **c, **r;
    int n;

public:
    OBST() { root = NULL; }
    OBST(int size)
    {
        this->root = NULL;
        this->n = size;
        key = new int[n + 1]; // 0 -> no value present
        p = new float[n];
        q = new float[n + 1];
        w = new double *[n + 1];
        c = new double *[n + 1];
        r = new double *[n + 1];
        for (int i = 0; i <= n; i++)
        {
            w[i] = new double[n + 1];
            c[i] = new double[n + 1];
            r[i] = new double[n + 1];
        }
        for (int i = 0; i <= n; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                w[i][j] = 0;
                c[i][j] = 0;
                r[i][j] = 0;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            cout << "Enter the key : ";
            cin >> key[i];
        }
        cout << "\nEnter the Successful Probability:\n";
        for (int i = 0; i < n; i++)
        {
            cout << "p" << i + 1 << " ";
            cin >> p[i];
        }
        cout << "\nEnter the Unsuccessful Probability:\n";
        for (int i = 0; i <= n; i++)
        {
            cout << "q" << i << " ";
            cin >> q[i];
        }
    }

    void display()
    {
        for (int i = 0; i <= n; i++)
        {

            for (int j = 0; j <= n; j++)
            {

                cout << "[" << w[i][j] << "," << c[i][j] << "," << r[i][j] << "]"
                     << "   ";
            }
            cout << "\n";
        }
    }

    void calculate_wt()
    {
        for (int i = 0; i < n; i++)
        {
            // diagonal i.e. j-i = 0
            w[i][i] = q[i];
            r[i][i] = c[i][i] = 0;

            // for just above diagonal i.e. j-i = 1
            w[i][i + 1] = p[i] + q[i] + q[i + 1];
            r[i][i + 1] = i + 1;
            c[i][i + 1] = w[i][i + 1];
        }
        // edge case
        w[n][n] = q[n];
        r[n][n] = c[n][n] = 0;
        for (int m = 2; m <= n; m++) // subtree size (subtrees with size 0 & 1 are already handled)
        {
            for (int i = 0; i <= n - m; i++) // starting key
            {
                double min = 9999; // minimum cost
                int j = i + m;     // ending key
                int k = 0;         // root of optimal subtree

                w[i][j] = w[i][j - 1] + p[j-1] + q[j]; // wt of subtree with keys i to j
                for (int it = i + 1; it <= j; it++)      // iterate over possible roots
                {
                    double sum = c[i][it - 1] + c[it][j]; // cost(left subtree) + cost(right subtree)
                    if (sum < min)
                    {
                        min = sum; // update minimum cost
                        k = it;    // update optimal root
                    }
                }
                c[i][j] = w[i][j] + c[i][k - 1] + c[k][j]; // cost of subtree with keys i to j
                r[i][j] = k;                               // root of subtree with keys i to j
            }
        }
        root = buildTree(0, n);
    }
    Node *buildTree(int i, int j)
    {
        if (i != j)
        {
            int k = r[i][j];
            Node *node = new Node(key[k]);
            node->left = buildTree(i, k - 1);
            node->right = buildTree(k, j);
            return node;
        }
        else
        {
            return NULL;
        }
    }
    void inorder(Node *node)
    {
        if (node == NULL)
        {
            return;
        }
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void printInorder()
    {
        inorder(root);
    }
};

int main()
{
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;
    OBST tree(n);
    tree.calculate_wt();
    tree.display();
    cout << "Inorder Traversal: ";
    tree.printInorder();
    cout << endl;
    return 0;
}

/*
example : 
key = {10,20,30,40};
p = {3,3,1,1};
q = {2,3,1,1,1};

final
w -> 16
cost -> 32
root -> 2
*/