//Created by Vaibhav Patel
//KnapSackDP with Complexity O(nW)
//KnapSackBB with worst O(2^n)
//KnapSackBB with best O(2*n + 1)
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include<queue>
#include <time.h>


using namespace std;

int weightLimit;
int numOfItems;
int itemNumber = 0;
int firstLineFlag = 0;
int optimalSol = 0;

struct ItemInfo {
	int weight;
	int value;
	double payOff;
};

struct TreeNodeInfo {
	int currentValue;
	int upperbound;
	int currentWeight;
	int branchLevel;
};

struct matrixInfo {
	int rawParent;
	int columnParent;
	int opt;
};

ItemInfo * items;
void printMenu();
void loadFromFile(const string& filename);
bool didConnectToFile(ifstream& fin, const string& filename);
int findMax(matrixInfo**matrix, int i, int j, int dvalue, int rvalue);
void insertionSort(int size, ItemInfo array[]);
int findUpperBound(TreeNodeInfo currentNode);
void knapSackDP();
void knapSackBB();
void goToParent(matrixInfo ** matrix, int i, int j);

int main() {

	int select;
	printMenu();
	cin >> select;
	cout << "\n********************************************************************************************" << endl;

	while (select != 0) {
		switch (select) {
		case 1:    	loadFromFile("knapsack1.txt");  break;
		case 2:    	loadFromFile("knapsack2.txt");  break;
		case 3:    	loadFromFile("knapsack3.txt");  break;
		case 4:    	loadFromFile("knapsack4.txt");  break;
		case 5:    	loadFromFile("knapsack5.txt");  break;
		case 6:    	loadFromFile("knapsack6.txt");  break;
		case 7:    	loadFromFile("knapsack7.txt");  break;
		case 8:    	loadFromFile("knapsack8.txt");  break;
		case 9:    	loadFromFile("knapsack9.txt");  break;
		case 10:    loadFromFile("knapsack10.txt");  break;

		}
		clock_t t1;
		clock_t	t2;
		double time;

		t1 = clock();
		knapSackDP();
		t2 = clock();
		time = (double)(t2 - t1) / CLOCKS_PER_SEC;
		cout << "\nIt took " << time << " seconds Using Dynamic programming.\n";

		t1 = clock();
		knapSackBB();
		t2 = clock();
		time = (double)(t2 - t1) / CLOCKS_PER_SEC;
		cout << "\nIt took " << time << " seconds Using BranchBound.\n";
		cout << "\n\n___________________________________________________\n\n\n";

		delete[] items;

		firstLineFlag = 0;
		itemNumber = 0;
		firstLineFlag = 0;
		optimalSol = 0;

		printMenu();
		cin >> select;
		cout << "\n********************************************************************************************" << endl;

	}
	return 0;
}
void printMenu() {
	cout << "********************************************************************************************" << endl;
	cout << "[" << 0 << "] " <<"Quit"<< endl;

	for (int i = 1; i <= 10; i++) {
			cout << "[" << i << "] "
				<< "knapsack"
				<< i
				<< ".txt\n";
	}
	cout << "\nEnter 0 to Quit or Choose which file to compare\n";
	cout << "time complexity Dynamic Programming vs Branch-Bound\n";
	cout << "(Starting with knapsack1.txt, I have 10 items in the file with weightLimit 100)\n";
	cout << "(From knapsack1 to knapsack5, i am adding 5 item each time, using same weightLimit 100)\n";
	cout << "\n(Starting with knapsack6.txt, I have 10 items in the file with weightLimit 110)\n";
	cout << "(From knapsack6 to knapsack10, i am adding 5 item each time also adding 10 to weightLimit)\n";


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

			items = new ItemInfo[numOfItems];

			firstLineFlag = 1;
		}
		else {
			stream >> items[itemNumber].weight;
			stream >> items[itemNumber].value;
			items[itemNumber].payOff = (double)items[itemNumber].value / (double)items[itemNumber].weight;
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
		matrix[i][j].columnParent = j - items[i-1].weight;
		return dvalue;
	}
	else {
		matrix[i][j].rawParent = i - 1;
		matrix[i][j].columnParent = j;
		return rvalue;
	}
}
void knapSackDP() {
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
			else if (items[i-1].weight <= j) {
				matrix[i][j].opt = findMax(matrix, i, j, items[i - 1].value + matrix[i - 1][j - items[i - 1].weight].opt, matrix[i - 1][j].opt);

			}
			else {
				matrix[i][j].opt = matrix[i - 1][j].opt;
				matrix[i][j].rawParent = i - 1;
				matrix[i][j].columnParent = j;

			}
		}
	}
	cout << "\n\n\n___________________________________________________\n";
	cout << "The optimal Knapsack solution using Dynamic Programming has total Value: " << matrix[numOfItems][weightLimit].opt << endl;
	cout << "It involes item Number: ";
	goToParent(matrix, numOfItems, weightLimit);
	cout << "}" << endl;

	for (int i = 0; i <= numOfItems; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
void insertionSort(int size, ItemInfo array[]) {
	for (int i = 1; i < size; i++) {
		ItemInfo temp;
		temp = array[i];
		int j = i - 1;
		while (j >= 0 && array[j].payOff > temp.payOff) {
			array[j + 1] = array[j];
			j--;
		}
		array[j + 1] = temp;
	}
}

void knapSackBB() {

	//Using insertion sort to sort items using payOff
	insertionSort(numOfItems, items);

	//created queue to store most promising nodes.
	queue<TreeNodeInfo> promisingNodeQ;
	TreeNodeInfo before;
	TreeNodeInfo after;

	//initializing root
	before.branchLevel = -1;
	before.currentValue = 0;
	before.currentWeight = 0;
	promisingNodeQ.push(before);

	while (!promisingNodeQ.empty()) {

		//backtracking to go up by poping each node
		before = promisingNodeQ.front();
		promisingNodeQ.pop();

		//reached the root
		if (before.branchLevel == -1) {
			after.branchLevel = 0;
		}

		//reached the leaves or one possible solution
		if (before.branchLevel == numOfItems - 1) {
			continue;
		}

		//Go to next level and calculate total weight and value.
		after.branchLevel = before.branchLevel + 1;
		after.currentWeight = before.currentWeight + items[after.branchLevel].weight;
		after.currentValue = before.currentValue + items[after.branchLevel].value;

		//check it does not exceed weightLimit
		if (after.currentValue > optimalSol && after.currentWeight <= weightLimit) {
			optimalSol = after.currentValue;
		}

		//Calculate upperBound and add item
		after.upperbound = findUpperBound(after);
		if (after.upperbound > optimalSol) {
			promisingNodeQ.push(after);
		}

		//Calculate upperBound and Not add item
		after.currentWeight = before.currentWeight;
		after.currentValue = before.currentValue;
		after.upperbound = findUpperBound(after);
		if (after.upperbound > optimalSol) {
			promisingNodeQ.push(after);
		}
	}
	cout << "The optimal Knapsack solution using Branch and Bound has total Value: " << optimalSol << endl;

}
int findUpperBound(TreeNodeInfo currentNode) {

	//checking if we exceed weightLimit than Go back
	//here it will prun infeasabale items 
	if (currentNode.currentWeight >= weightLimit) {
		return 0; 
	}

	//Figure out new best upperbound to go to.
	int upperBound = currentNode.currentValue;
	int next = currentNode.branchLevel + 1;
	int newWeight = currentNode.currentWeight;

	while ((newWeight + items[next].weight <= weightLimit) && (next < numOfItems)) {
		newWeight = newWeight + items[next].weight;
		upperBound = upperBound + items[next].value;
		next++;
	}

	//Calculate new upperBound using class slide formula
	if (next < numOfItems) {
		upperBound = upperBound + (weightLimit - newWeight) * items[next].payOff;
	}
	return upperBound;
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
		cout << ", " << i;

	}
}
