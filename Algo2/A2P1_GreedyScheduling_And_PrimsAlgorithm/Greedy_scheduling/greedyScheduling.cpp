#include <iostream>
#include <fstream>
#include <string>	// stoi() uses C++11
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct params_diff {
	int score;
	int weight;
	int len;
	int cumulativeLen;
};

struct params_ratio {
	float score;
	int weight;
	int len;
	int cumulativeLen;
};

bool compare_diff(const params_diff& a, const params_diff& b);
unsigned long long int computeSum_diff(vector<params_diff>& jobs);
bool compare_ratio(const params_ratio& a, const params_ratio& b);
unsigned long long int computeSum_ratio(vector<params_ratio>& jobs);

int main() {
	ifstream myfile("jobs.txt");
	//ifstream myfile("sample3.txt");
	string line;
	int n;
	
	// Read number of jobs
	getline(myfile, line);
	n = stoi(line);
	
	vector<params_diff> jobs1(n);	// for q1: score based on diff (weight - len)
	vector<params_ratio> jobs2(n);	// for q2: score based on ratio (weight / len)
	
	// Read all the jobs and compute differences
	for (int i = 0; i < n; i++) {
		getline(myfile, line);
		
		// Convert to c string to tokenize
		char* cstr = new char[line.size() + 1];
		char* temp;
		
		strcpy(cstr, line.c_str());
		
		// Extract weight and length and compute differences
		jobs1[i].weight = strtol(cstr, &temp, 10);
		jobs1[i].len = strtol(temp, NULL, 10);
		jobs2[i].weight = jobs1[i].weight;
		jobs2[i].len = jobs1[i].len;
		
		delete[] cstr;
	}
	
	
	// Calculate scores
	for (int i = 0; i < n; i++) {
		jobs1[i].score = jobs1[i].weight - jobs1[i].len;	// q1
		jobs2[i].score = (float) jobs2[i].weight / jobs2[i].len;	// q2
	}
	
	// Reverse sort the vector based on score; for entries with same score, reverse sort based on weight
	sort(jobs1.begin(), jobs1.end(), compare_diff);
	sort(jobs2.begin(), jobs2.end(), compare_ratio);
	
	unsigned long long int completionTime1 = computeSum_diff(jobs1);
	unsigned long long int completionTime2 = computeSum_ratio(jobs2);
	
	cout << completionTime1 << endl;
	cout << completionTime2 << endl;
	
	return 0;
}

bool compare_diff(const params_diff& a, const params_diff& b) {
	// return true -> a and b not swapped
	// return false -> a and b swapped
	
	// Reverse sort based on score
	// For same score
	// Reverse sort based on weight
	
	if (a.score > b.score) return true;
	else if (a.score < b.score) return false;
	else {
		if (a.weight >= b.weight) return true;
		else return false;
	}
}

bool compare_ratio(const params_ratio& a, const params_ratio& b) {	
	if (a.score > b.score) return true;
	else if (a.score < b.score) return false;
	else {
		if (a.weight >= b.weight) return true;
		else return false;
	}
}

unsigned long long int computeSum_diff(vector<params_diff>& jobs) {
	// Initialize cost to cost of first job
	unsigned long long int cost = jobs[0].weight * jobs[0].len;
	jobs[0].cumulativeLen = jobs[0].len;
	
	// Add the cumulative costs of the rest of the jobs
	for (int i = 1; i < jobs.size(); i++) {
		jobs[i].cumulativeLen = jobs[i - 1].cumulativeLen + jobs[i].len;
		cost += jobs[i].weight * jobs[i].cumulativeLen;
	}
	
	return cost;
}

unsigned long long int computeSum_ratio(vector<params_ratio>& jobs) {
	// Initialize cost to cost of first job
	unsigned long long int cost = jobs[0].weight * jobs[0].len;
	jobs[0].cumulativeLen = jobs[0].len;
	
	// Add the cumulative costs of the rest of the jobs
	for (int i = 1; i < jobs.size(); i++) {
		jobs[i].cumulativeLen = jobs[i - 1].cumulativeLen + jobs[i].len;
		cost += jobs[i].weight * jobs[i].cumulativeLen;
	}
	
	return cost;
}