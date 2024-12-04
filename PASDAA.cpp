#include <iostream>
#include <string>
#include <cmath>
#include <limits>
using namespace std;


//modul 2
// Struct untuk ikan
struct Ikan {
    int ID;
    string nama;
    int harga;
    int stok;
    Ikan* next;

    Ikan(int id, string n, int h, int s) : ID(id), nama(n), harga(h), stok(s), next(nullptr) {}
};

// Struct untuk node dalam stack manual
struct StackNode {
    Ikan data;
    StackNode* next;

    StackNode(Ikan ikan) : data(ikan), next(nullptr) {}
};

//modul 3
// Struct untuk node dalam queue manual
struct QueueNode {
    Ikan data;
    QueueNode* next;

    QueueNode(Ikan ikan) : data(ikan), next(nullptr) {}
};

// Variabel global untuk menyimpan top stack dan queue
StackNode* top = nullptr;
QueueNode* front = nullptr;
QueueNode* rear = nullptr;
Ikan* head = nullptr;

// Fungsi Stack
bool isEmptyStack() {
    return top == nullptr;
}
//modul 3
void push(Ikan ikan) {
    StackNode* newNode = new StackNode(ikan);
    newNode->next = top;
    top = newNode;
}

void pop() {
    if (isEmptyStack()) {
        cout << "Stack underflow\n";
        return;
    }
    StackNode* temp = top;
    top = top->next;
    delete temp;
}

void displayDeleteHistory() {
    if (isEmptyStack()) {
        cout << "Tidak ada history penghapusan.\n";
        return;
    }
    StackNode* temp = top;
    cout << "History penghapusan ikan: \n";
    while (temp) {
        cout << "ID: " << temp->data.ID << ", Nama: " << temp->data.nama << ", Harga: " << temp->data.harga << ", Stok: " << temp->data.stok << "\n";
        temp = temp->next;
    }
}

// Fungsi Queue
bool isEmptyQueue() {
    return front == nullptr;
}
//modul 3
void enqueue(Ikan ikan) {
    QueueNode* newNode = new QueueNode(ikan);
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    cout << "Ikan dengan ID " << ikan.ID << " dimasukkan ke dalam antrian perawatan.\n";
}

void dequeue() {
    if (isEmptyQueue()) {
        cout << "Antrian kosong. Tidak ada ikan untuk dirawat.\n";
        return;
    }
    QueueNode* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    cout << "Ikan dengan ID " << temp->data.ID << " sudah dirawat dan dihapus dari antrian.\n";
    enqueue(temp->data); // Enqueue kembali setelah perawatan
    delete temp;
}

void displayMaintenanceQueue() {
    if (isEmptyQueue()) {
        cout << "Antrian kosong.\n";
        return;
    }
    QueueNode* temp = front;
    cout << "Antrian perawatan ikan: \n";
    while (temp) {
        cout << "ID: " << temp->data.ID << ", Nama: " << temp->data.nama << ", Harga: " << temp->data.harga << ", Stok: " << temp->data.stok << "\n";
        temp = temp->next;
    }
}

/// Fungsi untuk memeriksa apakah ID ikan sudah ada di dalam linked list
bool isIDExist(int id) {
    Ikan* temp = head;
    while (temp) {
        if (temp->ID == id) {
            return true; // ID sudah ada
        }
        temp = temp->next;
    }
    return false; // ID belum ada
}

// Fungsi untuk menambahkan ikan baru
void addIkan(int id, string nama, int harga, int stok) {
    // Cek apakah ID sudah ada
    if (isIDExist(id)) {
        cout << "ID " << id << " sudah ada. Mohon masukkan ID yang lain.\n";
        return;
    }

    Ikan* newIkan = new Ikan(id, nama, harga, stok);
    if (!head) {
        head = newIkan;
    } else {
        Ikan* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newIkan;
    }

    enqueue(*newIkan); // Enqueue ke antrian perawatan
    cout << "Ikan dengan ID " << id << " ditambahkan.\n";
}

// Fungsi untuk mendapatkan elemen terakhir dari linked list
Ikan* getTail(Ikan* head) {
    while (head && head->next) {
        head = head->next;
    }
    return head;
}

void displayIkan() {
    if (!head) {
        cout << "Daftar ikan kosong.\n";
        return;
    }
    Ikan* temp = head;
    while (temp) {
        cout << "ID: " << temp->ID << ", Nama: " << temp->nama << ", Harga: " << temp->harga << ", Stok: " << temp->stok << "\n";
        temp = temp->next;
    }
}

void updateIkan(int id, string newNama, int newHarga, int newStok) {
    Ikan* temp = head;
    while (temp) {
        if (temp->ID == id) {
            temp->nama = newNama;
            temp->harga = newHarga;
            temp->stok = newStok;
            cout << "Ikan dengan ID " << id << " diperbarui.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Ikan dengan ID " << id << " tidak ditemukan.\n";
}

void deleteIkan(int id) {
    if (!head) {
        cout << "Daftar ikan kosong.\n";
        return;
    }
    if (head->ID == id) {
        Ikan* toDelete = head;
        head = head->next;
        push(*toDelete); // Menyimpan ke stack
        delete toDelete;
        cout << "Ikan dengan ID " << id << " dihapus.\n";
        return;
    }
    Ikan* temp = head;
    while (temp->next && temp->next->ID != id) {
        temp = temp->next;
    }
    if (temp->next) {
        Ikan* toDelete = temp->next;
        temp->next = temp->next->next;
        push(*toDelete); // Menyimpan ke stack
        delete toDelete;
        cout << "Ikan dengan ID " << id << " dihapus.\n";
    } else {
        cout << "Ikan dengan ID " << id << " tidak ditemukan.\n";
    }
}

//modul 5
// Fungsi partition untuk Quick Sort
Ikan* partition(Ikan* low, Ikan* high, Ikan** newLow, Ikan** newHigh) {
    // Menetapkan harga ikan pada node terakhir sebagai pivot
    int pivot = high->harga;
    Ikan* prev = nullptr;
    Ikan* cur = low;
    Ikan* tail = high;

    // Proses partisi, membagi linked list berdasarkan pivot
    while (cur != high) {
        if (cur->harga < pivot) {
            // Jika harga ikan lebih kecil dari pivot, masukkan ke sublist newLow
            if ((*newLow) == nullptr) {
                (*newLow) = cur;
            }
            prev = cur;
            cur = cur->next;
        } else {
            // Jika harga ikan lebih besar atau sama dengan pivot, pindahkan ke sublist newHigh
            if (prev) prev->next = cur->next;
            Ikan* temp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = temp;
        }
    }

    // Tentukan tail dan head untuk newLow dan newHigh
    if ((*newLow) == nullptr) {
        (*newLow) = high;
    }
    (*newHigh) = tail;

    // Kembalikan pivot yang akan digunakan untuk pemisahan lebih lanjut
    return high;
}

// QuickSort yang bekerja pada linked list
Ikan* quickSortRecur(Ikan* low, Ikan* high) {
    // Jika linked list kosong atau hanya berisi satu elemen, tidak perlu sorting
    if (!low || low == high) return low;

    Ikan* newLow = nullptr;
    Ikan* newHigh = nullptr;

    // Pisahkan linked list dengan pivot dan dapatkan newLow dan newHigh
    Ikan* pivot = partition(low, high, &newLow, &newHigh);

    // Rekursif quicksort untuk sublist sebelum dan sesudah pivot
    if (newLow != pivot) {
        // Pisahkan sublist sebelum pivot dan sorting kembali
        Ikan* temp = newLow;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;  // Pisahkan sublist sebelum pivot

        newLow = quickSortRecur(newLow, temp);

        // Gabungkan sublist yang telah disorting dengan pivot
        temp = getTail(newLow);
        temp->next = pivot;
    }

    // Rekursif quicksort untuk sublist setelah pivot
    pivot->next = quickSortRecur(pivot->next, newHigh);

    return newLow;  // Kembalikan linked list yang telah diurutkan
}

// Fungsi untuk mengurutkan linked list menggunakan Quick Sort
void sortIkanByHarga(Ikan*& head) {
    // Tentukan head yang baru setelah quicksort selesai
    head = quickSortRecur(head, getTail(head));
}

// Fungsi untuk menggabungkan dua sublist untuk merge sort
Ikan* merge(Ikan* left, Ikan* right) {
    // Jika salah satu list kosong, kembalikan list yang lainnya
    if (!left) return right;
    if (!right) return left;

    Ikan* result = nullptr;

    // Bandingkan stok ikan dan gabungkan list yang lebih kecil terlebih dahulu
    if (left->stok <= right->stok) {
        result = left;
        result->next = merge(left->next, right);  // Gabungkan sisa list kiri
    } else {
        result = right;
        result->next = merge(left, right->next);  // Gabungkan sisa list kanan
    }

    return result;  // Kembalikan list yang sudah digabungkan
}

// Fungsi untuk membagi linked list menjadi dua bagian
void splitList(Ikan* source, Ikan** frontRef, Ikan** backRef) {
    Ikan* slow = source;
    Ikan* fast = source->next;

    // Gunakan metode fast and slow pointer untuk membagi linked list
    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // Pisahkan linked list menjadi dua bagian
    *frontRef = source;
    *backRef = slow->next;
    slow->next = nullptr;  // Pisahkan keduanya
}

// Fungsi rekursif untuk merge sort
void mergeSort(Ikan** headRef) {
    Ikan* head = *headRef;
    // Jika list kosong atau hanya memiliki satu elemen, tidak perlu sorting
    if (!head || !head->next) return;

    Ikan* left;
    Ikan* right;

    // Pisahkan linked list menjadi dua sublist
    splitList(head, &left, &right);

    // Sort kedua sublist secara rekursif
    mergeSort(&left);
    mergeSort(&right);

    // Gabungkan kedua sublist yang telah diurutkan
    *headRef = merge(left, right);
}

//modul 6
// Fungsi Jump Search berdasarkan stok pada linked list
Ikan* jumpSearch(int targetStok) {
    int panjang = 0;
    Ikan* temp = head;

    // Menghitung panjang linked list
    while (temp) {
        panjang++;
        temp = temp->next;
    }

    int step = sqrt(panjang);
    Ikan* prev = nullptr;
    Ikan* current = head;

    // Melompat menggunakan blok ukuran step
    while (current && current->stok < targetStok) {
        prev = current;
        for (int i = 0; i < step && current->next; i++) {
            current = current->next;
        }
        if (current->stok >= targetStok) {
            break;
        }
    }

    // Linear search pada blok yang telah ditentukan
    while (prev && prev->stok < targetStok) {
        prev = prev->next;
    }

    if (prev && prev->stok == targetStok) {
        return prev;
    }

    return nullptr;
}

// Fungsi untuk menampilkan data ikan hasil pencarian
void tampilkanHasilPencarian(Ikan* ikan) {
    if (ikan) {
        cout << "ID: " << ikan->ID << ", Nama: " << ikan->nama 
             << ", Harga: " << ikan->harga << ", Stok: " << ikan->stok << endl;
    } else {
        cout << "Ikan dengan stok tersebut tidak ditemukan!\n";
    }
}

// Fungsi untuk membuat tabel pergeseran (bad character rule)
void buildBadCharTable(const string& pattern, int badCharTable[256]) {
    int m = pattern.length();
    // Inisialisasi bad character table
    for (int i = 0; i < 256; ++i) {
        badCharTable[i] = -1;  // Nilai default adalah -1 (menandakan karakter tidak ditemukan dalam pola)
    }
    // Isi bad character table dengan posisi terakhir dari setiap karakter dalam pola
    for (int i = 0; i < m; ++i) {
        badCharTable[pattern[i]] = i;
    }
}

// Fungsi untuk mencari nama ikan menggunakan algoritma Boyer-Moore
Ikan* boyerMooreSearch(Ikan* head, const string& targetNama) {
    int badCharTable[256];  // Tabel pergeseran untuk setiap karakter (untuk ASCII 256 karakter)
    buildBadCharTable(targetNama, badCharTable);

    int m = targetNama.length();
    Ikan* current = head;
    
    while (current) {
        int i = 0;
        while (i < m && current) {
            // Bandingkan dari belakang (jika karakter cocok)
            if (targetNama[m - 1 - i] == current->nama[m - 1 - i]) {
                i++;
            } else {
                break;
            }
        }
        
        // Jika i == m, berarti nama ikan ditemukan
        if (i == m) {
            return current; // Kembalikan ikan yang ditemukan
        }
        
        // Pergeseran berdasarkan bad character rule
        if (current->nama.length() < m) {
            current = current->next;
        } else {
            int shift = m;
            // Jika karakter yang tidak cocok ditemukan, geser sesuai dengan posisi terakhir karakter tersebut
            if (badCharTable[current->nama[m - 1]] != -1) {
                shift = m - badCharTable[current->nama[m - 1]] - 1;
            }
            // Geser posisi pencarian sesuai shift
            for (int j = 0; j < shift; ++j) {
                if (current != nullptr) current = current->next;
            }
        }
    }
    return nullptr;  // Tidak ditemukan
}

//Fungsi untuk menampilkan hasil pencarian ikan
void tampilkanHasilPencarianb(Ikan* hasil) {
    if (hasil) {
        cout << "Ikan ditemukan: ID = " << hasil->ID << ", Nama = " << hasil->nama 
            << ", Harga = " << hasil->harga << ", Stok = " << hasil->stok << "\n";
    } else {
        cout << "Ikan dengan nama tersebut tidak ditemukan.\n";
    }
}

// Fungsi Fibonacci Search untuk harga ikan
Ikan* fibonacciSearch(Ikan* head, int targetHarga) {
    // Menemukan panjang dari linked list
    int n = 0;
    Ikan* temp = head;
    while (temp) {
        n++;
        temp = temp->next;
    }

    // Menyusun dua angka Fibonacci yang lebih kecil dari n
    int fibMMm2 = 0; // (m-2)th Fibonacci
    int fibMMm1 = 1; // (m-1)th Fibonacci
    int fibM = fibMMm2 + fibMMm1; // mth Fibonacci

    // Menyusun dua angka Fibonacci yang lebih kecil atau sama dengan n
    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    // Variabel untuk melacak indeks
    int offset = -1;

    // Proses pencarian
    while (fibM > 1) {
        // Tentukan indeks yang akan diperiksa
        int i = min(offset + fibMMm2, n - 1);

        // Menelusuri linked list untuk mencapai indeks yang dihitung
        Ikan* temp = head;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }

        // Jika harga ikan pada i lebih besar dari targetHarga
        if (temp->harga < targetHarga) {
            // Sesuaikan fibM untuk mengurangi rentang pencarian
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        // Jika harga ikan pada i lebih kecil dari targetHarga
        else if (temp->harga > targetHarga) {
            // Sesuaikan fibM untuk memperkecil rentang pencarian
            fibM = fibMMm2;
            fibMMm2 = fibMMm1;
            fibMMm1 = fibM - fibMMm2;
        }
        // Jika ditemukan, kembalikan ikan
        else {
            return temp;
        }
    }

    // Cek elemen terakhir
    if (fibMMm1 && head->harga == targetHarga) {
        return head;
    }

    // Jika ikan tidak ditemukan
    return nullptr;
}


// Fungsi untuk menampilkan hasil pencarian ikan
void tampilkanHasilPencarianf(Ikan* hasil) {
    if (hasil) {
        cout << "Ikan ditemukan:\n";
        cout << "ID: " << hasil->ID << ", Nama: " << hasil->nama 
             << ", Harga: " << hasil->harga << ", Stok: " << hasil->stok << endl;
    } else {
        cout << "Ikan dengan harga yang dicari tidak ditemukan.\n";
    }
}

bool isValidInput(int& choice) {
    cin >> choice;
    // Jika input bukan angka
    if (cin.fail()) {
        cin.clear();  // Bersihkan input stream
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Abaikan input yang salah
        return false;
    }
    return true;
}

int main() {
    int choice, id, harga, stok;
    string nama;
    Ikan* hasil = nullptr;  // Deklarasi di luar switch agar tersedia di semua case
    bool pilihanTersedia[14] = {false};  // Array untuk melacak pilihan menu yang sudah dipilih

    addIkan(1, "mas", 50000, 10);
    addIkan(2, "koi", 75000, 5);
    addIkan(3, "lele", 30000, 15);
    addIkan(4, "nila", 20000, 20);
    
    while (true) {
        cout << "\nMenu:\n";
        cout << "1.  Tambah ikan\n";
        cout << "2.  Tampilkan daftar ikan\n";
        cout << "3.  Perbarui data ikan\n";
        cout << "4.  Hapus ikan\n";
        cout << "5.  Tampilkan history penghapusan\n";
        cout << "6.  Tampilkan antrian perawatan\n";
        cout << "7.  Rawat ikan (dequeue)\n";
        cout << "8.  Urutkan ikan berdasarkan stok (Merge Sort)\n";
        cout << "9.  Urutkan ikan berdasarkan harga (Quick Sort)\n";
        cout << "10. Cari ikan berdasarkan stok (Jump Search)\n";  
        cout << "11. Cari ikan berdasarkan nama (Boyer-Moore Search)\n";
        cout << "12. Cari ikan berdasarkan harga (Fibonacci Search)\n";
        cout << "13. Keluar\n";  
        cout << "Pilihan Anda: ";

        // Validasi input angka
        while (!isValidInput(choice) || choice < 1 || choice > 13) {
            cout << "Input tidak valid! Masukkan angka 1 hingga 13: ";
        }
        
        // Tandai bahwa pilihan sudah dipilih
        pilihanTersedia[choice] = true;

        switch (choice) {
            case 1:
                cout << "Masukkan ID ikan: ";
                cin >> id;
                cout << "Masukkan nama ikan: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan harga ikan: ";
                cin >> harga;
                cout << "Masukkan stok ikan: ";
                cin >> stok;
                addIkan(id, nama, harga, stok);
                break;
            case 2:
                displayIkan();
                break;
            case 3:
                cout << "Masukkan ID ikan yang ingin diperbarui: ";
                cin >> id;
                cout << "Masukkan nama baru: ";
                cin.ignore();
                getline(cin, nama);
                cout << "Masukkan harga baru: ";
                cin >> harga;
                cout << "Masukkan stok baru: ";
                cin >> stok;
                updateIkan(id, nama, harga, stok);
                break;
            case 4:
                cout << "Masukkan ID ikan yang ingin dihapus: ";
                cin >> id;
                deleteIkan(id);
                break;
            case 5:
                displayDeleteHistory();
                break;
            case 6:
                displayMaintenanceQueue();
                break;
            case 7:
                dequeue();
                break;
            case 8:
                mergeSort(&head);
                cout << "aftar ikan telah diurutkan berdasarkan stok.\n";
                displayIkan();
                break;
            case 9:
                sortIkanByHarga(head);
                cout << "\nData ikan setelah diurutkan berdasarkan harga:\n";
                displayIkan();
                break;
            case 10: {
                int targetStok;
                cout << "Masukkan stok ikan yang ingin dicari: ";
                cin >> targetStok;
                mergeSort(&head);
                hasil = jumpSearch(targetStok);  // Menggunakan jump search pada case 10
                tampilkanHasilPencarian(hasil);
                break;
            }
            case 11: {
                string targetNama;
                cout << "Masukkan nama ikan yang ingin dicari: ";
                cin.ignore();
                getline(cin, targetNama);
                Ikan* hasil = boyerMooreSearch(head, targetNama);  // Cari ikan menggunakan Boyer-Moore
                tampilkanHasilPencarianb(hasil);  // Tampilkan hasil pencarian
                break;
            }
            case 12: { // Pencarian berdasarkan harga menggunakan Fibonacci Search
                int targetHarga;
                cout << "Masukkan harga ikan yang ingin dicari: ";
                cin >> targetHarga;
                sortIkanByHarga(head);
                Ikan* hasil = fibonacciSearch(head, targetHarga);
                if (hasil) {
                    cout << "Ikan dengan harga " << targetHarga << " ditemukan: " << hasil->nama << endl;
                } else {
                    cout << "Ikan dengan harga " << targetHarga << " tidak ditemukan." << endl;
                }
                break;
            }
            case 13:
                cout << "Keluar dari program.\n";
                return 0;
                
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }
    }
}