//HW2 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CIS554 HW2
#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

const int MAXN = 99999;

class n_node { //stand for neighbor_node
public:
	int id;  //neighbor id
	int weight; //edge weight
	//Do your own constructor(s)

	n_node(int x, int y)
	{
		id = x;
		weight = y;
	}
};

class rt_node {
public:
	bool visited; //true if visited; else false
	int cost; //path cost
	int from; //from node
	int h_pos;//the positon of this node in heap
	//Do your own constructor(s)

	rt_node(bool rt_visited, int rt_cost, int rt_from, int rt_h_pos)
	{
		visited = rt_visited;
		cost = rt_cost;
		from = rt_from;
		h_pos = rt_h_pos;
	}

};

class h_node {
public:
	int id;//node id
	int cost; //cost to this node from source
	//Do your own constructor(s)

	h_node(int _id = 0, int _cost = 0) :id(_id), cost(_cost) {}
	bool operator <(const h_node& r)const
	{
		return cost > r.cost;
	}
};


vector<n_node> Graph[MAXN];
vector<rt_node> Routing_Table;

void Dijkstra(int n, int start)
{
	int pos = 0;
	for (int i = 0; i <= n; i++) {
		Routing_Table.push_back(rt_node(false, MAXN, -1, -1));
	}
	priority_queue<h_node> heap;
	while (!heap.empty()) heap.pop();
	Routing_Table[start].cost = 0;
	heap.push(h_node(start, 0));
	Routing_Table[start].h_pos = pos;
	h_node temp;
	while (!heap.empty())
	{
		temp = heap.top();
		heap.pop();
		int fid = temp.id;
		if (Routing_Table[fid].visited) continue;
		Routing_Table[fid].visited = true;
		for (int i = 0; i < Graph[fid].size(); i++)
		{
			int rtt = Graph[fid][i].id;
			int cost = Graph[fid][i].weight;

			if (!Routing_Table[rtt].visited && Routing_Table[rtt].cost > Routing_Table[fid].cost + cost)
			{
				Routing_Table[rtt].cost = Routing_Table[fid].cost + cost;
				Routing_Table[rtt].from = fid;

				pos += 1;
				Routing_Table[rtt].h_pos = pos;
				heap.push(h_node(rtt, Routing_Table[rtt].cost));
			}
		}
	}
	bool stamp = false;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (Routing_Table[j].h_pos == i)
			{
				stamp = true;
			}
		}
		if (!stamp)
		{
			for (int j = 0; j <= n; j++)
			{
				if (Routing_Table[j].h_pos > i)
				{
					Routing_Table[j].h_pos -= 1;
				}
			}
		}
		stamp = false;
	}
}

void pedge(int u, int v, int w)
{
	Graph[u].push_back(n_node(v, w));
}

int main()
{
	int i, from_temp, to_temp, cost_temp;

	for (int i = 0; i <= MAXN; i++)
		if (!Graph[i].empty())
			Graph[i].clear();
	int source;
	int node_num;
	int edge_num;
	ifstream infile;
	infile.open("data.txt");

	infile >> source;
	infile >> node_num;
	infile >> edge_num;

	for (int i = 1; i <= edge_num; i++)
	{
		infile >> from_temp;
		infile >> to_temp;
		infile >> cost_temp;
		pedge(from_temp, to_temp, cost_temp);
	}
	Dijkstra(node_num, source);
	for (int i = 0; i < node_num; i++)
	{
		cout <<"The cost from node "<<source<<" to node "<<i<<" is "<<Routing_Table[i].cost<< "      h_pos: "<< Routing_Table[i].h_pos << " "<<endl;
	}

	cout << endl;

	getchar();
	getchar();
	return 0;
}

