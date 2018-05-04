//Created by Vaibhav Patel

#include<iostream>
#include <fstream>
#include <string>

using namespace std;

struct Edge {
	int u;
	int v;
	int w;
};
struct Subset {
	int parent;
	int noOfNodes;
};
struct Vertex {
	int value;
	int cost;
	Vertex * nextVertex;
};
Vertex * VertexInfo(Vertex * head, int x, int weight) {
	Vertex * addinfo = new Vertex[sizeof(Vertex)];
	addinfo->value = x;
	addinfo->nextVertex = head;
	addinfo->cost = weight;
	head = addinfo;
	return addinfo;
}
class Graph {
private:
	int noOfvertex;
	int noOfedge;
	Edge * edgeList;
	Vertex * adjList[7];
	Vertex * finalMST[7];
	int source = 0;
	int destination;
	bool visited[7];
	Vertex * temp;
	Edge singalEdge;
	Edge arr[18];
	int sizeOfarr = 0;

	void buildHeap(int size, int root, Edge edgeList[]);
	void heapSort(int size, Edge edgeList[]);
	int  kruskalFindParent(Subset subList[], int i);
	void kruskalUnion(Subset subset[], int srcParent, int destParent);
	void addToList(Edge list[], int size, Edge i);
	void primsheapify(Edge list[], int size, int k);
	void deleteNode(Edge list[], int size, int k);
	Edge extractMin(Edge list[], int size);
	void primsSwap(Edge list[], int i, int j);
	void nextVertexToGO();
	void writeKruskalToFile(Edge mstList[], int count);
	void writePrimsToFile();

 
public:
	Graph(int noOfvertex, int noOfedge);
	void addEdge(int edgeNumber, int u, int v, int w);
	void KruskalMST();
	void PrimsMST();

};

Graph::Graph(int noOfvertex, int noOfedge) {
	this->noOfedge = noOfedge;
	this->noOfvertex = noOfvertex;
	edgeList = new Edge[noOfedge];
	
}
void Graph::addEdge(int edgeNumber, int u, int v, int w) {
	edgeList[edgeNumber].u = u;
	edgeList[edgeNumber].v = v;
	edgeList[edgeNumber].w = w;
}
void Graph::heapSort(int size, Edge edgeList[]) {
	int notLeaf = size / 2 - 1;
	for (int i = notLeaf; i >= 0; i--) {
		buildHeap(size, i, edgeList);
	}

	for (int j = size - 1; j >= 0; j--) {
		Edge temp = edgeList[0];
		edgeList[0] = edgeList[j];
		edgeList[j] = temp;
		buildHeap(j, 0, edgeList);
	}
}
void Graph::buildHeap(int size, int root, Edge edgeList[]) {
	int leftChild = 2 * root + 1;
	int rightChild = 2 * root + 2;
	int p = root;
	if (leftChild < size && edgeList[leftChild].w > edgeList[p].w) {
		p = leftChild;
	}
	if (rightChild < size && edgeList[rightChild].w > edgeList[p].w) {
		p = rightChild;
	}
	if (p != root) {
		Edge temp = edgeList[root];
		edgeList[root] = edgeList[p];
		edgeList[p] = temp;
		buildHeap(size, p, edgeList);
	}
}
int Graph::kruskalFindParent(Subset subList[], int i) {
	if (subList[i].parent != i) {
		subList[i].parent = kruskalFindParent(subList, subList[i].parent);
	}
	return subList[i].parent;
}
void Graph::kruskalUnion(Subset subList[], int srcParent, int destParent) {
	int srcRoot = kruskalFindParent(subList, (srcParent));
	int destRoot = kruskalFindParent(subList, (destParent));
	if (subList[srcRoot].noOfNodes < subList[destRoot].noOfNodes) {
		subList[srcRoot].parent = destRoot;
	} else if (subList[srcRoot].noOfNodes > subList[destRoot].noOfNodes) {
		subList[destRoot].parent = srcRoot;
	}
	else {
		subList[destRoot].parent = srcRoot;
		subList[srcRoot].noOfNodes++;
	}
}
void Graph::KruskalMST() {
	int countEdgekruskalUnion = 0;
	int nextSmallest = 0;
	Edge * mstList = new Edge[noOfvertex];

	heapSort(noOfedge, edgeList);
	Subset * subList = new Subset[noOfvertex];
	for (int i = 0; i < noOfvertex; i++) {
		subList[i].parent = i;
		subList[i].noOfNodes = 0;
	}
	while (countEdgekruskalUnion < (noOfvertex - 1)) {
		Edge edgeToMST = edgeList[nextSmallest++];
		int srcParent = kruskalFindParent(subList, edgeToMST.u);
		int destParent = kruskalFindParent(subList, edgeToMST.v);
		if (srcParent != destParent) {
			mstList[countEdgekruskalUnion++] = edgeToMST;
			kruskalUnion(subList, srcParent, destParent);
		}
	}
	writeKruskalToFile(mstList, countEdgekruskalUnion);
}

void Graph::addToList(Edge list[], int size, Edge i) {
	list[size] = i;
	while (size >= 1) {
		if (list[size / 2].w > list[size].w){
			primsSwap(list, size, size / 2);
			size = size / 2;
		}
		else{
			break;
		}
	}
}
void Graph::primsheapify(Edge list[], int size, int k)
{
	while ((2*k) < size) {
		if ((2*k) + 1 >= size) {
			if (list[k].w > list[2*k].w) {
				primsSwap(list, k, k*2);
				break;
			}
		}
		if (list[k].w > list[2*k].w || list[k].w > list[2*k+1].w) {
			if (list[2 * k].w <= list[(2 * k) + 1].w) {
				primsSwap(list, k, k * 2);
				k = 2 * k;
			} else if (list[2*k].w > list[2*k+1].w) {
				primsSwap(list, k, k*2+1);
				k = 2 * k + 1;
			}
		}
		else { break; }
	}
}
void Graph::deleteNode(Edge list[], int size, int k)
{
	primsSwap(list, k, size-1);
	--size;
	primsheapify(list, size, k);
}

Edge Graph::extractMin(Edge list[], int size)
{
	Edge smallest = list[0];
	deleteNode(list, size, 0);
	return smallest;
}
void Graph::primsSwap(Edge list[], int i, int j) {
	Edge temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}
void Graph::PrimsMST() {
	for (int i = 0; i < noOfvertex; ++i) {
		adjList[i] = NULL;
		finalMST[i] = NULL;
		visited[i] = false;

	}
	for (int i = 0; i < noOfedge; i++) {
		adjList[edgeList[i].u] = VertexInfo(adjList[edgeList[i].u], edgeList[i].v, edgeList[i].w);
	}
	int edgeInMST = 0;
	while (edgeInMST < noOfvertex-1) {
		if (visited[source] == false) {           
			visited[source] = true;
			temp = adjList[source];
			while (temp != NULL) {
				singalEdge.u = source;
				singalEdge.v = temp->value;
				singalEdge.w = temp->cost;
				if (!visited[singalEdge.v]) {
					addToList(arr, sizeOfarr, singalEdge);
					sizeOfarr++;
				}
				temp = temp->nextVertex;
			}
			nextVertexToGO();
			edgeInMST++;
		}
		else {
			nextVertexToGO();
		}
	}
	writePrimsToFile();
}
void Graph::nextVertexToGO() {
	singalEdge = extractMin(arr, sizeOfarr);
	sizeOfarr--;
	destination = singalEdge.v;
	source = singalEdge.u;
	if (visited[destination] == false) {
		finalMST[source] = VertexInfo(finalMST[source], destination, singalEdge.w);
		finalMST[destination] = VertexInfo(finalMST[destination], source, singalEdge.w);
	}
	source = destination;
}
void Graph::writeKruskalToFile(Edge mstList[], int count){
	string outfile = "kruskalout.txt";
	ofstream fout;
	fout.open(outfile);
	if (!fout.is_open()) {
		cerr << "Error writing to output file." << endl;
		exit(1);
	}
	fout << "Here is format of the list: \n"
		 << "(sourceVertex - destinationVertex): edgeWeight\n";
	cout << "\n\n\nHere is format of the list: \n"
		<< "(sourceVertex - destinationVertex): edgeWeight\n";


	for (int i = 0; i < count; i++) {
		fout<< "("
			<< (mstList[i].v + 1)
			<< "-"
			<< (mstList[i].u + 1)
			<< ")"
			<< ":"
			<< mstList[i].w
			<< endl;
		cout << "("
			<< (mstList[i].v + 1)
			<< "-"
			<< (mstList[i].u + 1)
			<< ")"
			<< ":"
			<< mstList[i].w
			<< endl;
	}
	fout.close();
}
void Graph::writePrimsToFile() {
	string outfile = "primout.txt";
	ofstream fout;
	fout.open(outfile);
	if (!fout.is_open()) {
		cerr << "Error writing to output file." << endl;
		exit(1);
	}
	fout << "Here is format of the list: \n"
		<< "(sourceVertex - destinationVertex): edgeWeight\n";
	cout << "\n\n\nHere is format of the list: \n"
		<< "(sourceVertex - destinationVertex): edgeWeight\n";

	for (int i = 0; i < noOfvertex - 1; ++i) {
		fout << "("
			<< (finalMST[i]->value + 1)
			<< "-"
			<< (i + 1)
			<< ")"
			<< ":"
			<< (finalMST[i]->cost)
			<< endl;

		cout << "("
			<< (finalMST[i]->value + 1)
			<< "-"
			<< (i + 1)
			<< ")"
			<< ":"
			<< (finalMST[i]->cost)
			<< endl;
	}
	fout.close();

}