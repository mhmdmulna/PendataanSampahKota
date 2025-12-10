#include <iostream>
#include "MLL.h"

using namespace std;

int main () {
    ListKota L;
    createListKota(L);
    kota dataKota;
    adrKota p;

    for (int i = 1; i <= 3; i++) {
        cout << "Masukkan Nama Kota: ";
        cin >> dataKota.nama;
        cout << "Luas Wilayah: ";
        cin >> dataKota.luasWilayah;
        cout << "Jumlah Penduduk: ";
        cin >> dataKota.jumlahPenduduk;
        cout << "Indeks Kebersihan (1 - 10): ";
        cin >> dataKota.indeksKebersihan;
        cout << endl;

        p = createElemenKota(dataKota);
        
    }

    return 0;
}