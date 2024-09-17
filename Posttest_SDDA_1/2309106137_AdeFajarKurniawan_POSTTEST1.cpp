#include <iostream>
#include <cmath> 
using namespace std;

void hanoi(int n, int cakram, string Asal, string Tujuan, string Sementara) {
    if (cakram == 1) 
    {
        cout << "Pindahkan cakram " << cakram << " dari " << Asal << " ke " << Tujuan << endl;
        return;
    } 
    hanoi(n, cakram - 1, Asal, Sementara, Tujuan);
    cout << "Pindahkan cakram " << cakram << " dari " << Asal << " ke " << Tujuan << endl;
    hanoi(n, cakram - 1, Sementara, Tujuan, Asal);
}


int jumlahLangkahPalingCepat(int n)
{
    return pow(2, n) - 1;  
}

int main() {
    int n;
    cout << "Masukkan jumlah cakram: ";
    cin >> n;
    
    int langkahMinimal = jumlahLangkahPalingCepat(n);
    cout << "Jumlah langkah paling cepat untuk memindahkan " << n << " cakram adalah: " << langkahMinimal << " langkah." << endl;
    
    hanoi(n, n, "Asal", "Tujuan", "Sementara"); 
    return 0;
}
