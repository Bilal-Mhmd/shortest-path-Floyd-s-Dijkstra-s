#include <iostream>
#include <climits>
#include <iomanip>
#include <fstream>
#include<cstdlib>

using namespace std;
//num of rows/columns is n
//you can change the const n upon of your file
const int n = 8;

//////// Table to store FLOYD's Algorithm  ////////
struct FloydS {	
	int dist[n][n] = {0};
	int path[n][n] = {0};
};
FloydS floyds;

//(1)Floyd's Algorithm
void printPath(int path[][n], int v, int u)
{
	if (path[v][u] == v)
		return;

	printPath(path, v, path[v][u]);
	cout << path[v][u] << " ";		
}


void printSolution(int cost[n][n], int path[n][n])
{
	cout << "(1) Floyd's Algorithm:" << endl << endl;
	cout << "The shortest cost with path information between all pairs of vertices" << endl << endl;
	for (int v = 0; v < n; v++)
	{
		for (int u = 0; u < n; u++)
		{
			if (cost[v][u] == INT_MAX) {
				cout << setw(5) << "inf";
				floyds.dist[v][u] = cost[v][u];
			}
			else {
				cout << setw(5) << cost[v][u];
				floyds.dist[v][u] = cost[v][u];
				
			}
		}
		cout << endl;
	}

	cout << endl;
	for (int v = 0; v < n; v++)
	{
		for (int u = 0; u < n; u++)
		{
			if (u != v && path[v][u] != -1)
			{
				cout << "Shortest Path from vertex " << v <<
					" to vertex " << u << " is (" << v << " ";
				printPath(path, v, u);
				cout << u << ")" << endl;
				
			}
		}
	}
}


void Floyd(int adjMatrix[][n])
{

	int cost[n][n], path[n][n];

	// initialize cost[] and parent[]
	for (int v = 0; v < n; v++)
	{
		for (int u = 0; u < n; u++)
		{
			// initally cost would be same as weight of the edge
			cost[v][u] = adjMatrix[v][u];

			if (v == u) {
				path[v][u] = 0;
				floyds.path[v][u] = 0;
			}
			else if (cost[v][u] != INT_MAX) {
				path[v][u] = v;
				floyds.path[v][u] = path[v][u];
			}
			else {
				path[v][u] = -1;
				floyds.path[v][u] = path[v][u];
			}
		}
	}

	// run Floyd
	for (int k = 0; k < n; k++)
	{
		for (int v = 0; v < n; v++)
		{
			for (int u = 0; u < n; u++)
			{
				// If vertex k is on the shortest path from v to u,
				// then update the value of cost[v][u], path[v][u]

				if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
					&& cost[v][k] + cost[k][u] < cost[v][u])
				{
					cost[v][u] = cost[v][k] + cost[k][u];
					path[v][u] = path[k][u];
					floyds.path[v][u] = path[v][u];
				}
			}

			// if diagonal elements become negative, the
			// graph contains a negative weight cycle
			if (cost[v][v] < 0)
			{
				cout << "Negative Weight Cycle Found!!";
				return;
			}
		}
	}

	// Print the shortest path between all pairs of vertices
	printSolution(cost, path);
}


//*********************************************************************************************

//////// Table to store Dijkstra's Algorithm ////////
struct Dijkstas {
	int dist[n] = {0};
	int parent[n] = { 0 };
};
Dijkstas dijkstras[n];

//(2)Dijkstra's Algorithm
int minDistance(int dist[], bool sptSet[])
{
	int min = INT_MAX, min_index = 0;

	for (int v = 0; v < n; v++)
	{
		if (sptSet[v] == false && dist[v] <= min)
		{
			min = dist[v], min_index = v;
		}
	}

	return min_index;
}
void printPath(int parent[], int j)
{
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);
	cout << " -> " << j;
}

void printSolution(int dist[], int n, int parent[], int src)
{
	int min = INT_MAX;
	int nodo = -1;
	cout << "Vertex   Distance from Source   Path" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << i << "\t\t\t" << dist[i] << "\t\t\t" << src;
		printPath(parent, i);
		cout << endl;

		if (dist[i] < min && dist[i] != 0)
		{
			min = dist[i];
			nodo = i;
		}
	}
	cout << endl;
	cout << "Shortest Path: " << min << endl;
	cout << "Destination Node: " << nodo << endl << endl;
}

void dijkstra(int graph[n][n], int src)
{
	int dist[n];
	bool sptSet[n];
	int parent[n];

	parent[src] = -1;
	dijkstras[src].parent[src] = -1;
	for (int i = 0; i < n; i++)
	{
		dist[i] = INT_MAX;
		sptSet[i] = false;
		dijkstras[src].dist[i] = dist[i];
	}

	dist[src] = 0;
	dijkstras[src].dist[src] = 0;

	for (int count = 0; count < n - 1; count++)
	{
		int u = minDistance(dist, sptSet);

		sptSet[u] = true;

		for (int v = 0; v < n; v++)
		{
			if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				dist[v] = dist[u] + graph[u][v];
				dijkstras[src].dist[v] = dist[v];

				parent[v] = u;
				dijkstras[src].parent[v] = parent[v];

			}
		}
	}

	printSolution(dist, n, parent, src);
}

int main()
{
	cout << "Enter the name of your file: ";
	string file_name;
	cin >> file_name;
	int AdjacencyMatrix[n][n];
    //read graph from file and store in an adjacency matrix
	ifstream myfile;
	myfile.open(file_name);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			myfile >> AdjacencyMatrix[i][j];

	cout << "Graph Adgacency Matrix:" << endl;
	for (int i = 0; i < n; i++) {
		cout << "\n";
		for (int j = 0; j < n; j++) {
			cout << AdjacencyMatrix[i][j]<<setw(5);
		}
	}
	cout << endl << endl;
	myfile.close();


	// Run Floyd's algorithm
	Floyd(AdjacencyMatrix);

	//Run Dijkstra's algorithm
	cout << "\n(2)Dijkstra Algorithm" << endl;
	for (int i = 0; i < n; i++) {
		cout << "if vertex (" << i << ") is the source:" << endl;
		dijkstra(AdjacencyMatrix, i);
		cout << endl;
	}
	
	//Answer user queries:::
	cout << "Enert two vertices to find the shortest path and to print the track:" << endl;
	cout << "\nEnter source vertex: ";
	int svertex;
	cin >> svertex;
	cout << endl;
	cout << "Enter destination vertex: "; 
	int dvertex;
	cin >> dvertex;
	cout << endl;
	cout << "The value/weight of shortest path using Floyd: ";
	cout << floyds.dist[svertex][dvertex] << endl;
	cout << "The track of the shortest path: ";
	cout << svertex << " ";
	printPath(floyds.path, svertex, dvertex);
	cout << dvertex << endl;
	cout << "The value/weight of shortest path using Dijkstra: ";
	cout << dijkstras[svertex].dist[dvertex]<<endl;
	cout << "The track of the shortest path: " << svertex;
	printPath(dijkstras[svertex].parent, dvertex);
	cout << endl;
	return 0;	
}

//contributed by Bilal Hoor
