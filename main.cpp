#include <iostream>
#include "MLL.h"

using namespace std;

int main () {
    ListKota L;
    createListKota(L);
    dataKota dk;
    dataRiwayat dr;
    adrKota p;
    adrRiwayat q;
    string namaKota;

    cout << "===== DATA KOTA =====" << endl;
    for (int i = 1; i <= 3; i++) {
        cout << "Masukkan Nama Kota: ";
        cin >> dk.nama;
        cout << "Luas Wilayah: ";
        cin >> dk.luasWilayah;
        cout << "Jumlah Penduduk: ";
        cin >> dk.jumlahPenduduk;
        cout << "Indeks Kebersihan (1 - 10): ";
        cin >> dk.indeksKebersihan;
        cout << endl;

        p = createElemenKota(dk);
        insertKota(L, p);
    }
        
    cout << "===== DATA RIWAYAT =====" << endl; 
    for (int i = 0; i < 3; i++) {
        cout << "Nama Petugas: ";
        cin >> dr.petugas;
        cout << "Tanggal Pengankutan Sampah: ";
        cin >> dr.tanggal;
        cout << "Jam Pengankutan Sampah: ";
        cin >> dr.jamPengambilan;
        cout << "Bobot Sampah: ";
        cin >> dr.bobot;
        cout << "Jenis Sampah: ";
        cin >> dr.jenisSampah;
        cout << endl;
        cout << "Nama Kota Yang Mau Diinput: ";
        cin >> namaKota;

        adrKota searchK = searchKota(L, namaKota);
        q = createElemenRiwayat(dr);
        insertRiwayat(searchK, q);
    }

    display(L);

    return 0;
}