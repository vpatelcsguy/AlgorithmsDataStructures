//Created by Vaibhav Patel
//KnapSack with Complexity O(nW)

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>

using namespace std;
int weightLimit;
int numOfItems;
int * weight;
int * value;
int itemNumber = 0;
int firstLineFlag = 0;

struct matrixInfo {
	int rawParent;
	int columnParent;
	int opt;
};

void loadFromFile(const string& filename);
bool didConnectToFile(ifstream& fin, const string& filename);
int findMax(matrixInfo**matrix, int i, int j, int dvalue, int rvalue);
void knapSack();
void goToParent(matrixInfo ** matrix, int i, int j);

int main() {
	loadFromFile("knapsack.txt");
	knapSack();
	cin.get();
	return 0;
}
void loadFromFile(const string& filename) {
	ifstream read;

	if (!didConnectToFile(read, filename)) {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}
	string oneLine;
	while (getline(read, oneLine, '\n')) {
		stringstream stream(oneLine);
		if (firstLineFlag == 0) {
			stream >> numOfItems;
			stream >> weightLimit;

			weight = new int[numOfItems];
			value = new int[numOfItems];

			firstLineFlag = 1;
		}
		else {
			stream >> weight[itemNumber];
			stream >> value[itemNumber];
			itemNumber++;
		}
	}
	read.close();
}
bool didConnectToFile(ifstream& fin, const string& filename) {
	fin.open(filename);
	return (fin.is_open());
}
int findMax(matrixInfo ** matrix, int i, int j, int dvalue, int rvalue) {
	if (dvalue > rvalue) {
		matrix[i][j].rawParent = i - 1;
		matrix[i][j].columnParent = j - weight[i - 1];
		return dvalue;
	}else {
		matrix[i][j].rawParent = i - 1;
		matrix[i][j].columnParent = j;
		return rvalue;
	}
}
void knapSack() {
	matrixInfo  * * matrix = new matrixInfo*[numOfItems + 1];
	for (int i = 0; i <= numOfItems; i++) {
		matrix[i] = new matrixInfo[weightLimit + 1];
	}
	for (int i = 0; i <= numOfItems; i++) {
		for (int j = 0; j <= weightLimit; j++) {
			if (i == 0 || j == 0) {
				matrix[i][j].opt = 0;
				matrix[i][j].rawParent = 0;
				matrix[i][j].columnParent = 0;
			}
			else if (weight[i - 1] <= j) {
				matrix[i][j].opt = findMax(matrix , i, j, value[i - 1] + matrix[i - 1][j - weight[i - 1]].opt, matrix[i - 1][j].opt);

			}
			else {
				matrix[i][j].opt = matrix[i - 1][j].opt;
				matrix[i][j].rawParent = i-1;
				matrix[i][j].columnParent = j;

			}
		}
	}
	cout << "The optimal Knapsack solution has total Value: " << matrix[numOfItems][weightLimit].opt << endl;
	cout << "It involes item Number: ";
	goToParent(matrix, numOfItems, weightLimit);
	cout << "}" << endl;

	for (int i = 0; i <= numOfItems; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
	delete[] weight;
	delete[] value;

}
void goToParent(matrixInfo ** matrix, int i, int j) {
	if (matrix[i][j].rawParent == 0 || matrix[i][j].columnParent == 0) {
		cout << "{" << i;
		return;
	}
	else if (matrix[i][j].rawParent == i || matrix[i][j].columnParent == j) {
		goToParent(matrix, matrix[i][j].rawParent, matrix[i][j].columnParent);
	}
	else {
		goToParent(matrix, matrix[i][j].rawParent, matrix[i][j].columnParent);
		cout << ", "  << i ;

	}
}
