#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SIZE 10000
#define FIRST 0
#define LAST 1
#define MEDIAN 2
using namespace std;

int quickSort(int* A, int left, int right, int mode);
void quickSortUtil(int* A, int left, int right, int& count, int mode);
int choosePivotAndPartition(int* A, int left, int right, int mode);
int partition(int* A, int left, int right);
int findMedian(int* A, int left, int right, int middle);

int main() {
	int* A = new int[SIZE];
	//ifstream myfile("test3.txt");
	ifstream myfile("QuickSort.txt");
	string line;
	
	// Read input
	int n = 0;
	while (getline(myfile, line)) {
		A[n] = stoi(line);
		n++;
	}
	cout << endl;
	cout << "n = " << n << endl;
	
	cout << quickSort(A, 0, n - 1, MEDIAN) << endl;
	
	return 0;
}

int quickSort(int* A, int left, int right, int mode) {
	int count = 0;
	quickSortUtil(A, left, right, count, mode);
	return count;
}

void quickSortUtil(int* A, int left, int right, int& count, int mode) {
	if (right > left) {
		count += right - left;	// Partition called on size n, increment count by n - 1
		int pIndex = choosePivotAndPartition(A, left, right, mode);
		quickSortUtil(A, left, pIndex - 1, count, mode);
		quickSortUtil(A, pIndex + 1, right, count, mode);
	}
	
}

int choosePivotAndPartition(int* A, int left, int right, int mode) {
	int middle, median;
	switch(mode) {
		case FIRST: break;
		case LAST: swap(A[left], A[right]);
					break;
		case MEDIAN: middle = left + (right - left) / 2;	// here middle: (n - 1) / 2 or (right + left) / 2
					// If middle is the median
					median = findMedian(A, left, right, middle);
					swap(A[left], A[median]);
					break;
		default: cout << "wrong mode: default to first\n";
				break;
	}
	return partition(A, left, right);
}

int partition(int* A, int left, int right) {
	int pivot = A[left];
	
	// Adjust i to be := first element > p
	// j := iterator over all the elements in range
	
	int i = left + 1;
	for (int j = left + 1; j <= right; j++) {
		if (A[j] < pivot) {	// This is the comparision to be counted
			swap(A[j], A[i]);
			i++;
		}
	}
	
	// Swap pivot with the last element less than the pivot
	// To get all elements < p to the left of p, and
	// All elements > p to the right of p
	swap(A[left], A[i - 1]);
	
	// return the index of the pivot
	return (i - 1);
}

int findMedian(int* A, int left, int right, int middle) {
	int median;
	
	// if L < M < R or R < M < L -> median = M
	// else if L < R < M or M < R < L -> median = R
	// else median = left
	if ((A[left] < A[middle] && A[middle] < A[right]) ||
		(A[right] < A[middle] && A[middle] < A[left])) {
			median = middle;
		}
	else if	((A[left] < A[right] && A[right] < A[middle]) ||
			(A[middle] < A[right] && A[right] < A[left])) {
				median = right;
			}
	else {
		median = left;
	}
	
	/*cout << "L R M Median = " << left << " " << right << " "
			<< middle << " " << median << endl;
	cout << "A[L] A[R] A[M] A[Median] = "<< A[left] << " " 
		<< A[right] << " " << A[middle] << " " 
		<< A[median] << endl;*/
	return median;
}