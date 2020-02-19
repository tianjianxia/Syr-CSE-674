//HW5 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//HW5  AVL Tree
//Due: Friday (Nov. 8) at 11:59PM
//55 points
//This homework requires more efforts. You should get started as soon as possible.

#include <iostream> //to use cout
#include <algorithm> //to use max function such as  i = max(a, b);

using namespace std;

//You need to use the following node class for each node of the AVL tree
class node {
public:
	int value;
	int height;//this is tree height. Leaf node is 1; empty node (i.e., NIL) is 0
	node* parent;
	node* l_child;
	node* r_child;
	node() {}
	node(int i) { value = i; height = 1; parent = l_child = r_child = nullptr; }

};

class avl_tree {
public:
	node* root;
	avl_tree() {
		root = nullptr;
	}

	//************************************************************************************
	//Implement the following member functions
	void add_node(int i)
		//if case of a tie, add i to the last of existing nodes with value i in the in-order sequence
	{
		if (!root) { root = new node(i); return; }
		node* current = root, * _p = root;
		bool _IsFind = false;
		while (!_IsFind) {
			if (current->value >= i) {
				if (current->l_child) current = current->l_child;
				else {
					current->l_child = new node(i);
					current->l_child->parent = current;
					_IsFind = true;
					_p = current->l_child;
				}
			}
			else {
				if (current->r_child) current = current->r_child;
				else {
					current->r_child = new node(i);
					current->r_child->parent = current;
					_IsFind = true;
					_p = current->r_child;
				}
			}
		}
		pair<node*, int> _Build = height_update(_p);
		if (_Build.second == 1) { L_Rotate(_Build.first); }
		else if (_Build.second == 2) { R_Rotate((_Build.first)->r_child); L_Rotate(_Build.first); }
		else if (_Build.second == 3) { R_Rotate(_Build.first); }
		else if (_Build.second == 4) { L_Rotate((_Build.first)->l_child); R_Rotate(_Build.first); }
	};

	void delete_node(int i)
		//Delete the node with value i.  in case of multiple nodes with value i, delete the first node with value i in the in-order traveral sequence
	{
		if (!root) return;
		else {
			node* cur = root;
			bool _IsFind = false;
			while (!_IsFind) {
				if (!cur) return;
				else if (cur->value == i) _IsFind = true;
				else if (cur->value > i) cur = cur->l_child;
				else if (cur->value < i) cur = cur->r_child;
			}
			
			int L_h, R_h;
			L_h = (cur->l_child) ? (cur->l_child->height) : 0;
			R_h = (cur->r_child) ? (cur->r_child->height) : 0;
			node* _p = cur->parent;
			int LR;
			if (_p && _p->l_child == cur) LR = 1;
			else LR = 2;
			if (L_h == R_h && L_h == 0) {
				if (cur == root) { delete cur; root = nullptr; return; }
				else {
					if (LR == 1) { _p->l_child = nullptr; cur->parent = nullptr; delete cur; }
					else if (LR == 2) { _p->r_child = nullptr; cur->parent = nullptr; delete cur; }
				}
			}
			else if (L_h >= R_h && L_h != 0) {
				node* f = cur->l_child;
				while (f->r_child) f = f->r_child;
				_p = f->parent;
				cur->value = f->value;
				_p->l_child = f->l_child;
				if (f->l_child) f->l_child->parent = _p;
				delete f;
			}
			else if (L_h < R_h && R_h != 0) {
				node* f = cur->r_child;
				while (f->l_child) f = f->l_child;
				_p = f->parent;
				cur->value = f->value;
				_p->r_child = f->r_child;
				if (f->r_child) f->r_child->parent = _p;
				delete f;
			}

			node* chd = nullptr;
			if (!_p->l_child && !_p->r_child) { chd = _p; chd->height = 1; }
			else if (!_p->l_child && _p->r_child) chd = _p->r_child;
			else if (_p->l_child && !_p->r_child) chd = _p->l_child;
			else chd = _p->l_child;

			pair<node*, int> _Build = height_update(chd);

			if (_Build.second == 1) { L_Rotate(_Build.first); }
			else if (_Build.second == 2) { R_Rotate((_Build.first)->r_child); L_Rotate(_Build.first); }
			else if (_Build.second == 3) { R_Rotate(_Build.first); }
			else if (_Build.second == 4) { L_Rotate((_Build.first)->l_child); R_Rotate(_Build.first); }
		}
	};

	void in_order_traversal(node* p) //such as 2 5 9 11 11 14 15 15 ...
	{
		if (!p) return;
		in_order_traversal(p->l_child);
		cout << p->value << " ";
		in_order_traversal(p->r_child);
	};


	pair<node*, int> height_update(node* p)
		/*
		This function will be invoked by add_node and delete_node.
		p points to the first node that we need to check for possible height update.  We then need to check possible height update toward root.
		All nodes whose heights need to be updated will be performed in this function.
		The function returns a pair.  If no imbalance is detected, the first of the pair will be nullptr; otherwise it will be the address of the action node.
		The second of the pair will be 0 if no imbalance is detected; otherwise its value is 1,2,3,4 for RR RL, LL, and LR pattern, respectively.
		*/
		//RR 1
		//RL 2
		//LL 3
		//LR 4
	{
		if (p == root) { return { nullptr,0 }; }
		node* current = p;
		node* _Parent = p->parent;
		bool _IsRet = false;
		node* ret = nullptr;
		while (!_IsRet && _Parent) {
			int diff;
			int L_h, R_h;
			L_h = (_Parent->l_child) ? (_Parent->l_child->height) : 0;
			R_h = (_Parent->r_child) ? (_Parent->r_child->height) : 0;
			diff = max(L_h, R_h) - min(L_h, R_h);
			if (diff > 1) {
				ret = _Parent;
				_IsRet = true;
			}
			else {
				int P_height;
				P_height = max(L_h, R_h) + 1;
				if (_Parent->height != P_height) {
					_Parent->height = P_height;
					current = _Parent;
					_Parent = _Parent->parent;
				}
				else break;
			}
		}

		int _ret = 0;
		if (ret == nullptr) _ret = 0;
		else {
			int ret_L, ret_R;
			ret_L = (ret->l_child) ? (ret->l_child->height) : 0;
			ret_R = (ret->r_child) ? (ret->r_child->height) : 0;

			if (ret_L > ret_R) {
				node* t = ret->l_child;
				int LL, LR;
				LL = (t->l_child) ? (t->l_child->height) : 0;
				LR = (t->r_child) ? (t->r_child->height) : 0;
				if (LL > LR) _ret = 3;
				else _ret = 4;
			}
			else if (ret_L < ret_R) {
				node* t = ret->r_child;
				int RL, RR;
				RL = (t->l_child) ? (t->l_child->height) : 0;
				RR = (t->r_child) ? (t->r_child->height) : 0;
				if (RL > RR) _ret = 2;
				else _ret = 1;
			}
		}

		return { ret,_ret };
	};

	void L_Rotate(node* p)
		//p points to the node at which the rotation will be performed.
	{
		node* act = p;
		node* _act = p->r_child;
		if (p == root) {
			root = nullptr;
			act->r_child = _act->l_child;
			if(_act->l_child) _act->l_child->parent = act;
			_act->l_child = act;
			act->parent = _act;
			root = _act;
			root->parent = nullptr;
			int act_L_h, act_R_h;
			act_L_h = (act->l_child) ? (act->l_child->height) : 0;
			act_R_h = (act->r_child) ? (act->r_child->height) : 0;
			act->height = max(act_L_h, act_R_h) + 1;
			int root_L_h, root_R_h;
			root_L_h = (root->l_child) ? (root->l_child->height) : 0;
			root_R_h = (root->r_child) ? (root->r_child->height) : 0;
			root->height = max(root_L_h, root_R_h) + 1;
		}
		else {
			node* stamp = p->parent;
			int LR;
			if (p == stamp->l_child) { LR = 1; stamp->l_child = nullptr; }
			else if (p == stamp->r_child) { LR = 2; stamp->r_child = nullptr; }
			p->parent = nullptr;
			act->r_child = _act->l_child;
			if(_act->l_child) _act->l_child->parent = act;
			_act->l_child = act;
			act->parent = _act;
			if (LR == 1) stamp->l_child = _act;
			else if (LR == 2) stamp->r_child = _act;
			_act->parent = stamp;
			int act_L_h, act_R_h;
			act_L_h = (act->l_child) ? (act->l_child->height) : 0;
			act_R_h = (act->r_child) ? (act->r_child->height) : 0;
			act->height = max(act_L_h, act_R_h) + 1;
			int _act_L_h, _act_R_h;
			_act_L_h = (_act->l_child) ? (_act->l_child->height) : 0;
			_act_R_h = (_act->r_child) ? (_act->r_child->height) : 0;
			_act->height = max(_act_L_h, _act_R_h) + 1;
			node* cur = _act->parent;
			while (cur) {
				int cur_L, cur_R;
				cur_L = (cur->l_child) ? (cur->l_child->height) : 0;
				cur_R = (cur->r_child) ? (cur->r_child->height) : 0;
				cur->height = max(cur_L, cur_R) + 1;
				cur = cur->parent;
			}
		}
	};

	void R_Rotate(node* p)
		//p points to the node at which the rotation will be performed.
	{
		node* act = p;
		node* _act = p->l_child;
		if (p == root) {
			root = nullptr;
			act->l_child = _act->r_child;
			if(_act->r_child) _act->r_child->parent = act;
			_act->r_child = act;
			act->parent = _act;
			root = _act;
			root->parent = nullptr;
			int act_L_h, act_R_h;
			act_L_h = (act->l_child) ? (act->l_child->height) : 0;
			act_R_h = (act->r_child) ? (act->r_child->height) : 0;
			act->height = max(act_L_h, act_R_h) + 1;
			int root_L_h, root_R_h;
			root_L_h = (root->l_child) ? (root->l_child->height) : 0;
			root_R_h = (root->r_child) ? (root->r_child->height) : 0;
			root->height = max(root_L_h, root_R_h) + 1;
		}
		else {
			node* stamp = p->parent;
			int LR;
			if (p == stamp->l_child) { LR = 1; stamp->l_child = nullptr; }
			else if (p == stamp->r_child) { LR = 2; stamp->r_child = nullptr; }
			p->parent = nullptr;
			act->l_child = _act->r_child;
			if(_act->r_child) _act->r_child->parent = act;
			_act->r_child = act;
			act->parent = _act;
			if (LR == 1) stamp->l_child = _act;
			else if (LR == 2) stamp->r_child = _act;
			_act->parent = stamp;
			int act_L_h, act_R_h;
			act_L_h = (act->l_child) ? (act->l_child->height) : 0;
			act_R_h = (act->r_child) ? (act->r_child->height) : 0;
			act->height = max(act_L_h, act_R_h) + 1;
			int _act_L_h, _act_R_h;
			_act_L_h = (_act->l_child) ? (_act->l_child->height) : 0;
			_act_R_h = (_act->r_child) ? (_act->r_child->height) : 0;
			_act->height = max(_act_L_h, _act_R_h) + 1;
			node* cur = _act->parent;
			while (cur) {
				int cur_L, cur_R;
				cur_L = (cur->l_child) ? (cur->l_child->height) : 0;
				cur_R = (cur->r_child) ? (cur->r_child->height) : 0;
				cur->height = max(cur_L, cur_R) + 1;
				cur = cur->parent;
			}
		}
	};
};



int main() {
	//Different test cases will be used during grading.
	avl_tree t1;
	t1.add_node(45);
	t1.delete_node(45);
	t1.in_order_traversal(t1.root);
	t1.add_node(50);
	t1.add_node(46);
	t1.add_node(30);
	t1.add_node(34);
	t1.in_order_traversal(t1.root);
	t1.delete_node(48);
	t1.in_order_traversal(t1.root);
	
	getchar();
	getchar();
	return 0;
}

//The following is an example showing how to return a pair.
/*
#include <iostream>
using namespace std;

pair<int *, int> f1(){
	return { new int {10}, 10 };
}
int main() {
	cout << *f1().first << " " << f1().second << endl;
	getchar();
	getchar();
	return 0;
}
*/
