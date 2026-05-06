#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
using namespace std;

struct Barang
{
    int id_barang;
    char nama[1000];
    float harga;
    int stok;
};

struct DataBarang 
{
    Barang Data;
    DataBarang *next;
};

DataBarang *head = nullptr;

void menuUtama();
void transaksiPelanggan();
void kelolaData();

void sorting();
void tampilData();
void cariBarang();
void tambahData();
void hapusData();
void updateBarang();

void saveFile(char nama[], float harga, int stok)
{
    FILE *file = fopen("swalayan.txt", "a");
    if (file == NULL)
    {
        cout << "Gagal buka file!\n";
        return;
    }

    fprintf(file, "%s;%.2f;%d\n", nama, harga, stok);

    fclose(file);
}

void bacaFile()
{
    FILE *file = fopen("swalayan.txt", "r");
    if (file == NULL)
        return;

    char nama[1000];
    float harga;
    int stok;

    int hasil;
    while ((hasil = fscanf(file, " %[^;];%f;%d", nama, &harga, &stok)) != EOF)
    {
        if (hasil == 3)
        {
            DataBarang *baru = new DataBarang;
            strcpy(baru->Data.nama, nama);
            baru->Data.harga = harga;
            baru->Data.stok = stok;
            baru->next = head;
            head = baru;
        }
    }

    fclose(file);
}

void rewriteFile()
{
    FILE *file = fopen("swalayan.txt", "w");
    if (file == NULL)
    {
        cout << "file kosong\n";
        return;
    }

    DataBarang *bantu = head;

    while (bantu != nullptr)
    {
        fprintf(file, "%s;%.2f;%d\n",
                bantu->Data.nama,
                bantu->Data.harga,
                bantu->Data.stok);
        bantu = bantu->next;
    }

    fclose(file);
}

int main()
{
    bacaFile();
    menuUtama();
    return 0;
}
void menuUtama()
{
    int pilihan;
    do
    {
        cout << "\nSYWALAYAN A" << endl;
        cout << "1. Transaksi Pelanggan" << endl;
        cout << "2. Kelola Data Barang" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            transaksiPelanggan();
            break;
        case 2:
            kelolaData();
            break;
        case 3:
            cout << "Program telah keluar" << endl;
            break;
        default:
            cout << "Pilihan tidak valid, silahkan pilih ulang!" << endl;
        }
    } while (pilihan != 3);
}

void transaksiPelanggan()
{
    if (head == nullptr)
    {
        cout << "Data barang kosong!\n";
        return;
    }

    char nama[1000];
    int jumlah;

    cout << "Masukkan nama barang: ";
    cin.ignore();
    cin.getline(nama, 1000);

    DataBarang *current = head;

    while (current != nullptr && strcmp(current->Data.nama, nama) != 0)
    {
        current = current->next;
    }

    if (current == nullptr)
    {
        cout << "Barang tidak ditemukan!\n";
        return;
    }

    cout << "Harga : " << current->Data.harga << endl;
    cout << "Stok  : " << current->Data.stok << endl;

    cout << "Jumlah beli: ";
    cin >> jumlah;

    if (jumlah > current->Data.stok)
    {
        cout << "Stok tidak cukup!\n";
        return;
    }

    float total = jumlah * current->Data.harga;
    current->Data.stok = current->Data.stok - jumlah;

    rewriteFile();

    cout << "\n=== STRUK ===\n";
    cout << "Nama   : " << current->Data.nama << endl;
    cout << "Jumlah : " << jumlah << endl;
    cout << "Total  : " << total << endl;

    cout << "\nTransaksi berhasil!\n";
}

void kelolaData()
{
    int pilihan;
    do
    {
        cout << "\nKELOLA DATA BARANG" << endl;
        cout << "1. Tampilkan Data Barang" << endl;
        cout << "2. Cari Data Barang" << endl;
        cout << "3. Tambah Data Barang" << endl;
        cout << "4. Hapus Data Barang" << endl;
        cout << "5. Update Barang" << endl;
        cout << "6. Kembali ke Menu Utama" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            tampilData();
            break;
        case 2:
            cariBarang();
            break;
        case 3:
            tambahData();
            break;
        }
    } while (pilihan != 6);
}