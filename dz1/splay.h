#ifndef SPLAY_H
#define SPLAY_H

class Splay {
private:
	struct Node {
		int info;
		Node *left, *right, *parent;
		Node(int n, Node *l = nullptr, Node *r = nullptr, Node *p = nullptr) : info(n), left(l), right(r), parent(p) {}
	};
	Node *root;

	void copy(const Splay&);

	void rightRotation(Node *x) {
		Node *y = x->left;
		Node *temp = y->right;
		Node *p = x->parent;

		y->right = x;
		if (temp) temp->parent = x;
		x->left = temp;
		x->parent = y;

		y->parent = p;
		if (!p) root = y;
		else if (p->left == x) p->left = y;
		else p->right = y;
	}

	void leftRotation(Node *x) {
		Node *y = x->right;
		Node *temp = y->left;
		Node *p = x->parent;

		y->left = x;
		if (temp) temp->parent = x;
		x->right = temp;
		x->parent = y;

		y->parent = p;
		if (!p) root = y;
		else if (p->left == x) p->left = y;
		else p->right = y;
	}

	int splay(Node *n);

public:
	Splay() : root(nullptr) {}
	Splay(int n) : root(new Node(n)) {}
	Splay(const Splay&);
	Splay(Splay&&);

	~Splay();

	Splay &operator=(const Splay&);
	Splay &operator=(Splay&&);

	int insert(int);
	int search(int);
	int remove(int);
	
	void print();
	void freeSplay();
};

#endif

