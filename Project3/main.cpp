//Created by Vaibhav Patel
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include "top.h"

using namespace std;
int select;

void printprompt();
void loadFromFile(const string& filename);
bool didConnectToFile(ifstream& fin, const string& filename);
void printMenu();

int main() {
	printprompt();
	cin.get();
	return 0;
}
void printprompt() {
	printMenu();
	while (select != 0) {
		string file1 = "graphin-DAG.txt";
		string file2 = "graphin-directed.txt";
		switch (select) {
		case 1: loadFromFile(file1); break;
		case 2: loadFromFile(file2); break;
		}
		printMenu();
	}
}
void loadFromFile(const string& filename) {
	ifstream fin;
	ifstream read;
	if (!didConnectToFile(read, filename)) {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}

	int count = 0;
	string justforcountingVertex;
	while (getline(read, justforcountingVertex, '\n')) {
		count++;
	}
	read.close();

	Graph g(count);

	if (!didConnectToFile(fin, filename)) {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}
	string oneLine;
	while (getline(fin, oneLine, '\n')) {

		int node = stoi(oneLine.substr(0, oneLine.find(":")));
		string children = oneLine.substr(oneLine.find(":") + 1);
		stringstream stream(children);

		while(true) {
			int vertex;
			stream >> vertex;
			if (!stream) { break; }
			g.addEdge(node - 1, vertex - 1);
		}
	}
	g.DFS();
	fin.close();
}
bool didConnectToFile(ifstream& fin, const string& filename) {
	fin.open(filename);
	return (fin.is_open());
}
void printMenu() {
	cout << "\n\n\nChoose a file to detect cycle in a graph: ";
	cout << "\n( If cycle found print all back-edge(s). ) ";
	cout << "\n( else print topological order.          ) ";

	cout << "\n\n[0] Exit";
	cout << "\n[1] graphin-DAG.txt";
	cout << "\n[2] graphin-directed.txt\n";
	cin >> select;
}