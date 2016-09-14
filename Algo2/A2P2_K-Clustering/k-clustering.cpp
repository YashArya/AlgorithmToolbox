/*
Kruskal's Algorithm.
Time: O(ElogE)
Space: O(V) other than the space to store the graph
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <fstream>
#include <string>
using namespace std;

typedef pair<int, int> iPair;

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
	vector <pair<int, iPair> > edges;

public:
	Graph(int n);
	void addEdge(int u, int v, int w);
	int kClustering(int k);
};

Graph::Graph(int n) {
	V = n;
}

void Graph::addEdge(int u, int v, int w) {
	edges.push_back(make_pair(w, make_pair(u, v)));
}

int Graph::kClustering(int k) {
	int minSeparation = INT_MAX;
	int numClusters = V;	// Solution must have V - 1 edges.	
	cout << "Here!\n";
	// Sort the edges in non-decreasing order of cost
	sort(edges.begin(), edges.end());
	
	DisjointSet ds(V);
	vector< pair<int, iPair> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++) {
		int u = it->second.first;
		int v = it->second.second;
		
		int set_u = ds.find(u);
		int set_v = ds.find(v);
		
		// If u and v belong to different sets, adding this edge does not cause a cycle
		// So add to result, and take union of sets
		if (set_u != set_v) {
			// Current edge will be in the MST
            // so print it
            //cout << u << " - " << v << endl;
			//cout << numClusters << endl;
			
            // Merge two sets
			if (numClusters > k) {
				ds.unionSet(set_u, set_v);
				numClusters--;
			}
            else {
				minSeparation = it->first;
				break;
			}	
		}
	}
	
	return minSeparation;
}

int main() {
	ifstream myfile("clustering1.txt");
	string line;
	std::string::size_type sz, tokStart;   // alias of size_t
	
	getline(myfile, line);
	
	int V = stoi(line);
	
	//cout << V << endl;
	Graph g(V);
	
	while(getline(myfile, line)) {
		int u = stoi(line, &sz);
		tokStart = sz + 1;
		int v = stoi(line.substr(tokStart), &sz);
		tokStart += sz + 1;
		int w = stoi(line.substr(tokStart));
		g.addEdge(u, v, w);
		//cout << u << " " << v << " " << w << endl;
	}
	
    /*g.addEdge(0, 1, 4);
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
    g.addEdge(7, 8, 7);*/
 
    cout << "Edges of MST are \n";
	int maxSeparation = g.kClustering(4);
 
    cout << "\nWeight of MST is " << maxSeparation;
 
    return 0;
}