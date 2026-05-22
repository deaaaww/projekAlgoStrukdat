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
        cout << "\n";
        cout << setfill('=') << setw(35) << "" << endl;
        cout << setfill(' ') << "|" << right << setw(22) << "SWALAYAN A" << setw(12) << "|" << endl;
        cout << setfill('=') << setw(35) << "" << endl;
        cout << setfill(' ');
        cout << "| " << left << setw(32) << "1. Transaksi Pelanggan" << "|" << endl;
        cout << "| " << left << setw(32) << "2. Kelola Data Barang" << "|" << endl;
        cout << "| " << left << setw(32) << "3. Keluar" << "|" << endl;
        cout << setfill('=') << setw(35) << "" << endl;
        cout << setfill(' ');
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

    cout << "\n";
    cout << "========== STRUK BELANJA ==========\n" << endl;
    cout << setfill(' ');
    cout << "-----------------------------------\n";
    cout << "| " << left << setw(32) << "           SWALAYAN A" << "|\n";
    cout << "-----------------------------------\n";
    cout << "| " << left << setw(8) << "Nama" << ": " << setw(22) << current->Data.nama << "|\n",
    cout << "| " << left << setw(8) << "Harga" << ": " << setw(22) << current->Data.harga << "|\n",
    cout << "| " << left << setw(8) << "Jumlah" << ": " << setw(22) << jumlah << "|\n",
    cout << "-----------------------------------\n";
    cout << "| " << "TOTAL  : " << left << setw(23) << total                                  << "|" << endl;
    cout << "===================================\n";
    cout << setfill(' ');

    cout << "Transaksi berhasil!\n\n";
}

void kelolaData()
{
    int pilihan;
    do
    {
        cout << "\n";
        cout << setfill('=') << setw(35) << "" << endl;
        cout << setfill(' ') << "|" << right << setw(26) << "KELOLA DATA BARANG" << setw(8) << "|" << endl;
        cout << setfill('=') << setw(35) << "" << endl;
        cout << setfill(' ');
        cout << "| " << left << setw(32) << "1. Tampilkan Data Barang" << "|" << endl;
        cout << "| " << left << setw(32) << "2. Cari Data Barang" << "|" << endl;
        cout << "| " << left << setw(32) << "3. Tambah Data Barang" << "|" << endl;
        cout << "| " << left << setw(32) << "4. Hapus Data Barang" << "|" << endl;
        cout << "| " << left << setw(32) << "5. Update Barang" << "|" << endl;
        cout << "| " << left << setw(32) << "6. Kembali ke Menu Utama" << "|" << endl;
        cout << setfill('=') << setw(35) << "" << endl;
        cout << setfill(' ');
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
        case 4:
            hapusData();
            break;
        
        case 6:
            break;
        default:
            cout << "Pilihan tidak valid, silahakan pilih ulang!" << endl;
        }
    } while (pilihan != 6);
}

void sorting()
{
    DataBarang *i, *j;

    for (i = head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->Data.nama, j->Data.nama) > 0)
            {

                char tempNama[1000];
                float tempHarga;
                int tempStok;

                strcpy(tempNama, i->Data.nama);
                tempHarga = i->Data.harga;
                tempStok = i->Data.stok;

                strcpy(i->Data.nama, j->Data.nama);
                i->Data.harga = j->Data.harga;
                i->Data.stok = j->Data.stok;

                strcpy(j->Data.nama, tempNama);
                j->Data.harga = tempHarga;
                j->Data.stok = tempStok;
            }
        }
    }
}

void tampilData()
{
    sorting();

    DataBarang *bantu = head;
    if (bantu == NULL)
    {
        cout << "Belum ada data barang\n";
        return;
    }

    cout << setfill('=') << setw(50) << "" << endl;

    cout << setfill(' ')
         << "|" << right << setw(30) << "DATA BARANG" << setw(19) << "|" << endl;

    cout << setfill('=') << setw(50) << "" << endl;

    cout << setfill(' ');
    cout << "|"
         << left << setw(20) << "Nama" << "|"
         << setw(13) << "Harga" << "|"
         << setw(13) << "Stok" << "|" << endl;

    cout << setfill('-') << setw(50) << "" << endl;
    cout << setfill(' ');

    while (bantu != NULL)
    {
        cout << "|"
             << left << setw(20) << bantu->Data.nama << "|"
             << setw(13) << bantu->Data.harga << "|"
             << setw(13) << bantu->Data.stok << "|" << endl;

        bantu = bantu->next;
    }

    cout << setfill('=') << setw(50) << "" << endl;
}

void cariBarang()
{
    char keyword[1000];

    cout << "Masukkan kata kunci: ";
    cin.ignore();
    cin.getline(keyword, 1000);

    DataBarang *current = head;
    int ketemu = 0;

    cout << "\nHasil pencarian:\n";
    while (current != nullptr)
    {
        // strstr cek apakah keyword ada di dalam nama barang
        if (strstr(current->Data.nama, keyword) != nullptr)
        {
            cout << "Nama\t: " << current->Data.nama << endl;
            cout << "Harga\t: " << current->Data.harga << endl;
            cout << "Stok\t: " << current->Data.stok << endl;
            ketemu++;
        }
        current = current->next;
    }

    if (ketemu == 0)
        cout << "Barang tidak ditemukan!\n";
    else
        cout << ketemu << " barang ditemukan.\n";
}     

void tambahData()
{
    int jumlah;

    cout << "Jumlah data yang ingin ditambahkan: ";
    cin >> jumlah;

    for (int i = 0; i < jumlah; i++)
    {
        DataBarang *newData = new DataBarang;

        cout << "\nData ke-" << i + 1 << endl;
        
        cin.ignore();

        cout << "Masukkan nama barang: ";
        cin.getline(newData->Data.nama, 1000);

        cout << "Masukkan harga barang: ";
        cin >> newData->Data.harga;

        cout << "Masukkan stok barang: ";
        cin >> newData->Data.stok;

        newData->next = head;
        head = newData;

        saveFile(newData->Data.nama, newData->Data.harga, newData->Data.stok);
        cout << "Data barang berhasil ditambahkan!" << endl;
    }
}

void hapusData()
{
    if (head == nullptr)
        return;

    char namaToDelete[1000];

    cout << "Masukkan nama barang yang ingin dihapus: ";
    cin.ignore();
    cin.getline(namaToDelete, 1000);

    if (strcmp(head->Data.nama, namaToDelete) == 0)
    {
        DataBarang *toDeleteNode = head;
        head = head->next;

        delete toDeleteNode;
        cout << "Data berhasil dihapus!\n";
        return;
    }

    DataBarang *current = head;

    while (current->next != nullptr && strcmp(current->next->Data.nama, namaToDelete) != 0)
    {
        current = current->next;
    }

    if (current->next == nullptr)
    {
        cout << "Barang tidak ditemukan\n";
        return;
    }

    DataBarang *toDeleteNode = current->next;
    current->next = toDeleteNode->next;

    delete toDeleteNode;

    rewriteFile();

    cout << "Data berhasil dihapus!\n";
}

void updateBarang()
{
    if (head == nullptr)
    {
        cout << "Data kosong!\n";
        return;
    }

    char nama[1000];

    cin.ignore();
    cout << "Masukkan nama barang yang ingin diupdate: ";
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

    char namaBaru[1000];
    float hargaBaru;
    int stokBaru;

    cout << "Nama baru  : ";
    cin.getline(namaBaru, 1000);

    cout << "Harga baru : ";
    cin >> hargaBaru;

    cout << "Stok baru  : ";
    cin >> stokBaru;

    strcpy(current->Data.nama, namaBaru);
    current->Data.harga = hargaBaru;
    current->Data.stok = stokBaru;

    rewriteFile();

    cout << "Data berhasil diupdate!\n";
}