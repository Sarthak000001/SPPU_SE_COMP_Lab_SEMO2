// ==============================================================
// Name : Sarthak Nirgude
// Roll No. : 21156
// Batch : G1
// Assignment No : 7
// ==============================================================

#include <iostream>
#include <string.h>
using namespace std;

class Graph
{
	int **graph;
	int vertices, edges;

public:
	Graph(int v, int e)
	{
		vertices = v;
		edges = e;
		graph = new int *[vertices];
		for (int i = 0; i < vertices; i++)
		{
			graph[i] = new int[vertices];
		}

		for (int i = 0; i < vertices; i++)
		{
			for (int j = 0; j < vertices; j++)
			{
				// Assign values to the
				// memory blocks created
				graph[i][j] = 0;
			}
		}
	}

	void createGraph()
	{
		int v = vertices;
		for (int i = 0; i < edges; i++)
		{
			int a, b, w;
			cout << "Enter the the 2 vertices of edge " << endl;
			cin >> a >> b;
			cout << "Enter the weight of edge" << endl;
			cin >> w;
			graph[a][b] = w;
			graph[b][a] = w;
		}
	}

	void display()
	{
		int i, j;
		cout << "\n\n"
			 << "\t"
			 << "";
		for (i = 0; i < vertices; i++)
			cout << "\t"
				 << "(" << i << ")";
		cout << "\n\n";
		for (i = 0; i < vertices; i++)
		{
			cout << "\t"
				 << "(" << i << ")";
			for (j = 0; j < vertices; j++)
			{
				cout << "\t" << graph[i][j];
			}
			cout << "\n\n";
		}
	}

	// Function to find the vertex with minimum key value
	int minKey(int key[], bool visited[])
	{
		int min = 999, minIndex; // 999 represents an Infinite value

		for (int v = 0; v < vertices; v++)
		{
			if (visited[v] == false && key[v] < min)
			{
				// vertex should not be visited
				min = key[v];
				minIndex = v;
			}
		}
		return minIndex;
	}

	// Function to print the final MST stored in parent[]
	void printMST(int parent[])
	{
		int minCost = 0;
		cout << "Edge \tWeight\n";
		for (int i = 1; i < vertices; i++)
		{
			cout << parent[i] << " - " << i << " \t" << graph[i][parent[i]] << " \n";
			minCost += graph[i][parent[i]];
		}
		cout << "Total cost is - " << minCost;
	}

	// Function to find the MST using adjacency graph matrix representation
	void find_MST()
	{
		int parent[vertices], key[vertices];
		bool visited[vertices];

		// Initialize all the arrays
		for (int i = 0; i < vertices; i++)
		{
			key[i] = 9999999; // 999 represents an Infinite value
			visited[i] = false;
			parent[i] = -1;
		}

		key[0] = 0;		// Include first vertex in MST by setting its key vaue to 0.
		parent[0] = -1; // First node is always root of MST

		// The MST will have maximum V-1 vertices
		for (int x = 0; x < vertices - 1; x++)
		{
			// Finding the minimum key vertex from the
			// set of vertices not yet included in MST
			int u = minKey(key, visited);

			visited[u] = true; // Add the minimum key vertex to the MST

			// Update key and parent arrays
			for (int v = 0; v < vertices; v++)
			{
				// graph[u][v] is non zero only for adjacent vertices of u
				// visited[v] is false for vertices not yet included in MST
				// key[] gets updated only if cost[u][v] is smaller than key[v]
				if (graph[u][v] != 0 && visited[v] == false && graph[u][v] < key[v])
				{
					parent[v] = u;
					key[v] = graph[u][v];
				}
			}
		}

		// print the final MST
		printMST(parent);
	}
	int find(int i, int parent[])
	{
		while (parent[i] != i)
		{
			i = parent[i];
		}
		return i;
	}
	void union1(int i, int j, int parent[])
	{
		int a = find(i, parent);
		int b = find(j, parent);
		parent[a] = b;
	}
	void Kruskal()
	{
		int parent[vertices];
		int minCost = 0;

		for (int i = 0; i < vertices; i++)
		{
			parent[i] = i;
		}
		int edgeCount = 0;
		while (edgeCount < vertices - 1)
		{
			int min = INT_MAX, a = -1, b = -1;
			for (int i = 0; i < vertices; i++)
			{
				for (int j = 0; j < vertices; j++)
				{
					if (find(i, parent) != find(j, parent) && graph[i][j] < min && graph[i][j] != 0)
					{
						min = graph[i][j];
						a = i;
						b = j;
					}
				}
			}

			union1(a, b, parent);
			edgeCount++;
			cout << "\nEdge " << edgeCount << " | " << a << " : " << b << " | ";
			cout << "Cost = " << min << endl;

			minCost += min;
		}
		cout << "Total cost of MST " << minCost << endl;
	}
};

int main()
{
	int v, e;
	cout << "Enter total no of vertices and total no of edges" << endl;
	cin >> v >> e;
	Graph g1(v, e);
	char c = 'y';
	while (c != 'n')
	{
		cout << "-------------------------------------------------" << endl;
		cout << "1. Create Graph" << endl;
		cout << "2. Display Graph" << endl;
		cout << "3. Find MST of Graph using prim's algorithm" << endl;
		cout << "-------------------------------------------------" << endl;
		int ch;
		cout << "Enter your choice" << endl;
		cin >> ch;
		if (ch == 1)
		{
			g1.createGraph();
		}
		else if (ch == 2)
		{
			g1.display();
		}
		else if (ch == 3)
		{
			g1.find_MST();
			cout << endl;
			g1.Kruskal();
		}
		else
		{
			cout << "You have eneterd a wrong choice" << endl;
		}
		cout << "Do you want to continue (y/n)" << endl;
		cin >> c;
	}
	return 0;
}

/* example
0,1 - 4
0,5 - 2
1,2 - 6
1,5 - 3
2,3 - 3
2,5 - 1
4,3 - 2

MST total cost is 11
*/