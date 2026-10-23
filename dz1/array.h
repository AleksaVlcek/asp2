#ifndef ARRAY_H
#define ARRAY_H

class Array {
private:
	int cap;
	int len;
	int *arr;

	void copy(const Array &a) {	
		for (int i = 0; i < a.len; i++) {
			arr[i] = a.arr[i];
		}
	}
		
	void resize() {
		int newCap = (cap == 0) ? 10 : 2 * cap;
		int *newArr = new int[newCap];
		for (int i = 0; i < len; i++) {
			newArr[i] = arr[i];
		}
		delete [] arr;
		arr = newArr;
		cap = newCap;
	}	

public:
	Array(int c = 10) : cap(c), len(0), arr(new int[cap]) {}
	Array(const Array &a) : cap(a.cap), len(a.len), arr(new int[a.cap]) {
		copy(a);
	}
	Array(Array &&a) : cap(a.cap), len(a.len), arr(a.arr) {
		a.cap = 0;
		a.len = 0;
		a.arr = nullptr;
	}

	~Array() {delete [] arr; arr = nullptr;}

	Array &operator=(const Array &a) {
		if (this != &a) {
			delete [] arr; arr = nullptr;
			cap = a.cap;
			len = a.len;
			arr = new int[cap];
			copy(a);
		}

		return *this;
	}

	Array &operator=(Array &&a) {
		if (this != &a) {
			delete [] arr; arr = nullptr;
			cap = a.cap;
			len = a.len;
			arr = a.arr;
			
			a.cap = 0;
			a.len = 0;
			a.arr = nullptr;
		}

		return *this;
	}

	int &operator[](int i) {return *(arr + i);}
	const int &operator[](int i) const {return *(arr + i);}

	int getCap() const {return cap;}
	int getLen() const {return len;}
	void print() const;

	void readStd();
	void readFile(const char *);

	int add(int);
	int remove(int);

	int search(int);
};

#endif // ARRAY_H

