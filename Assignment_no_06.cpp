// ==============================================================
// Assignment No : 06
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================

#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

class Node
{
    int val;
    string vertexName;
    Node *next;

public:
    Node(int n, string name)
    {
        val = n;
        vertexName = name;
        next = NULL;
    }
    friend class LL;
    friend class Graph;
};

class LL
{
public:
    Node *head;
    string mainVertexName;
    int mainVal;
    LL()
    {
        mainVertexName = "";
        mainVal = 0;
        head = NULL;
    }

    void insertEnd(int num, string name)
    {
        Node *temp = new Node(num, name);
        Node *p = NULL;

        if (head == NULL)
        {
            head = temp;
        }
        else
        {
            p = head;

            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = temp;
        }
    }

    void displayList()
    {
        Node *p = head;
        if (head == NULL)
        {
            return;
        }
        while (p != NULL)
        {
            cout << p->vertexName << " : " << p->val << ":->";
            p = p->next;
        }
    }

    friend class Graph;
};

class Graph
{
    int totalV;
    LL *tableVertex;
    unordered_map<int, bool> visitedDfs;

public:
    Graph(int n)
    {
        this->totalV = n;
        tableVertex = new LL[n];
    }

    void InsertGraph()
    {
        // 1st -> name of main vertex
        // 2nd -> adjacent neighbours of each main vertex

        for (int i = 0; i < this->totalV; i++)
        {
            string name_;
            cout << "Enter name of " << i << " vertex : ";
            cin >> name_;

            tableVertex[i].mainVertexName = name_;
            tableVertex[i].mainVal = i;
        }

        // for adjacent Vertices
        for (int i = 0; i < this->totalV; i++)
        {

            int adjnum;
            cout << "Enter number of adjacent vertices of {" << tableVertex[i].mainVertexName << "}:";
            cin >> adjnum;
            for (int j = 0; j < adjnum; j++)
            {
                string adjname_;
                cout << "Enter name of " << i << " neighbour : ";
                cin >> adjname_;

                // find value of adjname vertex;

                int k = 0;
                bool isFound = false;
                while (k <= totalV)
                {
                    if (tableVertex[k].mainVertexName == adjname_)
                    {
                        isFound = true;
                        break;
                    }
                    k++;
                }

                // insert k as value
                if (isFound)
                {
                    tableVertex[i].insertEnd(k, adjname_);
                }
                else
                {
                    cout << "Invalid Input" << endl;
                }
            }
        }
    }

    void displayGraph()
    {
        for (int i = 0; i < totalV; i++)
        {

            cout << "[ " << tableVertex[i].mainVertexName << " : " << tableVertex[i].mainVal << "]";
            tableVertex[i].displayList();
            cout << endl;
        }
    }

    void BFS(string vertexStart)
    {
        unordered_map<int, bool> visited;
        queue<int> q;
        // check whether vertexStart is present or not
        int k = 0, startVal;
        bool isFound = false;
        while (k <= totalV)
        {
            if (tableVertex[k].mainVertexName == vertexStart)
            {
                isFound = true;
                startVal = tableVertex[k].mainVal;
                break;
            }
            k++;
        }

        // insert startVal as value
        if (isFound)
        {
            q.push(startVal);
            visited[startVal] = 1;
            while (!q.empty())
            {
                int frontNode = q.front();
                q.pop();
                // print node name;
                cout << tableVertex[frontNode].mainVertexName << " ";
                // traverse neighbours
                Node *curr = tableVertex[frontNode].head;
                while (curr != NULL)
                {
                    if (!visited[curr->val])
                    {
                        q.push(curr->val);
                        visited[curr->val] = true;
                    }
                    curr = curr->next;
                }
            }
        }
        else
        {
            cout << "Invalid Input\n";
        }
    }

    void subDfs(int val)
    {
        cout << tableVertex[val].mainVertexName << " ";
        visitedDfs[val] = true;

        // recursive call for each neighbour
        Node *curr = tableVertex[val].head;
        while (curr != NULL)
        {
            if (!visitedDfs[curr->val])
            {
                subDfs(curr->val);
            }
            curr = curr->next;
        }
    }
    void DFS(string name)
    {
        // check node and get its value
        int k = 0, startVal;
        bool isFound = false;
        while (k <= totalV)
        {
            if (tableVertex[k].mainVertexName == name)
            {
                isFound = true;
                startVal = tableVertex[k].mainVal;
                break;
            }
        }

        if (!visitedDfs[startVal])
        {
            subDfs(startVal);
        }
    }
};

int main()
{
    int N;
    cout << "Enter no. of nodes : ";
    cin >> N;

    Graph g(N);

    g.InsertGraph();

    while (1)
    {
        string str_;
        cout << "\n1.Display\n2.BFS\n3.DFS\n4.Exit\n";
        int c;
        cin >> c;
        if (c == 1)
        {
            g.displayGraph();
            cout << endl;
        }
        else if (c == 2)
        {
            cout << "Enter vertex name to start BFS from : \n";
            cin >> str_;
            g.BFS(str_);
        }
        else if (c == 3)
        {
            cout << "Enter the vertex name to start DFS from : \n";
            cin >> str_;
            g.DFS(str_);
        }
        else
        {
            cout << "\nThank you !\n";
            break;
        }
    }

    return 0;
}