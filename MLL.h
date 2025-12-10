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

struct kota {
    dataKota info;
    adrKota next;
    adrRiwayat firstRiawayat;
};

struct riwayat {
    double bobot;
    string petugas;
    string jenisSampah;
    char tanggal;
    char jamPengambilan;
    adrRiwayat next;
};

struct ListKota {
    adrKota first;
};

void createListKota(ListKota &L);
adrKota createElemenKota(string namaKota);
adrRiwayat createElemenRiwayat(riwayat data);
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

#endif // MLL_H_INCLUDED