#ifndef BST_H
#define BST_H

class Bst {
private:
	struct Node {
		int info;
		Node *left, *right;
		Node(int n, Node *l = nullptr, Node *r = nullptr) : info(n), left(l), right(r) {}
	};
	Node *root;

	void copy(const Bst&);

public:
	Bst() : root(nullptr) {}
	Bst(const Bst&);
	Bst(Bst&&);

	~Bst();

	Bst &operator=(const Bst&);
	Bst &operator=(Bst&&);

	int insert(int);
	int search(int);
	int remove(int);

	void freeBst();
};

#endif
