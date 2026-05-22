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
        system("cls");
        cout << "\n";
        cout << setfill('=') << setw(55) << "" << endl;
        cout << setfill(' ') << "|" << right << setw(33) << "SWALAYAN A" << setw(21) << "|" << endl;
        cout << setfill('=') << setw(55) << "" << endl;
        cout << setfill(' ');
        cout << "| " << left << setw(52) << "1. Transaksi Pelanggan" << "|" << endl;
        cout << "| " << left << setw(52) << "2. Kelola Data Barang" << "|" << endl;
        cout << "| " << left << setw(52) << "3. Keluar" << "|" << endl;
        cout << setfill('=') << setw(55) << "" << endl;
        cout << setfill(' ');
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            transaksiPelanggan();
            system("pause");
            system("cls");
            break;
        case 2:
            kelolaData();
            system("pause");
            system("cls");
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
    system("cls");

    if (head == nullptr)
    {
        cout << "Data barang kosong!\n";
        return;
    }

    sorting();

    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(34) << "TRANSAKSI PELANGGAN" << setw(20) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');
    cout << "| " << left << setw(21) << "Nama" << setw(15) << "Harga" << setw(16) << "Stok" << "|" << endl;
    cout << setfill('-') << setw(55) << "" << endl;
    cout << setfill(' ');

    DataBarang *bantu = head;
    while (bantu != NULL)
    {
        cout << "| " << left << setw(21) << bantu->Data.nama
             << setw(15) << bantu->Data.harga
             << setw(16) << bantu->Data.stok << "|" << endl;

        bantu = bantu->next;
    }

    cout << setfill('-') << setw(55) << "" << endl;
    cout << setfill(' ');

    int jumlahBarang;
    cout << "Berapa jenis barang yang dibeli? ";
    cin >> jumlahBarang;

    char namaBeli[100][1000];
    int jumlahBeli[100];
    float hargaBeli[100];
    int itemValid = 0;
    float grandTotal = 0;

    for (int i = 0; i < jumlahBarang; i++)
    {
        char nama[1000];
        int jumlah;

        cout << "\nMasukkan nama barang: ";
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
            continue;
        }
        
        cout << "Jumlah beli: ";
        cin >> jumlah;
        
        if (jumlah > current->Data.stok)
        {
            cout << "Stok tidak cukup!\n";
            continue;
        }

        strcpy(namaBeli[itemValid], current->Data.nama);
        jumlahBeli[itemValid] = jumlah;
        hargaBeli[itemValid] = current->Data.harga;
        itemValid++;

        grandTotal += jumlah * current->Data.harga;
        current->Data.stok -= jumlah;
    }

    rewriteFile();

    cout << "\n";
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(33) << "STRUK BELANJA" << setw(21) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');
    cout << "| " << left << setw(21) << "Nama" << setw(15) << "Harga" << setw(16) << "Jumlah" << "|" << endl;
    cout << setfill('-') << setw(55) << "" << endl;
    cout << setfill(' ');

    for (int i = 0; i < itemValid; i++)
    {
        cout << "| " << left << setw(21) << namaBeli[i]
             << setw(15) << hargaBeli[i]
             << setw(16) << jumlahBeli[i] << "|" << endl;
    }

    cout << setfill('-') << setw(55) << "" << endl;
    cout << setfill(' ');
    cout << "| " << left << setw(10) << "TOTAL" << ": " << setw(40) << grandTotal << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');
    cout << "Transaksi berhasil!\n\n";
}

void kelolaData()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "\n";
        cout << setfill('=') << setw(55) << "" << endl;
        cout << setfill(' ') << "|" << right << setw(35) << "KELOLA DATA BARANG" << setw(19) << "|" << endl;
        cout << setfill('=') << setw(55) << "" << endl;
        cout << setfill(' ');
        cout << "| " << left << setw(52) << "1. Tampilkan Data Barang" << "|" << endl;
        cout << "| " << left << setw(52) << "2. Cari Data Barang" << "|" << endl;
        cout << "| " << left << setw(52) << "3. Tambah Data Barang" << "|" << endl;
        cout << "| " << left << setw(52) << "4. Hapus Data Barang" << "|" << endl;
        cout << "| " << left << setw(52) << "5. Update Barang" << "|" << endl;
        cout << "| " << left << setw(52) << "6. Kembali ke Menu Utama" << "|" << endl;
        cout << setfill('=') << setw(55) << "" << endl;
        cout << setfill(' ');
        cout << "Pilih menu: ";
        cin >> pilihan;
        
        switch (pilihan)
        {
        case 1:
            tampilData();
            system("pause");
            system("cls");
            break;
        case 2:
            cariBarang();
            system("pause");
            break;
        case 3:
            tambahData();
            system("pause");
            system("cls");
            break;
        case 4:
            hapusData();
            system("pause");
            system("cls");
            break;
        case 5:
            updateBarang();
            system("pause");
            system("cls");
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
    system("cls");
    sorting();

    DataBarang *bantu = head;
    if (bantu == NULL)
    {
        cout << "Belum ada data barang\n";
        return;
    }

    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(33) << "DATA BARANG" << setw(21) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');
    cout << "| " << left << setw(21) << "Nama" << setw(15) << "Harga" << setw(16) << "Stok" << "|" << endl;
    cout << setfill('-') << setw(55) << "" << endl;
    cout << setfill(' ');

    while (bantu != NULL)
    {
        cout << "| " << left << setw(21) << bantu->Data.nama
             << setw(15) << bantu->Data.harga
             << setw(16) << bantu->Data.stok << "|" << endl;

        bantu = bantu->next;
    }

    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');
}

void cariBarang()
{
    system("cls");
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(33) << "CARI DATA BARANG" << setw(21) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');

    char keyword[1000];

    cout << "Masukkan kata kunci: ";
    cin.ignore();
    cin.getline(keyword, 1000);

    DataBarang *current = head;
    int ketemu = 0;

    cout << "\n";
    cout << setfill('-') << setw(55) << "" << endl;
    cout << setfill(' ');

    while (current != nullptr)
    {
        if (strstr(current->Data.nama, keyword) != nullptr)
        {
            cout << "| " << left << setw(10) << "Nama"  << ": " << setw(40) << current->Data.nama  << "|" << endl;
            cout << "| " << left << setw(10) << "Harga"  << ": " << setw(40) << current->Data.harga  << "|" << endl;
            cout << "| " << left << setw(10) << "Stok"  << ": " << setw(40) << current->Data.stok  << "|" << endl;
            cout << setfill('-') << setw(55) << "" << endl;
            cout << setfill(' ');
            ketemu++;
        }
        current = current->next;
    }

    if (ketemu == 0)
        cout << "| " << left << setw(52) << "Barang tidak ditemukan!" << "|" << endl;
    else
        cout << "| " << setw(3) << ketemu << left << setw(48) << " barang ditemukan." << " |" << endl;

    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');
}     

void tambahData()
{
    system("cls");
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(34) << "TAMBAH DATA BARANG" << setw(20) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');

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
    system("cls");
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(33) << "HAPUS DATA BARANG" << setw(21) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');

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
        rewriteFile();
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
    system("cls");
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ') << "|" << right << setw(31) << "UPDATE BARANG" << setw(23) << "|" << endl;
    cout << setfill('=') << setw(55) << "" << endl;
    cout << setfill(' ');

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