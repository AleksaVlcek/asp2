#include "array.h"
#include <iostream>
#include <limits>
#include <string>
using namespace std;

bool readInt(int &x) {
    int t;
    if (cin >> t) {x = t; return true;}
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Greska: unesite broj!\n";
    return false;
}

int main() {
    Array a;
    int izbor;

    do {
        izbor = -1;
        cout << "\n--- MENI ---\n";
        cout << "1. Unos sa tastature\n";
        cout << "2. Unos iz fajla\n";
        cout << "3. Dodaj kljuc na pocetak\n";
        cout << "4. Obrisi kljuc\n";
        cout << "5. Pretrazi kljuc\n";
        cout << "6. Ispisi niz\n";
        cout << "0. Izlaz\n";
        cout << "Izbor: ";
        if (!readInt(izbor)) continue;

        switch (izbor) {
            case 1:
                a.readStd();
                break;
            case 2: {
                string filename;
                cout << "Unesite ime fajla: ";
                cin >> filename;
                if (!a.readFile(filename.c_str()))
                    cout << "Greska: Fajl " << filename << " nije moguce otvoriti!\n";
                break;
            }
            case 3: {
                int k;
                cout << "Unesite kljuc za dodavanje: ";
                if (!readInt(k)) break;
                cout << "Broj pristupa: " << a.add(k) << endl;
                break;
            }
            case 4: {
                int k;
                cout << "Unesite kljuc za brisanje: ";
                if (!readInt(k)) break;
                cout << "Broj pristupa: " << a.remove(k) << endl;
                break;
            }
            case 5: {
                int k;
                cout << "Unesite kljuc za pretragu: ";
                if (!readInt(k)) break;
                cout << "Broj pristupa: " << a.search(k) << endl;
                break;
            }
            case 6: {
                a.print();
                break;
            }
            case 0:
                cout << "Kraj programa.\n";
                break;
            default:
                cout << "Nevazeci izbor!\n";
        }
    } while (izbor != 0);

    return 0;
}

