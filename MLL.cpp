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
    p->firstRiwayat = nullptr;

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
    return p->firstRiwayat == nullptr;
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
    adrRiwayat r = p->firstRiwayat;

    if (isEmptyRiwayat(p)) {
        p->firstRiwayat = q;
    } else {
        while (r->next != nullptr) {
            r = r->next;
        }
        r->next = q;
    }
}

void deleteFirstRiwayat(adrKota p, adrRiwayat q) {
    p->firstRiwayat = q->next;
    q->next = nullptr;
}

void deleteLastRiwayat(adrKota p, adrRiwayat q) {
    adrRiwayat r = p->firstRiwayat;

    while (r->next != q) {
        r = r->next;
    }
    r->next = nullptr;
}

void deleteAfterRiwayat(adrKota p, adrRiwayat q) {
    adrRiwayat r = p->firstRiwayat;

    while (r->next != q) {
        r = r->next;
    }
    r->next = q->next;
    q->next = nullptr;
}

void display(ListKota L) {
    if (isEmptyKota(L)) {
        cout << "========================================" << endl;
        cout << "          DATA MASIH KOSONG             " << endl;
        cout << "========================================" << endl;
        return;
    }

    adrKota p = L.first;
    
    while (p != nullptr) {
        // --- BAGIAN HEADER KOTA ---
        cout << "================================================================================" << endl;
        cout << " KOTA: " << p->info.nama << endl;
        cout << " Detail Info:" << endl;
        cout << "  > Luas Wilayah      : " << p->info.luasWilayah << " hektar" << endl;
        cout << "  > Jumlah Penduduk   : " << p->info.jumlahPenduduk << " jiwa" << endl;
        cout << "  > Indeks Kebersihan : " << p->info.indeksKebersihan << "/10" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;

        // --- BAGIAN TABEL RIWAYAT ---
        adrRiwayat q = p->firstRiwayat;
        
        if (q == nullptr) {
            cout << "(Belum ada riwayat pengangkutan sampah di kota ini)" << endl;
        } else {
            // Header Tabel
            cout << " | No |  Tanggal   |  Jam  |   Petugas   |   Jenis Sampah   |   Bobot   |" << endl;
            cout << " |----|------------|-------|-------------|------------------|-----------|" << endl;
            
            int i = 1;
            while (q != nullptr) {
                // Tampilan Baris Tabel (Manual Formatting)
                cout << " | " << i << (i < 10 ? "  " : " ") << "| " 
                     << q->info.tanggal << " | " 
                     << q->info.jamPengambilan << " | " 
                     << q->info.petugas << "\t | " 
                     << q->info.jenisSampah << "\t    | " 
                     << q->info.bobot << " kg" << endl;
                     
                q = q->next;
                i++;
            }
        }
        cout << "================================================================================" << endl;
        cout << endl << endl; // Spasi antar kota
        p = p->next;
    }
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

void searchJenisSampah(ListKota L, string jenisSampah) {
    adrRiwayat q;
    adrKota p = L.first;

    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            if (q->info.jenisSampah == jenisSampah) {
                cout << p->info.nama << endl;
                cout << "Tanggal Pengangkutan: " << q->info.tanggal << endl;
                cout << "Jumlah Bobot: " << q->info.bobot << " (kg)" << endl;
                cout << "Jenis Sampah: " << q->info.jenisSampah << endl;
            }
        cout << endl;
        q = q->next;
        }
    p = p->next;
    }
}

void updateRiwayat(adrRiwayat &p, dataRiwayat u) {
    p->info = u;
}

void updateKota(ListKota &L, string namak) {
    adrKota p = searchKota(L, namak);
    dataKota dk;

    if (p == nullptr) {
        cout << "Data Kota Belum ada" << endl;
    } else {
        cout << "Update Luas Wilayah (Hektar): ";
        cin >> dk.luasWilayah;
        cout << "Update Jumlah Penduduk: ";
        cin >> dk.jumlahPenduduk;
        cout << "Update Indeks Kebersihan (1 - 10): ";
        cin >> dk.indeksKebersihan;
        cout << endl;
    }
}

void indeksMin(ListKota L) {
    adrKota p = L.first;
    adrKota x = L.first;

    while (p != nullptr) {
        if (p->info.indeksKebersihan < x->info.indeksKebersihan) {
            x = p;
        }
        p = p->next;
    }
    cout << "Nama Kota Terkotor " << x->info.nama << " Dengan Indeks Kebersihan " << x->info.indeksKebersihan << endl;
}

void indeksMax(ListKota L) {
    adrKota p = L.first;
    adrKota x = L.first;

    while (p != nullptr) {
        if (p->info.indeksKebersihan > x->info.indeksKebersihan) {
            x = p;
        }
        p = p->next;
    }
    cout << "Nama Kota Terbersih " << x->info.nama << " Dengan Indeks Kebersihan " << x->info.indeksKebersihan << endl;
}

void bobotMin(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q, r;

    while (p != nullptr) {
        q = p->firstRiwayat;
        r = p->firstRiwayat;
        while (q != nullptr) {
            if (q->info.bobot < r->info.bobot) {
                r = q;
            }
            q = q->next;
        }
        cout << "Kota: " << p->info.nama << endl;
        cout << "Tanggal Pengangkutan: " << r->info.tanggal << endl;
        cout << "Bobot Pengangkutan: " << r->info.bobot << endl;
        cout << endl;
        p = p->next;
    }
}

void bobotMax(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q, r;

    while (p != nullptr) {
        q = p->firstRiwayat;
        r = p->firstRiwayat;
        while (q != nullptr) {
            if (q->info.bobot > r->info.bobot) {
                r = q;
            }
            q = q->next;
        }
        cout << "Kota: " << p->info.nama << endl;
        cout << "Tanggal Pengangkutan: " << r->info.tanggal << endl;
        cout << "Bobot Pengangkutan: " << r->info.bobot << endl;
        cout << endl;
        p = p->next;
    }
}

void jumlahSampahKota(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q;
    int jumlahsampah = 0;

    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            jumlahsampah += q->info.bobot; 
            q = q->next;
        }
        cout << "Kota: " << p->info.nama << endl;
        cout << "Total Sampah: " << jumlahsampah << endl;
        p = p->next;
    }
}