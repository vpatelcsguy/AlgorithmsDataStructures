//Created by Vaibhav Patel

#include<iostream>
#include <list>
#include <stack>

using namespace std;
int time;
int flag;
int printOneTime = 1;

struct Info {
	string color;
	int start;
	int finish = 0;
	int parent;
};

class Graph {
private:
	int numOfVertex;    
	list<int> * vertexList;
	void DfsTravarsal(int i, Info x[], stack<int> &Stack);
public:
	Graph(int numOfVertex);  
	void addEdge(int u, int v);
	void DFS();
};

Graph::Graph(int numOfVertex) {
	this->numOfVertex = numOfVertex;
	vertexList = new list<int>[numOfVertex];
}

void Graph::addEdge(int u, int v) {
	vertexList[u].push_back(v);
}

void Graph::DfsTravarsal(int i, Info x[], stack<int> &Stack) {
	time = time + 1;
	x[i].start = time;
	x[i].color = "G";

	list<int>::iterator j;
	for (j = vertexList[i].begin(); j != vertexList[i].end(); j++) {
		if (x[*j].color == "W") {
			flag = 1;
			x[*j].parent = i;
			DfsTravarsal(*j, x, Stack);
		}
		if (x[*j].color == "G" && x[*j].finish == 0) {
			flag = 0;
			if (printOneTime == 1) {
				cout << "\n\nThe Graph has Cycle with back-edge(s): \n";
				printOneTime = 0;
			}
			cout << "(" << i + 1 << "," << *j + 1 << ")" << endl;
		}
	}

	x[i].color = "B";
	time = time + 1;
	x[i].finish = time;

	Stack.push(i);

}

void Graph::DFS() {
	stack<int> Stack;
	Info * vertexInfo = new Info[numOfVertex];

	for (int i = 0; i < numOfVertex; i++) {
		vertexInfo[i].color = "W";
		vertexInfo[i].parent = NULL;
	}
	time = 0;
	for (int i = 0; i < numOfVertex; i++) {
		if (vertexInfo[i].color != "B") {
			DfsTravarsal(i, vertexInfo, Stack);
		}
	}
	if (flag == 1) {
		cout << "\n\nThe Graph has No Cycle, Here is Topological Order: \n";
	}
	for (int i = 0; i < numOfVertex; i++) {
		if (flag == 1) {
			cout << Stack.top() + 1 << " ";
			Stack.pop();
		}
	}
}

