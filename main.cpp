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
            insertLastKota(L, p);
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
                insertLastRiwayat(kotaP, q);
            }
        }
        fileRia.close();
    }
    
    int pilihanUtama = -1, pilihanSub, pilihanTampil, pilihanRange;
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
        cout << "4. Menu Query" << endl;
        cout << "0. Keluar" << endl;
        cout << "============================================" << endl;
        cout << ">> Pilihan Anda: ";
        cin >> pilihanUtama;
        cout << endl;

        switch (pilihanUtama) {
        case 1:
            cout << "--- MENU KELOLA KOTA ---" << endl;
            cout << "1. Tambah Kota Baru" << endl;
            cout << "2. Ubah Data Kota" << endl;
            cout << "3. Hapus Data Kota" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n[PILIH KATEGORI INSERT]" << endl;
                cout << "1. Insert First" << endl;
                cout << "2. Insert After" << endl;
                cout << "3. Insert Last" << endl;
                cout << ">> Pilihan Kategori: ";
                cin >> pilihanTampil;

                if (pilihanTampil >= 1 && pilihanTampil <= 3) {
                    
                    cout << "\n[INPUT KOTA BARU]" << endl;
                    cout << "Nama Kota (tanpa_spasi) : "; cin >> dk.nama;

                    if (searchKota(L, dk.nama) == nullptr) {
                        cout << "Luas Wilayah (Hektar)   : "; cin >> dk.luasWilayah;
                        cout << "Jumlah Penduduk         : "; cin >> dk.jumlahPenduduk;
                        cout << "Indeks Kebersihan (1-10): "; cin >> dk.indeksKebersihan;
                        pKota = createElemenKota(dk);

                        if (pilihanTampil == 1) {
                            insertFirstKota(L, pKota);
                            cout << ">>> Sukses menambah kota (First): " << dk.nama << endl;

                        } else if (pilihanTampil == 2) {
                            tampilkanListKota(L);
                            int nomor;
                            cout << "Masukkan nomor urut yang ingin disisipkan: ";
                            cin >> nomor;

                            if (nomor >= 1 && nomor < countKota(L)) {
                                insertAfterKota(L, nomor, pKota);
                                cout << ">>> Sukses menambah kota (After): " << dk.nama << endl;
                            } else {
                                cout << ">>> Gagal: Nomor referensi tidak valid untuk insert after." << endl;
                            }

                        } else if (pilihanTampil == 3) {
                            insertLastKota(L, pKota);
                            cout << ">>> Sukses menambah kota (Last): " << dk.nama << endl;
                        }

                    } else {
                        cout << ">>> Gagal: Nama kota " << dk.nama << " sudah ada! Gunakan menu Ubah atau Tambah Riwayat." << endl;
                    }
                } else {
                    cout << ">>> Pilihan kategori insert tidak valid!" << endl;
                }
            } else if (pilihanSub == 2) {
                updateKota(L);
            } else if (pilihanSub == 3) {
                tampilkanListKota(L);
                cout << "Masukkan Nama Kota: "; cin >> inputNamaKota;
                deleteKota(L, inputNamaKota);
            } else {
                cout << "Kembali ke menu awal" << endl;
            }
            break;

        case 2:
            cout << "--- MENU KELOLA RIWAYAT SAMPAH ---" << endl;
            cout << "1. Tambah Riwayat" << endl;
            cout << "2. Ubah Riwayat" << endl;
            cout << "3. Hapus Riwayat" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
            tampilkanListKota(L);
            cout << "\n[INPUT RIWAYAT BARU]" << endl;
            cout << "Nama Kota Target (tanpa_spasi) : "; cin >> inputNamaKota;

            pKota = searchKota(L, inputNamaKota);
            
            if (pKota != nullptr) {
                cout << "Petugas (tanpa_spasi)                   : "; cin >> dr.petugas;
                cout << "Tanggal                                 : "; cin >> dr.tanggal;
                cout << "Bulan                                   : "; cin >> dr.bulan;
                cout << "Tahun                                   : "; cin >> dr.tahun;
                cout << "Jam (hh:mm)                             : "; cin >> dr.jamPengambilan;
                cout << "Jenis Sampah (Organik/Anorganik)        : "; cin >> dr.jenisSampah;
                cout << "Bobot (kg)                              : "; cin >> dr.bobot;
                
                adrRiwayat pRiwayat = createElemenRiwayat(dr);
                
                cout << "\n[PILIH POSISI INSERT RIWAYAT]" << endl;
                cout << "1. Insert First (Awal)" << endl;
                cout << "2. Insert After (Tengah)" << endl;
                cout << "3. Insert Last (Akhir)" << endl;
                cout << ">> Pilihan Posisi: ";
                cin >> pilihanTampil;
                
                if (pilihanTampil == 1) {
                    insertFirstRiwayat(pKota, pRiwayat);
                    cout << ">>> Sukses menambah riwayat (First)" << endl;
                } else if (pilihanTampil == 2) {
                    tampilkanRiwayatBernomor(pKota);
                    int nomor;
                    cout << "Masukkan nomor urut riwayat referensi: ";
                    cin >> nomor;
                    if (nomor >= 1 && nomor < countRiwayat(pKota)) {
                        insertAfterRiwayat(pKota, nomor, pRiwayat);
                        cout << ">>> Sukses menambah riwayat (After)" << endl;
                    } else {
                        cout << ">>> Gagal: Nomor referensi tidak valid." << endl;
                    }
                } else if (pilihanTampil == 3) {
                    insertLastRiwayat(pKota, pRiwayat);
                    cout << ">>> Sukses menambah riwayat (Last)" << endl;
                }
            } else {
                cout << ">>> Gagal: Kota " << inputNamaKota << " tidak ditemukan!" << endl;
            }
            } else if (pilihanSub == 2) {
                tampilkanListKota(L);
                cout << "\n[UBAH RIWAYAT]" << endl;
                cout << "Masukkan Nama Kota Target: ";
                cin >> inputNamaKota;

                pKota = searchKota(L, inputNamaKota);
                updateRiwayat(L, pKota);

            } else if (pilihanSub == 3) {
                tampilkanListKota(L);
                cout << "\n[HAPUS RIWAYAT]" << endl;
                cout << "Masukkan Nama Kota Target: ";
                cin >> inputNamaKota;
                pKota = searchKota(L, inputNamaKota);
                cout << countRiwayat(pKota);

                if (pKota != nullptr && !isEmptyRiwayat(pKota)) {
                    tampilkanRiwayatBernomor(pKota);
                    
                    int nomor;
                    cout << "Masukkan nomor urut riwayat yang ingin dihapus: ";
                    cin >> nomor;

                    if (nomor == 1) {
                        deleteFirstRiwayat(pKota, qTemp);
                        cout << ">>> Riwayat pertama berhasil dihapus." << endl;
                    } else if (nomor == countRiwayat(pKota)) {
                        deleteLastRiwayat(pKota, qTemp);
                        cout << ">>> Riwayat berhasil dihapus." << endl;
                    } else if (nomor > 1 && nomor < countRiwayat(pKota)){
                        adrRiwayat q;
                        deleteAfterRiwayat(pKota, nomor, q);
                        cout << ">>> Riwayat berhasil dihapus." << endl;
                    } else {
                        cout << "Nomor tidak valid." << endl;
                    }
                } else {
                    cout << ">>> Kota tidak ditemukan atau Riwayat kosong." << endl;
                }
            } else {
                cout << "Kembali ke menu awal" << endl;
            }
            break;

        case 3:
            cout << "--- MENU TAMPILAN DATA ---" << endl;
            cout << "1. Tampilkan Semua Data (Tabel)" << endl;
            cout << "2. Tampilkan Berdasarkan Kategori (Filter/Sort/Counting)" << endl;
            cout << "3. Tampilkan Kota Terbersih" << endl;
            cout << "4. Tampilkan Kota Terkotor" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "\n=== DATA KOTA DAN RIWAYAT ===" << endl;
                display(L);

            } else if (pilihanSub == 2) {
                cout << "\n[PILIH KATEGORI TAMPILAN]" << endl;
                cout << "1. Berdasarkan Tanggal (Terbaru - Terlama)" << endl;
                cout << "2. Berdasarkan Tanggal (Terlama - Terbaru)" << endl;
                cout << "3. Berdasarkan Bobot Sampah (Terendah - Tertinggi)" << endl;
                cout << "4. Berdasarkan Bobot Sampah (Tertinggi - Terendah)" << endl;
                cout << "5. Berdasarkan Jenis Sampah (Organik/Anorganik)" << endl;
                cout << "6. Total Sampah Setiap Kota" << endl;
                cout << ">> Pilihan Filter: ";
                cin >> pilihanTampil;

                if (pilihanTampil == 1) {
                    sortingTanggalTerbaru(L);
                    display(L);
                } else if (pilihanTampil == 2) {
                    sortingTanggalTerlama(L);
                    display(L);
                } else if (pilihanTampil == 3) {
                    sortingBobotTerendah(L);
                    display(L);
                } else if (pilihanTampil == 4) {
                    sortingBobotTertinggi(L);
                    display(L);
                } else if (pilihanTampil == 5) {
                    cout << "Masukkan Jenis Sampah: ";
                    string jenisCari;
                    cin >> jenisCari;
                    cout << endl;
                    searchJenisSampah(L, jenisCari);
                } else if (pilihanTampil == 6) {
                    jumlahSampahKota(L);
                }
            } else if (pilihanSub == 3) {
                cout << endl;
                indeksMax(L);
            } else if (pilihanSub == 4) {
                cout << endl;
                indeksMin(L);
            } else {
                cout << "Kembali ke menu awal" << endl;
            }
            break;
        case 4:
            cout << "--- MENU QUERY ---" << endl;
            cout << "1. Tampikan semua riwayat dari kota tertentu dalam urutan tanggal" << endl;
            cout << "2. Tampilkan semua riwayat dengan bobot tertentu di tanggal, bulan, tahun tertentu" << endl;
            cout << "3. Tampikan kota dengan indeks tertentu dan bobot serta jenis sampah tertentu" << endl;
            cout << "4. Tampilkan persentase sampah per orang" << endl;
            cout << "5. Tampilkan beban sampah per hektar di setiap kota" << endl;
            cout << "0. Kembali" << endl;
            cout << ">> Pilihan: ";
            cin >> pilihanSub;

            if (pilihanSub == 1) {
                cout << "--- PILIHAN URUTAN TANGGAL ---" << endl;
                cout << "1. Terbaru ke Terlama" << endl;
                cout << "2. Terlama ke Terbaru" << endl;
                cout << ">> Pilihan: ";
                cin >> pilihanTampil;

                if (pilihanTampil == 1) {
                    tampilkanListKota(L);
                    cout << "Masukkan Nama Kota Target: ";
                    cin >> inputNamaKota;
                    cout << endl;
                    queryKotaTanggalTerbaru(L, inputNamaKota);
                } else if (pilihanTampil == 2) {
                    tampilkanListKota(L);
                    cout << "Masukkan Nama Kota Target: ";
                    cin >> inputNamaKota;
                    cout << endl;
                    queryKotaTanggalTerlama(L, inputNamaKota);
                }
            } else if (pilihanSub == 2) {
                cout << "--- PILIHAN RANGE BOBOT ---" << endl;
                cout << "1. Diatas Bobot" << endl;
                cout << "2. Dibawah Bobot" << endl;
                cout << ">> Pilihan: ";
                cin >> pilihanTampil;

                if (pilihanTampil == 1) {
                    double bobot;
                    int tanggal, bulan, tahun;
                    cout << "Masukkan Bobot, Tanggal, Bulan, dan Tahun Target - Contoh (2.5 12 4 25): ";
                    cin >> bobot >> tanggal >> bulan >> tahun;
                    cout << endl;
                    queryDiatasBobotTanggal(L, bobot, tanggal, bulan, tahun);
                } else if (pilihanTampil == 2) {
                    double bobot;
                    int tanggal, bulan, tahun;
                    cout << "Masukkan Bobot, Tanggal, Bulan, dan Tahun Target - Contoh (2.5 12 4 25): ";
                    cin >> bobot >> tanggal >> bulan >> tahun;
                    cout << endl;
                    queryDibawahBobotTanggal(L, bobot, tanggal, bulan, tahun);
                } else {
                    cout << "Pilihan anda tidak valid." << endl;
                }
            } else if (pilihanSub == 3) {
                int pilihIndeks, pilihBobot, pilihJenis;
                int indeks;
                double bobot;
                string rangeIndeks, rangeBobot, jenis;

                cout << "--- PILIHAN RANGE INDEKS ---" << endl;
                cout << "1. Diatas Indeks" << endl;
                cout << "2. Dibawah Indeks" << endl;
                cout << ">> Pilihan: ";
                cin >> pilihIndeks;

                if (pilihIndeks == 1) {
                    rangeIndeks = "DIATAS";
                } else if (pilihIndeks == 2) {
                    rangeIndeks = "DIBAWAH";
                }

                cout << endl;

                cout << "--- PILIHAN RANGE BOBOT ---" << endl;
                cout << "1. Diatas Bobot" << endl;
                cout << "2. Dibawah Bobot" << endl;
                cout << ">> Pilihan: ";
                cin >> pilihBobot;

                if (pilihBobot == 1) {
                    rangeBobot = "DIATAS";
                } else if (pilihBobot == 2) {
                    rangeBobot = "DIBAWAH";
                }

                cout << endl;

                cout << "--- PILIHAN JENIS SAMPAH ---" << endl;
                cout << "1. Organik" << endl;
                cout << "2. Anorganik" << endl;
                cout << ">> Pilihan: ";
                cin >> pilihJenis;

                if (pilihJenis == 1) {
                    jenis = "Organik";
                } else {
                    jenis = "Anorganik";
                }

                cout << endl;

                cout << "Masukkan Nilai Indeks Target : ";
                cin >> indeks;

                cout << "Masukkan Nilai Bobot Target  : ";
                cin >> bobot;

                cout << endl;

                queryIndeksBobotJenis(L,indeks,rangeIndeks,bobot,rangeBobot,jenis);

            } else if (pilihanSub == 4) {
                int tgl, bln, thn;
                cout << "Masukkan Tanggal, Bulan, Tahun (contoh: 12 4 25): ";
                cin >> tgl >> bln >> thn;
                cout << endl;
                queryPersentaseSampahPerOrang(L, tgl, bln, thn);
                
            } else if (pilihanSub == 5) {
                int bulan, tahun;
                cout << "Masukkan Bulan dan Tahun (Contoh 5 25): ";
                cin >> bulan >> tahun;
                cout << endl;
                queryKepadatanSampah(L,bulan,tahun);
            } else {
                cout << "Kembali ke menu awal." << endl;
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