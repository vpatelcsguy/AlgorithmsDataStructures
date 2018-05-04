//Created by Vaibhav Patel
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sstream>
#include "Graph.hpp"

using namespace std;
int select;

void printprompt();
Graph loadFromFile(const string& filename);
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
		string file1 = "graphin_w_ud.txt";
		Graph g = loadFromFile(file1);
		switch (select) {
		case 1:  
				g.PrimsMST();
				break;
		case 2:
				g.KruskalMST();
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
			graph.addEdge(countEdge1, countNode1-1, vertex1-1, weight1);
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
	cout << "\n\n\nChoose which MST Algorithm to RUN on graphin_w_ud.txt: ";
	cout << "\n( Output of list of edges in MST is in seprate FILE) ";
	cout << "\n( inside same Project Folder and on the screen too.) ";

	cout << "\n\n[0] Exit";
	cout << "\n[1] Prim's Algorithm";
	cout << "\n[2] Kruskal's Algorithm\n";
	cin >> select;
}