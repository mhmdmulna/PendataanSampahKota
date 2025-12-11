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

void deleteKota(ListKota &L, string namaKota) {
    adrKota p = searchKota(L, namaKota);
    adrKota q = L.first;

    if (p == nullptr) {
        cout << "Kota Belum Ada";
    } else {
        if (p == L.first) {
            L.first->next = p->next;
            p->next = nullptr;
        } else {
            while (q->next != p) {
                q = q->next;
            }
            q->next = p->next;
            p->next = nullptr;
        }
    }
}

void deleteFirstRiwayat(adrKota p, adrRiwayat &q) {
    if (isEmptyRiwayat(p)) {
        q = nullptr;
    } else {
        q = p->firstRiwayat;
        p->firstRiwayat = q->next;
        q->next = nullptr;
    }
}

void deleteLastRiwayat(adrKota p, adrRiwayat &q) {
    if (isEmptyRiwayat(p)) {
        q = nullptr;
    } else if (p->firstRiwayat->next == nullptr) {
        deleteFirstRiwayat(p, q);
    } else {
        adrRiwayat r = p->firstRiwayat;
        while (r->next->next != nullptr) {
            r = r->next;
        }
        q = r->next;
        r->next = nullptr;
        q->next = nullptr;
    }
}

void deleteAfterRiwayat(adrKota p, adrRiwayat prec, adrRiwayat &q) {
    if (prec != nullptr && prec->next != nullptr) {
        q = prec->next;
        prec->next = q->next;
        q->next = nullptr;
    } else {
        q = nullptr;
    }
}

#include <cstdio> // Wajib untuk penggunaan printf

void display(ListKota L) {
    if (isEmptyKota(L)) {
        cout << "========================================" << endl;
        cout << "          DATA MASIH KOSONG             " << endl;
        cout << "========================================" << endl;
        return;
    }

    adrKota p = L.first;
    
    while (p != nullptr) {
        // --- BAGIAN HEADER KOTA (Tetap pakai cout tidak masalah) ---
        cout << "==================================================================================" << endl;
        printf(" KOTA: %-50s\n", p->info.nama.c_str()); // Pakai c_str() karena printf butuh char*
        cout << " Detail Info:" << endl;
        cout << "  > Luas Wilayah      : " << p->info.luasWilayah << " hektar" << endl;
        cout << "  > Jumlah Penduduk   : " << p->info.jumlahPenduduk << " jiwa" << endl;
        cout << "  > Indeks Kebersihan : " << p->info.indeksKebersihan << "/10" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;

        // --- BAGIAN TABEL RIWAYAT (Menggunakan printf agar rapi) ---
        adrRiwayat q = p->firstRiwayat;
        
        if (q == nullptr) {
            cout << "       (Belum ada riwayat pengangkutan sampah di kota ini)" << endl;
        } else {
            // 1. Header Tabel
            // %-Ns = Rata Kiri sebanyak N karakter
            // %-Nd = Angka Rata Kiri
            printf(" | %-3s | %-12s | %-5s | %-15s | %-15s | %-9s |\n", 
                   "No", "Tanggal", "Jam", "Petugas", "Jenis Sampah", "Bobot");
            
            // 2. Garis Pembatas (Disesuaikan dengan lebar di atas)
            printf(" |-----|--------------|-------|-----------------|-----------------|-----------|\n");
            
            int i = 1;
            while (q != nullptr) {
                // 3. Isi Data
                // Kita gabungkan tanggal-bulan-tahun langsung di format string
                // .c_str() WAJIB digunakan jika variabel di struct bertipe std::string
                printf(" | %-3d | %2d-%2d-%-4d | %-5s | %-15s | %-15s | %6.1f kg |\n", i, q->info.tanggal, q->info.bulan, q->info.tahun, q->info.jamPengambilan, q->info.petugas, q->info.jenisSampah, q->info.bobot);

                q = q->next;
                i++;
            }
        }
        cout << "==================================================================================" << endl;
        cout << endl << endl; 
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
    bool found = false;

    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            if (q->info.jenisSampah == jenisSampah) {
                cout << "Kota : "<< p->info.nama << endl;
                cout << "Tanggal Pengangkutan: " << q->info.tanggal << endl;
                cout << "Jumlah Bobot: " << q->info.bobot << " kg" << endl;
                cout << "Jenis Sampah: " << q->info.jenisSampah << endl;
                found = true;
            }
        cout << endl;
        q = q->next;
        }
    p = p->next;
    }
    if (!found) {
        cout << "Tidak ada sampah jenis " << jenisSampah << " ditemukan." << endl;
    }
}

void updateRiwayat(adrRiwayat &p, dataRiwayat u) {
    if (p != nullptr) {
        p->info = u;
    }
}

void updateKota(ListKota &L, string namak) {
    adrKota p = searchKota(L, namak);

    if (p == nullptr) {
        cout << "Data Kota Belum ada" << endl;
    } else {
        cout << "Update Luas Wilayah (Hektar): ";
        cin >> p->info.luasWilayah;
        cout << "Update Jumlah Penduduk: ";
        cin >> p->info.jumlahPenduduk;
        cout << "Update Indeks Kebersihan (1 - 10): ";
        cin >> p->info.indeksKebersihan;
        cout << "Update Berhasil." << endl;
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

// void sortingTanggal(ListKota L) {
//     adrKota p = L.first;
//     adrRiwayat q, r;

//     while (p != nullptr) {
//         r = p->firstRiwayat;
//         q = p->firstRiwayat->next;
//         while (q != nullptr) {
//             if (q->info.tahun)
//         }
//     }
// }