/*
See slides for problem description

knapsack() := recursive implementation. Time: O(capacity^n), Space: O(n) depth of tree
knapsack1() := top-down DP (memoization) Time: O(n * capacity), Space: O(n * capacity) as each (n, capacity) pair is a subproblem
knapsack2() := bottom-up DP (2D array) Time: O(n * capacity),  Space: O(n * capcacity)
*/

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>	// For strtol()
using namespace std;

typedef pair <int, int> iPair;

int knapsack(int val[], int wt[], int n, int capacity);
int knapsack1(int val[], int wt[], int n, int capacity);
int knapsack1Util(int val[], int wt[], int n, int capacity, map<iPair, int>& hmap);
int knapsack2(int val[], int wt[], int n, int capacity);
int knapsack3(int val[], int wt[], int n, int capacity);

int main() {
	ifstream myfile("knapsack_big.txt");
	string line;
	int* val, *wt;
	int n, capacity;
	
	getline(myfile, line);
	char* cstr = new char[line.size() + 1];
	strcpy(cstr, line.c_str());
		
	char* tok = strtok(cstr, " ");
	capacity = strtol(tok, NULL, 10);
	
	tok = strtok(NULL, " ");
	n = strtol(tok, NULL, 10);
		
	cout << capacity << " " << n << endl;

	delete[] cstr;
	
	val = new int[n];
	wt = new int[n];
	
	for (int i = 0; i < n; i++) {
		getline(myfile, line);
		cstr = new char[line.size() + 1];
		strcpy(cstr, line.c_str());
		
		tok = strtok(cstr, " ");
		val[i] = strtol(tok, NULL, 10);
		
		tok = strtok(NULL, " ");
		wt[i] = strtol(tok, NULL, 10);
		
		//cout << val[i] << " " << wt[i] << endl;
		
		delete[] cstr;
	}
	
	cout << knapsack1(val, wt, n, capacity) << endl;
	
	return 0;
}

int knapsack(int val[], int wt[], int n, int capacity) {
	if (n == 0) return 0;
	
	// If this element can be picked, return max of picking and not picking this element
	// Else return the value obtained by not picking this element
	if (wt[n - 1] <= capacity) {
		return max(knapsack(val, wt, n - 1, capacity - wt[n - 1]) + val[n - 1], knapsack(val, wt, n - 1, capacity));
	}
	else {
		return knapsack(val, wt, n - 1, capacity);
	}
}

int knapsack1(int val[], int wt[], int n, int capacity) {
	map<iPair, int> hmap;
	return knapsack1Util(val, wt, n, capacity, hmap);
}

int knapsack1Util(int val[], int wt[], int n, int capacity, map<iPair, int>& hmap) {
	if (n == 0) return 0;
	int pick, skip;
	
	// If this element can be picked, return max of picking and not picking this element
	// Else return the value obtained by not picking this element
	if (wt[n - 1] <= capacity) {
		// If subproblem isn't precomputed, compute and store
		if (hmap.count(make_pair(n - 1, capacity - wt[n - 1])) == 0) {
			hmap[make_pair(n - 1, capacity - wt[n - 1])] = knapsack1Util(val, wt, n - 1, capacity - wt[n - 1], hmap);
		}
		pick = hmap[make_pair(n - 1, capacity - wt[n - 1])] + val[n - 1];
		
		if (hmap.count(make_pair(n - 1, capacity)) == 0) {
			hmap[make_pair(n - 1, capacity)] = knapsack1Util(val, wt, n - 1, capacity, hmap);
		}
		skip = hmap[make_pair(n - 1, capacity)];
		
		return max(pick, skip);
		
	}
	else {
		if (hmap.count(make_pair(n - 1, capacity)) == 0) {
			hmap[make_pair(n - 1, capacity)] = knapsack1Util(val, wt, n - 1, capacity, hmap);
		}
		skip = hmap[make_pair(n - 1, capacity)];
		return skip;
	}
}

int knapsack2(int val[], int wt[], int n, int capacity) {
	vector<vector<int> > A(n + 1, vector<int>(capacity + 1));	// Create a table of n + 1 rows, capacity + 1 columns
	
	// If n = 0 return 0
	for (int j = 0; j <= capacity; j++) {
		A[0][j] = 0;
	}
	
	// Build up by solving smaller subproblems
	// For each prefix of the array compute solution for every possible capacity
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= capacity; j++) {
			// If this element can be picked, select the max of picking or not picking it; else use the result obtained by not picking it
			if (wt[i - 1] <= j) {
				A[i][j] = max(A[i - 1][j - wt[i - 1]] + val[i - 1], A[i - 1][j]);
			}
			else {
				A[i][j] = A[i - 1][j];
			}
		}
	}
	
	return A[n][capacity];
}