/*
Refer: http://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
Time: O(mlogn)
Space: O(m) for the heap
*/

#include <iostream>
#include <cstdio>
#include <list>
#include <queue>	// For priority_queue
#include <climits>
#include <fstream>
#include <cstring>
#include <cstdlib>	// For strtol()

#define MAX 1000000
using namespace std;
// iPair: integer pair
typedef pair<int, int> iPair;

class Graph {
	int V;
	list<iPair>* adj;

public:
	Graph(int n);
	void addEdge(int u, int v, int w);	// Add edge between u and v of weight w (undirected)
	void shortestPath(int s);	// Print shortest paths from start node s
};

// Allocates memory for adjacency list
Graph::Graph(int n) {
    V = n;
    adj = new list<iPair> [V];
}
 
void Graph::addEdge(int u, int v, int w) {
	// Undirected edge represented as directed edge in both directions
	// list: pair <vertex, weight>
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void Graph::shortestPath(int s) {
	// Create a min heap
	// http://geeksquiz.com/implement-min-heap-using-stl/
	priority_queue<iPair, vector<iPair>, greater<iPair> > minHeap;
	
	// Init all distances to MAX
	vector<int> dist(V, MAX);
	
	// Insert star node into min heap and set distance to zero
	// heap: pair<weight, vertex> - Weight needs to be first parameter for it to be used as heap key
	minHeap.push(make_pair(0, s));
	dist[s] = 0;
	
	// While there are still vertices to be processed
	// That is while heap is still not empty
	while (!minHeap.empty()) {
		// Top of the heap has vertex at minimum distance from the explored set
		// Extract top
		int u = minHeap.top().second;
		minHeap.pop();
		
		// For all neighbor vertices
		for (list<iPair>::iterator i = adj[u].begin(); i != adj[u].end(); i++) {
			// Get weight and vertex
			int v = (*i).first;
			int weight = (*i).second;
			
			// If there is a shorter path to v through u, update distance, add to min heap
			// Even though this will cause multiple instances of the same vertex to be in the heap, 
			// 	only the one with the minimum weight will make a difference
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				minHeap.push(make_pair(dist[v], v));
			}
		}
	}
	
	// Print shortest distances stored in dist[]
    printf("print selected vertices distances");
	cout << dist[6] << "," << dist[36] << "," << dist[58] << "," << dist[81] << "," << dist[98] << "," << dist[114] << "," 
	<< dist[132] << "," << dist[164] << "," << dist[187] << "," << dist[196] << endl;
}

int main() {
	Graph g(200);
	ifstream myfile("dijkstraData.txt");
	//ifstream myfile("sample1.txt");
	string line;
	
	while(getline(myfile, line)) {
		// Convert to c string to tokenize
		char* cstr = new char[line.size() + 1];
		strcpy(cstr, line.c_str());
		
		char* tok, *tok2;
		tok = strtok(cstr, " \t");
		
		// Get vertex number from the first token
		int u = strtol(tok, NULL, 10);
		
		// Loop over rest of the tokens
		tok = strtok(NULL, ",");
		while (tok != NULL) {
			int v = strtol(tok, NULL, 10);
			tok = strtok(NULL, " \t");
			int w = strtol(tok, NULL, 10);
			g.addEdge(u - 1, v - 1, w);
			tok = strtok(NULL, ",");
		}
		
		delete[] cstr;
	}
	
	g.shortestPath(0);
	
	return 0;
}