#include <iostream>
#include <string>
using namespace std;

struct Pakaian {
    string id;
    string nama_pakaian;
    int stok;
    string ukuran;
    string kategori_pakaian;
    Pakaian* next; 
};

Pakaian* head = nullptr;

void tambahPakaian(string id, string nama, int stok, string ukuran, string kategori) {
    Pakaian* newPakaian = new Pakaian;
    newPakaian->id = id;
    newPakaian->nama_pakaian = nama;
    newPakaian->stok = stok;
    newPakaian->ukuran = ukuran;
    newPakaian->kategori_pakaian = kategori;
    newPakaian->next = nullptr;

    if (head == nullptr) {
        head = newPakaian;
    } else {
        Pakaian* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPakaian;
    }
}

void tambahPakaian() {
    Pakaian* newPakaian = new Pakaian;
    cout << "Masukkan ID pakaian: ";
    cin >> newPakaian->id;
    cout << "Masukkan nama pakaian: ";
    cin.ignore();
    getline(cin, newPakaian->nama_pakaian);
    cout << "Masukkan stok pakaian: ";
    cin >> newPakaian->stok;
    cout << "Masukkan ukuran pakaian: ";
    cin >> newPakaian->ukuran;
    cout << "Masukkan kategori pakaian: ";
    cin.ignore();
    getline(cin, newPakaian->kategori_pakaian);
    newPakaian->next = nullptr;

    if (head == nullptr) {
        head = newPakaian;
    } else {
        Pakaian* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPakaian;
    }
    cout << "Pakaian berhasil ditambahkan.\n";
}

void tampilkanPakaian() {
    if (head == nullptr) {
        cout << "Tidak ada pakaian yang tersedia.\n";
        return;
    }
    Pakaian* temp = head;
    int count = 1;
    while (temp != nullptr) {
        cout << "\nPakaian " << count << ":\n";
        cout << "ID            : " << temp->id << "\n";
        cout << "Nama Pakaian  : " << temp->nama_pakaian << "\n";
        cout << "Stok          : " << temp->stok << "\n";
        cout << "Ukuran        : " << temp->ukuran << "\n";
        cout << "Kategori      : " << temp->kategori_pakaian << "\n";
        temp = temp->next;
        count++;
    }
}

Pakaian* cariPakaian(string id) {
    Pakaian* temp = head;
    while (temp != nullptr) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void updatePakaian() {
    string id;
    cout << "Masukkan ID pakaian yang ingin diupdate: ";
    cin >> id;
    Pakaian* pakaian = cariPakaian(id);

    if (pakaian != nullptr) {
        cout << "Masukkan nama pakaian baru: ";
        cin.ignore();
        getline(cin, pakaian->nama_pakaian);
        cout << "Masukkan stok pakaian baru: ";
        cin >> pakaian->stok;
        cout << "Masukkan ukuran pakaian baru: ";
        cin >> pakaian->ukuran;
        cout << "Masukkan kategori pakaian baru: ";
        cin.ignore();
        getline(cin, pakaian->kategori_pakaian);
        cout << "Pakaian berhasil diupdate.\n";
    } else {
        cout << "Pakaian tidak ditemukan.\n";
    }
}

void hapusPakaian() {
    string id;
    cout << "Masukkan ID pakaian yang ingin dihapus: ";
    cin >> id;

    if (head == nullptr) {
        cout << "Tidak ada pakaian yang bisa dihapus.\n";
        return;
    }

    if (head->id == id) {
        Pakaian* temp = head;
        head = head->next;
        delete temp;
        cout << "Pakaian berhasil dihapus.\n";
        return;
    }

    Pakaian* current = head;
    Pakaian* prev = nullptr;

    while (current != nullptr && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Pakaian tidak ditemukan.\n";
        return;
    }

    prev->next = current->next;
    delete current;
    cout << "Pakaian berhasil dihapus.\n";
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
