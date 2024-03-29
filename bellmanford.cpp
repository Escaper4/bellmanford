#include "pch.h"
#include "shortestpath.h"

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <limits>


using namespace std;

/*
SID: 100595064, 100650464
*/
struct Graph
{
	int V, E;
	struct Edge* edge;
};
struct transposedEdgeContainer
{
	int source;
	int dest;
	int weight;
};

struct NumberName
{
	string CityName;
	int CityNumber;

};

struct Edge
{
	/*All assignments modify to integer.*/

	string source; //Was string
	string dest; //Was string

	int source_i;
	int dest_i;

	int weight;
};

class weightedGraph
{
public:
	void removeEdge(std::vector<Edge>& edgeContainer, ifstream& inputFile);
	void PrintGraph(int dist[], int n);
	void bellManFord(Graph* graph, vector<transposedEdgeContainer> &superEdgeContainer, ifstream& inputFile, int nodeCount, int edgeCount, int src);
	vector<transposedEdgeContainer> transposeAdjacencyList(std::vector<Edge> &edgeContainer, ifstream &inputFile, vector<string>& nodeList, int edgeCount, vector<NumberName> &numberName);

	int edgeCount(std::ifstream &inputFile);
	int nodeCount(std::ifstream &inputFile, vector<string>& nodeList);
	int minimumSpanningTree(std::ifstream &inputFile, vector<transposedEdgeContainer>& edgesMatrice, int edgeCount);

	struct Graph* createGraph(int Nodes, int edges);
	vector<Edge> removeNode(std::vector<Edge>& input, ifstream&inputFile, vector<string>& listOfNodes);
	vector<Edge> initiateEdgesContainer(std::ifstream &inputFile, int numberOfEdges);
	vector<Edge> changeEdgeWeight(std::vector<Edge>& input, ifstream& InputFile);
	vector<string> getNodes(std::vector<Edge>& edgeContainer, ifstream& inputFile);
private:
};
int weightedGraph::minimumSpanningTree(std::ifstream &inputFile, vector<transposedEdgeContainer>& edgesMatrice, int edgeCount)
{
	inputFile.open("network.txt");
	cout << "\nCurrent Adjacency list: " << endl;

	/*Find edges with minimum weight*/
	/*Sort edges by weight*/

	vector<int> vi = {};

	int buffer;
	for (int i = 0; i <= edgeCount - 1; i++)
	{
		buffer = edgesMatrice.at(i).weight;
		vi.push_back(buffer);
		cout << buffer << endl;
	}

	//Sort edges by minimum weight;
	for (int i = 0; i <= edgeCount - 2; i++) //Was 5
	{
		for (int j = i + 1; j <= edgeCount - 1; j++) //Was 6
		{
			int temp;
			if (vi.at(i) > vi.at(j))
			{
				temp = vi.at(i);
				vi.at(i) = vi.at(j);
				vi.at(j) = temp;
			}

		}
	}
	inputFile.close();
	return 0;
}
void weightedGraph::bellManFord(Graph* graph, vector<transposedEdgeContainer> &superEdgeContainer, ifstream& inputFile, int nodeCount, int edgeCount, int src)
{
	inputFile.open("network.txt");
	int V = graph->V;
	int E = graph->E;
	int* dist = new int[nodeCount];
	for (int i = 0; i < V; i++)
	{
		dist[i] = INT_MAX;
	}
	dist[src] = 0;

	for (int i = 1; i <= V - 1; i++)
	{
		for (int j = 0; j < E; j++)
		{
			int u = graph->edge[j].source_i;
			int v = graph->edge[j].dest_i;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
			{
				dist[v] = dist[u] + weight;
			}
		}
	}
	for (int i = 0; i < E; i++)
	{
		int u = graph->edge[i].source_i;
		int v = graph->edge[i].dest_i;

		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
		{
			cout << "This graph has negative cycles.";
		}
	}
	PrintGraph(dist, V);
	inputFile.close();
	delete [] dist;

}
vector<transposedEdgeContainer> weightedGraph::transposeAdjacencyList(std::vector<Edge> &edgeContainer, ifstream &inputFile, vector<string>& nodeList, int edgeCount, vector<NumberName> &numberName)
{
	//Structs  { transpose edge container } , { NumberName }
	vector<transposedEdgeContainer> superEdgeContainer = {};

	string VertexA, VertexB;
	transposedEdgeContainer _OBJECT;
	inputFile.open("network.txt");
	for (int j = 0; j <= edgeCount - 1; j++) //was - 2;
	{
		_OBJECT.weight = edgeContainer.at(j).weight;
		if (edgeContainer.at(j).source == numberName.at(j).CityName)
		{
			_OBJECT.source = numberName.at(j).CityNumber;
		}
		else
		{
			for (int d = 0; d <= edgeCount - 1; d++) //was  -1
			{
				if (edgeContainer.at(j).source == numberName.at(d).CityName)
				{
					_OBJECT.source = numberName.at(d).CityNumber;
				}
				else
				{
					//do Nothing
				}
			}
		}
		if (edgeContainer.at(j).dest == numberName.at(j).CityName)
		{
			_OBJECT.dest = numberName.at(j).CityNumber;
		}
		else
		{
			for (int r = 0; r <= edgeCount - 1; r++)
			{
				if (edgeContainer.at(j).dest == numberName.at(r).CityName)
				{
					_OBJECT.dest = numberName.at(r).CityNumber;
				}
				else
				{
					//Do nothing
				}
			}
		}
		superEdgeContainer.push_back(_OBJECT);
	}
	
	inputFile.close();
	return superEdgeContainer;
}
void weightedGraph::PrintGraph(int dist[], int n)
{
	cout << "Vertex Distance from Source\n";
	for (int i = 0; i < n; ++i)
	{
		cout << i << "   " << dist[i] << '\n';
	}
}
vector<string> weightedGraph::getNodes(std::vector<Edge>& edgeContainer, ifstream& inputFile)
{
	inputFile.open("network.txt");

	vector<string> vertexListC = {};
	vector<string> vertexListA = {};
	vector<string> vertextListB = {};

	int weight;
	string vertexA, vertexB, BufferA, BufferB;

	for (int z = 0; z <= edgeContainer.size() -  1; z++)
	{
		inputFile >> vertexA >> vertexB >> weight;
		vertexListA.push_back(vertexA);
		vertextListB.push_back(vertexB);
	}
	for (int i = 0; i < vertexListA.size(); i++)
	{
		int j;
		for (j = 0; j < i; j++)
		{
			if (vertexListA.at(i) == vertexListA.at(j))
			{
				break;
			}
		}
		if (i == j)
		{
			BufferA = vertexListA.at(i);
			vertexListC.push_back(BufferA);
		}
	}

	for (int f = 0; f < vertextListB.size(); f++)
	{
		int l;
		for (l = 0; l < f; l++)
		{
			if (vertextListB.at(f) == vertextListB.at(l))
			{
				break;
			}
		}
		if (f == l)
		{
			BufferB = vertextListB.at(f);
			vertexListC.push_back(BufferB);
		}
	}
	
	inputFile.close();
	return vertexListC;
}
vector<Edge> weightedGraph::removeNode(std::vector<Edge> &edgeContainer, ifstream& inputFile, vector<string>& listOfNodes)
{
	int userInput;
	string tempBuffer;
	inputFile.open("network.txt");
	for (int z = 0; z <= listOfNodes.size() - 1; z++)
	{
		cout << z + 1 << ' ' << listOfNodes.at(z) << endl;
	}
	cout << "\nPlease select the node you would like to remove: ";
	cin >> userInput;
	tempBuffer = listOfNodes.at(userInput - 1);
	for (int u = 0; u <= edgeContainer.size() - 1; u++)
	{
		if (edgeContainer.at(u).dest == tempBuffer || edgeContainer.at(u).source == tempBuffer)
		{
			edgeContainer.at(u).dest = "---";
			edgeContainer.at(u).source = "---";
			edgeContainer.at(u).weight = 0;
		}
	}
	cout << "Updated Adjacency list: \n\n";
	for (int j = 0; j <= 4; j++) {
		cout << "Edge: " << j + 1 << ' ' << edgeContainer.at(j).dest << ' '
			<< edgeContainer.at(j).source << ' '
			<< edgeContainer.at(j).weight << endl;
	}
	cout << "\nUpdated Node list: " << endl;
	listOfNodes.erase(listOfNodes.begin() + userInput - 1);
	for (int m = 0; m <= 4; m++) {
		cout << listOfNodes.at(m) << endl;
	}
	inputFile.close();
	return edgeContainer;
}
int weightedGraph::edgeCount(std::ifstream &inputFile)
{
	inputFile.open("network.txt");
	int numberOfEdges = 0;
	string line;
	while (getline(inputFile, line))
	{
		++numberOfEdges;
	}
	inputFile.close();
	return numberOfEdges;
}
void weightedGraph::removeEdge(std::vector<Edge>& edgeContainer, ifstream& inputFile)
{
	int edgetoRemove = 0;

	cout << "===CURRENT EDGES===" << endl << endl;
	for (int j = 0; j <= 4; j++) {
		cout << "Edge: " << j + 1 << ' ' << edgeContainer.at(j).dest << ' '
			<< edgeContainer.at(j).source << ' '
			<< edgeContainer.at(j).weight << endl;
	}
	cout << "There are: " << edgeCount(inputFile) - 1 << " Edges in this graph" << endl << endl;
	cout << "Which edge would you like to remove: ";
	cin >> edgetoRemove;
	edgeContainer.at(edgetoRemove - 1).dest = "---";
	edgeContainer.at(edgetoRemove - 1).source = "---";
	edgeContainer.at(edgetoRemove - 1).weight = NULL;
	cout << "Updated Graph | Adjacency list: " << endl << endl;
	for (int j = 0; j <= 4; j++) {
		cout << "Edge: " << j + 1 << ' ' << edgeContainer.at(j).dest << ' '
			<< edgeContainer.at(j).source << ' '
			<< edgeContainer.at(j).weight << endl;
	}


}
vector<Edge> weightedGraph::changeEdgeWeight(std::vector<Edge>& edgeContainer, ifstream& inputFile)
{
	int numberOfEdges = 0;
	int inputBufferEdge = 0;
	int newEdgeValue = 0;
	cout << endl;
	for (int j = 0; j <= 4; j++) {
		cout << "Edge: " << j + 1 << ' ' << edgeContainer.at(j).dest << ' '
			<< edgeContainer.at(j).source << ' '
			<< edgeContainer.at(j).weight << endl;
	}
	numberOfEdges = edgeCount(inputFile);
	cout << "There are: " << numberOfEdges << " Edges in this graph" << endl << endl;
	cout << "Which edge would you like to modify: ";
	cin >> inputBufferEdge;
	if (inputBufferEdge < 1 || inputBufferEdge > numberOfEdges) {
		cerr << "ERROR: *That edge does not exist.";
	}
	else
	{
		cout << "Value of new edge: ";
		cin >> newEdgeValue;
		cout << '\n';

		edgeContainer.at(inputBufferEdge - 1).weight = newEdgeValue;
		cout << "Updated graph: " << endl << endl;
		for (int j = 0; j <= 4; j++) {
			cout << "Edge: " << j + 1 << ' ' << edgeContainer.at(j).dest << ' '
				<< edgeContainer.at(j).source << ' '
				<< edgeContainer.at(j).weight << endl;
		}
	}
	return edgeContainer;
	inputFile.close();
}
vector<Edge> weightedGraph::initiateEdgesContainer(std::ifstream &inputFile, int numberOfEdges)
{

	int weight;
	inputFile.open("network.txt");

	string vertexA, vertexB;
	vector<Edge> edgeContainer{};
	Edge object;

	for (int i = 0; i <= numberOfEdges - 1; i++) {
		inputFile >> vertexA >> vertexB >> weight;
		object.dest = vertexA;
		object.source = vertexB;
		object.weight = weight;
		edgeContainer.push_back(object);



	}
	inputFile.close();
	return edgeContainer;
}
struct Graph* weightedGraph::createGraph(int Nodes, int edges)
{
	struct Graph* graph = new Graph;
	graph->V = Nodes;
	graph->E = edges;

	graph->edge = new Edge[edges];
	return graph;
}
int weightedGraph::nodeCount(std::ifstream &inputFile, vector<string>& nodeList)
{
	int count = 0;
	inputFile.open("network.txt");
	for (int i = 0; i <= nodeList.size() - 1; i++)
		count++;
	inputFile.close();
	return count;
}
int main()
{
	int userInput;
	int f;
	int r;

	vector<string> p;
	vector<Edge> s;
	vector<transposedEdgeContainer> z;

	weightedGraph object;
	ifstream input;



	r = object.edgeCount(input);
	s = object.initiateEdgesContainer(input, r);
	p = object.getNodes(s, input);
	f = object.nodeCount(input, p);

	cout << "There are " << f << " Nodes in this graph" << endl;
	cout << "There are " << r << " Edges in this graph" << endl;

	vector<NumberName> numName = {};
	NumberName _OBJECT;

	for (int i = 0; i <= f - 1; i++)
	{
		_OBJECT.CityName = p.at(i);
		_OBJECT.CityNumber = i;
		numName.push_back(_OBJECT);
	}
	
	int V = f;
	int E = r;
	struct Graph* graph = object.createGraph(V, E);

	z = object.transposeAdjacencyList(s, input, p, r, numName);
	cout << endl;
	//Source and dest are sawapped
	cout << "[1] Change Edge weight" << '\n'
		<< "[2] Remove edge" << endl <<
		"[3] Remove node" << endl <<
		"[4] Shortest Path" << endl <<
		"[5] Minimum spanning tree" << endl;

	cout << "Input: ";
	cin >> userInput;
	if (userInput == 1)
	{
		object.changeEdgeWeight(s, input);
	}
	if (userInput == 2)
	{
		object.removeEdge(s, input);
	}
	if (userInput == 3)
	{
		cout << '\n';
		object.removeNode(s, input, p);
	}
	if (userInput == 4)
	{	
		int vertextInput;
		cout << "Please enter a start Vertex: ";
			cin >> vertextInput;
			for (int i = 0; i <= r - 1; i++)
			{
				graph->edge[i].dest_i = z.at(i).source;
				graph->edge[i].source_i = z.at(i).dest;
				graph->edge[i].weight = z.at(i).weight;
		}

		
		cout << '\n';
		object.bellManFord(graph, z, input, f, r, vertextInput);
	}
	if (userInput == 5)
	{
		object.minimumSpanningTree(input, z, r);
	}
	input.close();
	return 0;
}

