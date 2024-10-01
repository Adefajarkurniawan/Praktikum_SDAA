#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string nama;
    string universitas;
    string fakultas;
    string program_studi;
    string nim;
};

struct Node {
    Mahasiswa data;
    Node* next; // pointer ke node berikutnya
};



// Function to create a new node
Node* createNode(Mahasiswa mhs) {
    Node* newNode = new Node;
    newNode->data = mhs;
    newNode->next = NULL; //ndode terakhir atau baru
    return newNode;
}

// Function to insert a new mahasiswa at the end of the list
void inputMahasiswa(Node* &head, Mahasiswa &mhs ) {
    
    cout << "Masukkan Nama: ";
    getline(cin, mhs.nama);
    cout << "Masukkan Universitas: ";
    getline(cin, mhs.universitas);
    cout << "Masukkan Fakultas: ";
    getline(cin, mhs.fakultas);
    cout << "Masukkan Program Studi: ";
    getline(cin, mhs.program_studi);
    cout << "Masukkan NIM: ";
    getline(cin, mhs.nim);

    Node* newNode = createNode(mhs);

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Data mahasiswa berhasil ditambahkan.\n";
}

// Function to display all mahasiswa data
void tampilkanMahasiswa(Node* head) {
    if (head == NULL) {
        cout << "Tidak ada data mahasiswa.\n";
        return;
    }

    Node* temp = head;
    int index = 1;
    while (temp != NULL) {
        cout << "Mahasiswa ke-" << index++ << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Universitas: " << temp->data.universitas << endl;
        cout << "Fakultas: " << temp->data.fakultas << endl;
        cout << "Program Studi: " << temp->data.program_studi << endl;
        cout << "NIM: " << temp->data.nim << endl;
        cout << "-----------------------------" << endl;
        temp = temp->next;
    }
}

// Function to edit mahasiswa data
void editMahasiswa(Node* head, int jumlah) {
    int index;
    cout << "Masukkan nomor mahasiswa yang ingin diedit (1 - " << jumlah << "): ";
    cin >> index;
    cin.ignore();

    if (index <= 0 || index > jumlah) {
        cout << "Nomor mahasiswa tidak valid.\n";
        return;
    }

    Node* temp = head;
    for (int i = 1; i < index; i++) {
        temp = temp->next;
    }

    cout << "Masukkan data baru untuk Mahasiswa ke-" << index << endl;
    cout << "Masukkan Nama: ";
    getline(cin, temp->data.nama);
    cout << "Masukkan Universitas: ";
    getline(cin, temp->data.universitas);
    cout << "Masukkan Fakultas: ";
    getline(cin, temp->data.fakultas);
    cout << "Masukkan Program Studi: ";
    getline(cin, temp->data.program_studi);
    cout << "Masukkan NIM: ";
    getline(cin, temp->data.nim);
    cout << "Data mahasiswa berhasil diubah.\n";
}

// Function to delete a mahasiswa from the list
void hapusMahasiswa(Node* &head, int &jumlah) {
    int index;
    cout << "Masukkan nomor mahasiswa yang ingin dihapus (1 - " << jumlah << "): ";
    cin >> index;
    cin.ignore();

    if (index <= 0 || index > jumlah) {
        cout << "Nomor mahasiswa tidak valid.\n";
        return;
    }

    Node* temp = head;

    // Jika node pertama yang akan dihapus
    if (index == 1) {
        head = head->next; // Kepala list pindah ke node berikutnya
        delete temp; // Hapus node lama
    } else {
        // Temukan node sebelum node yang akan dihapus
        Node* current = head;
        for (int i = 1; i < index - 1; i++) {
            current = current->next;
        }

        // Simpan node yang akan dihapus
        Node* nodeToDelete = current->next;
        // Hubungkan node sebelum yang dihapus dengan node setelahnya
        current->next = nodeToDelete->next;
        // Hapus node
        delete nodeToDelete;
    }

    jumlah--;
    cout << "Data mahasiswa berhasil dihapus.\n";
}


int main() {
    Mahasiswa mhs;
    Node* mahasiswa = NULL; // Head pointer to the linked list
    int jumlah = 0; // Counter for number of mahasiswa
    int pilihan;

    do {
        cout << "\nMenu:\n";
        cout << "1. Input data mahasiswa\n";
        cout << "2. Tampilkan data mahasiswa\n";
        cout << "3. Edit data mahasiswa\n";
        cout << "4. Hapus data mahasiswa\n";
        cout << "5. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore(); 

        switch (pilihan) {
            case 1:
                inputMahasiswa(mahasiswa, mhs);
                jumlah++;
                break;
            case 2:
                tampilkanMahasiswa(mahasiswa);
                break;
            case 3:
                editMahasiswa(mahasiswa, jumlah);
                break;
            case 4:
                hapusMahasiswa(mahasiswa, jumlah);
                break;
            case 5:
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    // Clean up linked list memory
    while (mahasiswa != NULL) {
        Node* temp = mahasiswa;
        mahasiswa = mahasiswa->next;
        delete temp;
    }

    return 0;
}
