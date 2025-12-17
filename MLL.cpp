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

void deleteAfterRiwayat(adrKota Kota, int no, adrRiwayat &q) {
    int i = 1;
    adrRiwayat p = Kota->firstRiwayat;

    while (i < no - 1) {
        p = p->next;
        i++;
    }
    q = p->next;
    p->next = q->next;
    q->next = nullptr;
}

int countRiwayat(adrKota Kota) {
    adrRiwayat p = Kota->firstRiwayat;
    int i = 0;

    while (p != nullptr) {
        i++;
        p = p->next;
    }
    return i;
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

void updateRiwayat(ListKota &L, adrKota pKota) {
    if (pKota != nullptr && !isEmptyRiwayat(pKota)) {

        tampilkanRiwayatBernomor(pKota);

        int nomor;
        cout << "\nPilih nomor riwayat yang ingin diubah: ";
        cin >> nomor;

        adrRiwayat target = getRiwayatByIndex(pKota, nomor);

        if (target == nullptr) {
            cout << ">>> Nomor riwayat tidak valid!" << endl;
        } else {
            cout << "\n[UPDATE DATA RIWAYAT]" << endl;
            cout << "Petugas baru          : "; cin >> target->info.petugas;
            cout << "Tanggal baru          : "; cin >> target->info.tanggal;
            cout << "Bulan baru            : "; cin >> target->info.bulan;
            cout << "Tahun baru            : "; cin >> target->info.tahun;
            cout << "Jam baru (hh:mm)      : "; cin >> target->info.jamPengambilan;
            cout << "Jenis Sampah baru     : "; cin >> target->info.jenisSampah;
            cout << "Bobot baru (kg)       : "; cin >> target->info.bobot;

            cout << ">>> Riwayat nomor " << nomor << " berhasil diperbarui!" << endl;
        }
    } else {
        cout << ">>> Kota tidak ditemukan atau riwayat kosong!" << endl;
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
        cout << "Kota tidak ditemukan." << endl;
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
    cout << "Kota Terkotor " << x->info.nama << " Dengan Indeks Kebersihan " << x->info.indeksKebersihan << endl;
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
    cout << "Kota Terbersih " << x->info.nama << " Dengan Indeks Kebersihan " << x->info.indeksKebersihan << endl;
}

void jumlahSampahKota(ListKota L) {
    adrKota p = L.first;
    adrRiwayat q;
    double jumlahsampah = 0;

    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            jumlahsampah += q->info.bobot; 
            q = q->next;
        }
        cout << "Kota        : " << p->info.nama << endl;
        cout << "Total Sampah: " << jumlahsampah << " kg" << endl << endl;
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
        if (i == index){
            return q;
        }
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

void queryKotaTanggalTerbaru(ListKota L, string namaKota) {
    adrKota searchK = searchKota(L, namaKota);
    adrRiwayat q, r;

    q = searchK->firstRiwayat;
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
    q = searchK->firstRiwayat;

    cout << "---  HASIL QUERY  ---" << endl;
    cout << "Nama Kota: " << namaKota << endl;
    cout << "==================================================================================" << endl;
    printf(" | %-3s | %-12s | %-5s | %-15s | %-15s | %-9s |\n", "No", "Tanggal", "Jam", "Petugas", "Jenis Sampah", "Bobot");       
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
    cout << "==================================================================================" << endl;
    cout << endl;
}

void queryKotaTanggalTerlama(ListKota L, string namaKota) {
    adrKota searchK = searchKota(L, namaKota);
    adrRiwayat q, r;

    q = searchK->firstRiwayat;
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
    q = searchK->firstRiwayat;

    cout << "---  HASIL QUERY  ---" << endl;
    cout << "Nama Kota: " << namaKota << endl;
    cout << "==================================================================================" << endl;
    printf(" | %-3s | %-12s | %-5s | %-15s | %-15s | %-9s |\n", "No", "Tanggal", "Jam", "Petugas", "Jenis Sampah", "Bobot");       
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
    cout << "==================================================================================" << endl;
    cout << endl;
}

void queryDiatasBobotTanggal(ListKota L, double bobot, int tanggal, int bulan, int tahun) {
    adrKota p = L.first;
    adrRiwayat q;
    int i = 1;
    
    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            if (q->info.tanggal == tanggal && q->info.bulan == bulan && q->info.tahun == tahun && q->info.bobot >= bobot) {
                cout << "---  HASIL QUERY  ---" << endl;
                cout << "Nama Kota: " << p->info.nama << endl;
                cout << "==================================================================================" << endl;
                printf(" | %-3s | %-12s | %-5s | %-15s | %-15s | %-9s |\n", "No", "Tanggal", "Jam", "Petugas", "Jenis Sampah", "Bobot");       
                printf(" |-----|--------------|-------|-----------------|-----------------|-----------|\n");
                
                char tanggalStr[15];
                sprintf(tanggalStr, "%02d-%02d-%02d", q->info.tanggal, q->info.bulan, q->info.tahun);

                printf(" | %-3d | %-12s | %-5s | %-15s | %-15s | %6.1f kg |\n",
                i, tanggalStr, q->info.jamPengambilan.c_str(), q->info.petugas.c_str(), q->info.jenisSampah.c_str(), q->info.bobot);

                i++;
                cout << "==================================================================================" << endl;
                cout << endl;
            } else {
                cout << "Input anda tidak sesuai dengan format." << endl;
            }
            q = q->next;
        }
        p = p->next;
    }
}

void queryDibawahBobotTanggal(ListKota L, double bobot, int tanggal, int bulan, int tahun) {
    adrKota p = L.first;
    adrRiwayat q;
    int i = 1;
    
    while (p != nullptr) {
        q = p->firstRiwayat;
        while (q != nullptr) {
            if (q->info.tanggal == tanggal && q->info.bulan == bulan && q->info.tahun == tahun && q->info.bobot <= bobot) {
                cout << "---  HASIL QUERY  ---" << endl;
                cout << "Nama Kota: " << p->info.nama << endl;
                cout << "==================================================================================" << endl;
                printf(" | %-3s | %-12s | %-5s | %-15s | %-15s | %-9s |\n", "No", "Tanggal", "Jam", "Petugas", "Jenis Sampah", "Bobot");       
                printf(" |-----|--------------|-------|-----------------|-----------------|-----------|\n");
                

                char tanggalStr[15];
                sprintf(tanggalStr, "%02d-%02d-%02d", q->info.tanggal, q->info.bulan, q->info.tahun);

                printf(" | %-3d | %-12s | %-5s | %-15s | %-15s | %6.1f kg |\n",
                i, tanggalStr, q->info.jamPengambilan.c_str(), q->info.petugas.c_str(), q->info.jenisSampah.c_str(), q->info.bobot);

                i++;
                cout << "==================================================================================" << endl;
                cout << endl;
            } else {
                cout << "Input anda tidak sesuai dengan format." << endl;
            }
            q = q->next;
        }
        p = p->next;
    }
}

void queryIndeksBobotJenis(ListKota L, int indeksTarget, string rangeIndeks, double bobotTarget, string rangeBobot, string jenisSampah) {
    adrKota p = L.first;
    bool adaHasil = false;

    cout << "\n=== HASIL QUERY INDEKS - BOBOT - JENIS ===\n";

    while (p != nullptr) {

        bool indeksOK;

        if (rangeIndeks == "DIATAS") {
            indeksOK = p->info.indeksKebersihan > indeksTarget;
        } else if (rangeIndeks == "DIBAWAH") {
            indeksOK = p->info.indeksKebersihan < indeksTarget;
        }

        if (indeksOK) {
            adrRiwayat q = p->firstRiwayat;

            while (q != nullptr) {

                bool bobotOK;
                if (rangeBobot == "DIATAS") {
                    bobotOK = q->info.bobot > bobotTarget;
                } else if (rangeBobot == "DIBAWAH") {
                    bobotOK = q->info.bobot < bobotTarget;
                }

                bool jenisOK = (q->info.jenisSampah == jenisSampah);

                if (bobotOK && jenisOK) {

                    if (!adaHasil) {
                        printf("==================================================================================\n");
                        printf(" | %-15s | %-6s | %-12s | %-10s | %-10s |\n",
                               "Kota", "Indeks", "Tanggal", "Bobot", "Jenis");
                        printf("----------------------------------------------------------------------------------\n");
                    }

                    char tanggalStr[15];
                    sprintf(tanggalStr, "%02d-%02d-%02d", q->info.tanggal, q->info.bulan, q->info.tahun);

                    printf(" | %-15s | %-6d | %-12s | %6.1f kg | %-10s |\n", p->info.nama.c_str(), p->info.indeksKebersihan, tanggalStr, q->info.bobot, q->info.jenisSampah.c_str());

                    adaHasil = true;
                }
                q = q->next;
            }
        }
        p = p->next;
    }

    if (adaHasil) {
        printf("==================================================================================\n");
    } else {
        cout << ">>> Tidak ada data yang memenuhi kriteria.\n";
    }
}

void queryPersentaseSampahPerOrang(ListKota L, int tanggal, int bulan, int tahun) {
    adrKota p = L.first;
    adrRiwayat q;
    bool adaHasil = false;

    cout << "\n=== PERSENTASE SAMPAH PER ORANG PER HARI ===\n";
    cout << "Tanggal: " << tanggal << "-" << bulan << "-" << tahun << endl;
    cout << "=================================================================================\n";
    printf(" | %-15s | %-12s | %-10s | %-15s | %-12s |\n",
           "Kota", "Total Sampah", "Penduduk", "Kg/Orang", "Persentase");
    cout << "---------------------------------------------------------------------------------\n";
    
    while (p != nullptr) {
        q = p->firstRiwayat;
        double totalSampah = 0;
        while (q != nullptr) {
            if (q->info.tanggal == tanggal && q->info.bulan == bulan && q->info.tahun == tahun) {
                totalSampah += q->info.bobot;
            }
            q = q->next;
        }
        if (totalSampah > 0 && p->info.jumlahPenduduk > 0) {
            double kgPerOrang = totalSampah / p->info.jumlahPenduduk;
            double persentasiPerPenduduk = kgPerOrang * 100;
 
            printf(" | %-15s | %-9.2f kg | %-10d | %-15f | %-10f %% |\n", p->info.nama.c_str(), totalSampah, p->info.jumlahPenduduk, kgPerOrang, persentasiPerPenduduk);

            adaHasil = true;
        }
        p = p->next;
    }

    if (adaHasil) {
        cout << "=================================================================================\n";
    } else {
        cout << "Tidak ada data yang memenuhi kriteria." << endl;
    }
}

void queryKepadatanSampah(ListKota L, int bulan, int tahun){
    adrKota p = L.first;
    adrRiwayat q;
    double total;
    bool adaHasil = false;

    cout << "\n=== ANALISIS KEPADATAN SAMPAH PER HEKTAR ===\n";
    cout << "Periode: Bulan " << bulan << " Tahun " << tahun << endl;
    //cout << "Rumus  : Total Sampah (kg) / Luas Wilayah (Ha)" << endl;
    
    printf("============================================================================\n");
    printf(" | %-15s | %-12s | %-12s | %-22s |\n", "Nama Kota", "Total Sampah", "Luas Wilayah", "Kepadatan (kg/Ha)");
    printf("----------------------------------------------------------------------------\n");

    while (p != nullptr) {
        q = p->firstRiwayat;
        total = 0;
        while (q != nullptr) {
            if (q->info.bulan == bulan && q->info.tahun == tahun) {
                total = total + q->info.bobot;
            }
            q = q->next;
        }

        printf(" | %-15s | %-9.1f kg | %-9.1f Ha | %-16.2f kg/Ha |\n", p->info.nama.c_str(), total, p->info.luasWilayah, total/p->info.luasWilayah);

        adaHasil = true;

        p = p->next;        
    }

    if (adaHasil) {
        printf("============================================================================\n");
    } else {
        cout << "Tidak ada data yang memenuhi kriteria bulan dan tahun." << endl;
    }
}