//Created by Vaibhav Patel

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include "graph.hpp"

using namespace std;
int select;

void printprompt();
Graph loadFromFile(const string& filename);
bool didConnectToFile(ifstream& fin, const string& filename);
void printMenu();
void askUser(Graph g);

int main() {
	printprompt();
	cin.get();
	return 0;
}
void printprompt() {
	printMenu();
	while (select != 0) {
		string file1 = "graphin_Fig1.txt";
		string file2 = "graphin_Fig2.txt";
		string file3 = "graphin_Fig4.txt";
		string file4 = "graphin_Fig5.txt";

		switch (select) {
		case 1:
			{Graph g1 = loadFromFile(file1); askUser(g1);}
			break;
		case 2:
			{Graph g2 = loadFromFile(file2); askUser(g2); }
			break;
		case 3:
			{Graph g3 = loadFromFile(file3); askUser(g3); }
			break;
		case 4:
			{Graph g4 = loadFromFile(file4); askUser(g4); }
			break;

		}
		printMenu();
	}
}
Graph loadFromFile(const string& filename) {
	ifstream fin;
	ifstream read;

	int countNode = 0;
	int countEdge = 0;
	int countNode1 = 1;
	int countEdge1 = 0;

	if (!didConnectToFile(fin, filename)) {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}
	string oneLine;
	while (getline(fin, oneLine, '\n')) {
		int node = stoi(oneLine.substr(0, oneLine.find(":")));
		string children = oneLine.substr(oneLine.find(":") + 1);
		stringstream stream(children);
		while (true) {
			int vertex;
			int weight;
			stream >> vertex;
			stream >> weight;
			if (!stream) { break; }
			countEdge++;
		}
		countNode++;
	}
	fin.close();

	Graph graph(countNode, countEdge);

	if (!didConnectToFile(read, filename)) {
		cerr << "Error: Unable to open file." << endl;
		exit(1);
	}
	string oneLine1;
	while (getline(read, oneLine1, '\n')) {
		int node1 = stoi(oneLine1.substr(0, oneLine1.find(":")));
		string children1 = oneLine1.substr(oneLine1.find(":") + 1);
		stringstream stream1(children1);
		while (true) {
			int vertex1;
			int weight1;
			stream1 >> vertex1;
			stream1 >> weight1;

			if (!stream1) { break; }
			graph.addEdge(countEdge1, countNode1 - 1, vertex1 - 1, weight1);
			countEdge1++;
		}
		countNode1++;
	}
	read.close();
	return graph;
}
bool didConnectToFile(ifstream& fin, const string& filename) {
	fin.open(filename);
	return (fin.is_open());
}
void printMenu() {
	cout << "\n\n\nChoose a file to find Shortest-Path in a graph: ";
	cout << "\n\n[0] Exit\n";
	cout << "[1] graphin_Fig1.txt\n";
	cout << "[2] graphin_Fig2.txt\n";
	cout << "[3] graphin_Fig4.txt\n";
	cout << "[4] graphin_Fig5.txt\n";

	cin >> select;
}
void askUser(Graph g) {
	int source;
	cout << "\n____________________________________________\n";
	cout << "\nEnter a source node: "
			<< "(or Enter 0 to Go Back) \n";

	cin >> source;
			
	while (source != 0) { 
		g.DFS(source - 1); 
		cout << "\n____________________________________________\n";

		cout << "\nEnter another Source node: \n"
			<< "(or Enter 0 to Go Back) \n";
		cin >> source;
	}

}
