
#include <fstream>
#include <string>
#include <time.h>
#include <iostream>
using namespace std;

void loadFromFile(string array[] , const string& filename);
bool didConnectToFile(ifstream& fin, const string& filename);
void printPrompt();
void printSelectionForSort(int size, const string& file);
string insertionSort(int size, string array[]);
string mergeSort(int size, int first, int last, string array[]);
void merge(int first, int half, int last, string array[]);
void printMenu();
string heapSort(int size, string array[]);
void buildHeap(int size, int root, string array[]);
void writeToFile(int size, string outfile, string array[]);

int main() {
	printPrompt();
	cin.get();
	return 0;
}
void loadFromFile(string  array[], const string& filename) {
	ifstream fin;

	if (!didConnectToFile(fin, filename)) {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}
	int x = 0;
	getline(fin, array[x]);
	while (!fin.eof()) {
		getline(fin, array[x++]);
	}
	fin.close();
}
bool didConnectToFile(ifstream& fin, const string& filename) {
	fin.open(filename);
	return (fin.is_open());
}
void printPrompt() {
	int select;
	printMenu();
	cin >> select;
	while (select != 0) {
		int size1 = 15000; string file1 = "perm15K.txt"; string file11 = "sorted15K.txt";
		int size2 = 30000; string file2 = "perm30K.txt"; string file12 = "sorted30K.txt";
		int size3 = 45000; string file3 = "perm45K.txt"; string file13 = "sorted45K.txt";
		int size4 = 60000; string file4 = "perm60K.txt"; string file14 = "sorted60K.txt";
		int size5 = 75000; string file5 = "perm75K.txt"; string file15 = "sorted75K.txt";
		int size6 = 90000; string file6 = "perm90K.txt"; string file16 = "sorted90K.txt";
		int size7 = 105000; string file7 = "perm105K.txt"; string file17 = "sorted105K.txt";
		int size8 = 120000; string file8 = "perm120K.txt"; string file18 = "sorted120K.txt";
		int size9 = 135000; string file9 = "perm135K.txt"; string file19 = "sorted135K.txt";
		int size10 = 150000; string file10 = "perm150K.txt"; string file20 = "sorted150K.txt";
		
		switch (select) {
		case 1:    printSelectionForSort(size1, file1); break;
		case 2:    printSelectionForSort(size2, file2); break;
		case 3:    printSelectionForSort(size3, file3); break;
		case 4:    printSelectionForSort(size4, file4); break;
		case 5:    printSelectionForSort(size5, file5); break;
		case 6:    printSelectionForSort(size6, file6); break;
		case 7:    printSelectionForSort(size7, file7); break;
		case 8:    printSelectionForSort(size8, file8); break;
		case 9:    printSelectionForSort(size9, file9); break;
		case 10:    printSelectionForSort(size10, file10); break;

		case 11:    printSelectionForSort(size1, file11); break;
		case 12:    printSelectionForSort(size2, file12); break;
		case 13:    printSelectionForSort(size3, file13); break;
		case 14:    printSelectionForSort(size4, file14); break;
		case 15:    printSelectionForSort(size5, file15); break;
		case 16:    printSelectionForSort(size6, file16); break;
		case 17:    printSelectionForSort(size7, file17); break;
		case 18:    printSelectionForSort(size8, file18); break;
		case 19:    printSelectionForSort(size9, file19); break;
		case 20:    printSelectionForSort(size10, file20); break;
		}
		printMenu();
		cin >> select;
	}
}

void printMenu(){
	cout << endl << endl;
	for (int i = 1; i <= 20; i++) {
		if (i <= 10) {
			cout << "[" << i << "] "
				<< "perm"
				<< i * 15
				<< "K.txt\n";
		}
		if (i > 10) {
			cout << "[" << i << "] "
				<< "sorted"
				<< (i - 10) * 15
				<< "K.txt\n";
		}
	}
cout << "\nEnter 0 to Quit or Choose which file to Sort\n";
cout << "(For example Enter 1 for perm15K.txt): ";
}

void printSelectionForSort(int size, const string& file) {
	char choose;
	cout << "\n\n[1] Insertion\n" << "[2] Merge\n" <<"[3] Heap";
	cout << "\n\nEnter 0 to Quit or Choose Sorting Algorithm\n";
	cout << "(For example Enter 1 for Insertion Sort): ";
	cin >> choose;
	while (choose != '0') {

		string * array = new string[size];
		loadFromFile(array, file);
		string outfile;
		clock_t t1;
		clock_t	t2;
		double time;

		switch (choose) {
		case '1': 
			cout << "\n\nlist is sorting wait for it.\n\n";
			t1 = clock();
			outfile = insertionSort(size, array); 
			t2 = clock();
			break;

		case '2': 
			cout << "\nlist is sorting wait for it.";
			t1 = clock();
			outfile = mergeSort(size, 0, size-1, array); 
			t2 = clock();
			break;

		case '3': 
			cout << "\nlist is sorting wait for it.";
			t1 = clock();
			outfile = heapSort(size, array); 
			t2 = clock();
			break;
		}

		time = (double)(t2 - t1) / CLOCKS_PER_SEC;
		cout << "\n\n****************************************************\n";
		cout << "\nIt took " << time << " seconds to sort this file.\n";
		writeToFile(size, outfile, array);

		delete[] array;
		array = nullptr;

		cout << "\n\n[1] Insertion\n" << "[2] Merge\n" << "[3] Heap";
		cout << "\n\nEnter 0 to Quit or Choose Sorting Algorithm\n";
		cout << "(For example Enter 1 for Insertion Sort): ";
		cin >> choose;
	}
}

string insertionSort(int size, string array[]) {
	for (int i = 1; i < size; i++) {
		string word;
		word = array[i];
		int j = i - 1;
		while (j >= 0 && array[j] > word) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = word;
	}
	string infix = to_string((size / 1000));
	string outfile = "IS" + infix + "K.txt";
	return outfile;
}
string mergeSort(int size, int first, int last, string array[]) {
	if (first < last) {
		int half = (first + last) / 2;
		mergeSort(size, first, half, array);
		mergeSort(size, half + 1, last, array);
		merge(first, half, last, array);

	}
	string infix = to_string((size / 1000));
	string outfile = "MS" + infix + "K.txt";
	return outfile;
}
void merge(int first, int half, int last, string array[]) {
	int x = 0;
	int y = 0;
	int k = first;
	int arraySize1 = half - first + 1;
	int arraySize2 = last - half;

	string * array1 = new string[arraySize1];
	string * array2 = new string[arraySize2];

	for (int i = 0; i < arraySize1; i++) {
		array1[i] = array[first + i];
	}
	for (int j = 0; j < arraySize2; j++) {
		array2[j] = array[half +1 +j];
	}
	while(x < arraySize1 && y < arraySize2) {
		if (array1[x] <= array2[y]) {
			array[k] = array1[x];
			x++;
		}
		else {
			array[k] = array2[y];
			y++;
		}
		k++;
	}
	while (x < arraySize1) {
		array[k] = array1[x];
		x++;
		k++;
	}
	while (y < arraySize2) {
		array[k] = array2[y];
		y++;
		k++;
	}
	delete[] array1;
	delete[] array2;
	array1 = nullptr;
	array2 = nullptr;
	
}
string heapSort(int size, string array[]) {
	clock_t t1;
	clock_t	t2;
	double time;
	int notLeaf = size / 2 - 1;
	t1 = clock();
	for (int i = notLeaf; i >= 0; i--) {
		buildHeap(size, i, array);
	}
	t2 = clock();
	time = (double)(t2 - t1) / CLOCKS_PER_SEC;
	cout << "\n\n****************************************************\n";
	cout << "\nIt took " << time << " seconds to BuildHeap this file.\n";
	cout << "\n\n****************************************************\n";

	for (int j = size - 1; j >= 0; j--) {
		string temp = array[0];
		array[0] = array[j];
		array[j] = temp;
		buildHeap(j, 0, array);
	}
	string infix = to_string((size / 1000));
	string outfile = "HS" + infix + "K.txt";
	return outfile;
}
void buildHeap(int size, int root, string array[]) {
	int leftChild = 2 * root + 1;
	int rightChild = 2 * root + 2;
	int parent = root;
	if (leftChild < size && array[leftChild] > array[parent]) {
		parent = leftChild;
	}
	if (rightChild < size && array[rightChild] > array[parent]) {
		parent = rightChild;
	}
	if (parent != root) {
		string temp = array[root];
		array[root] = array[parent];
		array[parent] = temp;
		buildHeap(size, parent, array);
	}
}
void writeToFile(int size, string outfile, string array[]) {
	ofstream fout;
	fout.open(outfile);
	if (!fout.is_open()) {
		cerr << "Error writing to output file." << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++) {
		fout << array[i] << endl;
	}
	fout.close();
	cout << "Output of the sorted list is created in a seprate" << endl;
	cout << "file in a project folder. It is named: " << outfile;
	cout << "\n\n****************************************************\n";

}