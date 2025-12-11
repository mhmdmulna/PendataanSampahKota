#include <iostream>
#include <fstream>
#include "MLL.h"

using namespace std;

int main() {
    ListKota L;
    createListKota(L);
    
    dataKota dk;
    dataRiwayat dr;
    string kotaTujuan;

    // --- READ FILE KOTA ---
    ifstream fileKota("kota.txt");
    if (fileKota.is_open()) {
        while (fileKota >> dk.nama >> dk.luasWilayah >> dk.jumlahPenduduk >> dk.indeksKebersihan) {
            adrKota p = createElemenKota(dk);
            insertKota(L, p);
        }
        fileKota.close();
    }

    // --- READ FILE RIWAYAT ---
    ifstream fileRia("riwayat.txt");
    if (fileRia.is_open()) {
        while (fileRia >> dr.bobot >> dr.petugas >> dr.jenisSampah >> dr.tanggal >> dr.bulan >> dr.tahun >> dr.jamPengambilan >> kotaTujuan) {
            adrRiwayat q = createElemenRiwayat(dr);
            adrKota kotaP = searchKota(L, kotaTujuan);

            if (kotaP != nullptr) {
                insertRiwayat(kotaP, q);
            }
        }
        fileRia.close();
    }
    
    int pilihanUtama = -1, pilihanSub, pilihanTampil;
    adrKota pKota;
    adrRiwayat pRiwayat; 
    adrRiwayat qTemp = nullptr;
    string inputNamaKota;
    
    while (pilihanUtama != 0) {
        cout << "\n============================================" << endl;
        cout << "      APLIKASI MANAJEMEN SAMPAH KOTA        " << endl;
        cout << "============================================" << endl;
        cout << "1. Kelola Data Kota" << endl;
        cout << "2. Kelola Data Riwayat Sampah" << endl;
        cout << "3. Tampilkan Data" << endl;
        cout << "0. Keluar" << endl;
        cout << "============================================" << endl;
        cout << ">> Pilihan Anda: ";
        cin >> pilihanUtama;
        cout << endl;

        switch (pilihanUtama) {
        case 1: // === SUB MENU KOTA ===
            cout << "--- MENU KELOLA KOTA ---" << endl;
            cout << "1. Tambah Kota Baru" << endl;
            cout << "2. Ubah Data Kota" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n[INPUT KOTA BARU]" << endl;
                cout << "Nama Kota (tanpa_spasi) : "; cin >> dk.nama;
                cout << "Luas Wilayah (Hektar)   : "; cin >> dk.luasWilayah;
                cout << "Jumlah Penduduk         : "; cin >> dk.jumlahPenduduk;
                cout << "Indeks Kebersihan (1-10): "; cin >> dk.indeksKebersihan;
                
                pKota = createElemenKota(dk);
                insertKota(L, pKota);
                cout << ">>> Sukses menambah kota: " << dk.nama << endl;

            } else if (pilihanSub == 2) {
                cout << "Masukkan Nama Kota: "; cin >> inputNamaKota;
                updateKota(L, inputNamaKota);
            }
            break;

        case 2: // === SUB MENU RIWAYAT ===
            cout << "--- MENU KELOLA RIWAYAT SAMPAH ---" << endl;
            cout << "1. Tambah Riwayat" << endl;
            cout << "2. Hapus Riwayat" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n[TAMBAH RIWAYAT]" << endl;
                cout << "Masukkan Nama Kota Target: ";
                cin >> inputNamaKota;
                
                pKota = searchKota(L, inputNamaKota);
                if (pKota != nullptr) {
                    cout << "Petugas (tanpa_spasi) : "; cin >> dr.petugas;
                    cout << "Tanggal               : "; cin >> dr.tanggal;
                    cout << "Bulan                 : "; cin >> dr.bulan;
                    cout << "Tahun                 : "; cin >> dr.tahun;
                    cout << "Jam (hh:mm)           : "; cin >> dr.jamPengambilan;
                    cout << "Jenis Sampah          : "; cin >> dr.jenisSampah;
                    cout << "Bobot (kg)            : "; cin >> dr.bobot;
                    
                    pRiwayat = createElemenRiwayat(dr);
                    insertRiwayat(pKota, pRiwayat);
                    cout << ">>> Sukses menambah riwayat." << endl;
                } else {
                    cout << ">>> Error: Kota tidak ditemukan!" << endl;
                }

            } else if (pilihanSub == 2) {
                cout << "\n[HAPUS RIWAYAT]" << endl;
                cout << "Masukkan Nama Kota Target: ";
                cin >> inputNamaKota;
                pKota = searchKota(L, inputNamaKota);

                if (pKota != nullptr && !isEmptyRiwayat(pKota)) {
                    cout << "1. Hapus Riwayat Pertama" << endl;
                    cout << "2. Hapus Riwayat Terakhir" << endl;
                    cout << ">> Pilihan Hapus: ";
                    int pilHapus; cin >> pilHapus;

                    if (pilHapus == 1) {
                        deleteFirstRiwayat(pKota, qTemp);
                        cout << ">>> Riwayat pertama berhasil dihapus." << endl;
                    } else if (pilHapus == 2) {
                        deleteLastRiwayat(pKota, qTemp);
                        cout << ">>> Riwayat terakhir berhasil dihapus." << endl;
                    }
                    // Jika qTemp tidak null, memori harusnya dibebaskan di C++ standar
                    // delete qTemp; 
                } else {
                    cout << ">>> Kota tidak ditemukan atau Riwayat kosong." << endl;
                }
            }
            break;

        case 3: // === SUB MENU TAMPILAN ===
            cout << "--- MENU TAMPILAN DATA ---" << endl;
            cout << "1. Tampilkan Semua Data (Tabel)" << endl;
            cout << "2. Statistik Kota (Bersih/Kotor/Total Sampah)" << endl;
            cout << "3. Cari Berdasarkan Jenis Sampah" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n=== DATA KOTA DAN RIWAYAT ===" << endl;
                display(L);

            } else if (pilihanSub == 2) {
                cout << "\n=== STATISTIK ===" << endl;
                indeksMax(L);
                indeksMin(L);
                cout << "-----------------" << endl;
                jumlahSampahKota(L);
                cout << "-----------------" << endl;
                cout << "Detail Ekstrem Bobot:" << endl;
                bobotMax(L);
                bobotMin(L);

            } else if (pilihanSub == 3) {
                cout << "Masukkan Jenis Sampah: ";
                string jenisCari;
                cin >> jenisCari;
                searchJenisSampah(L, jenisCari);
            }
            break;
        
        case 0:
            cout << "Keluar." << endl;
            break;
            
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    }

    return 0;
}