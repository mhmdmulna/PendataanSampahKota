#include <iostream>
#include "MLL.h"

using namespace std;

void createListKota(ListKota &L) {
    L.first = nullptr;
}

adrKota createElemenKota(dataKota data) {
    adrKota p = new kota;
    p->info = data;
    p->next = nullptr;
    p->firstRiawayat = nullptr;

    return p;
}

adrRiwayat createElemenRiwayat(dataRiwayat data) {
    adrRiwayat p = new riwayat;
    p->next = nullptr;
    p->info = data;
    return p;
}

bool isEmptyKota(ListKota L) {
    return L.first == nullptr;
}

bool isEmptyRiwayat(adrKota p) {
    return p->firstRiawayat == nullptr;
}

void insertKota(ListKota &L, adrKota p) {
    adrKota q = L.first;

    if (isEmptyKota(L)) {
        L.first = p;
    } else {
        while (q->next != nullptr) {
            q = q->next;
        }
        q->next = p;
    }
}

void insertRiwayat(adrKota &p, adrRiwayat q) {
    adrRiwayat r = p->firstRiawayat;

    if (isEmptyRiwayat(p)) {
        p->firstRiawayat = q;
    } else {
        while (r->next != nullptr) {
            r = r->next;
        }
        r->next = q;
    }
}

void deleteFirstRiwayat(adrKota p, adrRiwayat q) {
    p->firstRiawayat = q->next;
    q->next = nullptr;
}

void deleteLastRiwayat(adrKota p, adrRiwayat q) {
    adrRiwayat r = p->firstRiawayat;

    while (r->next != q) {
        r = r->next;
    }
    r->next = nullptr;
}

void deleteAfterRiwayat(adrKota p, adrRiwayat q) {
    adrRiwayat r = p->firstRiawayat;

    while (r->next != q) {
        r = r->next;
    }
    r->next = q->next;
    q->next = nullptr;
}

void display(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q;

    while (p != nullptr) {
        cout << p->info.nama << endl;
        q = p->firstRiawayat;
        while (q != nullptr) {
            cout << q->info.jenisSampah << ", ";
        }
        q = q->next;
        cout << endl;
    }
    p = p->next;
}

void updateRiwayat(adrRiwayat &p, dataRiwayat u) {
    p->info = u;
}

adrKota searchKota(ListKota L, string namaK) {
    adrKota p = L.first;

    while (p != nullptr) {
        if (p->info.nama == namaK) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}