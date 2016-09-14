#include <iostream>
#include <list>
#include <queue>	// priority_queue
#include <climits>	// INT_MAX
#include <fstream>
#include <cstring>
#include <cstdlib>	// strtol()
using namespace std;

typedef pair<int, int> iPair;

class Graph {
	int V;
	list<iPair>* adj;

public:
	Graph(int n);
	void addEdge(int u, int v, int w);
	void primMST();
};

Graph::Graph(int n) {
	V = n;
	adj = new list<iPair>[V];
}

void Graph::addEdge(int u, int v, int w) {
	adj[u].push_back(make_pair(v, w));
	adj[v].push_back(make_pair(u, w));
}

void Graph::primMST() {
	// Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
	// In heap the pair format is (key, vertex) since the first element of the pair is used as the key of the heap by default
    priority_queue< iPair, vector <iPair> , greater<iPair> > minHeap;
	
	// Init parents of all vertices to -1
	vector<int> parent(V, -1);
	int res = 0;
	
	// Init all keys to INT_MAX
	vector<int> key(V, INT_MAX);
	
	// Init all vertices to not being in MST
	vector<bool> inMST(V, false);
	
	// Select vector 0 as the src vector. Set its key to 0, add to MST, and to minHeap
	int src = 0;
	key[src] = 0;
	minHeap.push(make_pair(key[src], src));

	// While the heap isn't empty
	while (!minHeap.empty()) {
		// Extract the minimum element (top) of the heap
		int u = minHeap.top().second; 
		int minEdge = minHeap.top().first;
				minHeap.pop();
		
		// A vertex will be pushed to the heap every time a shorter path is found to it; only consider the minimum (first to be popped)
		if (inMST[u] == false) {
			res += minEdge;	// Add key/weight of the min edge to accumulate result
		}
		
		// u is now part of MST
		inMST[u] = true;
		
		// Update the keys of all the neighbors of u that are not yet part of the MST
		for (list<iPair>::iterator i = adj[u].begin(); i != adj[u].end(); i++) {
			// Get vertex and edge weight from list pair
			int v = (*i).first;
			int weight = (*i).second;
			
			// If not in MST yet and edge weight lesser than current key value of this neighbor, update its key, parent, and push to heap
			if (inMST[v] == false && weight < key[v]) {
				parent[v] = u;
				key[v] = weight;
				minHeap.push(make_pair(key[v], v));
			}
		}
	}
	
	// Print edges of the MST using parent array
	//for (int i = 0; i < V; i++) {
	//	cout << parent[i] << " - " << i << endl;
	//}
	cout << res << endl;
}

int main() {
	ifstream myfile("edges.txt");
	// ifstream myfile("sample2.txt");
	string line;
	char* cstr, *tmp;
	
	getline(myfile, line);
	cstr = new char[line.size() + 1];
	strcpy(cstr, line.c_str());
	
	int n = strtol(cstr, &tmp, 10);
	int m = strtol(tmp, NULL, 10);
	delete[] cstr;
	
	cout << n << " " << m << endl;
	
	Graph g(n);
	// Parse the graph
	while (getline(myfile, line)) {
		cstr = new char[line.size() + 1];
		strcpy(cstr, line.c_str());
		
		int u = strtol(cstr, &tmp, 10);
		int v = strtol(tmp, &tmp, 10);
		int w = strtol(tmp, NULL, 10);
		g.addEdge(u - 1, v - 1, w);
		delete[] cstr;
	}
	
    g.primMST();

	return 0;
}