#include <iostream>
#include <string>
#include "MLL.h"

using namespace std;

int main() {
    ListKota L;
    createListKota(L);
    
    // Variabel Bantuan
    int pilihanUtama, pilihanSub, pilihanTampil;
    dataKota dk;
    dataRiwayat dr;
    adrKota pKota;
    adrRiwayat pRiwayat, qTemp; // qTemp untuk keperluan delete
    string inputNamaKota;
    
    while (pilihanUtama != 0) {
        cout << "============================================" << endl;
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
            cout << "2. Ubah Data Kota (Placeholder)" << endl;
            cout << "3. Hapus Kota (Placeholder)" << endl;
            cout << "0. Kembali ke Menu Utama" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n[INPUT KOTA BARU]" << endl;
                cout << "Nama Kota               : "; 
                cin >> dk.nama;
                cout << "Luas Wilayah (Hektar)   : "; 
                cin >> dk.luasWilayah;
                cout << "Jumlah Penduduk         : "; 
                cin >> dk.jumlahPenduduk;
                cout << "Indeks Kebersihan (1-10): "; 
                cin >> dk.indeksKebersihan;
                
                pKota = createElemenKota(dk);
                insertKota(L, pKota);
                cout << ">>> Sukses menambah kota: " << dk.nama << endl << endl;
            } else if (pilihanSub == 2 || pilihanSub == 3) {
                cout << ">>> Fitur Ubah/Hapus Kota belum diimplementasikan di library." << endl << endl;
            }
            break;

        case 2: // === SUB MENU RIWAYAT ===
            cout << "--- MENU KELOLA RIWAYAT SAMPAH ---" << endl;
            cout << "1. Tambah Riwayat ke Kota Tertentu" << endl;
            cout << "2. Hapus Riwayat (Awal/Akhir/Pilih)" << endl;
            cout << "3. Ubah Data Riwayat (Update)" << endl;
            cout << "0. Kembali ke Menu Utama" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                // INPUT RIWAYAT
                cout << "\n[TAMBAH RIWAYAT]" << endl;
                cout << "Masukkan Nama Kota Target: ";
                cin >> inputNamaKota;
                
                pKota = searchKota(L, inputNamaKota);
                if (pKota != nullptr) {
                    cout << ">> Kota Ditemukan. Masukkan Data Riwayat:" << endl;
                    cout << "Petugas            : "; getline(cin, dr.petugas);
                    cout << "Tanggal (dd-mm-yy) : "; getline(cin, dr.tanggal);
                    cout << "Jam (hh:mm)        : "; getline(cin, dr.jamPengambilan);
                    cout << "Jenis Sampah       : "; getline(cin, dr.jenisSampah);
                    cout << "Bobot (kg)         : "; cin >> dr.bobot;
                    
                    pRiwayat = createElemenRiwayat(dr);
                    insertRiwayat(pKota, pRiwayat);
                    cout << ">>> Sukses menambah riwayat ke " << inputNamaKota << endl << endl;
                } else {
                    cout << ">>> Error: Kota tidak ditemukan!" << endl << endl;
                }

            } else if (pilihanSub == 2) {
                // HAPUS RIWAYAT
                cout << "\n[HAPUS RIWAYAT]" << endl;
                cout << "Masukkan Nama Kota Target: ";
                cin >> inputNamaKota;
                pKota = searchKota(L, inputNamaKota);

                if (pKota != nullptr && !isEmptyRiwayat(pKota)) {
                    cout << "1. Hapus Riwayat Pertama" << endl;
                    cout << "2. Hapus Riwayat Terakhir" << endl;
                    cout << "3. Hapus Spesifik (After)" << endl;
                    cout << ">> Pilihan Hapus: ";
                    int pilHapus; cin >> pilHapus;

                    if (pilHapus == 1) {
                        deleteFirstRiwayat(pKota, qTemp); // qTemp menampung yang dihapus
                        cout << ">>> Riwayat pertama berhasil dihapus." << endl;
                    } else if (pilHapus == 2) {
                        deleteLastRiwayat(pKota, qTemp);
                        cout << ">>> Riwayat terakhir berhasil dihapus." << endl;
                    } else if (pilHapus == 3) {
                        cout << ">>> Fitur deleteAfter perlu logika pointer prec." << endl;
                    }
                } else {
                    cout << ">>> Kota tidak ditemukan atau Riwayat kosong." << endl;
                }
                cout << endl;

            } else if (pilihanSub == 3) {
                // UPDATE RIWAYAT
                cout << ">>> Fitur Update Riwayat (Memerlukan logika pencarian riwayat spesifik)." << endl << endl;
            }
            break;

        case 3: // === SUB MENU TAMPILAN ===
            cout << "--- MENU TAMPILAN DATA ---" << endl;
            cout << "1. Tampilkan Semua Data (Default)" << endl;
            cout << "2. Tampilkan Berdasarkan Kategori (Filter/Sort)" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n=== SELURUH DATA KOTA DAN RIWAYAT ===" << endl;
                display(L);
                cout << endl;
            } else if (pilihanSub == 2) {
                // MENU FILTER / SORTING (HANYA KERANGKA)
                cout << "\n[PILIH KATEGORI TAMPILAN]" << endl;
                cout << "1. Berdasarkan Tanggal (Terbaru - Terlama)" << endl;
                cout << "2. Berdasarkan Jam Pengangkutan" << endl;
                cout << "3. Berdasarkan Bobot Sampah (Tertinggi - Terendah)" << endl;
                cout << "4. Berdasarkan Jenis Sampah (Organik/Anorganik)" << endl;
                cout << ">> Pilihan Filter: ";
                cin >> pilihanTampil;

                if (pilihanTampil == 3) {
                    bobotMin(L);
                    bobotMax(L);
                }
            }
            break;

        case 0:
            cout << "Keluar dari program. Terima kasih!" << endl;
            break;

        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl << endl;
        }

    }

    return 0;
}