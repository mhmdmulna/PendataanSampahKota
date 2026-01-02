#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct kota *adrKota;
typedef struct riwayat *adrRiwayat;

struct dataKota {
    string nama;
    double luasWilayah;
    int jumlahPenduduk;
    int indeksKebersihan;
};

struct dataRiwayat {
    double bobot;
    string petugas;
    string jenisSampah;
    string jamPengambilan;
    int tanggal;
    int bulan;
    int tahun;
};

struct kota {
    dataKota info;
    adrKota next;
    adrRiwayat firstRiwayat;
};

struct riwayat {
    dataRiwayat info;
    adrRiwayat next;
};

struct ListKota {
    adrKota first;
};
// CREATE & CHECK
void createListKota(ListKota &L);
adrKota createElemenKota(dataKota data);
adrRiwayat createElemenRiwayat(dataRiwayat data);
bool isEmptyKota(ListKota L);
bool isEmptyRiwayat(adrKota p);

// INSERT
void insertFirstKota(ListKota &L, adrKota p);
void insertAfterKota(ListKota &L, int no, adrKota p);
void insertLastKota(ListKota &L, adrKota p);
void insertFirstRiwayat(adrKota &p, adrRiwayat q);
void insertAfterRiwayat(adrKota &p, int no, adrRiwayat q);
void insertLastRiwayat(adrKota &p, adrRiwayat q);

// DELETE
void deleteFirstRiwayat(adrKota p, adrRiwayat &q);
void deleteLastRiwayat(adrKota p, adrRiwayat &q);
void deleteAfterRiwayat(adrKota p, int no, adrRiwayat &q);
void deleteKota(ListKota &L, string namaKota);

// SEARCH & UPDATE
void updateRiwayat(ListKota &L, adrKota pKota);
void updateKota(ListKota &L);
adrKota searchKota(ListKota L, string namaK);
void searchJenisSampah(ListKota L, string jenisSampah);
adrRiwayat getRiwayatByIndex(adrKota pKota, int index);

// DISPLAY & FEATURE
void display(ListKota L);
void indeksMin(ListKota L);
void indeksMax(ListKota L);
int countRiwayat(adrKota Kota);
int countKota(ListKota L);
void jumlahSampahKota(ListKota L);
void tampilkanRiwayatBernomor(adrKota pKota);
void tampilkanListKota(ListKota L);

// SORTING
void sortingTanggalTerlama(ListKota L);
void sortingTanggalTerbaru(ListKota L);
void sortingBobotTerendah(ListKota L);
void sortingBobotTertinggi(ListKota L);

// QUERY
void queryKotaTanggalTerbaru(ListKota L, string namaKota);
void queryKotaTanggalTerlama(ListKota L, string namaKota);
void queryDiatasBobotTanggal(ListKota L, double bobot, int tanggal, int bulan, int tahun);
void queryDibawahBobotTanggal(ListKota L, double bobot, int tanggal, int bulan, int tahun);
void queryIndeksBobotJenis(ListKota L, int indeks, string rangeIndeks, double bobot, string rangeBobot,string jenis);
void queryPersentaseSampahPerOrang(ListKota L, int tanggal, int bulan, int tahun);
void queryKepadatanSampah(ListKota L, int bulan, int tahun);

#endif // MLL_H_INCLUDED