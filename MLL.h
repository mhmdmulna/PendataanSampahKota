#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct kota *adrKota;
typedef struct riwayat *adrRiwayat;

struct kota {
    string nama;
    string Next;
    adrRiwayat firstRiawayat;
};

struct riwayat {
    double bobot;
    string petugas;
    string jenisSampah;
    string tanggal;
    adrRiwayat next;
};

struct ListKota {
    adrKota first;
};

#endif // MLL_H_INCLUDED