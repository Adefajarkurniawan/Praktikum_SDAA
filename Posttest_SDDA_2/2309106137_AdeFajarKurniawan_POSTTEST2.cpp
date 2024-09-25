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


void inputMahasiswa(Mahasiswa* &mhs, int &jumlah) {
    int tambahan;
    cout << "Masukkan jumlah mahasiswa yang ingin ditambah: ";
    cin >> tambahan;
    cin.ignore(); 

    Mahasiswa* temp = new Mahasiswa[jumlah + tambahan];

    
    for (int i = 0; i < jumlah; i++) {
        temp[i] = mhs[i];
    }

   
    for (int i = jumlah; i < jumlah + tambahan; i++) {
        cout << "Mahasiswa ke-" << i+1 << endl;
        cout << "Masukkan Nama: ";
        getline(cin, temp[i].nama);
        cout << "Masukkan Universitas: ";
        getline(cin, temp[i].universitas);
        cout << "Masukkan Fakultas: ";
        getline(cin, temp[i].fakultas);
        cout << "Masukkan Program Studi: ";
        getline(cin, temp[i].program_studi);
        cout << "Masukkan NIM: ";
        getline(cin, temp[i].nim);
        cout << endl;
    }

    delete[] mhs;

    
    mhs = temp;
    jumlah += tambahan;
}


void tampilkanMahasiswa(Mahasiswa* mhs, int jumlah) {
    if (jumlah == 0) {
        cout << "Tidak ada data mahasiswa.\n";
        return;
    }

    for(int i = 0; i < jumlah; i++) {
        cout << "Mahasiswa ke-" << i+1 << endl;
        cout << "Nama: " << mhs[i].nama << endl;
        cout << "Universitas: " << mhs[i].universitas << endl;
        cout << "Fakultas: " << mhs[i].fakultas << endl;
        cout << "Program Studi: " << mhs[i].program_studi << endl;
        cout << "NIM: " << mhs[i].nim << endl;
        cout << "-----------------------------" << endl;
    }
}


void editMahasiswa(Mahasiswa* mhs, int jumlah) {
    int index;
    cout << "Masukkan nomor mahasiswa yang ingin diedit (1 - " << jumlah << "): ";
    cin >> index;
    cin.ignore(); 

    if (index > 0 && index <= jumlah) {
        index--; 
        cout << "Masukkan data baru untuk Mahasiswa ke-" << index+1 << endl;
        cout << "Masukkan Nama: ";
        getline(cin, mhs[index].nama);
        cout << "Masukkan Universitas: ";
        getline(cin, mhs[index].universitas);
        cout << "Masukkan Fakultas: ";
        getline(cin, mhs[index].fakultas);
        cout << "Masukkan Program Studi: ";
        getline(cin, mhs[index].program_studi);
        cout << "Masukkan NIM: ";
        getline(cin, mhs[index].nim);
        cout << "Data mahasiswa berhasil diubah.\n";
    } else {
        cout << "Nomor mahasiswa tidak valid.\n";
    }
}


void hapusMahasiswa(Mahasiswa* &mhs, int &jumlah) {
    int index;
    cout << "Masukkan nomor mahasiswa yang ingin dihapus (1 - " << jumlah << "): ";
    cin >> index;
    cin.ignore(); 

    if (index > 0 && index <= jumlah) {
        index--; 
        for (int i = index; i < jumlah - 1; i++) {
            mhs[i] = mhs[i + 1]; 
        }
        jumlah--; 
        cout << "Data mahasiswa berhasil dihapus.\n";

        Mahasiswa* temp = new Mahasiswa[jumlah];
        for (int i = 0; i < jumlah; i++) {
            temp[i] = mhs[i];
        }
        delete[] mhs;
        mhs = temp;
    } else {
        cout << "Nomor mahasiswa tidak valid.\n";
    }
}

int main() {
    int jumlah = 0;
    Mahasiswa* mahasiswa = NULL; 

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
                inputMahasiswa(mahasiswa, jumlah);
                break;
            case 2:
                tampilkanMahasiswa(mahasiswa, jumlah);
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

    
    delete[] mahasiswa;

    return 0;
}
