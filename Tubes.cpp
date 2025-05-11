#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdio>
#define w1 11
#define w2 41
using namespace std;

class Kasir
{
    private:
     string container;
     string arrayData[3];
     string id;
     string metodePembayaran = "Cash"; 
     size_t pos = 0; 
     int pilihan;
     int jumlah = 0;
     //?kapan mendeklarasikan variabel didalam fungsi?
    public:
        void tampilkan(); 
        void tambah();
        void hapus();
        void filter();
        void checkout();
        void gantiMetode() //! Pemngembangan
        {
          cout << "Metode tersedia:" << endl << "1. cash" << endl << "2. Transfer Bank (BRI)" << endl << "3. Dompet Virtual (OVO)" << endl;
          cin >> pilihan;

          if (pilihan == 1) metodePembayaran = "Cash";
          else if (pilihan == 2) metodePembayaran = "Transfer Bank (0000 1111 2222 3333)";
          else if (pilihan == 3) metodePembayaran = "Dompet Virtual (0812 3456 789)";
          else {cout << "Masukkan pilihan yang valid"; gantiMetode();}
          
        }

        void head();
        void menu();
        void parse()
        {
          for (int i = 0; (pos = container.find('|')) != string::npos; i++)
          {
               arrayData[i] = container.substr(0, pos + 1);
               container.erase(0, pos + 1);
          }
        }
        int cast(string s)
        {
               int result = 0;
               for (size_t i = 0; s[i] < s.length(); i++)
               {
                    //! jika input bukan angka di [0], coba throw error/exception (try/catch)
                    if (int(s[i]) < 48 || int(s[i] > 57)) return result;
                    result = result * 10 + (s[i++] - '0');
               } 
               
               return result;
        }
};

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
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Filter Barang (3)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1 + w2*2) << "Check Out (4)|" << endl;
     cout << '+' << setfill('-') << setw(w1 + w2*2) << '+' << endl;
}

void Kasir::tampilkan()
{
     system ("cls");
     ifstream data("database.txt"); 
    
     head();
     while(getline(data, container))
     {
          parse();
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                      << setw(w2) << arrayData[1] 
                                      << setw(w2) << arrayData[2] << endl;
     }
     menu();

     cout << "\nMasukkan pilihan: ";
     cin >> pilihan;

     while (pilihan < 1 && pilihan > 4)
     {
          cout << "Masukkan angka yang valid!" << endl;
          cout << "Masukkan pilihan: ";
          cin >> pilihan;
     }
     if (pilihan == 1) tambah(); //! bagus mana banding switch
     if (pilihan == 2) hapus();
     if (pilihan == 3) filter();
     if (pilihan == 4) checkout();

 
     
     data.close(); 
     tampilkan();
}

void Kasir::tambah()
{    
     ifstream data("database.txt");
     fstream keranjang("keranjang.txt", ios::app | ios::in);
     cout << "masukkan ID barang: ";
     cin >> id;

     while(getline(data, container))
     {
          if((pos = container.find(id)) == string::npos) continue;
          else break;
     }  
     parse();
     cout << "Barang yang ingin ditambah: " << arrayData[1] << endl
          << "Jumlah dalam keranjang: " << arrayData[3] << endl;
     cout << "Tambah sebanyak: ";
     cin >> jumlah;
     jumlah = jumlah + cast(arrayData[3]); //* menambahkan jumlah yang diberi user dengan yang di keranjang

     keranjang << container + to_string(jumlah) + '|' << endl;

     data.close();
     keranjang.close();

     tampilkan();
}

void Kasir::hapus()
{    
     ifstream keranjang("keranjang.txt");
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

void Kasir::filter()
{
     cout << "Filter Berdasarkan: " << endl;
     cout << "1. Barang" << endl << "2. Makanan" << endl << "3. Pakaian" << endl;
     cout << "Pilihan: ";
     cin >> pilihan;
     if (pilihan == 1) pilihan = 'b'; 
     if (pilihan == 2) pilihan = 'm';
     if (pilihan == 3) pilihan = 'p';
     
     ifstream data("database.txt");

     system("cls");

     head();
     while (getline(data, container))
     {
          for (int i = 0; ((pos = container.find('|')) != string::npos); i++)
          {
               arrayData[i] = container.substr(0, pos + 1);
               container.erase(0, pos + 1);
          }

          container = arrayData[0]; //* mengubah elemen menjadi array
          if (container[0] == pilihan) cout << '|' << setfill(' ') << setw(w1) << arrayData[0] 
                                                                   << setw(w2) << arrayData[1] 
                                                                   << setw(w2) << arrayData[2] << endl;
     }
     data.close();
     menu();
}

void Kasir::checkout()
{
     system ("cls");
     ifstream keranjang("keranjang.txt");

     jumlah = 0; //! butuh perbaikan
     cout << '+' << setfill('-') << setw (w1 + w2*2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1) << "<--  (1)|" << setw (w2*2) << "Detil Pesanan|" << endl;

     head();
     while(getline(keranjang, container))
     {
          parse();
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                      << setw(w2) << arrayData[1]
                                      << setw(w2) << 'x' + arrayData[3] +  "       " + arrayData[2] << endl; //! butuh perbaikan
          jumlah = jumlah + cast(arrayData[3]);
     }

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

     cout << "Total: " << jumlah; 
         
     // cout << "\nMasukkan pilihan: ";
     // cin >> pilihan;

     while (pilihan < 1 || pilihan > 3)
     {
          cout << "Masukkan angka yang valid!" << endl;
          cout << "Masukkan pilihan: ";
          cin >> pilihan;
     }

     if (pilihan == 1)tampilkan();
     else if (pilihan == 2) gantiMetode(); 
     else if (pilihan == 3)tampilkan ();
}

int main()
{
    Kasir Kasir1;
    Kasir1.tampilkan();
    return 0;
}

