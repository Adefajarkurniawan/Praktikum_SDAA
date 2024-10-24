#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>  // For stringstream to convert string to integer

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

// Stack functionality: Push
void push(Node* &stack, Mahasiswa mhs) {
    Node* newNode = new Node;
    newNode->data = mhs;
    newNode->next = stack;
    stack = newNode;
}

// Stack functionality: Pop
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

// Queue functionality: Enqueue
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

// Queue functionality: Dequeue
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

// Function to input Mahasiswa data
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

    Node* newNode = new Node;
    newNode->data = mhs;
    newNode->next = NULL;

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

// Function to convert linked list of NIMs to a vector of integers
vector<int> getNIMVector(Node* head) {
    vector<int> nims;
    while (head != NULL) {
        stringstream ss(head->data.nim);  // Create a stringstream object
        int nim;
        ss >> nim;  // Convert string to integer
        nims.push_back(nim);  // Push the integer to the vector
        head = head->next;
    }
    return nims;
}

// Fibonacci Search on a sorted integer array
int fibonacciSearch(vector<int> arr, int x) {
    int n = arr.size();
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
        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && arr[offset + 1] == x) {
        return offset + 1;
    }

    return -1;
}

// Jump Search for an integer array
int jumpSearch(vector<int> arr, int x) {
    int n = arr.size();
    int step = sqrt(n);

    int prev = 0;
    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if (arr[i] == x)
            return i;
    }
    return -1;
}

// Function to build the Boyer-Moore bad character heuristic table
void badCharHeuristic(string str, int size, int badChar[256]) {
    for (int i = 0; i < 256; i++)
        badChar[i] = -1;

    for (int i = 0; i < size; i++)
        badChar[(int) str[i]] = i;
}

// Boyer-Moore string search algorithm
int boyerMooreSearch(string txt, string pat) {
    int m = pat.size();
    int n = txt.size();

    int badChar[256];
    badCharHeuristic(pat, m, badChar);

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0) {
            return s;
        } else {
            s += max(1, j - badChar[txt[s + j]]);
        }
    }
    return -1;
}

int main() {
    Mahasiswa mhs;
    Node* mahasiswa = NULL;
    Node* stack = NULL;
    Node* front = NULL;
    Node* rear = NULL;
    int pilihan;
    int searchNIM;
    string searchNama;

    do {
        cout << "\nMenu:\n";
        cout << "1. Input data mahasiswa\n";
        cout << "2. Cari NIM menggunakan Fibonacci Search\n";
        cout << "3. Cari NIM menggunakan Jump Search\n";
        cout << "4. Cari Nama menggunakan Boyer-Moore\n";
        cout << "5. Push data ke Stack\n";
        cout << "6. Pop data dari Stack\n";
        cout << "7. Enqueue data ke Queue\n";
        cout << "8. Dequeue data dari Queue\n";
        cout << "9. Keluar\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                inputMahasiswa(mahasiswa, mhs);
                break;
            case 2:
                cout << "Masukkan NIM yang ingin dicari: ";
                cin >> searchNIM;
                cin.ignore();
                {
                    vector<int> nims = getNIMVector(mahasiswa);
                    int result = fibonacciSearch(nims, searchNIM);
                    if (result != -1)
                        cout << "NIM ditemukan di indeks ke-" << result + 1 << endl;
                    else
                        cout << "NIM tidak ditemukan\n";
                }
                break;
            case 3:
                cout << "Masukkan NIM yang ingin dicari: ";
                cin >> searchNIM;
                cin.ignore();
                {
                    vector<int> nims = getNIMVector(mahasiswa);
                    int result = jumpSearch(nims, searchNIM);
                    if (result != -1)
                        cout << "NIM ditemukan di indeks ke-" << result + 1 << endl;
                    else
                        cout << "NIM tidak ditemukan\n";
                }
                break;
            case 4:
                cout << "Masukkan nama yang ingin dicari: ";
                getline(cin, searchNama);
                {
                    Node* temp = mahasiswa;
                    while (temp != NULL) {
                        if (boyerMooreSearch(temp->data.nama, searchNama) != -1) {
                            cout << "Nama ditemukan: " << temp->data.nama << endl;
                            break;
                        }
                        temp = temp->next;
                    }
                    if (!temp) {
                        cout << "Nama tidak ditemukan\n";
                    }
                }
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
                cout << "Keluar dari program.\n";
                break;
            default:
                cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 9);

    return 0;
}
