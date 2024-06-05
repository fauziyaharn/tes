#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

using namespace std;

const int MAX_SIZE = 10000;

struct dataAntrian {
    string nama;
    int umur;
    string penyakit;
    char jenis_kelamin;
    string no_antrian;
};

struct janjiTemu {
    string nama;
    string dokter;
    string waktu_janji;
    string no_antrian;
};

struct Queue {
    dataAntrian data[MAX_SIZE];
    int front, rear;
};

struct AntrianJanjiTemu {
    janjiTemu data[MAX_SIZE];
    int front, rear;
};

// Struktur data untuk Binary Search Tree
struct Node {
    dataAntrian data;
    Node* left;
    Node* right;
};

Queue q;
int antrianCounter = 0;
AntrianJanjiTemu Aq;
int JanjiCounter = 0;
vector<string> daftarDokter = {"Dr. Ahmad", "Dr. Smith", "Dr. Brown", "Dr. Sulastri", "Dr. Rudi"};

// inisialisasi queue antrian pasien umum
void inisqueue(Queue &q) {
    q.front = -1;
    q.rear = -1;
}

// inisialisasi antrian pasien janji
void inisJanji(AntrianJanjiTemu &Aq) {
    Aq.front = -1;
    Aq.rear = -1;
}

// periksa apakah queue kosong

// antrian untuk pasien umum
bool isEmpty(Queue &q) {
    return (q.front == -1 && q.rear == -1);
}

// antrian untuk pasien Janji
bool isEmptyjanji(AntrianJanjiTemu &Aq) {
    return (Aq.front == -1 && Aq.rear == -1);
}

// periksa apakah antrian penuh
// antrian pasien
bool isFull(Queue &q) {
    return ((q.rear + 1) % MAX_SIZE == q.front);
}

// antrian janji temu
bool isFulljanji(AntrianJanjiTemu &Aq) {
    return ((Aq.rear + 1) % MAX_SIZE == Aq.front);
}

// generate nomor antrian untuk pasien umum dan janji
string generateQueueNumber() {
    antrianCounter++;
    stringstream ss;
    ss << "0" << antrianCounter;
    return ss.str();
}

string generateQueueNumberJanji() {
    JanjiCounter++;
    stringstream ss;
    ss << "0" << JanjiCounter;
    return ss.str();
}

// tambah antrian
Node* root = nullptr; // Deklarasi variabel global root

// Fungsi untuk membuat node baru dalam BST
Node* createNode(dataAntrian data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Fungsi untuk memasukkan data ke dalam BST (Case-Insensitive)
Node* insertNode(Node* root, dataAntrian data) {
    string nama_lowercase = data.nama;
    for (char& c : nama_lowercase) {
        c = tolower(c);
    }

    if (root == nullptr) {
        return createNode(data);
    }

    string root_nama_lowercase = root->data.nama;
    for (char& c : root_nama_lowercase) {
        c = tolower(c);
    }

    if (nama_lowercase < root_nama_lowercase) {
        root->left = insertNode(root->left, data);
    } else if (nama_lowercase > root_nama_lowercase) {
        root->right = insertNode(root->right, data);
    } else {
        // Jika nama sama, simpan data dengan nomor antrian yang lebih kecil
        if (data.no_antrian < root->data.no_antrian) {
            root->data = data;
        }
    }

    return root;
}

// Fungsi untuk melakukan inorder traversal pada BST
void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << "| " << root->data.no_antrian;
        for (int j = root->data.no_antrian.length(); j < 16; j++) cout << " ";
        cout << "| " << root->data.nama;
        for (int j = root->data.nama.length(); j < 7; j++) cout << " ";
        cout << "| " << root->data.umur;
        for (int j = to_string(root->data.umur).length(); j < 14; j++) cout << " ";
        cout << "| " << root->data.penyakit;
        for (int j = root->data.penyakit.length(); j < 14; j++) cout << " ";
        cout << "| " << root->data.jenis_kelamin << " |" << endl;
        inorderTraversal(root->right);
    }
}

// Fungsi untuk menampilkan antrian pasien yang diurutkan berdasarkan nama
void displaySorted(Node* root) {
    if (root == nullptr) {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << "==================+========+===============+===============+===============" << endl;
    cout << "| No. Antrian     | Nama   | Umur          | Penyakit      | Jenis Kelamin |" << endl;
    cout << "==================+========+===============+===============+===============" << endl;
    inorderTraversal(root);
    cout << "==================+========+===============+===============+===============" << endl;
}

// Tambahkan kedalam antrian umum
void enqueeu(Queue &q, dataAntrian newData) {
    if (isFull(q)) {
        cout << "Antrian Penuh" << endl;
        return;
    }
    if (isEmpty(q)) {
        q.front = 0;
        q.rear = 0;
    } else {
        q.rear = (q.rear + 1) % MAX_SIZE;
    }
    newData.jenis_kelamin = toupper(newData.jenis_kelamin);
    newData.no_antrian = generateQueueNumber();
    q.data[q.rear] = newData;

    root = insertNode(root, newData);
}

// tambah janji temu
void enqueueJanjiTemu(AntrianJanjiTemu &Aq, janjiTemu newdata) {
    if (isFulljanji(Aq)) {
        cout << "Antrian Janji temu Penuh" << endl;
        return;
    }
    if (isEmptyjanji(Aq)) {
        Aq.front = 0;
        Aq.rear = 0;
    } else {
        Aq.rear = (Aq.rear + 1) % MAX_SIZE;
    }
    newdata.no_antrian = generateQueueNumberJanji();
    Aq.data[Aq.rear] = newdata;
}

// menghapus antrian
// menghapus antrian pasien biasa
void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian Kosong!" << endl;
        return;
    }

    // jika hanya ada satu elemnen, atur depan dan belakang ke -1
    if (q.front == q.rear) {
        q.front = -1;
        q.rear = -1;
    } else {
        q.front = (q.front + 1) % MAX_SIZE;
    }
}

// menghapus antrian janji temu
void dequeueJanji(AntrianJanjiTemu &Aq) {
    if (isEmptyjanji(Aq)) {
        cout << "Antrian Janji Temu Kosong" << endl;
        return;
    }
    if (Aq.front == Aq.rear) {
        Aq.front = -1;
        Aq.rear = -1;
    } else {
        Aq.front = (Aq.front + 1) % MAX_SIZE;
    }
}

void displayQueue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Antrian kosong!" << endl;
        return;
    }
    cout << "==================+========+===============+===============+===============" << endl;
    cout << "| No. Antrian     | Nama   | Umur          | Penyakit      | Jenis Kelamin |" << endl;
    cout << "==================+========+===============+===============+===============" << endl;
    int i = q.front;
    while (i != q.rear) {
        cout << "| " << q.data[i].no_antrian;
        for (int j = q.data[i].no_antrian.length(); j < 16; j++) cout << " ";
        cout << "| " << q.data[i].nama;
        for (int j = q.data[i].nama.length(); j < 7; j++) cout << " ";
        cout << "| " << q.data[i].umur;
        for (int j = to_string(q.data[i].umur).length(); j < 14; j++) cout << " ";
        cout << "| " << q.data[i].penyakit;
        for (int j = q.data[i].penyakit.length(); j < 14; j++) cout << " ";
        cout << "| " << q.data[i].jenis_kelamin;
        cout << " |" << endl;
        i = (i + 1) % MAX_SIZE;
    }
    // Output data terakhir
    cout << "| " << q.data[i].no_antrian;
    for (int j = q.data[i].no_antrian.length(); j < 16; j++) cout << " ";
    cout << "| " << q.data[i].nama;
    for (int j = q.data[i].nama.length(); j < 7; j++) cout << " ";
    cout << "| " << q.data[i].umur;
    for (int j = to_string(q.data[i].umur).length(); j < 14; j++) cout << " ";
    cout << "| " << q.data[i].penyakit;
    for (int j = q.data[i].penyakit.length(); j < 14; j++) cout << " ";
    cout << "| " << q.data[i].jenis_kelamin << " |" << endl;

    cout << "==================+========+===============+===============+===============" << endl;
}

void displayQueueJanji(AntrianJanjiTemu &Aq) {
    if (isEmptyjanji(Aq)) {
        cout << "Antrian janji temu kosong!" << endl;
        return;
    }
    cout << "==================+===============+===============+========================" << endl;
    cout << "| No. Antrian     | Nama          | Dokter        | Waktu Janji            " << endl;
    cout << "==================+===============+===============+========================" << endl;
    int i = Aq.front;
    while (i != Aq.rear) {
        cout << "| " << Aq.data[i].no_antrian;
        for (int j = Aq.data[i].no_antrian.length(); j < 16; j++) cout << " ";
        cout << "| " << Aq.data[i].nama;
        for (int j = Aq.data[i].nama.length(); j < 15; j++) cout << " ";
        cout << "| " << Aq.data[i].dokter;
        for (int j = Aq.data[i].dokter.length(); j < 14; j++) cout << " ";
        cout << "| " << Aq.data[i].waktu_janji;
        for (int j = Aq.data[i].waktu_janji.length(); j < 23; j++) cout << " ";
        cout << "|" << endl;
        i = (i + 1) % MAX_SIZE;
    }
    // Output data terakhir
    cout << "| " << Aq.data[i].no_antrian;
    for (int j = Aq.data[i].no_antrian.length(); j < 16; j++) cout << " ";
    cout << "| " << Aq.data[i].nama;
    for (int j = Aq.data[i].nama.length(); j < 15; j++) cout << " ";
    cout << "| " << Aq.data[i].dokter;
    for (int j = Aq.data[i].dokter.length(); j < 14; j++) cout << " ";
    cout << "| " << Aq.data[i].waktu_janji;
    for (int j = Aq.data[i].waktu_janji.length(); j < 23; j++) cout << " ";
    cout << "|" << endl;

    cout << "==================+===============+===============+========================" << endl;
}

void searchPasien(Node* root, const string& nama) {
    if (root == nullptr) {
        cout << "Pasien dengan nama " << nama << " tidak ditemukan." << endl;
        return;
    }

    if (nama < root->data.nama) {
        searchPasien(root->left, nama);
    } else if (nama > root->data.nama) {
        searchPasien(root->right, nama);
    } else {
        // Pasien ditemukan
        cout << "==================+========+===============+===============+===============" << endl;
        cout << "| No. Antrian     | Nama   | Umur          | Penyakit      | Jenis Kelamin |" << endl;
        cout << "==================+========+===============+===============+===============" << endl;
        cout << "| " << root->data.no_antrian;
        for (int j = root->data.no_antrian.length(); j < 16; j++) cout << " ";
        cout << "| " << root->data.nama;
        for (int j = root->data.nama.length(); j < 7; j++) cout << " ";
        cout << "| " << root->data.umur;
        for (int j = to_string(root->data.umur).length(); j < 14; j++) cout << " ";
        cout << "| " << root->data.penyakit;
        for (int j = root->data.penyakit.length(); j < 14; j++) cout << " ";
        cout << "| " << root->data.jenis_kelamin << " |" << endl;
        cout << "==================+========+===============+===============+===============" << endl;
    }
}
int main() {
    inisqueue(q);
    inisJanji(Aq);

    int choice;
    while (true) {
        cout << "\nVisual Clinic System" << endl;
        cout << "1. Tambah Pasien Umum" << endl;
        cout << "2. Tambah Janji Temu" << endl;
        cout << "3. Layani Pasien Umum" << endl;
        cout << "4. Layani Pasien Janji" << endl;
        cout << "5. Tampilkan Antrian Pasien Umum" << endl;
        cout << "6. Tampilkan Antrian Pasien Janji" << endl;
        cout << "7. Cari Pasien" << endl;
        cout << "8. Tampilkan Antrian Pasien (Diurutkan)" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Untuk menangani karakter newline

        if (choice == 9) {
            break;
        }

        switch (choice) {
            case 1: {
                system ("cls");
                dataAntrian newData;
                cout << "Masukkan Nama: ";
                getline(cin, newData.nama);
                cout << "Masukkan Umur: ";
                cin >> newData.umur;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Untuk menangani karakter newline
                cout << "Masukkan Penyakit: ";
                getline(cin, newData.penyakit);
                cout << "Masukkan Jenis Kelamin (L/P): ";
                cin >> newData.jenis_kelamin;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Untuk menangani karakter newline
                enqueeu(q, newData);
                system("cls");
                break;
            }
            case 2: {
                janjiTemu newJanji;
                cout << "Masukkan Nama: ";
                getline(cin, newJanji.nama);
                cout << "Pilih Dokter:" << endl;
                for (size_t i = 0; i < daftarDokter.size(); ++i) {
                    cout << i + 1 << ". " << daftarDokter[i] << endl;
                }
                int dokterChoice;
                cout << "Pilihan: ";
                cin >> dokterChoice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Untuk menangani karakter newline
                if (dokterChoice < 1 || dokterChoice > (int)daftarDokter.size()) {
                    cout << "Pilihan dokter tidak valid." << endl;
                    break;
                }
                newJanji.dokter = daftarDokter[dokterChoice - 1];
                cout << "Masukkan Waktu Janji : ";
                getline(cin, newJanji.waktu_janji);
                enqueueJanjiTemu(Aq, newJanji);
                break;
            }
            case 3:
                dequeue(q);
                break;
            case 4:
                dequeueJanji(Aq);
                break;
            case 5:
                displayQueue(q);
                break;
            case 6:
                displayQueueJanji(Aq);
                break;
            case 7: {
                string nama;
                cout << "Masukkan Nama Pasien yang Dicari: ";
                getline(cin, nama);
                searchPasien(root, nama);
                break;
            }
            case 8:
                displaySorted(root);
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }
    }

    return 0;
}
