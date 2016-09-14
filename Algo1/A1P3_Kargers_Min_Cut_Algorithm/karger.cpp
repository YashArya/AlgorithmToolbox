#include <iostream>
#include <vector>
#include <fstream>
#include <string> 	// stoi() c++11
#include <climits>
#include <cstdlib>	// rand(), srand()
#include <ctime>
using namespace std;

typedef pair<int, int> iPair;
const int NUM_VERTICES = 200;

class DisjointSet {
	int n;
	int* rank;
	int* parent;

public:
	DisjointSet(int n);
	int find(int x);	// Uses path compression
	int Union(int x, int y);	// Union by rank
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
	
int DisjointSet::Union(int x, int y) {
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
	vector<iPair> edges;
public:
	Graph(int n);
	void addEdge(int u, int v);
	int kargerMinCut();
};

Graph::Graph(int n) {
	V = n;
}

void Graph::addEdge(int u, int v) {
	edges.push_back(make_pair(u, v));
}

int Graph::kargerMinCut() {
	DisjointSet ds(V);
	
	int vertices = V;
	int numEdges = edges.size();
	
	// Keep contracting till only two vertices remain
	while (vertices > 2) {
		int i = rand() % numEdges;
		
		// Find the sets two which both the vertices corresponding to edge-i belong to
		int subset1 = ds.find(edges[i].first);
		int subset2 = ds.find(edges[i].second);
		
		// If edge makes a self-loop, ignore.
		if (subset1 == subset2) {
			continue;
		}
		
		// Else contract the two vertices into one
		//cout << "contracting edge " << edges[i].first << " - " << edges[i].second << endl;
		vertices--;
		ds.Union(subset1, subset2);
		
	}
	//cout << "end\n";
	
	// On getting two vertices, count the number of edges cutting between the two (half the number since we have 2*E edges here)
	int cutedges = 0;
	for (int i = 0; i < numEdges; i++) {
		int subset1 = ds.find(edges[i].first);
		int subset2 = ds.find(edges[i].second);
		if (subset1 != subset2) {
			cutedges++;
		}
	}
	
	cutedges /= 2;
	
	//cout << "cutedges = " << cutedges << endl;
	
	return cutedges;
}

int main() {
	// The adj list representation of the file will cause 2*E edges in the edge list representation used in this program 
	// (undirected edge represented as 2 directed edges in adj list representation)
	Graph g(NUM_VERTICES);
	ifstream myfile("kargerMinCut.txt");
	string line;
	std::string::size_type sz, tok;
	srand(time(NULL));
	
	while (getline(myfile, line)) {
		int u = stoi(line, &sz);	// Get source vertex
		//cout << u << " ";
		// Get rest of the vertices
		tok = sz + 1;
		while (tok < line.size()) {
			int v = stoi(line.substr(tok), &sz);
			//cout << v << " ";
			tok += sz + 1;
			g.addEdge(u, v);
		}
		//cout << endl;
	}
	
	int minCut = INT_MAX;
	int kargerCut;
	for (int i = 0; i < NUM_VERTICES * NUM_VERTICES; i++) {
		kargerCut = g.kargerMinCut();
		//cout << "kargerCut" << i << " " << kargerCut << endl;
		if (minCut > kargerCut) {
			minCut = kargerCut;
		}
	}
	
	kargerCut = g.kargerMinCut();
	
	cout << "mincut is: " << minCut << endl;
	
	return 0;
}