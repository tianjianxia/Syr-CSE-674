//HW6 by Tianjian Xia
//SU Net ID: txia09  SUID: 350385039
//CSE674 HW6  Due: 11:59PM, Nov. 26 (Tuesday)
#include <iostream>
using namespace std;

class node {
public:
	node* p_parent;
	node* p_Lchild;
	node* p_Rchild;
	int value;
	bool color; //true: red, false: black
	node() { p_parent = p_Lchild = p_Rchild = nullptr; }
	node(int i) { value = i; p_parent = p_Lchild = p_Rchild = nullptr; }
};

class tree {
public:
	node* root;
	tree() { root = nullptr; }

	//For insert, the new node should be the last of nodes with the same value in the order of 
	//inorder traversal.  (The same as HW5.)
	void insert_node(int i);
	void insert_R_rotate(node* p);//For insert_node, R-rotate at node pointed by p
	void insert_L_rotate(node* p);//for insert_node, L-rotate at node pointed by p
	//All other siutions of insert_node should be directly implemented inside add_node


	//For delete, the deleted node shoud be the first of nodes with the same value in the order of
	//inorder traversal. (The same as HW5).
	//For replacement, always recursively replace it with predecessor, unless there is no predecessor. (In this
	//case, replace it with sucessor.)


	void delete_node(int i);
	void delete_1(node* p); //case 1 of delete_node; p points to the parent of double black node
	void delete_1_R_rotate(node* p);//R_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_1_L_rotate(node* p);//L_totate used in case 1 of delete_node; p points to the parent of double black node
	void delete_2A(node* p); //case 2A of delete_node; p points to the parent of double black node
	void delete_2B(node* p);//case 2B of delete_node; p points to the parent of double black node
	void delete_3(node* p);//case 3 of delete_node; p points to the parent of double black node
	//All other cases of delete_node should be directly implemented inside the delete_node.

	//For the following, during traveral, print (value, color) of each node.
	void InorderPrint(node*);
	void PostorderPrint(node*);
	void PreorderPrint(node*);
};

int main() {
	tree t;
	t.insert_node(1);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(2);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(3);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(4);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(5);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(6);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(7);
	t.InorderPrint(t.root);
	cout << endl;
	t.insert_node(8);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(8);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(4);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(3);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(2);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(6);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(5);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(1);
	t.InorderPrint(t.root);
	cout << endl;
	t.delete_node(7);
	t.InorderPrint(t.root);
	cout << endl;
	system("pause");
	return 0;
}

void tree::InorderPrint(node* root) {
	if (!root) return;
	InorderPrint(root->p_Lchild);
	cout << " (" << root->value << "," << boolalpha << root->color << ")  ";
	InorderPrint(root->p_Rchild);
}

void tree::PostorderPrint(node* root) {
	if (!root) return;
	PostorderPrint(root->p_Lchild);
	PostorderPrint(root->p_Rchild);
	cout << " (" << root->value << "," << boolalpha << root->color << ")  ";
}

void tree::PreorderPrint(node* root) {
	if (!root) return;
	cout << " (" << root->value << "," << boolalpha << root->color << ")  ";
	PreorderPrint(root->p_Lchild);
	PreorderPrint(root->p_Rchild);
}

void tree::insert_node(int i) {
	node* p_node = nullptr, * x_node = new node(i), * cur_node = root;
	while (cur_node) {
		p_node = cur_node;
		if (x_node->value > cur_node->value)
			cur_node = cur_node->p_Rchild;
		else cur_node = cur_node->p_Lchild;
	}
	x_node->p_parent = p_node;
	if (!p_node)
		root = x_node;
	else if (x_node->value > p_node->value)
		p_node->p_Rchild = x_node;
	else p_node->p_Lchild = x_node;
	x_node->color = true;
	//reset color
	while (x_node->p_parent && x_node->p_parent->color) {
		if (x_node->p_parent == x_node->p_parent->p_parent->p_Lchild) {
			node* u_node = x_node->p_parent->p_parent->p_Rchild;
			if (u_node && u_node->color) {
				x_node->p_parent->color = false;
				u_node->color = false;
				x_node->p_parent->p_parent->color = true;
				x_node = x_node->p_parent->p_parent;
			}
			else if (x_node == x_node->p_parent->p_Rchild) {
				x_node = x_node->p_parent;
				insert_L_rotate(x_node);
			}
			else if (x_node == x_node->p_parent->p_Lchild) {
				x_node->p_parent->color = false;
				x_node->p_parent->p_parent->color = true;
				insert_R_rotate(x_node->p_parent->p_parent);
			}
		}
		else if(x_node->p_parent == x_node->p_parent->p_parent->p_Rchild){
			node* u_node = x_node->p_parent->p_parent->p_Lchild;
			if (u_node && u_node->color) {
				x_node->p_parent->color = false;
				u_node->color = false;
				x_node->p_parent->p_parent->color = true;
				x_node = x_node->p_parent->p_parent;
			}
			else if (x_node == x_node->p_parent->p_Lchild) {
				x_node = x_node->p_parent;
				insert_R_rotate(x_node);
			}
			else if (x_node == x_node->p_parent->p_Rchild) {
				x_node->p_parent->color = false;
				x_node->p_parent->p_parent->color = true;
				insert_L_rotate(x_node->p_parent->p_parent);
			}
		}
	}
	root->color = false;
	return;
}

void tree::insert_L_rotate(node* act) {
	node* _act = act->p_Rchild;
	act->p_Rchild = _act->p_Lchild;
	if (_act->p_Lchild) 
		_act->p_Lchild->p_parent = act;
	_act->p_parent = act->p_parent;
	if (!act->p_parent)
		root = _act;
	else if (act == act->p_parent->p_Lchild)
		act->p_parent->p_Lchild = _act;
	else act->p_parent->p_Rchild = _act;
	_act->p_Lchild = act;
	act->p_parent = _act;
	return;
}

void tree::insert_R_rotate(node* act) {
	node* _act = act->p_Lchild;
	act->p_Lchild = _act->p_Rchild;
	if (_act->p_Rchild)
		_act->p_Rchild->p_parent = act;
	_act->p_parent = act->p_parent;
	if (!act->p_parent)
		root = _act;
	else if (act == act->p_parent->p_Lchild)
		act->p_parent->p_Lchild = _act;
	else act->p_parent->p_Rchild = _act;
	_act->p_Lchild = act;
	act->p_parent = _act;
	return;
}

void tree::delete_node(int i) {
	if (!root) return;
	if (!root->p_Lchild && !root->p_Rchild && root->value == i) {
		node* del = root;
		root = nullptr;
		delete del;
		return;
	}
	node* curr = root;
	bool IsFind = false;
	while (!IsFind) {
		if (!curr) break;
		if (curr->value == i)
			IsFind = true;
		else if (curr->value < i)
			curr = curr->p_Rchild;
		else
			curr = curr->p_Lchild;
	}
	if (!IsFind) return;
	bool IsLeaf = false;
	do {
		if (!curr->p_Lchild && !curr->p_Rchild)
			IsLeaf = true;
		if (curr->p_Lchild || curr->p_Rchild)
			IsLeaf = false;

		if(IsLeaf)
			if (curr->color) {
				((curr->p_parent->p_Lchild == curr) ? curr->p_parent->p_Lchild : curr->p_parent->p_Rchild) = nullptr;
				curr->p_parent = nullptr;
				delete curr;
				break;
			}
			else {
				node* sibling = (curr == curr->p_parent->p_Lchild) ? curr->p_parent->p_Rchild : curr->p_parent->p_Lchild;
				if (!sibling || !sibling->color) {
					if ((sibling->p_Lchild && sibling->p_Lchild->color) || (sibling->p_Rchild && sibling->p_Rchild->color))
						delete_1(curr);
					else if ((!sibling->p_Lchild || !sibling->p_Lchild->color) && (!sibling->p_Rchild||!sibling->p_Rchild->color))
						if (!curr->p_parent->color) {
							delete_2A(curr);
							((curr->p_parent->p_Lchild == curr) ? curr->p_parent->p_Lchild : curr->p_parent->p_Rchild) = nullptr;
							curr->p_parent = nullptr;
							delete curr;
							break;
						}
						else {
							delete_2B(curr);
							break;
						}
				}
				else if (sibling->color) {
					delete_3(curr);
					break;
				}
			}
		else {
			bool IsChildOnlyandDiff = false;
			if ((curr->p_Lchild && !curr->p_Rchild) || (curr->p_Rchild && !curr->p_Lchild)) {
				node* child = curr->p_Lchild ? curr->p_Lchild : curr->p_Rchild;
				if (curr->color != child->color)
					IsChildOnlyandDiff = true;
			}
			if (IsChildOnlyandDiff) {
				curr->value = (curr->p_Lchild ? curr->p_Lchild : curr->p_Rchild)->value;
				curr->color = false;
				(curr->p_Lchild ? curr->p_Lchild->p_parent : curr->p_Rchild->p_parent) = nullptr;
				(curr->p_Lchild ? curr->p_Lchild : curr->p_Rchild) = nullptr;
				delete (curr->p_Lchild ? curr->p_Lchild : curr->p_Rchild);
				break;
			}
			else {
				node* pre = curr, * n = curr->p_Lchild;
				while (n) {
					pre = n;
					n = n->p_Rchild;
				}
				curr->value = pre->value;
				curr = pre;
				IsLeaf = true;
			}
		}
	} while (IsLeaf);
	return;
}

void tree::delete_1(node* p) {
	node* parent = p->p_parent, * sibling = (p == p->p_parent->p_Lchild) ? p->p_parent->p_Rchild : p->p_parent->p_Lchild;
	node* stamp = parent->p_parent;
	int LR = stamp->p_Lchild == parent ? 1 : 2;
	(parent->p_Lchild ? parent->p_Lchild : parent->p_Rchild) = nullptr;
	p->p_parent = nullptr;
	delete p;
	/*if (parent == root)
		root = nullptr;
	else
		(LR == 1) ? stamp->p_Lchild : stamp->p_Rchild = nullptr;
	parent->p_parent = nullptr;*/
	if (sibling == parent->p_Lchild) {
		if (sibling->p_Rchild->color && sibling->p_Lchild->color) {
			delete_1_R_rotate(parent);
			sibling->p_Lchild->color = !sibling->p_Lchild->color;
			sibling->color = parent->color;
			parent->color = false;
		}
		else if (sibling->p_Rchild->color && (!sibling->p_Lchild || !sibling->p_Lchild->color)) {
			delete_1_L_rotate(sibling);
			delete_1_R_rotate(parent);
			parent->p_parent->color = parent->color;
			parent->color = false;
		}
	}
	else{
		if (sibling->p_Lchild->color && sibling->p_Rchild->color) {
			delete_1_L_rotate(parent);
			sibling->p_Rchild->color = !sibling->p_Rchild->color;
			sibling->color = parent->color;
			parent->color = false;
		}
		else if (sibling->p_Rchild->color && (!sibling->p_Lchild || !sibling->p_Lchild->color)) {
			delete_1_R_rotate(sibling);
			delete_1_L_rotate(parent);
			parent->p_parent->color = parent->color;
			parent->color = false;
		}
	}
	return;
}

void tree::delete_1_L_rotate(node* act) {
	node* _act = act->p_Rchild;
	node* stamp = act->p_parent;
	int LR = 1;
	if (!stamp)
		root = nullptr;
	else if (stamp->p_Rchild == act) {
		LR = 2;
		stamp->p_Rchild = nullptr;
	}
	else
		stamp->p_Lchild = nullptr;
		
	act->p_Rchild = _act->p_Lchild;
	if (_act->p_Lchild) _act->p_Lchild->p_parent = act;
	_act->p_Lchild = act;
	act->p_parent = _act;

	if (!stamp)
		root = _act;
	else if (LR == 1)
		stamp->p_Lchild = _act;
	else
		stamp->p_Rchild = _act;
}

void tree::delete_1_R_rotate(node* act) {
	node* _act = act->p_Lchild;
	node* stamp = act->p_parent;
	int LR = 1;
	if (!stamp)
		root = nullptr;
	else if (stamp->p_Rchild == act) {
		LR = 2;
		stamp->p_Rchild = nullptr;
	}
	else
		stamp->p_Lchild = nullptr;

	act->p_Lchild = _act->p_Rchild;
	if (_act->p_Rchild) _act->p_Rchild->p_parent = act;
	_act->p_Rchild = act;
	act->p_parent = _act;

	if (!stamp)
		root = _act;
	else if (LR == 1)
		stamp->p_Lchild = _act;
	else
		stamp->p_Rchild = _act;
}

void tree::delete_2A(node* p) {
	if (!p||!p->p_parent) return;
	node* parent = p->p_parent;
	node* sibling = p->p_parent->p_Lchild == p ? p->p_parent->p_Rchild : p->p_parent->p_Lchild;
	if (!p->p_parent->color) {
		sibling->color = true;
		delete_2A(parent);
	}
	else if(p->p_parent->color) {
		sibling->color = true;
		parent->color = false;
		return;
	}
	return;
}

void tree::delete_2B(node* p) {
	node* parent = p->p_parent;
	node* sibling = p->p_parent->p_Lchild == p ? p->p_parent->p_Rchild : p->p_parent->p_Lchild;
	sibling->color = true;
	parent->color = false;
	((p->p_parent->p_Lchild == p) ? parent->p_Lchild : parent->p_Rchild) = nullptr;
	p->p_parent = nullptr;
	delete p;
	return;
}

void tree::delete_3(node* p) {
	node* parent = p->p_parent;
	node* stamp = parent->p_parent;
	int LR = 0;
	if(stamp) LR = (stamp->p_Lchild == parent) ? 1 : 2;
	if (LR == 1)
		stamp->p_Lchild = nullptr;
	else if (LR == 2)
		stamp->p_Rchild = nullptr;
	else
		root = nullptr;
	parent->p_parent = nullptr;
	if (p == parent->p_Lchild) {
		node* act = parent, * _act = parent->p_Rchild;
		act->p_Rchild = _act->p_Lchild;
		if (_act->p_Lchild) _act->p_Lchild->p_parent = act;
		_act->p_Lchild = act;
		act->p_parent = _act;
		act->color = !act->color;
		_act->color = !_act->color;
		if (stamp == nullptr) {
			root = _act;
			_act->p_parent = nullptr;
		}
		else if (LR == 1) {
			stamp->p_Lchild = _act;
			_act->p_parent = stamp;
		}
		else {
			stamp->p_Rchild = _act;
			_act->p_parent = stamp;
		}
	}
	else {
		node* act = parent, * _act = parent->p_Lchild;
		act->p_Lchild = _act->p_Rchild;
		if (_act->p_Rchild) _act->p_Rchild->p_parent = act;
		_act->p_Rchild = act;
		act->p_parent = _act;
		act->color = !act->color;
		_act->color = !_act->color;
		act->color = !act->color;
		_act->color = !_act->color;
		if (stamp == nullptr) {
			root = _act;
			_act->p_parent = nullptr;
		}
		else if (LR == 1) {
			stamp->p_Lchild = _act;
			_act->p_parent = stamp;
		}
		else {
			stamp->p_Rchild = _act;
			_act->p_parent = stamp;
		}
	}
	node* sibling = (p == p->p_parent->p_Lchild) ? p->p_parent->p_Rchild : p->p_parent->p_Lchild;
	if (!sibling || !sibling->color) {
		if ((sibling->p_Lchild && sibling->p_Lchild->color) || (sibling->p_Rchild && sibling->p_Rchild->color))
			delete_1(p);
		else if ((!sibling->p_Lchild || !sibling->p_Lchild->color) && (!sibling->p_Rchild || !sibling->p_Rchild->color))
			if (!p->p_parent->color) {
				delete_2A(p);
				((p->p_parent->p_Lchild == p) ? p->p_parent->p_Lchild : p->p_parent->p_Rchild) = nullptr;
				p->p_parent = nullptr;
				delete p;
			}
			else {
				delete_2B(p);
			}
	}
	else if (sibling->color) {
		delete_3(p);
	}
	return;
}
