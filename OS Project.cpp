#include <iostream>
#include<string>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include<algorithm>
#include<cctype>
#include<fstream>
using namespace std;
int inframes(int val, int*& y, int num2) {
	for (int i = 0; i < num2; i++) {
		if (val == y[i])
			return i;
	}
	return -1;
}
int emptyspace(int*& y, int num2) {
	for (int i = 0; i < num2; i++) {
		if (y[i] == -1)
			return i;
	}
	return -1;
}
int lruindex(int*& arr, int num2) {
	int x = arr[0]; int min = 0;
	for (int i = 1; i < num2; i++) {
		if (x > arr[i]) {
			x = arr[i];
			min = i;
		}
	}
	return min;
}
int optval(int*& x, int*& y, int num1, int num2, int ind) {
	//int val=x[ind+1];
	int* arr;
	arr = new int[num2];
	for (int i = 0; i < num2; i++)
		arr[i] = -1;
	int p2 = 0;
	for (int i = ind + 1; i < num1; i++) {
		int p = inframes(x[i], y, num2);
		if (p != -1) {
			int p1 = inframes(x[i], arr, num2);
			if (p1 == -1) {
				p2 = emptyspace(arr, num2);
				if (p2 == num2 - 1)
					return x[i];
				else {
					arr[p2] = x[i];
				}

			}
		}
	}
	for (int l = 0; l < num2; l++) {
		int p3 = y[l];
		int p4 = inframes(p3, arr, num2);
		if (p4 == -1)
			return l;
	}

	return -1;
}

int lru(int*& x, int*& y, int num1, int num2) {
	int pf = 0;//page fault
	int* arr;
	arr = new int[num2];


	for (int i = 0; i < num1; i++) {
		int p1 = inframes(x[i], y, num2);
		if (p1 == -1) {
			++pf;
			int p2 = emptyspace(y, num2);
			if (p2 != -1) {
				y[p2] = x[i];
				arr[p2] = i;
			}
			else {
				int p3 = lruindex(arr, num2);
				y[p3] = x[i];
				arr[p3] = i;
			}
		}
		else {
			arr[p1] = i;
		}


	}
	return pf;

	/*	for (int i = 0; i < num2; i++){
			y[i] = x[i];
			pf++;
			arr[i] = i + 1;

		}
		for (int i = num2; i < num1; i++) {
			int k = arr[0],q=0;
			arr[i % num2] = i;
			for (int j = 0; j < num2; j++) {
				if (x[i] == y[j]) {
					q = 1;
				}
			}
			if (q == 0) {

			}
			/* int uniquecounter = 0;
			int *arr;
			arr = new int(num2);
			for (int q = 0; q < num2; q++)
				arr[q] = -1;

			for (int j = i - 1; j >= 0; j--) {
				for (int k = 0; k < num2; k++) {
					if (uniquecounter == 0) {
						arr[0] = x[-1];
						uniquecounter++;
					}
					else if (uniquecounter>0 && uniquecounter<num2) {

					}
				}

			}
			for (int z = 0; z < num2; z++) {
				if (y[z] == arr[uniquecounter]) {
					y[z] = x[i];
					cout << "loop 2el y[z";
					cout << y[z] << endl<<endl;
				}


			}*/

}
int optimal(int*& x, int*& y, int num1, int num2) {
	int pf = 0;//page fault
	/*int* arr;
	arr = new int[num2];*/

	for (int i = 0; i < num1; i++) {
		int p1 = inframes(x[i], y, num2);
		if (p1 == -1) {
			pf++;
			int p2 = emptyspace(y, num2);
			if (p2 != -1) {
				y[p2] = x[i];
			}
			else {
				int p3 = optval(x, y, num1, num2, i);
				y[p3] = x[i];
			}
		}
		cout << "process number " << i << endl;
		for (int k = 0; k < num2; k++) {
			cout << y[k] << endl;
		}
		cout << endl;
	}

	return pf;
}
int fifo(int*& x, int*& y, int num1, int num2) {
	int pf = 0;
	int fi = 0;
	for (int i = 0; i < num1; i++) {
		int p1 = inframes(x[i], y, num2);
		if (p1 == -1) {
			++pf;
			int p2 = emptyspace(y, num2);
			if (p2 != -1) {
				y[fi] = x[i];
				fi = ((fi + 1) % num2);
				cout << y[p2] << endl;
			}
			else {

				y[fi] = x[i];
				fi = ((fi + 1) % num2);

			}

		}

		cout << "process number " << i << endl;
		for (int j = 0; j < num2; j++)
			cout << y[j] << endl;
	}
	return pf;
}
int main()
{
	int num1, num2;
	cout << "Enter the array of processes" << endl;
	cin >> num1;
	int* x;
	x = new int[num1];

	for (int i = 0; i < num1; i++) {
		cout << "the value in page=" << i + 1 << endl;
		cin >> x[i];
	}

	cout << "Enter the number of pages" << endl;
	cin >> num2;
	int* y;
	y = new int[num2];
	for (int i = 0; i < num2; i++)
		y[i] = -1;

	cout << "enter the algorithm you want to choose:" << endl;
	cout << "1)lru" << endl;
	cout << "2)opt" << endl;
	cout << "3)fifo" << endl;
	int choice;
	cin >> choice;
	if (choice == 1)
		cout << lru(x, y, num1, num2);
	else if (choice == 2)
		cout << optimal(x, y, num1, num2);
	else if (choice == 3)
		cout << fifo(x, y, num1, num2);
	return 0;
}