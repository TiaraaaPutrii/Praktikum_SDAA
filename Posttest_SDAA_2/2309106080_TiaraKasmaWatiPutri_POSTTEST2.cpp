#include <iostream>
#include <string>
using namespace std;

struct Pakaian {
    string id;
    string nama_pakaian;
    int stok;
    string ukuran;
    string kategori_pakaian;
};

void tambahPakaian(Pakaian *pakaian, int *jumlah) {
    cout << "Masukkan ID pakaian: ";
    cin >> pakaian[*jumlah].id;
    cout << "Masukkan nama pakaian: ";
    cin.ignore();
    getline(cin, pakaian[*jumlah].nama_pakaian);
    cout << "Masukkan stok pakaian: ";
    cin >> pakaian[*jumlah].stok;
    cout << "Masukkan ukuran pakaian: ";
    cin >> pakaian[*jumlah].ukuran;
    cout << "Masukkan kategori pakaian: ";
    cin.ignore();
    getline(cin, pakaian[*jumlah].kategori_pakaian);
    (*jumlah)++;
}

void tampilkanPakaian(Pakaian *pakaian, int *jumlah) {
    if (*jumlah == 0) {
        cout << "Tidak ada pakaian yang tersedia.\n";
        return;
    }
    
    for (int i = 0; i < *jumlah; i++) {
        cout << "\nPakaian " << i + 1 << ":\n";
        cout << "ID            : " << pakaian[i].id << "\n";
        cout << "Nama Pakaian  : " << pakaian[i].nama_pakaian << "\n";
        cout << "Stok          : " << pakaian[i].stok << "\n";
        cout << "Ukuran        : " << pakaian[i].ukuran << "\n";
        cout << "Kategori      : " << pakaian[i].kategori_pakaian << "\n";
    }
}

int cariPakaian(Pakaian *pakaian, int *jumlah, string id) {
    for (int i = 0; i < *jumlah; i++) {
        if (pakaian[i].id == id) {
            return i;
        }
    }
    return -1;
}

void updatePakaian(Pakaian *pakaian, int *jumlah) {
    string id;
    cout << "Masukkan ID pakaian yang ingin diupdate: ";
    cin >> id;
    int index = cariPakaian(pakaian, jumlah, id);
    
    if (index != -1) {
        cout << "Masukkan nama pakaian baru: ";
        cin.ignore();
        getline(cin, pakaian[index].nama_pakaian);
        cout << "Masukkan stok pakaian baru: ";
        cin >> pakaian[index].stok;
        cout << "Masukkan ukuran pakaian baru: ";
        cin >> pakaian[index].ukuran;
        cout << "Masukkan kategori pakaian baru: ";
        cin.ignore();
        getline(cin, pakaian[index].kategori_pakaian);
        cout << "Pakaian berhasil diupdate.\n";
    } else {
        cout << "Pakaian tidak ditemukan.\n";
    }
}

void hapusPakaian(Pakaian *pakaian, int *jumlah) {
    string id;
    cout << "Masukkan ID pakaian yang ingin dihapus: ";
    cin >> id;
    int index = cariPakaian(pakaian, jumlah, id);
    
    if (index != -1) {
        for (int i = index; i < *jumlah - 1; i++) {
            pakaian[i] = pakaian[i + 1];
        }
        (*jumlah)--;
        cout << "Pakaian berhasil dihapus.\n";
    } else {
        cout << "Pakaian tidak ditemukan.\n";
    }
}

int main() {
    const int maxPakaian = 100;
    Pakaian *pakaian = new Pakaian[maxPakaian];
    int jumlahPakaian = 0;
    int *jumlahPtr = &jumlahPakaian; 
    int pilihan;
    
    do {
        cout << "\nManajemen Toko Pakaian\n";
        cout << "1. Tambah Pakaian\n";
        cout << "2. Tampilkan Semua Pakaian\n";
        cout << "3. Update Pakaian\n";
        cout << "4. Hapus Pakaian\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch (pilihan) {
            case 1:
                if (*jumlahPtr < maxPakaian) {
                    tambahPakaian(pakaian, jumlahPtr);  
                } else {
                    cout << "Kapasitas penyimpanan penuh.\n";
                }
                break;
            case 2:
                tampilkanPakaian(pakaian, jumlahPtr); 
                break;
            case 3:
                updatePakaian(pakaian, jumlahPtr); 
                break;
            case 4:
                hapusPakaian(pakaian, jumlahPtr);
                break;
            case 5:
                cout << "Terima kasih !\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
    
    delete[] pakaian;
    return 0;
}
