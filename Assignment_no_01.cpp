// ==============================================================
// Assignment No : 1
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================

// Problem Statement :
//  Beginning with an empty binary search tree. Construct the binary search tree by
//  inserting the values in given order. After constructing binary search tree perform
//  following operations
//  1) Insert a new node
//   2) Find numbers of node in longest path
//  3) Minimum and maximum data value found in tree
//  4) Change a tree so that the roles of the left and right pointers are swapped at every node
//   5)Search an element

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;
    Node(int d)
    {
        this->data = d;
        left = NULL;
        right = NULL;
    }
};
class BST
{
public:
    Node *root;
    BST()
    {
        root = NULL;
    }
    // Inserting data in the BST
    Node *insertBST(Node *rt, int val)
    {
        // base case
        if (rt == NULL)
        {
            return new Node(val);
        }
        if (val <= rt->data)
        { // left side me insert karo
            rt->left = insertBST(rt->left, val);
        }
        else if (val > rt->data)
        {
            // val > root->data
            rt->right = insertBST(rt->right, val);
        }

        // return
        return rt;
    }

    // Find numbers of node in longest path
    int longestPathInBST(Node *root)
    {
        int maxCount = 0;
        stack<pair<Node *, int>> st;
        if (root != NULL)
        {
            st.push(make_pair(root, 0));
        }

        while (!st.empty())
        {
            Node *curr = st.top().first;
            int currCount = st.top().second;
            st.pop();
            //   maxCount = max(maxCount,currCount);
            maxCount < currCount ? maxCount = currCount : maxCount = maxCount;
            if (curr->left != NULL)
            {
                st.push(make_pair(curr->left, currCount + 1));
            }
            if (curr->right != NULL)
            {
                st.push(make_pair(curr->right, currCount + 1));
            }
        }

        return maxCount;
    }

    // Display function for BST
    void inorder(Node *rt)
    { // base case
        if (rt == NULL)
        {
            return;
        }
        inorder(rt->left);
        cout << rt->data << " ";
        inorder(rt->right);
    }
    void preorder(Node *rt)
    { // base case
        if (rt == NULL)
        {
            return;
        }
        cout << rt->data << " ";
        inorder(rt->left);
        inorder(rt->right);
    }
    void postorder(Node *rt)
    { // base case
        if (rt == NULL)
        {
            return;
        }
        inorder(rt->left);
        inorder(rt->right);
        cout << rt->data << " ";
    }

    int Minvalue(Node *rt)
    { // return minimum ele.
        Node *temp = root;
        while (temp->left != NULL)
        {
            temp = temp->left;
        }
        return temp->data;
    }
    int Maxvalue(Node *rt)
    { // return maximum ele.
        Node *temp = root;
        while (temp->right != NULL)
        {
            temp = temp->right;
        }
        return temp->data;
    }

    void SwapNodeInBST(Node *root)
    {
        // base case
        if (root == NULL)
        {
            return;
        }
        // swaping left and right node of the BST
        swap(root->left, root->right);
        SwapNodeInBST(root->left);
        SwapNodeInBST(root->right);
    }

    Node *SearchInbst(Node *root, int key)
    { // search for the key in the BST
        if (root == NULL)
        {
            return NULL;
        }
        if (root->data == key)
        {
            return root;
        }
        if (root->data > key)
        {
            return SearchInbst(root->left, key);
        }

        return SearchInbst(root->right, key);
    }

    // Delete function
    Node *finalright(Node *root)
    {
        Node *curr = root;
        while (curr->right != NULL)
        {
            curr = curr->right;
        }
        return curr;
    }
    Node *helper(Node *root)
    {
        if (root->left == NULL)
        {
            return root->right;
        }
        else if (root->right == NULL)
        {
            return root->left;
        }
        else
        {
            Node *rightChild = root->right;
            Node *lastRightChild = finalright(root->left);
            lastRightChild->right = rightChild;
            return root->left;
        }
    }
    Node *deleteNode(Node *root, int key)
    {

        if (root == NULL)
        {
            return NULL;
        }

        if (root->data == key)
        {
            return helper(root);
        }

        Node *dummy = root;
        while (root != NULL)
        {
            if (root->data > key)
            {
                if (root->left != NULL && root->left->data == key)
                {
                    root->left = helper(root->left);
                }
                else
                {
                    root = root->left;
                }
            }
            else
            {
                if (root->right != NULL && root->right->data == key)
                {
                    root->right = helper(root->right);
                }
                else
                {
                    root = root->right;
                }
            }
        }

        return dummy;
    }
};

int main()
{
    BST obj;
    // Node *root = NULL;

    // example : 50 30 25 20 35 60 55 51 57 80 90

    cout << "________________Menu Bar______________\n";
    while (1)
    {
        cout << "1.Insert a new node\n2.Find numbers of node in longest path\n3.Min & Max value in tree\n4.Delete a node in BST\n5.Search an element\n6.Display\n7.Swapped an every node in BST\n8.Exit\n";
        cout << "Enter your choice : " << endl;
        int c;
        cin >> c;
        if (c == 1)
        {

            int n;
            cout << "Enter no. of element : " << endl;
            cin >> n;
            cout << "Enter the value : ";
            while (n > 0)
            {
                int val;
                cin >> val;
                if (obj.root == NULL)
                {
                   obj.root = obj.insertBST(obj.root, val);
                }
                else
                {

                    obj.insertBST(obj.root, val);
                }
                n--;
            }
            cout << endl;
        }
        else if (c == 2)
        {

            cout << "The Numbers of node in Longest Path : " << obj.longestPathInBST(obj.root) << endl;
        }
        else if (c == 3)
        {
            cout << "\nMinimum : " << obj.Minvalue(obj.root);          // displaying Minimum ele. of BST
            cout << "\nMaximum  : " << obj.Maxvalue(obj.root) << endl; // displaying Maximum ele. of BST
        }
        else if (c == 4)
        {
            cout << "\nEnter the value of Node  : " << endl;
            int val;
            cin >> val;
            Node *temp = obj.deleteNode(obj.root, val);
            cout << "deleted node : " << temp->data << endl;
            obj.inorder(obj.root);
            cout << endl;
        }
        else if (c == 5)
        {
            int key;
            cout << "\nEnter the Element you want to Search in BST : ";
            cin >> key;
            // Searching for the ele. in the BST
            if (obj.SearchInbst(obj.root, key) == NULL)
            {
                cout << "Element doesn't present in the BST\n";
            }
            else
            {
                cout << "Element is present in the BST\n";
            }
            cout << endl;
        }
        else if (c == 6)
        {
            cout << "\nInorder : " << endl;
            obj.inorder(obj.root);
            cout << "\nPreorder : " << endl;
            obj.preorder(obj.root);
            cout << "\nPostorder : " << endl;
            obj.postorder(obj.root);
            cout << endl;
        }
        else if (c == 7)
        {
            // Swaping the left and right nodes of BST
            obj.SwapNodeInBST(obj.root);
            cout << "\nAfter Swapping :" << endl;
            obj.inorder(obj.root); // displaying ele. after swapping

            cout << endl;
        }
        else if (c == 8)
        {
            cout << "Thank you !\n";
            break;
        }
        else
        {
            cout << "\nInvalid Input\n";
        }
    }
    return 0;
}
