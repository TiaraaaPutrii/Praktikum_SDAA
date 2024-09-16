#include <iostream>
using namespace std;

// Fungsi rekursif untuk menghitung nilai pada Segitiga Pascal
int hitungNilai(int baris, int kolom) {
 
    if (kolom == 0 || kolom == baris) {
        return 1;
    }

    return hitungNilai(baris - 1, kolom - 1) + hitungNilai(baris - 1, kolom);
}

void tampilkanSegitigaPascal(int jumlahTingkat) {
    for (int baris = 0; baris < jumlahTingkat; ++baris) {
        for (int kolom = 0; kolom <= baris; ++kolom) {
           
            int nilai = hitungNilai(baris, kolom);
            cout << nilai << " ";
        }
        cout << endl;
    }
}

int main() {

    int jumlahTingkat = 3;

    tampilkanSegitigaPascal(jumlahTingkat);

    return 0;
}
