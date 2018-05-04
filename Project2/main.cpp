#include "BinarySearchTree.h"
#include "RBTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstring>

using namespace std;

void printPrompt();
void printMenu();
void printSelectionForSearch(const string& file);
bool wordMatching(string const &searchFor, string const &word);
void search(string word);
void loadinBST(string filename);
void loadinRBT(string filename);
void traversBST(BinarySearchTree<string> bst);
void traversRBT(RBTree<string> rbt);

string searchKey;
int x;
BinarySearchTree<string> bst;
RBTree<string> rbt;

int main() {

	printPrompt();
	cout << endl;
	return 0;
}

void loadinBST(string filename) {
	ifstream fin;
	
	fin.open(filename);
	if (!fin.good()) {
		cout << "Error: Exiting the program" << endl;
		return;
	}
	string word;


	while (!fin.eof()) {
		getline(fin, word);
		bst.insert(word);
	}
	fin.close();
}
void loadinRBT(string filename) {
	ifstream fin;
	fin.open(filename);
	if (!fin.good()) {
		cout << "Error: Exiting the program" << endl;
		return;
	}
	string word;
	while (!fin.eof()) {
		getline(fin, word);
		rbt.insert(word);
	}
	fin.close();
}

void printPrompt() {
	int select;
	printMenu();
	cin >> select;
	while (select != 0) {
		string file1 = "perm15K.txt"; string file11 = "sorted15K.txt";
		string file2 = "perm30K.txt"; string file12 = "sorted30K.txt";
		string file3 = "perm45K.txt"; string file13 = "sorted45K.txt";
		string file4 = "perm60K.txt"; string file14 = "sorted60K.txt";
		string file5 = "perm75K.txt"; string file15 = "sorted75K.txt";
		string file6 = "perm90K.txt"; string file16 = "sorted90K.txt";
		string file7 = "perm105K.txt"; string file17 = "sorted105K.txt";
		string file8 = "perm120K.txt"; string file18 = "sorted120K.txt";
		string file9 = "perm135K.txt"; string file19 = "sorted135K.txt";
		string file10 = "perm150K.txt"; string file20 = "sorted150K.txt";

		switch (select) {
		case 1:    printSelectionForSearch(file1); break;
		case 2:    printSelectionForSearch(file2); break;
		case 3:    printSelectionForSearch(file3); break;
		case 4:    printSelectionForSearch(file4); break;
		case 5:    printSelectionForSearch(file5); break;
		case 6:    printSelectionForSearch(file6); break;
		case 7:    printSelectionForSearch(file7); break;
		case 8:    printSelectionForSearch(file8); break;
		case 9:    printSelectionForSearch(file9); break;
		case 10:    printSelectionForSearch(file10); break;

		case 11:    printSelectionForSearch(file11); break;
		case 12:    printSelectionForSearch(file12); break;
		case 13:    printSelectionForSearch(file13); break;
		case 14:    printSelectionForSearch(file14); break;
		case 15:    printSelectionForSearch(file15); break;
		case 16:    printSelectionForSearch(file16); break;
		case 17:    printSelectionForSearch(file17); break;
		case 18:    printSelectionForSearch(file18); break;
		case 19:    printSelectionForSearch(file19); break;
		case 20:    printSelectionForSearch(file20); break;
		}
		printMenu();
		cin >> select;
	}
}

void printMenu() {
	cout << endl << endl;
	cout << "[0] Exit the Program" << endl;
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
	cout << "\nEnter 0 to Quit or Choose which file to Search Query From.\n";
	cout << "(For example Enter 1 for perm15K.txt): ";
}

void printSelectionForSearch(const string& file) {
	char choose;
	cout << "\n\n" << "[0] Go back to previous Menu\n"<< "[1] Binary Search Tree\n" << "[2] Red-Black Tree\n";
	cout << "\n\nEnter 0 to Go Back or Choose Tree to Search Query.\n";
	cout << "(For example Enter 1 for Binary Serch Tree): ";
	cin >> choose;
	while (choose != '0') {

		clock_t t1;
		clock_t	t2;
		double time;
		switch (choose) {
		case '1':
			cout << "\n\nLoading Words into Binary Search Tree\n\n";
			t1 = clock();
			loadinBST(file);
			t2 = clock();
			time = (double)(t2 - t1) / CLOCKS_PER_SEC;
			cout << "\n\n****************************************************\n";
			cout << "\nIt took " << time << " seconds to construct BST.\n";
			cout << "\n\n****************************************************\n";
			traversBST(bst);

			break;

		case '2':
			cout << "\n\nLoading Words into Red Black Tree\n\n";
			t1 = clock();
			loadinRBT(file);
			t2 = clock();
			time = (double)(t2 - t1) / CLOCKS_PER_SEC;
			cout << "\n\n****************************************************\n";
			cout << "\nIt took " << time << " seconds to construct RBT.\n";
			cout << "\n\n****************************************************\n";
			traversRBT(rbt);

			break;
		}

		cout << "\n\n" << "[0] Go back to previous Menu\n" << "[1] Binary Search Tree\n" << "[2] Red-Black Tree\n";
		cout << "\n\nEnter 0 to Go Back or Choose Tree to Search Query.\n";
		cout << "(For example Enter 1 for Binary Serch Tree): ";

		cin >> choose;
	}
}
bool wordMatching(string const &searchFor, string const &word) {
	if (searchFor.size() != word.size()) {
		return false;
	}
	size_t pos;

	for (pos = 0; pos < searchFor.size(); pos++) {
		if (searchFor[pos] != '*' && searchFor[pos] != word[pos]) {
			break;
		}
	}
	if (pos == searchFor.size()) {
		return true;
	}
	return false;
}
void search(string word) {
	
	if (wordMatching(searchKey, word) == true) {
		cout << word << endl;
		x++;
		
	}	
}
void traversBST(BinarySearchTree<string> bst) {
	clock_t t3;
	clock_t	t4;
	double time;
	string query = "1";
	cout << "\n\nEnter 0 to Exit or Enter a Query to Search\n ";
	cout << "(Use uppercase letters and astirisk Only): " << endl;
	cin >> query;
	searchKey = query;
	cout << "\n\n\n";


	while (query != "0") {
		x = 0;
		t3 = clock();
		bst.traverse(search);
		t4 = clock();
		time = (double)(t4 - t3) / CLOCKS_PER_SEC;

		cout << "\n\n****************************************************\n";
		cout << "\nIt took " << time << " seconds to search Query.\n";
		cout << "\n There are " << x << " matching Found.";
		cout << "\n\n****************************************************\n";


		cout << "\n\nEnter 0 to Exit or Enter a Query to Search\n ";
		cout << "(Use uppercase letters and astirisk Only): " << endl;
		cin >> query;
		cout << "\n\n\n";
		searchKey = query;
	}
	exit(EXIT_SUCCESS);

}
void traversRBT(RBTree<string> rbt) {
	clock_t t5;
	clock_t	t6;
	double time;
	string query = "1";
	cout << "\n\nEnter 0 to Exit or Enter a Query to Search\n ";
	cout << "(Use uppercase letters and astirisk Only): " << endl;
	cin >> query;
	searchKey = query;
	cout << "\n\n\n";


	while (query != "0") {
		x = 0;
		t5 = clock();
		rbt.traverse(search);
		t6 = clock();
		time = (double)(t6 - t5) / CLOCKS_PER_SEC;

		cout << "\n\n****************************************************\n";
		cout << "\nIt took " << time << " seconds to search Query.\n";
		cout << "\n There are " << x << " matching Found.";
		cout << "\n\n****************************************************\n";


		cout << "\n\nEnter 0 to Exit or Enter a Query to Search\n ";
		cout << "(Use uppercase letters and astirisk Only): " << endl;
		cin >> query;
		cout << "\n\n\n";
		searchKey = query;
	}
	exit(EXIT_SUCCESS);

}
