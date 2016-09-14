/*
Kruskal's Algorithm.
Time: O(ElogE)
Space: O(V) other than the space to store the graph
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair< int, int > iPair;

class DisjointSet {
	int n;
	int* rank;
	int* parent;

public:
	DisjointSet(int n);
	int find(int x);	// Uses path compression
	int unionSet(int x, int y);	// Union by rank
};

DisjointSet::DisjointSet(int n) {
	this->n = n;
	rank = new int[n];
	parent = new int[n];
	
	for (int i = 0; i <= n; i++) {
		rank[i] = 0;
		parent[i] = i;
	}
}

// Use path compression
int DisjointSet::find(int x) {
	
	//Make the parent of the nodes in the path
	//from x --> parent[x] point to parent[x] 
	if (parent[x] != x) {
		parent[x] = find(parent[x]);
	}
	
	return parent[x];
}
	
int DisjointSet::unionSet(int x, int y) {
	int xRoot = find(x);
	int yRoot = find(y);
	
	// Make higher rank tree parent of lower rank tree; if equal rank, make one the parent of other and increase its rank
	if (rank[x] > rank[y]) {
		parent[y] = x;
	}
	else if (rank[x] < rank[y]) {
		parent[x] = y;
	}
	else {
		parent[x] = y;
		rank[y]++;
	}
}

class Graph {
	int V;
	int E;
	vector < pair<int, iPair> > edges;

public:
	Graph(int m, int n);
	void addEdge(int u, int v, int w);
	int kruskalMST();
};

Graph::Graph(int n, int m) {
	V = n;
	E = m;
}

void Graph::addEdge(int u, int v, int w) {
	edges.push_back(make_pair(w, make_pair(u, v)));
}

int Graph::kruskalMST() {
	int mst_wt = 0;
	int countEdges = 0;	// Solution must have V - 1 edges.	
	
	// Sort the edges in non-decreasing order of cost
	sort(edges.begin(), edges.end());
	
	DisjointSet ds(V);
	for (vector< pair<int, iPair> >::iterator it = edges.begin(); it != edges.end(); it++) {
		int u = it->second.first;
		int v = it->second.second;
		
		int set_u = ds.find(u);
		int set_v = ds.find(v);
		
		// If u and v belong to different sets, adding this edge does not cause a cycle
		// So add to result, and take union of sets
		if (set_u != set_v) {
			// Current edge will be in the MST
            // so print it
            cout << u << " - " << v << endl;
 
            // Update MST weight
            mst_wt += it->first;
 
            // Merge two sets
            ds.unionSet(set_u, set_v);
			
			countEdges++;
		}
		
		// Break when solution is complete;
		if (countEdges == V - 1) {
			break;
		}
	}
	
	return mst_wt;
}

int main() {
	int V = 9, E = 14;
    Graph g(V, E);
	
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
 
    cout << "Edges of MST are \n";
	int mst_wt = g.kruskalMST();
 
    cout << "\nWeight of MST is " << mst_wt;
 
    return 0;
}