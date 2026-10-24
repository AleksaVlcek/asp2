#include "splay.h"
#include <iostream>
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

int main() {
    Splay *s = nullptr;
    int izbor;

    do {
        izbor = -1;
        cout << "\n--- MENI ---\n";
        cout << "1. Formiraj prazno stablo\n";
        cout << "2. Umetni kljuc\n";
        cout << "3. Pretrazi kljuc\n";
        cout << "4. Obrisi kljuc\n";
        cout << "5. Ispisi stablo\n";
        cout << "6. Obrisi stablo iz memorije\n";
        cout << "0. Izlaz\n";
        cout << "Izbor: ";
        if (!readInt(izbor)) continue;

        if (izbor >= 2 && izbor <= 6 && !s) {
            cout << "Greska: stablo nije formirano!\n";
            continue;
        }

        switch (izbor) {
            case 1:
                if (s) {
                    cout << "Stablo vec postoji, prvo ga obrisite.\n";
                    break;
                }
                s = new Splay;
                cout << "Formirano prazno stablo.\n";
                break;
            case 2: {
                int k;
                cout << "Unesite kljuc za umetanje: ";
                if (!readInt(k)) break;
                cout << "Broj pristupa: " << s->insert(k) << endl;
                break;
            }
            case 3: {
                int k;
                cout << "Unesite kljuc za pretragu: ";
                if (!readInt(k)) break;
                cout << "Broj pristupa: " << s->search(k) << endl;
                break;
            }
            case 4: {
                int k;
                cout << "Unesite kljuc za brisanje: ";
                if (!readInt(k)) break;
                cout << "Broj pristupa: " << s->remove(k) << endl;
                break;
            }
            case 5:
                s->print();
                break;
            case 6:
                delete s;
                s = nullptr;
                cout << "Stablo obrisano.\n";
                break;
            case 0:
                cout << "Kraj programa.\n";
                break;
            default:
                cout << "Nevazeci izbor!\n";
        }
    } while (izbor != 0);

    delete s;
    return 0;
}
