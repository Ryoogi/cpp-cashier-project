#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdio>
#define w1 11
#define w2 41
using namespace std;
#include "header.h"

//* GLOBAL
int to_int(string s)
        {
               int result = 0;
               for (size_t i = 0; i < s.length(); i++)
               {
                    if (s[i] < '0' || s[i] > '9') return result;
                    result =  result * 10 + (s[i] - '0');
               } 
               
               return result;
        }


//* PARENT
void Kasir::head()
{
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+' << setw(w2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1) << "ID|" << setw(w2) << "Nama Barang|" << setw(w2) << "Harga|" << endl;
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;
}

void Kasir::menu() 
{
     
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Tambah ke Keranjang (1)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Hapus dari Keranjang (2)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Kurangi Barang (3)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Filter Barang (4)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Keranjang & CheckOut (5)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
}

void Kasir::parse()
{
     //p0005|Rok|26000|2|
     for (this->size = 0; (pos = container.find('|')) != string::npos;size++)
     {
          arrayData[size] = container.substr(0, pos + 1);
          container.erase(0, pos + 1);
     }
}

void Kasir::tampilkan()
{
     system ("cls");
     ifstream file(namaFile);
     head();
     while(getline(file, container))
     {
          parse();
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                      << setw(w2) << arrayData[1] 
                                      << setw(w2) << arrayData[2] << endl;
     }
     file.close();
}


//*CHILD1
void Produk::tampilkan()
{
     Kasir::tampilkan();
     menu();
}

void Produk::filter()
{
     cout << "Filter Berdasarkan: " << endl;
     cout << "1. Barang" << endl << "2. Makanan" << endl << "3. Pakaian" << endl;
     cout << "Pilihan: ";
     cin >> pilihan;
     if (pilihan == 1) pilihan = 'b'; //*pilihannya diwakili huruf biar ga ribet dibawah
     if (pilihan == 2) pilihan = 'm';
     if (pilihan == 3) pilihan = 'p';

     system("cls");

     ifstream data("database.txt");
     head();
     while (getline(data, container))
     {
          parse();
          container = arrayData[0]; //* mengubah elemen (cth: "lost") menjadi array ('l', 'o', 's', 't') 
          if (container[0] == pilihan) cout << '|' << setfill(' ') << setw(w1) << arrayData[0] //* kalau huruf awal id = pilihan, dia diprint
                                                                   << setw(w2) << arrayData[1] 
                                                                   << setw(w2) << arrayData[2] << endl;
     }
     data.close();
     menu();
}


//*CHILD2 
void Keranjang::head()
{
     cout << setfill(' ') << setw(w1+5) << '|' << setw(w1) << "ID|" << setw(w2-20) << "Nama Barang|" << setw(w2-15) << "Jumlah|" << endl;
     cout << setw(w1+5) << '+' << setfill('-')  << setw(w1) << '+' << setw(w2-20) << '+'<< setw(w2-15) << '+' << endl;
}

void Keranjang::tampilkan()
{
     ifstream file(namaFile);
     head();
     while(getline(file, container))
     {
          parse();
          cout << setw(w1+5) << setfill(' ') << '|'  << setw(w1) << arrayData[0]
                                      << setw(w2-20) << arrayData[1] 
                                      << setw(w2-15) << arrayData[3] << endl;
     }
     file.close();

     cout << setw(w1+5) << '|' << setfill('-') << setw(w1) << "+" << setw(w2+6) << "+" << endl;
     cout << setw(w1+5) << setfill(' ') << '|'  << setw(w1) << "Tutup Keranjang (6)|" << setw(w2-3) << "CheckOut (7)|" << endl;
     cout << setw(w1+5) << '+' << setfill('-') << setw(w2+w1+6) << "+" << endl;
}

void Keranjang::tambah()
{
     jumlah = 0;
     ditemukan = false;
     ifstream keranjang("keranjang.txt");
     while(getline(keranjang, container)) //* mencari data dari keranjang, di keranjang ada data jumlah barang
     {
          if((pos = container.find(id)) == string::npos) continue;
          else {ditemukan = true; break;}
     }  
     keranjang.close();//* nutup file biar pointer internal reset, capek kena bug babi
     
     if (!ditemukan)//* jika tidak ada di keranjang, dia ambil dari database
     {
          ifstream data("database.txt");
          while(getline(data, container)) //* mencari data dari database
          {
               if((pos = container.find(id)) == string::npos) continue;
               else {ditemukan = true; break;}
          }  
          data.close();
     }


     if (ditemukan) //*setelah datanya diambil dari database/keranjang, jalankan fungsi tambah untuk ngupdate
     {
          
          parse();
          cout << "Barang yang ingin ditambah: " << arrayData[1] + "\b " << endl;
          cout << "Tambah sebanyak: ";
          cin >> jumlah; 
          
          if (size == 4) jumlah += to_int(arrayData[3]);//*mengupdate jumlah  
          else if (size == 3) size++;   

          arrayData[3] = to_string(jumlah) + '|';

          hapus(); //* setelah jumlah diupdate, hapus datanya dari keranjang
          ofstream keranjang("keranjang.txt", ios::app);
          for (int i = 0; i < size; i++) keranjang << arrayData[i];//* print ulang data dan jumlah yang baru
          keranjang << endl;
          keranjang.close();
     }
}

void Keranjang::kurang()
{
     ditemukan = false;
     jumlah = 0;
     ifstream keranjangIn("keranjang.txt");//*cari datanya dari keranjang
     while (getline(keranjangIn, container))
     {
          if((pos = container.find(id)) == string::npos) continue;
          else {ditemukan = true; break;}
     }
     keranjangIn.close();
     parse(); //* setelah data diambil, uraikan jadi array dengan parse

     cout << "Ada " << arrayData[3] + "\b " << arrayData[1] + "\b " << "didalam keranjang." << endl
          << "Kurangi sebanyak: "; //* minta berapa banyak yang ingin dikurangi
     cin >> jumlah;

     if(jumlah < to_int(arrayData[3]) && jumlah > 0) //* jika jumlah yang ingin dikurangi lebih kecil dari jumlah di keranjang, jalankan
     {
          arrayData[3] = to_string(to_int(arrayData[3]) - jumlah) + '|';
          if (to_int(arrayData[3]) == 0) //* jika setelah dikurangi, isi barang dikeranjang jadi 0, hapus aja
          {
               hapus();
               return;
          }
     }
     else //* kalau angkanya tidak valid, ulangi
     {
          system("cls");
          cout << "\nMasukkan angka yang valid!" << endl;
          kurang();
     }
     hapus(); //* setelah jumlah baru udh dapat, hapus data yang lama
     ofstream keranjangOut("keranjang.txt", ios::app);//* print ke keranjang data yang terupdate
     for (int i = 0; i < size; i++) keranjangOut << arrayData[i];
     keranjangOut << endl;
     keranjangOut.close();
}

void Keranjang::hapus()
{
     ofstream temp("temp.txt", ios::app);
     ifstream keranjang("keranjang.txt");

     while(getline(keranjang, container))//* print semua isi keranjang.txt ke temp.txt kecuali data yang mau dihapus
     {
          if((pos = container.find(id)) == string::npos) temp << container << endl;
          else continue;
     }   
     
     temp.close();
     keranjang.close();

     remove("keranjang.txt");
     rename("temp.txt", "keranjang.txt");
}

//*CHILD#
void Transaksi::head()
{
     Kasir::head();
}

void Transaksi::gantiMetode()
{
          cout << "Metode tersedia:" << endl << "1. cash" << endl << "2. Transfer Bank (BRI)" << endl << "3. Dompet Virtual (OVO)" << endl;
          cin >> pilihan;

          if (pilihan == 1) metodePembayaran = "Cash";
          else if (pilihan == 2) metodePembayaran = "Transfer Bank (0000 1111 2222 3333)";
          else if (pilihan == 3) metodePembayaran = "Dompet Virtual (0812 3456 789)";
          else {cout << "Masukkan pilihan yang valid"; gantiMetode();}
}

void Transaksi::checkout()
{
     system ("cls");

     jumlah = 0; //! butuh perbaikan
     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1) << "<--  (1)|" << setw (w2*2) << "Detil Pesanan|" << endl;

     ifstream keranjang("keranjang.txt");
     head();
     while(getline(keranjang, container))
     {
          parse();
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                      << setw(w2) << arrayData[1]
                                      << setw(w2) << 'x' + arrayData[3] +  "       " + arrayData[2] << endl; //! butuh perbaikan
          jumlah = jumlah + to_int(arrayData[3]);
     }
     keranjang.close();

     cout << '|' << setfill(' ') << setw(w1+w2) << "Total|" << setw(w2) << to_string(jumlah) + '|' << endl;
     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2) << '|' << setw(w2) << '|' << endl;  
     cout << "|" << setfill(' ') << setw (w1 + w2) << "Metode Pembayaran: " + metodePembayaran + " |" << setw (w2) << "Ganti (2)|" << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2) << '|' << setw(w2) << '|' << endl;  

     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2*2) << "|" << endl;  
     cout << '|' << setfill(' ') << setw (w1 + w2*2) << "Selesai (3)|" << endl;
     cout << '|' << setw (w1 + w2*2) << "|" << endl;  
     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;

         
     cout << "\nMasukkan pilihan: ";
     cin >> pilihan;

     while (pilihan < 1 || pilihan > 3)
     {
          cout << "Masukkan angka yang valid!" << endl;
          cout << "Masukkan pilihan: ";
          cin >> pilihan;
     }

     if (pilihan == 1)tampilkan();
     else if (pilihan == 2) gantiMetode(); 
     else if (pilihan == 3)tampilkan (); //* +print struk, +bersihkan isi keranjang.txt
}

