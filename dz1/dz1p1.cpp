#include "array.h"
#include <iostream>
#include <limits>
using namespace std;

int main() {
    Array a;
    int izbor;

    do {
        cout << "\n--- MENI ---\n";
        cout << "1. Unos sa tastature\n";
        cout << "2. Unos iz fajla\n";
        cout << "3. Dodaj kljuc na pocetak\n";
        cout << "4. Obrisi kljuc\n";
        cout << "5. Pretrazi kljuc\n";
        cout << "6. Ispisi niz\n";
        cout << "0. Izlaz\n";
        cout << "Izbor: ";
        cin >> izbor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Greska: Molimo unesite broj!\n";
            continue;
        }

        switch (izbor) {
            case 1:
                a.readStd();
                break;
            case 2: {
                char filename[100];
                cout << "Unesite ime fajla: ";
                cin >> filename;
                a.readFile(filename);
                break;
            }
            case 3: {
                int k;
                cout << "Unesite kljuc za dodavanje: ";
                cin >> k;
                cout << "Broj pristupa: " << a.add(k) << endl;
                break;
            }
            case 4: {
                int k;
                cout << "Unesite kljuc za brisanje: ";
                cin >> k;
                cout << "Broj pristupa: " << a.remove(k) << endl;
                break;
            }
            case 5: {
                int k;
                cout << "Unesite kljuc za pretragu: ";
                cin >> k;
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

