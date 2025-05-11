#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdio>
#define w1 9
#define w2 41
using namespace std;

class Kasir
{
    private:
    //? cek jika langsung di cout
     string container; //* ini variabel untuk menampung line dari database.txt
     string arrayData[3]; //* variabel array untuk nyimpan isi container
     string id;
     size_t pos = 0; 
     int pilihan;
    public:
        void tampilkan(); 
        void tambah();
        void hapus();
        void checkout();
        void metodePembayaran() {cout << "ini Metode Pembayaran";}
};

void Kasir::tampilkan()
{
     system ("cls");
     ifstream data("database.txt"); //* file diakses pake variabel data
     //? apa bedanya dengan data.open()?
    

     
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+' << setw(w2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1) << "ID|" << setw(w2) << "Nama Barang|" << setw(w2) << "Harga|" << endl;
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;

     while(getline(data, container))
     {
          for (int i = 0; (pos = container.find('|')) != string::npos; i++)
          {
               arrayData[i] = container.substr(0, pos + 1);
               container.erase(0, pos + 1);
          }
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0] << setw(w2) << arrayData[1] << setw(w2) << arrayData[2] << endl;
     }

     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Tambah ke Keranjang (1)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Hapus dari Keranjang (2)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Check Out (3)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << "\nMasukkan pilihan: ";
     cin >> pilihan;

     while (pilihan != 1 && pilihan != 2 && pilihan != 3)
     {
          cout << "Masukkan angka yang valid!" << endl;
          cout << "Masukkan pilihan: ";
          cin >> pilihan;
     }
     if (pilihan == 1) tambah();
     if (pilihan == 2) hapus();
     if (pilihan == 3) checkout();

     data.close(); 

}

void Kasir::tambah()
{    
     ifstream data("database.txt");
     ofstream keranjang("keranjang.txt", ios::app);
     cout << "masukkan ID barang: ";
     cin >> id;

     while(getline(data, container))
     {
          if((pos = container.find(id)) == string::npos) continue;
          else break;
     }   
     keranjang << endl << container;

     data.close();
     keranjang.close();

     tampilkan();
}

void Kasir::hapus()
{    
     ifstream keranjang("keranjang.txt", ios::app);
     ofstream temp("temp.txt", ios::app);

     cout << "masukkan ID barang yang ingin dihapus: ";
     cin >> id;

     while(getline(keranjang, container))
     {
          if((pos = container.find(id)) == string::npos) temp << endl << container;
          else continue;
     }   

     keranjang.close();
     temp.close();
     remove("keranjang.txt");
     rename("temp.txt", "keranjang.txt");

     tampilkan();
     //TODO: pengondisian ketika gagal dibuka
}

void Kasir::checkout()
{
     system ("cls");
     ifstream keranjang("keranjang.txt");

     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2*2) << "Detil Pesanan|" << endl;

     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+' << setw(w2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1) << "ID|" << setw(w2) << "Nama Barang|" << setw(w2) << "Harga|" << endl;
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;

     while(getline(keranjang, container))
     {
          for (int i = 0; (pos = container.find('|')) != string::npos; i++)
          {
               arrayData[i] = container.substr(0, pos + 1);
               container.erase(0, pos + 1);
          }
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0] << setw(w2) << arrayData[1] << setw(w2) << arrayData[2] << endl;
     }

     cout << '|' << setfill(' ') << setw(w1+w2) << "Total|" << setw(w2) << "xxx|" << endl;
     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2) << '|' << setw(w2) << '|' << endl;  
     cout << "|" << setfill(' ') << setw (w1 + w2) << "Metode Pembayaran: Cash (Default)|" << setw (w2) << "Ganti (1)|" << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2) << '|' << setw(w2) << '|' << endl;  

     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw (w1 + w2*2) << "|" << endl;  
     cout << '|' << setfill(' ') << setw (w1 + w2*2) << "Selesai (2)|" << endl;
     cout << '|' << setw (w1 + w2*2) << "|" << endl;  
     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
         
          cout << "\nMasukkan pilihan: ";
          cin >> pilihan;

          while (pilihan != 1 && pilihan != 2)
          {
               cout << "Masukkan angka yang valid!" << endl;
               cout << "Masukkan pilihan: ";
               cin >> pilihan;
          }
          
          if (pilihan == 1) metodePembayaran();
          else if (pilihan == 2) tampilkan();
}

int main()
{
    Kasir Kasir1;
    Kasir1.tampilkan();
    return 0;
}

//TODO: jumlah Barang, total harga
//TODO: Metode Pembayaran
//TODO: Efisiensi Program
//TODO: Sorting feature
//? jika ada fungsi yang bukan berperan sebagai method