#include <iostream>
#include <fstream>
#include <string>
#define SIZE 1000000
using namespace std;

unsigned int countInv(int* src, int n);
unsigned int countInvHelper(int* src, int* dst, int left, int right);
unsigned int countSplitInv(int* src1, int* src2, int* dst, int len1, int len2);

int main() {
	int* A = new int[SIZE];
	//ifstream myfile("sampleInput.txt");
	ifstream myfile("IntegerArray.txt");
	string line;
	
	if (!myfile.is_open()) {
		cout << "file read error\n";
		return 1;
	}
	
	// Read input
	int n = 0;
	while (getline(myfile, line)) {
		A[n] = stoi(line);
		n++;
	}
	
	//for (int i = 0; i < n; i++) {
	//	cout << A[i] << " ";
	//}
	//cout << endl;
	
	cout << n << endl;
	cout << countInv(A, n) << endl;
	
	return 0;
}

unsigned int countInv(int* src, int n) {
	int* dst = new int[n];
	int count = countInvHelper(src, dst, 0, n);
	delete[] dst;
	return count;
}

unsigned int countInvHelper(int* src, int* dst, int left, int right) {
	if (right - left < 1) {
		cout << "error!\n";
	}
	
	if (right - left == 1) {
		dst[0] = src[left];
		return 0;
	}
	
	// mid = (left + right) / 2
	int mid = left + (right - left) / 2;
	
	int leftSize = mid - left;
	int rightSize = right - mid;
	int* L = new int[leftSize];
	int* R = new int[rightSize];
	
	int x = countInvHelper(src, L, left, mid);
	int y = countInvHelper(src, R, mid, right);
	int z = countSplitInv(L, R, dst, leftSize, rightSize);
	
	//cout << "x = " << x << ", y = " << y << ", z = " << z << endl;
	
	delete[] L;
	delete[] R;
	
	return x + y + z;
}

unsigned int countSplitInv(int* src1, int* src2, int* dst, int len1, int len2) {
	int i = 0;	// Iterator for src1
	int j = 0;	// Iterator for src2
	int k = 0;	// Iterator for dst
	int count = 0;
	
	// Follow merge sorted arrays algorithm with the change below
	// While both sorted halves have elements
	// If the second half has an element less than an element in the first half
	// 	then it is also less than all the next elements in the first half 
	//	So increment count by the remaining length of the first half
	while (i < len1 && j < len2) {
		if (src1[i] <= src2[j]) {
			dst[k] = src1[i];
			i++;
		}
		else {
			dst[k] = src2[j];
			j++;
			count += (len1 - i);	// Increment count by remaining length of first array
		}
		k++;
	}
	
	// Copy over the remaining elements, no modification here
	while (i < len1) {
		dst[k] = src1[i];
		i++; k++;
	}
	
	while (j < len2) {
		dst[k] = src2[j];
		j++; k++;
	}
	
	return count;
}