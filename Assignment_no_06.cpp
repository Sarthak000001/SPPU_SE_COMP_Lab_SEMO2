// ==============================================================
// Assignment No : 06
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// ==============================================================

// Problem Statement :
//   Represent a given graph using adjacency list to perform DFS and BFS.
//   Use the map of the area around the college as the graph.
//   Identify the prominent land marks as nodes and perform DFS and BFS on that.

#include <iostream>
using namespace std;
#define size 20

class Node
{
    int x;
    Node *next;
    friend class Graph;

public:
    Node(int d = 0)
    {
        this->x = d;
        next = NULL;
    }
};

class Stack
{
    int top;
    int s[size];

public:
    Stack() { top = -1; }
    void push(int val)
    {
        if (top == size - 1)
        {
            cout << "Stack Overflow" << endl;
        }
        else
        {
            top++;
            s[top] = val;
        }
    }
    int pop()
    {
        int temp;
        if (top == -1)
        {
            cout << "Stack Underflow" << endl;
        }
        else
        {
            temp = s[top];
            top--;
            return temp;
        }
    }
    bool isempty()
    {
        if (top == -1)
        {
            return 1;
        }
        return 0;
    }
};

class Queue
{
    int front, rear;
    int q[size];

public:
    Queue()
    {
        front = rear = -1;
    }
    bool isempty()
    {
        if (rear == -1 && front == -1)
        {
            return true;
        }
        return false;
    }
    bool isfull()
    {
        if (rear == size - 1)
        {
            return true;
        }
        return false;
    }
    void enqueue(int s)
    {
        if (isfull())
        {
            cout << "queue Overflow" << endl;
            return;
        }
        if (front == -1)
        {
            front = 0;
            rear = 0;
            q[front] = s;
        }
        else
        {
            rear++;
            q[rear] = s;
        }
    }
    int dequeue()
    {
        int temp;
        if (isempty())
        {
            cout << "queue underflow" << endl;
        }
        else
        {
            if (front == rear)
            {
                temp = q[front];
                front = rear = -1;
            }
            else
            {
                temp = q[front];
                front++;
            }
            return temp;
        }
    }
};

class Graph
{
    Node *adjlist[10];
    bool *visited;
    int v, e;
    string name[10];

public:
    Graph(int v, int e)
    {
        this->v = v;
        this->e = e;
        visited = new bool[v];
        for (int i = 0; i < v; i++)
        {
            adjlist[i] = NULL;
            visited[i] = false;
        }
    }

    void insert()
    {
        int src, dest;
        string n1, n2;
        cout << "Enter the names of places " << endl;
        for (int i = 0; i < v; i++)
        {
            cin >> name[i];
        }
        for (int i = 0; i < e; i++)
        {
            cout << "Enter the src and dest place " << endl;
            cin >> n1 >> n2;

            for (int i = 0; i < v; i++)
            {
                if (n1 == name[i])
                {
                    src = i;
                    break;
                }
            }
            for (int i = 0; i < v; i++)
            {
                if (n2 == name[i])
                {
                    dest = i;
                    break;
                }
            }

            Node *t1 = new Node(src);
            Node *t2 = new Node(dest);
            if (adjlist[src] == NULL)
            {
                adjlist[src] = t1;
                adjlist[src]->next = t2;
            }
            else
            {
                Node *head = adjlist[src];
                while (head->next != NULL)
                {
                    head = head->next;
                }
                head->next = t2;
            }
        }
    }
    void display()
    {
        Node *temp;
        for (int i = 0; i < v; i++)
        {
            temp = adjlist[i];
            while (temp != NULL)
            {
                cout << name[temp->x] << " --> ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    void DFS(int s)
    {
        Stack st;
        for (int i = 0; i < v; i++)
        {
            visited[i] = false;
        }

        Node *temp;
        cout << name[s] << "--> ";
        st.push(s);
        visited[s] = true;

        while (!st.isempty())
        {
            int curr = st.pop();
            if (visited[curr] == false)
            {
                cout << name[curr] << "--> ";
                visited[curr] = true;
            }

            temp = adjlist[curr];
            while (temp != NULL)
            {
                if (visited[temp->x] == false)
                {
                    st.push(temp->x);
                }
                temp = temp->next;
            }
        }
    }

    void BFS(int s)
    {
        for (int i = 0; i < v; i++)
        {
            visited[i] = false;
        }

        Queue q;
        visited[s] = true;
        q.enqueue(s);
        Node *temp;
        int curr;
        while (!q.isempty())
        {
            curr = q.dequeue();

            cout << name[curr] << "--> ";

            temp = adjlist[curr];
            while (temp != NULL)
            {

                if (visited[temp->x] == false)
                {
                    q.enqueue(temp->x);
                    visited[temp->x] = true;
                }
                temp = temp->next;
            }
        }
    }
};

int main()
{
    int v, e;
    int chc;
    cout << "Enter the no. of nodes" << endl;
    cin >> v;
    cout << "Enter the no. of edges" << endl;
    cin >> e;
    Graph g(v, e);
    do
    {
        cout << "Menu\n1.Read the graph\n2.Display the adjacency list\n3.DFS of the graph\n4.BFS of the graph\n5.Exit" << endl;
        cout << "Enter your choice: ";
        cin >> chc;
        if (chc == 1)
        {
            g.insert();
        }
        else if (chc == 2)
        {
            g.display();
        }
        else if (chc == 3)
        {
            cout << "The DFS traversal is" << endl;
            g.DFS(0);
            cout << endl;
        }
        else if (chc == 4)
        {
            cout << "The BFS traversal is" << endl;
            g.BFS(0);
            cout << endl;
        }
        else if (chc == 5)
        {
            cout << "Thank You !" << endl;
            return 0;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    } while (chc != 5);

    return 0;
}