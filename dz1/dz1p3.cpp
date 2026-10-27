#include "array.h"
#include "bst.h"
#include "splay.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <limits>
using namespace std;

bool readInt(int &x) {
    int t;
    if (cin >> t) {x = t; return true;}
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Greska: unesite broj!\n";
    return false;
}

void printHeader() {
    cout << endl;
    cout << setw(16) << "Broj operacija" << " | "
         << setw(22) << "Niz, sa prebacivanjem" << " | "
         << setw(10) << "BST" << " | "
         << setw(12) << "Splay stablo" << endl;
    cout << string(16 + 22 + 10 + 12 + 9, '-') << endl;
}

void printRow(long long n, long long ta, long long tb, long long ts) {
    double d = n ? n : 1;
    cout << fixed << setprecision(2)
         << setw(16) << n << " | "
         << setw(22) << ta / d << " | "
         << setw(10) << tb / d << " | "
         << setw(12) << ts / d << endl;
}

void measure(istream &in) {
    Array a;
    Bst b;
    Splay s;
    long long n = 0, ta = 0, tb = 0, ts = 0;

    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        char op;
        int key;

        if (!(iss >> op)) continue;

        if (!(iss >> key)) {
            cout << "Neispravna operacija: " << line << endl;
            continue;
        }

        switch (toupper(op)) {
            case 'I':
                ta += a.add(key);
                tb += b.insert(key);
                ts += s.insert(key);
                break;
            case 'D':
                ta += a.remove(key);
                tb += b.remove(key);
                ts += s.remove(key);
                break;
            case 'S':
                ta += a.search(key);
                tb += b.search(key);
                ts += s.search(key);
                break;
            default:
                cout << "Neispravna operacija: " << line << endl;
                continue;
        }
        n++;
    }

    printRow(n, ta, tb, ts);
}

int main() {
    int izbor;

    do {
        izbor = -1;
        cout << "\n--- MENI ---\n";
        cout << "1. Simulacija iz fajlova\n";
        cout << "2. Unos operacija sa standardnog ulaza\n";
        cout << "0. Izlaz\n";
        cout << "Izbor: ";
        if (!readInt(izbor)) continue;

        switch (izbor) {
            case 1: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Unesite imena fajlova u jednom redu: ";
                string names;
                getline(cin, names);

                istringstream iss(names);
                string filename;
                bool header = false;
                while (iss >> filename) {
                    ifstream file(filename);
                    if (!file.is_open()) {
                        cout << "Greska: Fajl " << filename << " nije moguce otvoriti!\n";
                        continue;
                    }
                    if (!header) {
                        printHeader();
                        header = true;
                    }
                    measure(file);
                }
                break;
            }
            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Unesite operacije (npr. I 37), prazan red za kraj:\n";
                {
                    ostringstream buf;
                    string line;
                    while (getline(cin, line) && line.find_first_not_of(" \t\r") != string::npos)
                        buf << line << '\n';
                    istringstream ops(buf.str());
                    printHeader();
                    measure(ops);
                }
                break;
            case 0:
                cout << "Kraj programa.\n";
                break;
            default:
                cout << "Nevazeci izbor!\n";
        }
    } while (izbor != 0);

    return 0;
}
