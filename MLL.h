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
    string tanggal;
    string jamPengambilan;
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

void createListKota(ListKota &L);
adrKota createElemenKota(dataKota data);
adrRiwayat createElemenRiwayat(dataRiwayat data);
bool isEmptyKota(ListKota L);
bool isEmptyRiwayat(adrKota p);
void insertKota(ListKota &L, adrKota p);
void insertRiwayat(adrKota &p, adrRiwayat q);
void deleteFirstRiwayat(adrKota p, adrRiwayat q);
void deleteLastRiwayat(adrKota p, adrRiwayat q);
void deleteAfterRiwayat(adrKota p, adrRiwayat q);
void display(ListKota L);
void updateRiwayat(adrRiwayat p, riwayat u);
adrKota searchKota(ListKota L, string namaK);
void indeksMin(ListKota L);
void indeksMax(ListKota L);
void bobotMin(ListKota L);
void bobotMax(ListKota L);
void jumlahSampahKota(ListKota L);

#endif // MLL_H_INCLUDED