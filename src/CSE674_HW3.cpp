//HW3 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CSE674 HW3
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class n_node   //stand for neighbor_node
{
public:
	int id;  //neighbor id
	int weight; //edge weight
	//Do your own constructor(s)
	n_node(){}
	n_node(int x, int y) {
		id = x;
		weight = y;
	}
};

/*
class rt_node
{
public:
	bool is_visited; //true if visited; else false
	int cost; //path cost
	int from; //from node
//    int h_pos;//the positon of this node in heap
//Do your own constructor(s)
};
*/

class h_node
{
public:
	int from;
	int id;//node id
	int cost; //cost to this node from source
	//Do your own constructor(s)
	h_node() {}
	h_node(int x, int y,int z) {
		from = x;
		id = y;
		cost = z;
	}
};

class check
{
public:
	int from;
	int to;
	int len;
	check() {}
};

vector < vector<n_node>* > Graph;
vector <h_node> Heap;
vector <check> Check;


void heapify(vector<h_node>& heap, int tail) {
	if (tail == 0) { return; }
	int parent = (tail - 1) / 2;
	if (heap.empty()) { return; }
	else {
		if (heap[parent].cost > heap[tail].cost) {
			h_node temp;
			temp = heap[parent];
			heap[parent] = heap[tail];
			heap[tail] = temp;
		}
		else { return; }
	}
	heapify(heap, parent);
}

int main()
{
	int source, num_nodes, num_edges, from_temp, to_temp, weigh;
	ifstream in("graph.txt");
	in >> source >> num_nodes >> num_edges;
	for (int i = 1; i <= num_nodes; i++) {
		vector<n_node>* V_t = new vector<n_node>;
		Graph.push_back(V_t);
	}
	for (int j = 1; j <= num_edges; j++) {
		in >> from_temp >> to_temp >> weigh;
		n_node n1(from_temp, weigh);
		n_node n2(to_temp, weigh);
		Graph[from_temp]->push_back(n2);
		Graph[to_temp]->push_back(n1);
	}
	//int tjmadeit = 0;
	int key = source;
	bool visited[999] = { false };
	visited[source] = true;
	while (true) {
		int count = 0;
		for (int ch = 1; ch <= num_nodes; ch++) {
			if (visited[ch - 1] == true)count++;
		}
		if (count == num_nodes) break;
		for (auto it1 = Graph[key]->begin(); it1 != Graph[key]->end(); it1++) {
			if (visited[(*it1).id] == false) {
				h_node h_temp(key,(*it1).id, (*it1).weight);
				Heap.push_back(h_temp);
				heapify(Heap, Heap.size() - 1);
			}
		}
	label:
		if (visited[Heap[0].id] == true) {
			h_node poptemp_0;
			poptemp_0 = Heap[0];
			Heap[0] = Heap[Heap.size() - 1];
			Heap[Heap.size() - 1] = poptemp_0;
			Heap.pop_back();
			goto label;
		}
		visited[Heap[0].id] = true;
		check outp;
		outp.from = Heap[0].from;
		outp.to = Heap[0].id;
		outp.len = Heap[0].cost;
		Check.push_back(outp);
		key = Heap[0].id;
		h_node poptemp;
		poptemp = Heap[0];
		Heap[0] = Heap[Heap.size() - 1];
		Heap[Heap.size() - 1] = poptemp;
		Heap.pop_back();
	}
	
	int sum = 0;
	for (auto it2 : Check) {
		cout << it2.from << " " << it2.to << " " << it2.len << endl;
		sum += it2.len;
	}
	cout << "The overall cost of the minimum spinning tree is " << sum << "." << endl;
	cout << endl;
	cout << endl;
	cout << endl;



	in.close();
	system("pause");
	return 0;
	
}
