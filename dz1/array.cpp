#include "array.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

void Array::readStd() {
	int c;
	cin >> c;

	if (c <= 0) c = 10;

	delete [] arr;
	cap = c;
	len = 0;
	arr = new int[cap];
	
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string s;
	getline(cin, s);
	istringstream iss(s);

	int key;
	while (iss >> key) {
		bool exist = false;
		for (int i = 0; i < len; i++) {
			if (arr[i] == key) {exist = true; break;}
		}

		if (!exist) {
			if (len == cap) resize();
			arr[len++] = key;
		}
	}
}

void Array::readFile(const char *filename) {
	ifstream file(filename);
	if (!file.is_open()) return;

	int c;
	file >> c;
	
	if (c <= 0) c = 10;

	delete [] arr;
	cap = c;
	len = 0;
	arr = new int[cap];

	
	int key;
	while (file >> key) {
		bool exist = false;
		for (int i = 0; i < len; i++) {
			if (arr[i] == key) {exist = true; break;}
		}

		if (!exist) {
			if (len == cap) resize();
			arr[len++] = key;
		}
	}
}

int Array::search(int key) {
	int cnt = 0;
	int n = -1;
	for (int i = 0; i < len; i++) {
		cnt++;
		if (arr[i] == key) {
			n = i;
			break;
		}
	}

	if (n == -1) return len + 1;

	if (n == 0) return cnt;

	for (int i = n; i > 0; i--) {
		arr[i] = arr[i - 1];
		cnt += 2;
	}

	arr[0] = key;
	cnt++;
	return cnt;
}

int Array::remove(int key) {
	int cnt = 0;
	int n = -1;
	for (int i = 0; i < len; i++) {
		cnt++;
		if (arr[i] == key) {
			n = i;
			break;
		}
	}

	if (n == -1) return cnt;

	for (int i = n + 1; i < len; i++) {
		arr[i - 1] = arr[i];
		cnt += 2;
	}

	len--;
	return cnt;
}

int Array::add(int key) {
	int cnt = 0;

	for (int i = 0; i < len; i++) {
		cnt++;
		if (arr[i] == key) return cnt;
	}

	if (len == cap) resize();

	for (int i = len; i > 0; i--) {
		arr[i] = arr[i - 1];
		cnt += 2;
	}

	arr[0] = key;
	cnt++;
	len++;
	return cnt;
}

void Array::print() const {
	cout << endl;
	for (int i = 0; i < len; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

