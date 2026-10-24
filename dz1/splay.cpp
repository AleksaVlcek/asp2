#include "splay.h"
#include <iostream>
#include <string>
using namespace std;

void Splay::copy(const Splay &s) {
	root = nullptr;
	if (!s.root) return;

	root = new Node(s.root->info);
	Node *src = s.root, *dst = root;

	while (src) {
		if (src->left && !dst->left) {
			dst->left = new Node(src->left->info, nullptr, nullptr, dst);
			src = src->left;
			dst = dst->left;
		}
		else if (src->right && !dst->right) {
			dst->right = new Node(src->right->info, nullptr, nullptr, dst);
			src = src->right;
			dst = dst->right;
		}
		else {
			src = src->parent;
			dst = dst->parent;
		}
	}
}

Splay::Splay(const Splay &s) : root(nullptr) {
	copy(s);
}

Splay::Splay(Splay &&s) : root(s.root) {
	s.root = nullptr;
}

Splay::~Splay() {
	freeSplay();
}

Splay &Splay::operator=(const Splay &s) {
	if (this != &s) {
		freeSplay();
		copy(s);
	}

	return *this;
}

Splay &Splay::operator=(Splay &&s) {
	if (this != &s) {
		freeSplay();
		root = s.root;
		s.root = nullptr;
	}

	return *this;
}

void Splay::freeSplay() {
	Node *cur = root;

	while (cur) {
		if (cur->left) cur = cur->left;
		else if (cur->right) cur = cur->right;
		else {
			Node *p = cur->parent;
			if (p) {
				if (p->left == cur) p->left = nullptr;
				else p->right = nullptr;
			}
			delete cur;
			cur = p;
		}
	}

	root = nullptr;
}

int Splay::splay(Node *n) {
	int cnt = 0;
	while (n->parent) {
		Node *p = n->parent;
		Node *g = p->parent;
		if (g) {
			cnt += 6;
			if (p == g->left && n == p->left) {rightRotation(g); rightRotation(p);}
			else if (p == g->left && n == p->right) {leftRotation(p); rightRotation(g);}
			else if (p == g->right && n == p->right) {leftRotation(g); leftRotation(p);}
			else {rightRotation(p); leftRotation(g);}
		}
		else {
			cnt += 3;
			if (n == p->left) rightRotation(p);
			else leftRotation(p);
		}
	}
	return cnt;
}

int Splay::search(int key) {
	if (!root) return 0;
	int cnt = 0;
	Node *cur = root, *p = nullptr;

	while (cur) {
		cnt++;
		if (key == cur->info) break;
		else if (key < cur->info) {p = cur; cur = cur->left;}
		else {p = cur; cur = cur->right;}
	}

	if (cur) cnt += splay(cur);
	else cnt += splay(p);

	return cnt;
}

int Splay::insert(int key) {
	int cnt = 0;
	Node *cur = root, *p = nullptr;

	while (cur) {
		cnt++;
		if (key == cur->info) break;
		else if (key < cur->info) {p = cur; cur = cur->left;}
		else {p = cur; cur = cur->right;}
	}

	if (!cur) {
		cnt++;
		cur = new Node(key, nullptr, nullptr, p);
		if (!p) root = cur;
		else if (key < p->info) p->left = cur;
		else p->right = cur;
	}

	cnt += splay(cur);
	return cnt;
}

int Splay::remove(int key) {
	if (!root) return 0;
	int cnt = 0;
	Node *cur = root, *p = nullptr;

	while (cur) {
		cnt++;
		if (key == cur->info) break;
		else if (key < cur->info) {p = cur; cur = cur->left;}
		else {p = cur; cur = cur->right;}
	}

	if (cur) cnt += splay(cur);
	else {cnt += splay(p); return cnt;}

	if (!cur->left && !cur->right) {
		root = nullptr;
	}
	else if (!cur->left) {
		cur->right->parent = nullptr;
		root = cur->right;
	}
	else if (!cur->right) {
		cur->left->parent = nullptr;
		root = cur->left;
	}
	else {
		Node *l = cur->left, *r = cur->right;
		l->parent = nullptr;
		root = l;

		p = l;
		cnt++;
		while (p->right) {p = p->right; cnt++;}
		cnt += splay(p);

		p->right = r;
		r->parent = p;
	}

	delete cur;
	return cnt;
}

void Splay::print() {
	if (!root) {
		cout << "Stablo je prazno.\n";
		return;
	}

	Node *cur = root, *prev = nullptr;
	int depth = 0;

	cout << endl;
	while (cur) {
		if (prev == cur->parent && cur->right) {
			prev = cur;
			cur = cur->right;
			depth++;
			continue;
		}

		if (prev == cur->parent || prev == cur->right) {
			cout << string(depth * 6, ' ');
			if (cur->parent) cout << (cur == cur->parent->right ? "/ " : "\\ ");
			cout << cur->info << endl;

			if (cur->left) {
				prev = cur;
				cur = cur->left;
				depth++;
				continue;
			}
		}

		prev = cur;
		cur = cur->parent;
		depth--;
	}
	cout << endl;
}
