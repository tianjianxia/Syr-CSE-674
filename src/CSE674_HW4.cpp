//HW4 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CSE674 HW4
#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<math.h>

using namespace std;

class cell {
public:
	int id;
	int wall;
	bool visited;
	bool in_structure;
	int from;
	cell() {
		visited = false;
		in_structure = false;
		from = -1;
	}
	cell(int id0, int wall0) {
		id = id0;
		wall = wall0;
		visited = false;
		in_structure = false;
		from = -1;
	}
};

vector<cell> Maze;
vector<vector<bool>> rt;
stack<cell> Stack;
queue<cell> Queue;
vector<int> output;

vector<vector<int>*> MazeToGraph(vector<cell>& maze) {
	vector<bool> V_temp(4);

	for (int i = 0; i <= maze.size() - 1; i++) {
		switch (maze[i].wall) {
		case 0: V_temp = { true,true,true,true }; break;
		case 1: V_temp = { false,true,true,true }; break;
		case 2: V_temp = { true,false,true,true }; break;
		case 3: V_temp = { false,false,true,true }; break;
		case 4: V_temp = { true,true,false,true }; break;
		case 5: V_temp = { false,true,false,true }; break;
		case 6: V_temp = { true,false,false,true }; break;
		case 7: V_temp = { false,false,false,true }; break;
		case 8: V_temp = { true,true,true,false }; break;
		case 9: V_temp = { false,true,true,false }; break;
		case 10: V_temp = { true,false,true,false }; break;
		case 11: V_temp = { false,false,true,false }; break;
		case 12: V_temp = { true,true,false,false }; break;
		case 13: V_temp = { false,true,false,false }; break;
		case 14: V_temp = { true,false,false,false }; break;
		case 15: V_temp = { false,false,false,false }; break;
		}
		rt.push_back(V_temp);
	}
	vector<vector<int>*> g;
	for (int j = 0; j <= maze.size() - 1; j++) {
		vector<int>* neighbour = new vector<int>;
		//In case there is no neighbour out of bound
		if (rt[j][0] && (j + (sqrt(maze.size()))) >= 0 && (j + (sqrt(maze.size()))) <= (maze.size() - 1)) { neighbour->push_back(j + (sqrt(maze.size()))); }
		if (rt[j][1] && (j + 1) >= 0 && (j + 1) <= (maze.size() - 1)) { neighbour->push_back(j + 1); }
		if (rt[j][2] && (j - (sqrt(maze.size()))) >= 0 && (j - (sqrt(maze.size()))) <= (maze.size() - 1)) { neighbour->push_back(j - (sqrt(maze.size()))); }
		if (rt[j][3] && (j - 1) >= 0 && (j - 1) <= (maze.size() - 1)) { neighbour->push_back(j - 1); }

		g.push_back(neighbour);
	}

	return g;
}

void addRandW(int index, int m_size, vector<vector<char>>& M) {
	int i = ((index) / m_size) * 3 + 1, j = (index % m_size) * 5 + 2;
	int si, sj, ei, ej, ni, nj, wi, wj;
	si = i + 1;
	sj = j;
	ei = i;
	ej = j + 2;
	ni = i - 1;
	nj = j;
	wi = i;
	wj = j - 1;
	if (!rt[index][0]) M[si][sj] = '-';
	if (!rt[index][1]) M[ei][ej] = '-';
	if (!rt[index][2]) M[ni][nj] = '-';
	if (!rt[index][3]) M[wi][wj] = '-';
	for (int idx = 0; idx <= output.size() - 1; idx++) {
		if (index == output[idx]) {
			M[i][j] = '*';
		}
	}
}
void printMaze(int start, int m_size, vector<vector<bool>> rt, vector<int> output) {
	vector<vector<char>> maze_m;
	vector<char> colomn;
	//Build cell
	for (int i = 1; i <= m_size * 5; i++) {
		colomn.push_back(' ');
	}
	for (int i = 1; i <= m_size * 3; i++) {
		maze_m.push_back(colomn);
	}
	for (int i = 0; i <= (m_size - 1) * 3; i += 3) {
		for (int j = 0; j <= (m_size - 1) * 5; j += 5) {
			maze_m[i][j] = '/';
		}
	}
	for (int i = 2; i <= m_size * 3 - 1; i += 3) {
		for (int j = 4; j <= m_size * 5 - 1; j += 5) {
			maze_m[i][j] = '/';
		}
	}
	for (int i = 0; i <= (m_size - 1) * 3; i += 3) {
		for (int j = 4; j <= m_size * 5 - 1; j += 5) {
			maze_m[i][j] = '\\';
		}
	}
	for (int i = 2; i <= m_size * 3 - 1; i += 3) {
		for (int j = 0; j <= (m_size - 1) * 5; j += 5) {
			maze_m[i][j] = '\\';
		}
	}
	int ist = ((start) / m_size) * 3 + 1, jst = (start % m_size) * 5 + 2;
	maze_m[ist][jst] = '*';

	//Build the wall
	for (int pr = 0; pr <= m_size * m_size - 1; pr++) {
		addRandW(pr, m_size, maze_m);
	}

	for (int s = 0; s <= m_size * 3 - 1; s++) {
		for (int h = 0; h <= m_size * 5 - 1; h++) {
			int w = h + 2;
			if (h == m_size * 5 - 1) { break; }
			if (w > m_size * 5 - 1) { break; }
			if (maze_m[s][h] == '-') {
				if (maze_m[s][w] == '-') {
					maze_m[s][w] = ' ';
				}
			}
		}
	}

	//Print
	for (int i = 0; i <= m_size * 3 - 1; i++) {
		for (int j = 0; j <= m_size * 5 - 1; j++) {
			cout << maze_m[i][j];
		}
		cout << endl;
	}
}

void DFS(vector<cell>& maze, int n, int start, int end) {
	//Convert maze to a graph
	vector<vector<int>*> Graph = MazeToGraph(maze);
	if (start == end) {
		cout << "The end is the start itself." << endl;
		return;
	}
	Stack.push(maze[start]);
	maze[start].in_structure = true;
	while (!Stack.empty()) {
		bool Has_neighbour = false;
		//To find a neighbour with not in the stack and unvisited
		for (auto it : *Graph[Stack.top().id]) {
			if (maze[it].in_structure == false && maze[it].visited == false) {
				Has_neighbour = true;
				break;
			}
			else { Has_neighbour = false; }
		}
		while (Has_neighbour) {
			for (auto it : *Graph[Stack.top().id]) {
				if (maze[it].in_structure == false && maze[it].visited == false) {
					maze[it].from = Stack.top().id;
					maze[it].in_structure = true;
					Stack.push(maze[it]);
					if (it == end) { goto output; }
					break;
				}
			}
			//To find a neighbour with not in the stack and unvisited
			for (auto it : *Graph[Stack.top().id]) {
				if (maze[it].in_structure == false && maze[it].visited == false) {
					Has_neighbour = true;
					break;
				}
				else { Has_neighbour = false; }
			}
		}
		while (!Has_neighbour) {
			maze[Stack.top().id].visited = true;
			Stack.pop();
			//In case that Has_neighbour cannot updated
			if (Stack.empty()) { Has_neighbour = true; break; }
			//To find a neighbour with not in the stack and unvisited
			for (auto it : *Graph[Stack.top().id]) {
				if (maze[it].in_structure == false && maze[it].visited == false) {
					Has_neighbour = true;
					break;
				}
				else { Has_neighbour = false; }
			}
		}
	}
	cout << "DFS:" << endl;
	cout << "No solution." << endl;
	return;

	//Output the maze
output:
	cout << "DFS:" << endl;
	cell t = maze[end];
	while (t.from != -1) {
		output.push_back(t.id);
		t = maze[t.from];
	}
	cout << start;
	for (int outit = output.size() - 1; outit >= 0; outit--) {
		cout << " -> " << output[outit];
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Start from " << start << " to " << end << endl;
	cout << endl;
	printMaze(start, n, rt, output);

	//Rebuild the data structure
	for (int itr0 = rt.size() - 1; itr0 >= 0; itr0--) {
		for (int itr1 = rt[itr0].size() - 1; itr1 >= 0; itr1--) {
			rt[itr0].erase(rt[itr0].begin() + itr1);
		}
		rt.erase(rt.begin() + itr0);
	}
	while (true) {
		if (Stack.empty()) { break; }
		Stack.pop();
	}
	for (int itr0 = output.size() - 1; itr0 >= 0; itr0--) {
		output.erase(output.begin() + itr0);
	}
	for (int itr0 = Maze.size() - 1; itr0 >= 0; itr0--) {
		Maze[itr0].from = -1;
		Maze[itr0].in_structure = false;
		Maze[itr0].visited = false;
	}
}

void BFS(vector<cell>& maze, int n, int start, int end) {
	//Convert maze to a graph
	vector<vector<int>*> Graph = MazeToGraph(maze);
	Queue.push(maze[start]);
	maze[start].in_structure == true;
	while (!Queue.empty()) {
		for (auto it : *Graph[Queue.front().id]) {
			if (maze[it].visited != true && maze[it].in_structure != true) {
				Queue.push(maze[it]);
				maze[it].in_structure = true;
				maze[it].from = Queue.front().id;
				if (it == end) { goto output; }
			}
		}
		maze[Queue.front().id].visited = true;
		Queue.pop();
	}
	cout << "BFS:" << endl;
	cout << "No solution." << endl;
	return;

	//Output the maze
output:
	cout << "BFS:" << endl;
	cell t = maze[end];
	while (t.from != -1) {
		output.push_back(t.id);
		t = maze[t.from];
	}
	cout << start;
	for (int outit = output.size() - 1; outit >= 0; outit--) {
		cout << " -> " << output[outit];
	}
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "Start from " << start << " to " << end << endl;
	cout << endl;
	printMaze(start, n, rt, output);

	//Rebuild the data structure
	for (int itr0 = rt.size() - 1; itr0 >= 0; itr0--) {
		for (int itr1 = rt[itr0].size() - 1; itr1 >= 0; itr1--) {
			rt[itr0].erase(rt[itr0].begin() + itr1);
		}
		rt.erase(rt.begin() + itr0);
	}
	while (true) {
		if (Queue.empty()) { break; }
		Queue.pop();
	}
	for (int itr0 = output.size() - 1; itr0 >= 0; itr0--) {
		output.erase(output.begin() + itr0);
	}
	for (int itr0 = Maze.size() - 1; itr0 >= 0; itr0--) {
		Maze[itr0].from = -1;
		Maze[itr0].in_structure = false;
		Maze[itr0].visited = false;
	}
}

int main() {
	ifstream in("maze5.txt");
	int cell_num, start, end;
	in >> cell_num >> start >> end;
	for (int i = 0; i <= cell_num - 1; i++) {
		cell c;
		in >> c.wall;
		c.id = i;
		Maze.push_back(c);
	}
	cout << "/   \\" << endl;
	cout << "     " << endl;
	cout << "\\   / is a cell, and - is wall. * is the route." << endl;
	cout << endl;
	cout << endl;
	DFS(Maze, sqrt(cell_num), start, end);
	cout << endl;
	cout << endl;
	cout << endl;
	BFS(Maze, sqrt(cell_num), start, end);
	cout << endl;
	cout << endl;
	cout << endl;
	system("pause");
	return 0;
}
