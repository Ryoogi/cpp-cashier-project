#ifndef HEADER_H
#define HEADER_H
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdio>
using namespace std;

class Kasir
{
     private:
     protected:
          string *arrayData;
          size_t size;
          size_t pos;
          string id;
          string container;
          string namaFile;
          int pilihan;
     public:
          //*Constructor
          Kasir(){};
          Kasir(string inputFile) : namaFile(inputFile) {
            size = 4;
            arrayData = new string[size];}

          //*Destructor
          virtual ~Kasir(){ //? mengapa harus virtual
            delete[] arrayData;}
          
          //*Method
          virtual void tampilkan(); 
          void setPilihan(){cin >> pilihan;}
          void setPilihan(char a){pilihan = a;}
          int getPilihan() {return pilihan;}
          void setID(){cin >> id;}
          //*Fungsi
          virtual void head();
          void menu();
          void parse();

};

class Produk : public Kasir
{
     private:   

     public:
          Produk() : Kasir("database.txt"){}
          void tampilkan() override;   
          void filter();
};

class Keranjang : public Kasir
{
     protected:
          int jumlah;
          bool ditemukan;
          bool statusKeranjang;
     public:
          Keranjang() : Kasir("keranjang.txt"){statusKeranjang = false;}
          void head() override;
          void tampilkan() override;
          void tambah();
          void kurang();
          void hapus();
          void setStatusKeranjang(bool status){statusKeranjang = status;}
          bool getStatusKeranjang(){return statusKeranjang;}

};

class Transaksi : public Keranjang
{
     private:
          string metodePembayaran;
     public:
          void head() override;
          void gantiMetode();
          void checkout();
};
#endif
