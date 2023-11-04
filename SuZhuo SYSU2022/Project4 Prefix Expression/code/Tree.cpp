#include "Tree.h"
bool flag = true;

Tree ReadExpr(string& name_) {
	flag = true;
	Tree tmp; 
	tmp.name = name_;
	string p;
	cin >> p;
	int i;
	int len = p.size();
	stack<TreeNode*> s;
	for (i = len - 1; i >= 0; --i) {
		TreeNode* tmp = new TreeNode(p[i]);
		if (issym(p[i])) {
			if (s.empty()) {
				cout << "Wrong Input. " << endl;
				flag = false;
				Tree emp;
				return emp;
			}
			TreeNode* a = s.top();
			s.pop();
			if (s.empty()) {
				cout << "Wrong Input. " << endl;
				flag = false;
				Tree emp;
				return emp;
			}
			TreeNode* b = s.top();
			s.pop();
			tmp->lchild = a;
			tmp->rchild = b;
			s.push(tmp);
		}
		else {
			s.push(tmp);
		}
	}
	tmp.root = new TreeNode(s.top());
	return tmp;
}


void Value(Tree& tree) {
	if (allvalued(tree.root)) {
		double res = value_node(tree.root);
		cout << "The result is:" << res << endl;
	}
	else {
		print_node_by_value(tree.root, 0);
	}
}

bool allvalued(TreeNode*& root)
{
	if (root == NULL) return true;
	if (root->v[2] == 1 && root->v[1] == 1) return true;
	else if (root->v[2] == 0 && root->v[1] == 1) return false;
	else if (root->v[2] == 1 && root->v[1] == 0) return true;
	else {
		if (allvalued(root->lchild) && allvalued(root->rchild)) {
			return true;
		}
		return false;
	}
}

double value_node(TreeNode*& root) {
	if (root->lchild == NULL && root->rchild == NULL && root->v[2] == 1) return root->number;
	if (root->v[0] == 1) {
		if (root->sym == '+')  return value_node(root->lchild) + value_node(root->rchild);
		else if (root->sym == '-') return value_node(root->lchild) - value_node(root->rchild);
		else if (root->sym == '*') return value_node(root->lchild) * value_node(root->rchild);
		else if (root->sym == '/') return value_node(root->lchild) / value_node(root->rchild);
		else if (root->sym == '^') return pow(value_node(root->lchild), value_node(root->rchild));
	}
}

Tree CompoundExpr(char P, Tree E1, Tree E2) {
	Tree res;
	if (P == '+') res = E1 + E2;
	else if (P == '-') res = E1 - E2;
	else if (P == '*') res = E1 * E2;
	else if (P == '/') res = E1 / E2;
	else if (P == '^') res = E1 ^ E2;
	return res;
}


inline Tree::Tree(Tree& tree) {
	this->name = tree.name;
	this->root = new TreeNode(tree.root);
}
inline Tree::Tree(Tree&& tree) noexcept {
	this->name = tree.name;
	this->root = new TreeNode(tree.root);
}
void Tree::Assign(char V, double c) {
	TreeNode* p = this->root;
	stack<TreeNode*> s;
	if (p != NULL) {
		s.push(p);
		while (!s.empty()) {
			TreeNode* q = s.top();
			if (q->v[1] == 1 && q->vari == V) {
				q->v[2] = 1;
				q->number = c;
			}
			s.pop();
			if (q->rchild != NULL) s.push(q->rchild);
			if (q->lchild != NULL) s.push(q->lchild);
		}
	}
}

void WriteExpr(Tree& tree) {
	tree.print();
}

void Tree::print(void) {
	cout << this->name << ':' << endl;
	print_node(this->root, 0);
}

void print_node(TreeNode*& node, int layer) {
	if (node == NULL) return;
	else {
		if (node->v[0] == 1 && layer != 0) cout << '(';
		layer++;
		print_node(node->lchild, layer);
		if (node->v[0] == 1) {
			cout << node->sym;
		}
		else if (node->v[1] == 1) {
			cout << node->vari;
		}
		else if (node->v[2] == 1) {
			cout << node->number;
		}
		print_node(node->rchild, layer);
		layer--;
		if (node->v[0] == 1 && layer != 0) cout << ')';
	}
}

void print_node_by_value(TreeNode*& node, int layer) {
	if (node == NULL) return;
	else {
		if (node->v[0] == 1 && layer != 0) cout << '(';
		layer++;
		print_node_by_value(node->lchild, layer);
		if (node->v[0] == 1) {
			cout << node->sym;
		}
		else if (node->v[2] == 1) {
			cout << node->number;
		}
		else if (node->v[1] == 1) {
			cout << node->vari;
		}
		print_node_by_value(node->rchild, layer);
		layer--;
		if (node->v[0] == 1 && layer != 0) cout << ')';
	}
}

bool issym(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') return true;
	return false;
}

bool isvari(char ch) {
	if (ch >= 'a' && ch <= 'z') return true;
	return false;
}

bool isnum(char ch) {
	if (ch >= '0' && ch <= '9') return true;
	return false;
}

double chtodouble(char ch) {
	int x = ch - '0';
	double x_ = (double)x;
	return x_;
}


Tree MergeConst(Tree& E) {
	E.root = MergeConst_node(E.root);
	return E;
}

TreeNode* MergeConst_node(TreeNode*& root) {
	if (root == NULL) return NULL;
	root->lchild = MergeConst_node(root->lchild);
	root->rchild = MergeConst_node(root->rchild);
	if (root->v[0] == 1 && root->lchild != NULL && root->rchild != NULL && root->lchild->v[2] == 1 && root->rchild->v[2] == 1) {
		TreeNode* res = new TreeNode();
		res->v[2] = 1;
		if (root->sym == '+') {
			res->number = root->lchild->number + root->rchild->number;
		}
		else if (root->sym == '-') {
			res->number = root->lchild->number - root->rchild->number;
		}
		else if (root->sym == '*') {
			res->number = root->lchild->number * root->rchild->number;
		}
		else if (root->sym == '/') {
			res->number = root->lchild->number / root->rchild->number;
		}
		else if (root->sym == '^') {
			res->number = pow(root->lchild->number, root->rchild->number);
		}
		return res;
	}
	else {
		return root;
	}
}


inline TreeNode::TreeNode(TreeNode*& node) :sym('\0'), vari('\0'), number(0), v(new int[3]()), lchild(NULL), rchild(NULL) {
	if (node == NULL) {
		return;
	}
	else {
		this->sym = node->sym;
		this->vari = node->vari;
		this->number = node->number;
		this->v = new int[3];
		this->v[0] = node->v[0];
		this->v[1] = node->v[1];
		this->v[2] = node->v[2];

		if (node->lchild != NULL) this->lchild = new TreeNode(node->lchild);

		if (node->rchild != NULL) this->rchild = new TreeNode(node->rchild);
	}
}

inline TreeNode::TreeNode(double x) :sym('\0'), vari('\0'), number(x), v(new int[3]()), lchild(NULL), rchild(NULL) {
	v[2] = 1;
}

inline TreeNode::TreeNode(char ch) :sym('\0'), vari('\0'), number(0), v(new int[3]()), lchild(NULL), rchild(NULL) {
	if (issym(ch)) {
		this->sym = ch;
		v[0] = 1;
	}
	else if (isvari(ch)) {
		this->vari = ch;
		v[1] = 1;
	}
	else if (isnum(ch)) {
		this->number = chtodouble(ch);
		v[2] = 1;
	}
}
