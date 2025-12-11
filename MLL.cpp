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
        cout << "Data Kota Tidak Ditemukan!";
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
        cout << "Penghapusan kota " << p->info.nama << " berhasil dilakukan." << endl;
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

void display(ListKota L) {
    if (isEmptyKota(L)) {
        cout << "========================================" << endl;
        cout << "          DATA MASIH KOSONG             " << endl;
        cout << "========================================" << endl;
        return;
    }

    adrKota p = L.first;
    
    while (p != nullptr) {
        cout << "==================================================================================" << endl;
        printf(" KOTA: %-50s\n", p->info.nama.c_str());
        cout << " Detail Info:" << endl;
        cout << "  > Luas Wilayah      : " << p->info.luasWilayah << " hektar" << endl;
        cout << "  > Jumlah Penduduk   : " << p->info.jumlahPenduduk << " jiwa" << endl;
        cout << "  > Indeks Kebersihan : " << p->info.indeksKebersihan << "/10" << endl;
        cout << "----------------------------------------------------------------------------------" << endl;

        adrRiwayat q = p->firstRiwayat;
        
        if (q == nullptr) {
            cout << "(Belum ada riwayat pengangkutan sampah di kota ini)" << endl;
        } else {
            printf(" | %-3s | %-12s | %-5s | %-15s | %-15s | %-9s |\n", 
                   "No", "Tanggal", "Jam", "Petugas", "Jenis Sampah", "Bobot");
            
            printf(" |-----|--------------|-------|-----------------|-----------------|-----------|\n");
            
            int i = 1;
            while (q != nullptr) {
                char tanggalStr[15];
                sprintf(tanggalStr, "%02d-%02d-%02d", q->info.tanggal, q->info.bulan, q->info.tahun);

                printf(" | %-3d | %-12s | %-5s | %-15s | %-15s | %6.1f kg |\n",
                i, tanggalStr, q->info.jamPengambilan.c_str(), q->info.petugas.c_str(), q->info.jenisSampah.c_str(), q->info.bobot);

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

    cout << "=== HASIL PENCARIAN JENIS SAMPAH: " << jenisSampah << " ===\n";

    while (p != nullptr) {
        q = p->firstRiwayat;

        while (q != nullptr) {
            if (q->info.jenisSampah == jenisSampah) {

                cout << "----------------------------------------\n";
                cout << "Kota                : " << p->info.nama << "\n";
                cout << "Tanggal Pengambilan : " << q->info.tanggal << "-" << q->info.bulan << "-"<< q->info.tahun << "\n";
                cout << "Jam Pengambilan     : " << q->info.jamPengambilan << "\n";
                cout << "Petugas             : " << q->info.petugas << "\n";
                cout << "Jenis Sampah        : " << q->info.jenisSampah << "\n";
                cout << "Bobot               : " << q->info.bobot << " kg\n";
                cout << "----------------------------------------\n\n";

                found = true;
            }
            q = q->next;
        }
        p = p->next;
    }

    if (!found) {
        cout << "Tidak ada data dengan jenis sampah \"" << jenisSampah << "\" ditemukan.\n";
    }
}

void updateRiwayat(adrRiwayat &p, dataRiwayat u) {
    if (p != nullptr) {
        p->info = u;
    }
}

void updateKota(ListKota &L) {
    tampilkanListKota(L);    

    string inputNamaKota;
    cout << "Masukkan nama kota yang ingin diubah: ";
    cin >> inputNamaKota;
    
    adrKota p = searchKota(L, inputNamaKota);
    if (p != nullptr) {
        cout << "\nMasukkan data baru:\n";
        cout << "Nama Kota Baru        : ";
        cin >> p->info.nama;
        cout << "Luas Wilayah Baru     : ";
        cin >> p->info.luasWilayah;
        cout << "Jumlah Penduduk Baru  : ";
        cin >> p->info.jumlahPenduduk;
        cout << "Indeks Kebersihan Baru: ";
        cin >> p->info.indeksKebersihan;
        cout << "\n>>> Data kota berhasil diperbarui!\n";
    } else {
        cout << "Kota tidak ditemukan!." << endl;
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

void sortingTanggalTerlama(ListKota L) {

    adrKota p = L.first;
    adrRiwayat q, r;

    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            r = q->next;
            while (r != nullptr) {

                bool shouldSwap = false;
                if (q->info.tahun > r->info.tahun) {
                    shouldSwap = true;
                }
                else if (q->info.tahun == r->info.tahun && q->info.bulan > r->info.bulan) {
                    shouldSwap = true;
                }
                else if (q->info.tahun == r->info.tahun && q->info.bulan == r->info.bulan && q->info.tanggal > r->info.tanggal) {
                    shouldSwap = true;
                }
                else if (q->info.tanggal == r->info.tanggal && q->info.jamPengambilan > r->info.jamPengambilan) {
                    shouldSwap = true;
                }
                if (shouldSwap) {
                    dataRiwayat temp = q->info;
                    q->info = r->info;
                    r->info = temp;
                }
                r = r->next;
            }
            q = q->next;
        }
        p = p->next;
    }
    display(L);
}

void sortingTanggalTerbaru(ListKota L) {
    
    adrKota p = L.first;
    adrRiwayat q, r;

    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            r = q->next;
            while (r != nullptr) {

                bool shouldSwap = false;
                if (q->info.tahun < r->info.tahun) {
                    shouldSwap = true;
                }
                else if (q->info.tahun == r->info.tahun && q->info.bulan < r->info.bulan) {
                    shouldSwap = true;
                }
                else if (q->info.tahun == r->info.tahun && q->info.bulan == r->info.bulan && q->info.tanggal < r->info.tanggal) {
                    shouldSwap = true;
                }
                else if (q->info.tanggal == r->info.tanggal && q->info.jamPengambilan < r->info.jamPengambilan) {
                    shouldSwap = true;
                }
                if (shouldSwap) {
                    dataRiwayat temp = q->info;
                    q->info = r->info;
                    r->info = temp;
                }
                r = r->next;
            }
            q = q->next;
        }
        p = p->next;
    }
    display(L);
}

void sortingBobotTerendah(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q, r;

    while (p != nullptr) {
        q = p->firstRiwayat;

        while (q != nullptr) {
            r = q->next;

            while (r != nullptr) {

                if (q->info.bobot > r->info.bobot) {
                    dataRiwayat temp = q->info;
                    q->info = r->info;
                    r->info = temp;
                }
                r = r->next;
            }
            q = q->next;
        }
        p = p->next;
    }
    display(L);
}

void sortingBobotTertinggi(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q, r;

    while (p != nullptr) {
        q = p->firstRiwayat;

        while (q != nullptr) {
            r = q->next;

            while (r != nullptr) {

                if (q->info.bobot < r->info.bobot) {
                    dataRiwayat temp = q->info;
                    q->info = r->info;
                    r->info = temp;
                }
                r = r->next;
            }
            q = q->next;
        }
        p = p->next;
    }
    display(L);
}

void tampilkanRiwayatBernomor(adrKota pKota) {
    if (isEmptyRiwayat(pKota)) {
        cout << ">>> Riwayat kosong.\n";
        return;
    }

    adrRiwayat q = pKota->firstRiwayat;
    int i = 1;

    cout << "\n=== DAFTAR RIWAYAT DI KOTA " << pKota->info.nama << " ===\n\n";

    while (q != nullptr) {
        cout << i << ")\n";
        cout << "  Tanggal       : " << q->info.tanggal << "/" << q->info.bulan   << "/" << q->info.tahun   << endl;
        cout << "  Bobot         : " << q->info.bobot << " kg" << endl;
        cout << "  Petugas       : " << q->info.petugas << endl;
        cout << "  Jenis Sampah  : " << q->info.jenisSampah << endl;
        cout << "  Jam           : " << q->info.jamPengambilan << endl;
        cout << "--------------------------------------------------\n";

        q = q->next;
        i++;
    }
}

adrRiwayat getRiwayatByIndex(adrKota pKota, int index) {
    adrRiwayat q = pKota->firstRiwayat;
    int i = 1;

    while (q != nullptr) {
        if (i == index) return q;
        q = q->next;
        i++;
    }
    return nullptr;
}

void tampilkanListKota(ListKota L) {
    if (isEmptyKota(L)) {
        cout << ">>> Tidak ada data kota.\n";
        return;
    }

    adrKota p = L.first;
    int i = 1;

    cout << "\n=== DAFTAR KOTA ===\n\n";

    while (p != nullptr) {
        cout << i << ")\n";
        cout << "  Nama Kota        : " << p->info.nama << endl;
        cout << "  Luas Wilayah     : " << p->info.luasWilayah << " km2" << endl;
        cout << "  Jumlah Penduduk  : " << p->info.jumlahPenduduk << endl;
        cout << "  Indeks Kebersihan: " << p->info.indeksKebersihan << endl;
        cout << "--------------------------------------------------\n";

        p = p->next;
        i++;
    }
}
