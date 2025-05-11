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
    //? cek jika langsung di cout
     string container; //* ini variabel untuk menampung line dari database.txt
     string arrayData[4]; //* variabel array untuk nyimpan isi container
     string id; //* sebagai identitas data atau array
     string metodePembayaran = "Cash"; //! reassign menggunakan constructor
     size_t pos = 0; 
     int pilihan;
     int jumlah;          
     int size;
     bool ditemukan = false;
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
          for (this->size = 0; (pos = container.find('|')) != string::npos;size++)
          {
               arrayData[size] = container.substr(0, pos + 1);
               container.erase(0, pos + 1);
          }
        }
        int to_int(string s)
        {
               int result = 0;
               for (size_t i = 0; i < s.length(); i++)
               {
                    //! jika input bukan angka di [0], coba throw error/exception (try/catch)
                    if (int(s[i]) < 48 || int(s[i] > 57)) return result;
                    result = result * 10 + (s[i++] - '0');
               } 
               
               return result;
               //? apa yang terjadi jika ada 2x pendeklarasian, int halo, int halo?
               //?apakah result ini sudah tepat dideklarasikan dalam fungsi
        }
};

void Kasir::head()
{
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+' << setw(w2) << '+' << endl;
     cout << '|' << setfill(' ') << setw(w1) << "ID|" << setw(w2) << "Nama Barang|" << setw(w2) << "Harga|" << endl;
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;

}

void Kasir::menu() //? mengapa void::menu berhasil alih alih void Kasir::menu
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
     ifstream keranjang("keranjang.txt");
     jumlah = 0;
     ditemukan = false;

     cout << "masukkan ID barang: ";
     cin >> id;

     while(getline(keranjang, container)) //* mencari data dari keranjang
     {
          if((pos = container.find(id)) == string::npos) continue;
          else {ditemukan = true; break;}
     }  
     if (!ditemukan)
     {
          while(getline(data, container)) //* mencari data dari database
          {
               if((pos = container.find(id)) == string::npos) continue;
               else {ditemukan = true; break;}
          }  
     }
     keranjang.close();
     if (ditemukan) 
     {
          ofstream keranjang("keranjang.txt", ios::app);
          parse();
          cout << "size = " << size << endl; //! debugger
          cout << "Barang yang ingin ditambah: " << arrayData[1] + "\b " << endl;
          cout << "Tambah sebanyak: ";
          cin >> jumlah;
          
          if (size == 4) {jumlah += to_int(arrayData[3]); cout << endl << to_int(arrayData[3]) << endl << jumlah << endl;}//*mengupdate jumlah     
          cin >> jumlah;    //!debugger
          arrayData[3] = to_string(jumlah) + '|';

          for (int i = 0; i < size; i++) keranjang << arrayData[i];

          data.close();
          keranjang.close();

     }
     if (data.is_open()) data.close();
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
     if (pilihan == 1) pilihan = 'b'; //*mengubah pilihan menjadi kode awal ID 
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
          jumlah = jumlah + to_int(arrayData[3]);
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

     cout << "Total: " << jumlah; //*Debugger sementara
         
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
     else if (pilihan == 3)tampilkan (); //* +print struk, +bersihkan isi keranjang.txt
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
//TODO: Fitur Kembali
//TODO: Struk

//TODO: Coba pakai Try-Catch untuk menangkap error ketika salah menginput nilai

//TODO: Perbaiki looping unlimited ketikka ctrl alt n saat input nilai
//? jika ada fungsi yang bukan berperan sebagai method