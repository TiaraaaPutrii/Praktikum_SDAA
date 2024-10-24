#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
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
    cout << "===========================================================\n";
    cout << "|                 Pakaian berhasil ditambahkan.           |\n";
    cout << "===========================================================\n";
}

void tampilkanPakaian() {
    if (head == nullptr) {
        cout << "===========================================================\n";
        cout << "|                Tidak ada pakaian yang tersedia.         |\n";
        cout << "===========================================================\n";
        return;
    }
    
    cout << "===========================================================\n";
    cout << "| No | ID    | Nama Pakaian          | Stok | Ukuran | Kategori          |\n";
    cout << "===========================================================\n";
    
    Pakaian* temp = head;
    int count = 1;
    
    while (temp != nullptr) {
        cout << "| " << setw(2) << count << " | "
             << setw(6) << temp->id << " | "
             << left << setw(20) << temp->nama_pakaian << " | "
             << setw(4) << temp->stok << " | "
             << setw(6) << temp->ukuran << " | "
             << setw(16) << temp->kategori_pakaian << " |\n";
        
        temp = temp->next;
        count++;
    }
    
    cout << "===========================================================\n";
}

int fibonacciSearchID(Pakaian* arr[], int n, string id) {
    int fibMMm2 = 0;
    int fibMMm1 = 1;
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i]->id < id) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i]->id > id) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1]->id == id) return offset + 1;

    return -1;
}

int jumpSearchStok(Pakaian* arr[], int n, int stok) {
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1]->stok < stok) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1; 
    }

    while (arr[prev]->stok < stok) {
        prev++;
        if (prev == min(step, n)) return -1; 
    }

    if (arr[prev]->stok == stok) return prev;

    return -1; 
}

void BoyerMooreSearchNama(Pakaian* arr[], int n, string pattern) {
    const int NO_OF_CHARS = 256;
    int badChar[NO_OF_CHARS];

    for (int i = 0; i < NO_OF_CHARS; i++) badChar[i] = -1;

    for (int i = 0; i < pattern.size(); i++)
        badChar[(int) pattern[i]] = i;

    for (int idx = 0; idx < n; idx++) {
        string text = arr[idx]->nama_pakaian;
        int s = 0;
        while (s <= (text.size() - pattern.size())) {
            int j = pattern.size() - 1;

            while (j >= 0 && pattern[j] == text[s + j]) j--;

            if (j < 0) {
                cout << "Nama pakaian ditemukan: " << arr[idx]->nama_pakaian << "\n";
                s += (s + pattern.size() < text.size()) ? pattern.size() - badChar[text[s + pattern.size()]] : 1;
            } else {
                s += max(1, j - badChar[text[s + j]]);
            }
        }
    }
}

Pakaian* cariPakaianByID(string id) {
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
    cout << "Masukkan ID pakaian yang ingin diupdate: ";
    string id;
    cin >> id;

    Pakaian* pakaian = cariPakaianByID(id);
    if (pakaian != nullptr) {
        cout << "Masukkan nama baru pakaian: ";
        cin.ignore(); 
        getline(cin, pakaian->nama_pakaian);
        
        cout << "Masukkan stok baru pakaian: ";
        cin >> pakaian->stok;
        
        cout << "Masukkan ukuran baru pakaian: ";
        cin >> pakaian->ukuran;
        
        cout << "Masukkan kategori baru pakaian: ";
        cin.ignore(); 
        getline(cin, pakaian->kategori_pakaian);

        cout << "===========================================================\n";
        cout << "|              Pakaian berhasil diupdate.                 |\n";
        cout << "===========================================================\n";
    } else {
        cout << "===========================================================\n";
        cout << "|                Pakaian tidak ditemukan.                 |\n";
        cout << "===========================================================\n";
    }
}

void hapusPakaian() {
    cout << "Masukkan ID pakaian yang ingin dihapus: ";
    string id;
    cin >> id;

    if (head == nullptr) {
        cout << "===========================================================\n";
        cout << "|                Tidak ada pakaian yang tersedia.         |\n";
        cout << "===========================================================\n";
        return;
    }

    if (head->id == id) {
        Pakaian* temp = head;
        head = head->next;
        delete temp;
        cout << "===========================================================\n";
        cout << "|                Pakaian berhasil dihapus.                |\n";
        cout << "===========================================================\n";
        return;
    }

    Pakaian* current = head;
    Pakaian* previous = nullptr;
    while (current != nullptr && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) {
        cout << "===========================================================\n";
        cout << "|                Pakaian tidak ditemukan.                 |\n";
        cout << "===========================================================\n";
        return;
    }

    previous->next = current->next;
    delete current;
    cout << "===========================================================\n";
    cout << "|                Pakaian berhasil dihapus.                |\n";
    cout << "===========================================================\n";
}

void DataPakaianTersedia() {
    tambahPakaian("P001", "Kaos Polos", 50, "L", "Casual");
    tambahPakaian("P002", "Kemeja Batik", 30, "M", "Formal");
    tambahPakaian("P003", "Jaket Kulit", 20, "XL", "Outdoor");
    tambahPakaian("P004", "Celana Jeans", 40, "32", "Casual");
    tambahPakaian("P005", "Blazer Formal", 25, "L", "Formal");
    tambahPakaian("P006", "Sweater Rajut", 35, "M", "Casual");
    tambahPakaian("P007", "Kemeja Denim", 18, "L", "Casual");
    tambahPakaian("P008", "Celana Jogger", 45, "L", "Casual");
    tambahPakaian("P009", "Rompi Formal", 28, "M", "Formal");
    tambahPakaian("P010", "Tunik Muslimah", 32, "M", "Muslim");
}

void tampilkanMenu() {
    cout << "\n===========================================================\n";
    cout << "|                        Menu                             |\n";
    cout << "===========================================================\n";
    cout << "| 1. Tambah pakaian                                        |\n";
    cout << "| 2. Tampilkan daftar pakaian                              |\n";
    cout << "| 3. Update pakaian                                        |\n";
    cout << "| 4. Hapus pakaian                                         |\n";
    cout << "| 5. Fibonacci Search (cari ID pakaian)                    |\n";
    cout << "| 6. Jump Search (cari stok pakaian)                       |\n";
    cout << "| 7. Boyer-Moore Search (cari nama pakaian)                |\n";
    cout << "| 0. Keluar                                                |\n";
    cout << "===========================================================\n";
    cout << "Masukkan pilihan Anda: ";
}

int main() {
    DataPakaianTersedia();
    int pilihan;
    do {
        tampilkanMenu();
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
            case 5: {
                
                string idCari;
                cout << "Masukkan ID pakaian yang ingin dicari: ";
                cin >> idCari;

                Pakaian* arr[100];
                Pakaian* temp = head;
                int i = 0;
                while (temp != nullptr) {
                    arr[i] = temp;
                    temp = temp->next;
                    i++;
                }

                int index = fibonacciSearchID(arr, i, idCari);
                if (index != -1) {
                    cout << "Pakaian ditemukan pada index: " << index << "\n";
                } else {
                    cout << "Pakaian tidak ditemukan\n";
                }
                break;
            }
            case 6: {
                int stokCari;
                cout << "Masukkan stok pakaian yang ingin dicari: ";
                cin >> stokCari;

                Pakaian* arr[100];
                Pakaian* temp = head;
                int i = 0;
                while (temp != nullptr) {
                    arr[i] = temp;
                    temp = temp->next;
                    i++;
                }

                int index = jumpSearchStok(arr, i, stokCari);
                if (index != -1) {
                    cout << "Pakaian ditemukan:\n";
                    cout << "===========================================================\n";
                    cout << "| ID      : " << arr[index]->id << "\n";
                    cout << "| Nama    : " << arr[index]->nama_pakaian << "\n";
                    cout << "| Stok    : " << arr[index]->stok << "\n";
                    cout << "| Ukuran  : " << arr[index]->ukuran << "\n";
                    cout << "| Kategori: " << arr[index]->kategori_pakaian << "\n";
                    cout << "===========================================================\n";
                } else {
                    cout << "===========================================================\n";
                    cout << "|                Pakaian tidak ditemukan                  |\n";
                    cout << "===========================================================\n";
                }
                break;
            }
            case 7: {
                string namaCari;
                cout << "Masukkan nama pakaian yang ingin dicari: ";
                cin.ignore();
                getline(cin, namaCari);

                Pakaian* arr[100];
                Pakaian* temp = head;
                int i = 0;
                while (temp != nullptr) {
                    arr[i] = temp;
                    temp = temp->next;
                    i++;
                }

                BoyerMooreSearchNama(arr, i, namaCari);
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan program ini.\n";
                break;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi.\n";
                break;
        }
    } while (pilihan != 0);

    return 0;
}
