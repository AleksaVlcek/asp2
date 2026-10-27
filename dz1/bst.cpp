#include "bst.h"
#include <stack>
#include <utility>
using namespace std;

void Bst::copy(const Bst &b) {
	root = nullptr;
	if (!b.root) return;

	stack<pair<Node*, Node**>> s;
	s.push({b.root, &root});

	while (!s.empty()) {
		Node *src = s.top().first;
		Node **dst = s.top().second;
		s.pop();

		*dst = new Node(src->info);
		if (src->right) s.push({src->right, &(*dst)->right});
		if (src->left) s.push({src->left, &(*dst)->left});
	}
}

Bst::Bst(const Bst &b) : root(nullptr) {
	copy(b);
}

Bst::Bst(Bst &&b) : root(b.root) {
	b.root = nullptr;
}

Bst::~Bst() {
	freeBst();
}

Bst &Bst::operator=(const Bst &b) {
	if (this != &b) {
		freeBst();
		copy(b);
	}

	return *this;
}

Bst &Bst::operator=(Bst &&b) {
	if (this != &b) {
		freeBst();
		root = b.root;
		b.root = nullptr;
	}

	return *this;
}

void Bst::freeBst() {
	if (!root) return;

	stack<Node*> s;
	s.push(root);

	while (!s.empty()) {
		Node *cur = s.top();
		s.pop();

		if (cur->right) s.push(cur->right);
		if (cur->left) s.push(cur->left);
		delete cur;
	}

	root = nullptr;
}

int Bst::search(int key) {
	int cnt = 0;
	Node *cur = root;

	while (cur) {
		cnt++;
		if (key == cur->info) break;
		else if (key < cur->info) cur = cur->left;
		else cur = cur->right;
	}

	return cnt;
}

int Bst::insert(int key) {
	int cnt = 0;
	Node *cur = root, *p = nullptr;

	while (cur) {
		cnt++;
		if (key == cur->info) return cnt;
		p = cur;
		if (key < cur->info) cur = cur->left;
		else cur = cur->right;
	}

	cur = new Node(key);
	if (!p) root = cur;
	else if (key < p->info) p->left = cur;
	else p->right = cur;

	return cnt + 1;
}

int Bst::remove(int key) {
	int cnt = 0;
	Node *cur = root, *q = nullptr;

	while (cur) {
		cnt++;
		if (key == cur->info) break;
		q = cur;
		if (key < cur->info) cur = cur->left;
		else cur = cur->right;
	}

	if (!cur) return cnt;

	Node *rp;
	if (!cur->left) rp = cur->right;
	else if (!cur->right) rp = cur->left;
	else {
		Node *f = cur;
		rp = cur->right;
		cnt++;
		while (rp->left) {
			f = rp;
			rp = rp->left;
			cnt++;
		}

		if (f != cur) {
			f->left = rp->right;
			rp->right = cur->right;
		}
		rp->left = cur->left;
	}

	if (!q) root = rp;
	else if (q->left == cur) q->left = rp;
	else q->right = rp;

	delete cur;
	return cnt + 2;
}
