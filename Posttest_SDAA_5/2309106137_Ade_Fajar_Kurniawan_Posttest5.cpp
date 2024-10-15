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
    Node* next;      
};


void push(Node* &stack, Mahasiswa mhs) {
    Node* newNode = new Node; 
    newNode->data = mhs;      
    newNode->next = stack;    
    stack = newNode;       
}

void pop(Node* &stack) {
    if (stack == NULL) {
        cout << "Stack kosong, tidak ada data untuk dihapus.\n";
        return;
    }
    Node* temp = stack;       
    stack = stack->next;      
    delete temp;             
    cout << "Data terakhir dalam Stack berhasil dihapus.\n";
}


void enqueue(Node* &front, Node* &rear, Mahasiswa mhs) {
    Node* newNode = new Node; 
    newNode->data = mhs;      
    newNode->next = NULL;     

    if (rear == NULL) {     
        front = rear = newNode; 
    } else {
        rear->next = newNode;
        rear = newNode;     
    }
}

void dequeue(Node* &front, Node* &rear) {
    if (front == NULL) {
        cout << "Queue kosong, tidak ada data untuk dihapus.\n"; 
        return;
    }
    Node* temp = front;      
    front = front->next;      

    if (front == NULL) {      
        rear = NULL;         
    }

    delete temp;              
    cout << "Data pertama dalam Queue berhasil dihapus.\n";
}


Node* createNode(Mahasiswa mhs) {
    Node* newNode = new Node; 
    newNode->data = mhs;      
    newNode->next = NULL;     
    return newNode;           
}

void inputMahasiswa(Node* &head, Mahasiswa &mhs) {
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

    if (index == 1) {
        head = head->next; 
        delete temp;       
    } else {
        Node* current = head;
        for (int i = 1; i < index - 1; i++) {
            current = current->next; 
        }

        Node* nodeToDelete = current->next; 
        current->next = nodeToDelete->next; 
        delete nodeToDelete; 
    }

    jumlah--; 
    cout << "Data mahasiswa berhasil dihapus.\n";
}


Node* merge(Node* kiri, Node* kanan) {
    if (!kiri) return kanan;
    if (!kanan) return kiri;

    if (kiri->data.nama <= kanan->data.nama) {
        kiri->next = merge(kiri->next, kanan);
        return kiri;
    } else {
        kanan->next = merge(kiri, kanan->next);
        return kanan;
    }
}

Node* mergeSort(Node* head) {
    if (!head || !head->next) {
        return head;
    }

    Node* tengah = head;
    Node* cepat = head->next;

    while (cepat && cepat->next) {
        tengah = tengah->next;
        cepat = cepat->next->next;
    }

    Node* separuhKedua = tengah->next;
    tengah->next = NULL;

    Node* kiri = mergeSort(head);
    Node* kanan = mergeSort(separuhKedua);

    return merge(kiri, kanan);
}


Node* partition(Node* head, Node** depan, Node** belakang) {
    Node* pivot = head;
    Node* saatIni = head->next;

    Node* besar = NULL;
    Node* kecil = NULL;

    while (saatIni != NULL) {
        Node* nextNode = saatIni->next;
        if (saatIni->data.nama > pivot->data.nama) {
            saatIni->next = besar;
            besar = saatIni;
        } else {
            saatIni->next = kecil;
            kecil = saatIni;
        }
        saatIni = nextNode;
    }

    *depan = besar;
    *belakang = kecil;
    return pivot;
}

Node* quickSort(Node* head) {
    if (!head || !head->next) {
        return head;
    }

    Node* depan = NULL;
    Node* belakang = NULL;

    Node* pivot = partition(head, &depan, &belakang);

    depan = quickSort(depan);
    belakang = quickSort(belakang);

    if (!depan) {
        pivot->next = belakang;
        return pivot;
    } else {
        Node* temp = depan;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = pivot;
        pivot->next = belakang;
        return depan;
    }
}


int main() {
    Mahasiswa mhs;              
    Node* mahasiswa = NULL;      
    Node* stack = NULL;          
    Node* front = NULL;          
    Node* rear = NULL;           
    int jumlah = 0;              
    int pilihan;

    do {
        cout << "\nMenu:\n";
        cout << "1. Input data mahasiswa\n";
        cout << "2. Tampilkan data mahasiswa\n";
        cout << "3. Edit data mahasiswa\n";
        cout << "4. Hapus data mahasiswa\n";
        cout << "5. Push data ke Stack\n";
        cout << "6. Pop data dari Stack\n";
        cout << "7. Enqueue data ke Queue\n";
        cout << "8. Dequeue data dari Queue\n";
        cout << "9. Urutkan data mahasiswa (Ascending menggunakan Merge Sort)\n";
        cout << "10. Urutkan data mahasiswa (Descending menggunakan Quick Sort)\n";
        cout << "11. Keluar\n";
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
                cout << "Input data untuk Stack:\n";
                inputMahasiswa(mahasiswa, mhs); 
                push(stack, mhs);
                break;
            case 6:
                pop(stack); 
                break;
            case 7:
                cout << "Input data untuk Queue:\n";
                inputMahasiswa(mahasiswa, mhs);
                enqueue(front, rear, mhs);
                break;
            case 8:
                dequeue(front, rear); 
                break;
            case 9:
                mahasiswa = mergeSort(mahasiswa);
                cout << "Data mahasiswa berhasil diurutkan (Ascending - Berdasarkan Nama)\n";
                break;
            case 10:
                mahasiswa = quickSort(mahasiswa);
                cout << "Data mahasiswa berhasil diurutkan (Descending - Berdasarkan Nama)\n";
                break;
            case 11:
                cout << "Keluar dari program.\n"; 
                break;
            default:
                cout << "Pilihan tidak valid.\n"; 
        }
    } while (pilihan != 11); 

 
    while (mahasiswa != NULL) {
        Node* temp = mahasiswa;
        mahasiswa = mahasiswa->next; 
        delete temp; 
    }

  
    while (stack != NULL) {
        Node* temp = stack;
        stack = stack->next; 
        delete temp; 
    }

  
    while (front != NULL) {
        Node* temp = front;
        front = front->next; 
        delete temp; 
    }

    return 0; 
}
