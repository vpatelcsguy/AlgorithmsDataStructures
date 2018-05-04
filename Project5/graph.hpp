//Created by Vaibhav Patel

#include<iostream>
#include <fstream>
#include <string>
#include <list>
#include <stack>
#define infinity INT_MAX
#define NULL1	-1

using namespace std;

struct Edge {
	int u;
	int v;
	int w;
	struct Edge * nextEdge;
};
struct DFS_Info {
	string color;
	int start;
	int finish = 0;
};
struct Vertex_Info
{
	int v;
	int d;
};
Edge * Edge_Info(Edge * head, int v, int w) {
	Edge * singleEdge = new Edge[sizeof(Edge)];
	singleEdge->v = v;
	singleEdge->w = w;
	singleEdge->nextEdge = head;

	return singleEdge;
}
class Graph {
private:
	int negativeWeightCycle = -1;
	int noOfvertex;
	int noOfedge;
	int negEdgeCount = 0;
	int noCycleflag;
	int time;
	Edge * edgeList;
	list<Edge> * DFS_vertexList;
	int cost[10];
	int parent[10];

	void DfsTravarsal(int i, DFS_Info x[], stack<int> &Stack);
	void printMSG(int source);
	void Dijkstra(int source);
	void BellmanFord(int source);
	void heap(Vertex_Info list[], int size, int location[]);
	void dijkstraHeapify(Vertex_Info list[], int size, int i, int location[]);
	Vertex_Info getMinVertex(Vertex_Info list[], int size, int location[]);
	void swapLocation(Vertex_Info list[], int location[], int i, int j);
	void decreaseKey(Vertex_Info list[], Vertex_Info singleEdge, int location[]);
	void findPath(int parent[], int v, int source);
	void printPath(int parent[], int source);

public:
	Graph(int noOfvertex, int noOfedge);
	void addEdge(int edgeNumber, int u, int v, int w);
	void DFS(int source);
};
Graph::Graph(int noOfvertex, int noOfedge) {
	this->noOfedge = noOfedge;
	this->noOfvertex = noOfvertex;
	edgeList = new Edge[noOfedge];
	DFS_vertexList = new list<Edge>[noOfvertex];
}
void Graph::addEdge(int edgeNumber, int u, int v, int w) {
	if (w < 0) { negEdgeCount++; }
	edgeList[edgeNumber].u = u;
	edgeList[edgeNumber].v = v;
	edgeList[edgeNumber].w = w;
	DFS_vertexList[u].push_back(edgeList[edgeNumber]);
}

void Graph::DfsTravarsal(int i, DFS_Info x[], stack<int> &Stack) {
	time = time + 1;
	x[i].start = time;
	x[i].color = "G";
	list<Edge>::iterator j;
	for (j = DFS_vertexList[i].begin(); j != DFS_vertexList[i].end(); j++) {
		Edge edge = *j;
		if (x[j->v].color == "W") {
			noCycleflag = 1;
			DfsTravarsal(j->v, x, Stack);
		}
		if (x[j->v].color == "G" && x[j->v].finish == 0) {
			noCycleflag = 0;
		}
	}
	x[i].color = "B";
	time = time + 1;
	x[i].finish = time;
	Stack.push(i);

}

void Graph::DFS(int source) {
	stack<int> Stack;
	DFS_Info * DFS_vertexInfo = new DFS_Info[noOfvertex];

	for (int i = 0; i < noOfvertex; i++) {
		DFS_vertexInfo[i].color = "W";
		parent[i] = NULL1;
		cost[i] = infinity;
	}
	cost[source] = 0;
	parent[source] = 0;
	time = 0;
	for (int i = 0; i < noOfvertex; i++) {
		if (DFS_vertexInfo[i].color != "B") {
			DfsTravarsal(i, DFS_vertexInfo, Stack);
		}
	}
	
	printMSG(source);

	//Running DAG if No Cycle
	if (noCycleflag == 1) {
		while (Stack.empty() == false) {
			int source = Stack.top();
			Stack.pop();
			list<Edge>::iterator j;
			if (cost[source] != infinity) {
				for (j = DFS_vertexList[source].begin(); j != DFS_vertexList[source].end(); j++) {
					if (cost[j->v] > cost[source] + j->w) {
						cost[j->v] = cost[source] + j->w;
						parent[j->v] = j->u;
					}
				}
			}
		}
		printPath(parent, source);
	}
}

void Graph::printMSG(int source) {
	if (noCycleflag == 1 && negEdgeCount == 0) {
		cout << "\n\nThe Graph has No Cycle, and No negative edge-weight. \n";
		cout << "Running DAG on this graph.\n";
	}
	else if (noCycleflag == 1 && negEdgeCount > 0) {
		cout << "\n\nThe Graph has No Cycle, but has negative edge-weight. \n";
		cout << "Running DAG on this graph.\n";
	}
	else if (noCycleflag == 0 && negEdgeCount == 0) {
		cout << "\n\nThe Graph has Cycle, but No negative edge-weight. \n";
		cout << "Running Dijkstra on this graph.\n";
		Dijkstra(source);
	}
	else if (noCycleflag == 0 && negEdgeCount > 0) {
		cout << "\n\nThe Graph has Cycle, and has negative edge-weight. \n";
		cout << "Running Bellman-Ford on this graph.\n";
		BellmanFord(source);
	}
}
void Graph::Dijkstra(int source) {
	Edge * adjList[10];
	Vertex_Info minimum;
	Vertex_Info list[10];
	int location[10];

	for (int i = 0; i < noOfvertex; i++) {
		adjList[i] = NULL;
		cost[i] = infinity;
		parent[i] = NULL1;
		list[i].d = infinity;
		list[i].v = i;
		location[i] = list[i].v;
	}
	for (int i = 0; i < noOfedge; i++) {
		adjList[edgeList[i].u] = Edge_Info(adjList[edgeList[i].u], edgeList[i].v, edgeList[i].w);
	}
	cost[source] = 0;
	list[source].d = 0;
	heap(list, noOfvertex-1, location);
	for (int i = 0; i < noOfvertex; i++) {
		minimum = getMinVertex(list, noOfvertex-1, location);
		Edge * traverse = adjList[minimum.v];

		while (traverse != NULL) {
			int u = minimum.v;
			int v = traverse->v;
			int w = traverse->w;
			if (cost[u] != infinity && cost[v] > cost[u] + w) {
				cost[v] = cost[u] + w;
				parent[v] = u;
				Vertex_Info change;
				change.v = v;
				change.d = cost[v];
				decreaseKey(list, change, location);
			}
			traverse = traverse->nextEdge;
		}
	}
	printPath(parent, source);
}
void Graph::heap(Vertex_Info list[], int size, int location[]) {
	for (int i = size / 2; i >= 0; i--) {
		dijkstraHeapify(list, size, i, location);
	}
}
void Graph::swapLocation(Vertex_Info list[], int location[], int i, int j) {
	Vertex_Info temp;
	location[list[j].v] = i;
	location[list[i].v] = j;
	temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}
void Graph::dijkstraHeapify(Vertex_Info list[], int size, int index, int location[]) {
	while ((2 * index) <= size) {
		if ((2 * index) + 1 > size) {
			if (list[index].d > list[2 * index].d) {} break;
		}
		if (list[index].d > list[2 * index].d || list[index].d > list[2 * index + 1].d) {
			if (list[2 * index].d <= list[(2 * index) + 1].d) {
				swapLocation(list, location, 2 * index, index);
				index = 2 * index;
			}
			else if (list[2 * index].d > list[(2 * index) + 1].d) {
				swapLocation(list, location, 2 * index + 1, index);
				index = (2 * index) + 1;
			}
		}
		else {	break;	}
	}
}
Vertex_Info Graph::getMinVertex(Vertex_Info list[], int size, int location[]) {
	location[list[0].v] = size;
	location[list[size].v] = 0;
	Vertex_Info min = list[0];
	list[0] = list[size];
	--size;
	dijkstraHeapify(list, size, 0, location);
	return min;
}
void Graph::decreaseKey(Vertex_Info list[], Vertex_Info singleEdge, int location[]) {
	list[location[singleEdge.v]].d = singleEdge.d;
	int k = location[singleEdge.v];
	while (k > 1) {
		if (list[k / 2].d > list[k].d) {
			swapLocation(list, location, k / 2, k);
			k = k / 2;
		}
		else {	break;	}
	}
}
void Graph::BellmanFord(int source) {
	Edge * adjList[10];
	Edge * traverse;
	
	for (int i = 0; i < noOfvertex; i++) {
		adjList[i] = NULL;
		cost[i] = infinity;
		parent[i] = NULL1;
	}
	for (int i = 0; i < noOfedge; i++) {
		adjList[edgeList[i].u] = Edge_Info(adjList[edgeList[i].u], edgeList[i].v, edgeList[i].w);
	}
	cost[source] = 0;
	parent[source] = 0;
	for (int i = 0; i < noOfvertex-1; ++i) {
		for (int j = 0; j < noOfvertex; ++j) {
			traverse = adjList[j];
			while (traverse != NULL) {
				if (cost[j] == infinity) {
					traverse = traverse->nextEdge;
					continue;
				}
				if (traverse->w + cost[j] < cost[traverse->v]) {
					cost[traverse->v] = traverse->w + cost[j];
					parent[traverse->v] = j;
				}
				traverse = traverse->nextEdge;
			}
		}
	}
	for (int j = 0; j < noOfvertex; ++j) {
		traverse = adjList[j];
		while (traverse != NULL) {
			if (traverse->w + cost[j] < cost[traverse->v]) {
				negativeWeightCycle = j;
			}
			traverse = traverse->nextEdge;
		}
	}
	if (negativeWeightCycle != -1) {
		cout << "*************************************************\n";
		cout << "\nNegative weight cycle in the Graph.\n" << endl;
		cout << "*************************************************\n";

	}
	else {
		printPath(parent, source);
	}
}
void Graph::findPath(int parent[], int v, int source) {
	if (v == source) {
		cout << source + 1 << " ";
		return;
	}
	else if (parent[v] == NULL1) {
		cout << v + 1 << " ";
		return;
	}
	else {
		findPath(parent, parent[v], source);
		cout << v + 1 << " ";
	}
}
void Graph::printPath(int parent[], int source) {
	cout << "*************************************************\n";
	cout << "Shortest Path from Source to each Vertex:\n\n";

	for (int i = 0; i < noOfvertex; ++i) {
		if (cost[i] == infinity) {
			cout << "| " << source + 1 << " to " << i + 1 << " |"
				<< "   | No Path Found |\n";
		}
		else {
			cout << "| " << source + 1 << " to " << i + 1 << " |"
				<< "   | Distance: " << cost[i] << " |"
				<< "   | Path: ";
			findPath(parent, i, source);
			cout << " |\n";
		}
	}
	cout << "\n*************************************************\n";
}
