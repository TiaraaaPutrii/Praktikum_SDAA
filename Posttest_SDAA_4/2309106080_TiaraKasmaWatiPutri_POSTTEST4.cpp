#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Pakaian {
    string id;
    string nama_pakaian;
    int stok;
    string ukuran;
    string kategori_pakaian;
};

stack<Pakaian*> pakaianStack; // Stack 
queue<Pakaian*> pakaianQueue; // Queue 

void tampilkanHeader(string judul) {
    cout << "\n====================================\n";
    cout << "         " << judul << "         \n";
    cout << "====================================\n";
}

void tambahPakaian(string id, string nama, int stok, string ukuran, string kategori) {
    Pakaian* newPakaian = new Pakaian;
    newPakaian->id = id;
    newPakaian->nama_pakaian = nama;
    newPakaian->stok = stok;
    newPakaian->ukuran = ukuran;
    newPakaian->kategori_pakaian = kategori;
    pakaianStack.push(newPakaian);
}

void tambahPakaian() {
    Pakaian* newPakaian = new Pakaian;
    tampilkanHeader("Form Tambah Pakaian");
    cout << "| Masukkan ID pakaian       : ";
    cin >> newPakaian->id;
    cout << "| Masukkan nama pakaian     : ";
    cin.ignore();
    getline(cin, newPakaian->nama_pakaian);
    cout << "| Masukkan stok pakaian     : ";
    cin >> newPakaian->stok;
    cout << "| Masukkan ukuran pakaian   : ";
    cin >> newPakaian->ukuran;
    cout << "| Masukkan kategori pakaian : ";
    cin.ignore();
    getline(cin, newPakaian->kategori_pakaian);
    cout << "====================================\n";

    pakaianStack.push(newPakaian);
    cout << "Pakaian berhasil ditambahkan.\n";
}

void hapusPakaian() {
    if (pakaianStack.empty()) {
        cout << "Tidak ada pakaian yang bisa dihapus.\n";
        return;
    }

    string id;
    tampilkanHeader("Hapus Pakaian");
    cout << "| Masukkan ID pakaian yang ingin dihapus: ";
    cin >> id;
    cout << "====================================\n";

    stack<Pakaian*> tempStack;
    bool found = false;

    while (!pakaianStack.empty()) {
        Pakaian* topPakaian = pakaianStack.top();
        pakaianStack.pop();

        if (topPakaian->id == id) {
            cout << "Pakaian dengan ID " << topPakaian->id << " berhasil dihapus.\n";
            delete topPakaian;
            found = true;
            break;
        } else {
            tempStack.push(topPakaian);
        }
    }

    while (!tempStack.empty()) {
        pakaianStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found) {
        cout << "Pakaian dengan ID " << id << " tidak ditemukan.\n";
    }
}

void updatePakaian() {
    string id;
    tampilkanHeader("Update Pakaian");
    cout << "| Masukkan ID pakaian yang ingin diupdate: ";
    cin >> id;
    cout << "====================================\n";

    stack<Pakaian*> tempStack;
    bool found = false;

    while (!pakaianStack.empty()) {
        Pakaian* topPakaian = pakaianStack.top();
        pakaianStack.pop();

        if (topPakaian->id == id) {
            found = true;
            int pilihan;
            do {
                cout << "\nPakaian ditemukan. Pilih apa yang ingin diupdate:\n";
                cout << "1. Update Nama Pakaian\n";
                cout << "2. Update Stok Pakaian\n";
                cout << "3. Update Ukuran Pakaian\n";
                cout << "4. Update Kategori Pakaian\n";
                cout << "5. Selesai\n";
                cout << "Masukkan pilihan: ";
                cin >> pilihan;

                switch (pilihan) {
                    case 1:
                        cout << "| Masukkan nama pakaian baru: ";
                        cin.ignore();
                        getline(cin, topPakaian->nama_pakaian);
                        cout << "Nama pakaian berhasil diupdate.\n";
                        break;
                    case 2:
                        cout << "| Masukkan stok pakaian baru: ";
                        cin >> topPakaian->stok;
                        cout << "Stok pakaian berhasil diupdate.\n";
                        break;
                    case 3:
                        cout << "| Masukkan ukuran pakaian baru: ";
                        cin >> topPakaian->ukuran;
                        cout << "Ukuran pakaian berhasil diupdate.\n";
                        break;
                    case 4:
                        cout << "| Masukkan kategori pakaian baru: ";
                        cin.ignore();
                        getline(cin, topPakaian->kategori_pakaian);
                        cout << "Kategori pakaian berhasil diupdate.\n";
                        break;
                    case 5:
                        cout << "Selesai mengupdate pakaian.\n";
                        break;
                    default:
                        cout << "Pilihan tidak valid.\n";
                        break;
                }
            } while (pilihan != 5);
        }

        tempStack.push(topPakaian);
    }

    while (!tempStack.empty()) {
        pakaianStack.push(tempStack.top());
        tempStack.pop();
    }

    if (!found) {
        cout << "Pakaian dengan ID " << id << " tidak ditemukan.\n";
    }
}

void tampilkanPakaian() {
    if (pakaianStack.empty()) {
        cout << "Tidak ada pakaian yang tersedia.\n";
        return;
    }

    stack<Pakaian*> tempStack = pakaianStack;
    while (!tempStack.empty()) {
        pakaianQueue.push(tempStack.top());
        tempStack.pop();
    }

    int count = 1;
    tampilkanHeader("Daftar Pakaian");
    while (!pakaianQueue.empty()) {
        Pakaian* frontPakaian = pakaianQueue.front();
        cout << "\nPakaian " << count << ":\n";
        cout << "ID            : " << frontPakaian->id << "\n";
        cout << "Nama Pakaian  : " << frontPakaian->nama_pakaian << "\n";
        cout << "Stok          : " << frontPakaian->stok << "\n";
        cout << "Ukuran        : " << frontPakaian->ukuran << "\n";
        cout << "Kategori      : " << frontPakaian->kategori_pakaian << "\n";
        pakaianQueue.pop();
        count++;
    }
    cout << "====================================\n";
}

void DataPakaianTersedia() {
    tambahPakaian("P001", "Kaos Polos", 50, "L", "Casual");
    tambahPakaian("P002", "Kemeja Batik", 30, "M", "Formal");
    tambahPakaian("P003", "Jaket Kulit", 20, "XL", "Outdoor");
    tambahPakaian("P004", "Celana Jeans", 40, "32", "Casual");
    tambahPakaian("P005", "Blazer Formal", 25, "L", "Formal");
}

int main() {
    int pilihan;

    DataPakaianTersedia();

    do {
        tampilkanHeader("Manajemen Toko Pakaian");
        cout << "1. Tambah Pakaian\n";
        cout << "2. Tampilkan Semua Pakaian\n";
        cout << "3. Update Pakaian\n";
        cout << "4. Hapus Pakaian\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPakaian();
                break;
            case 2:
                tampilkanPakaian();
                break;
            case 3:
                updatePakaian();
                break;
            case 4:
                hapusPakaian();
                break;
            case 5:
                cout << "Terima kasih!\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}
