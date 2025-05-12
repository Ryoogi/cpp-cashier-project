#include<iostream>
#include<csignal>
#include<fstream>
#include "header.h"

using namespace std;

void handleSIGINT(int signal)
{
     ofstream keranjang("keranjang.txt", ios::trunc);
     keranjang.close();
     exit(signal);
}

int main()
{
     signal(SIGINT, handleSIGINT); //* truncate data keranjang ketika exit paksa (ctrl + c)
     Produk produk;
     Keranjang keranjang;
     Transaksi transaksi;
     int pilihan;

     produk.tampilkan();

     while(true)
     {
          cout << "\nMasukkan pilihan: ";
          cin >> pilihan;

          switch (pilihan)
          {
          case 1:    
               cout << "masukkan ID barang: ";
               keranjang.setID();         
               keranjang.tambah();
               produk.tampilkan();
               if (keranjang.getFlag()) cout << "Barang dengan ID " << keranjang.getID() << " berhasil ditambah!" << endl;
               else cerr << "Barang dengan ID " << keranjang.getID() << " tidak ditemukan!" << endl;
               break;
          case 2:
               cout << "masukkan ID barang yang ingin dihapus: ";
               keranjang.setID();
               keranjang.hapus();
               produk.tampilkan();
               if (keranjang.getFlag()) cout << "Barang dengan ID " << keranjang.getID() << " berhasil dihapus!" << endl;
               else cerr << "Barang dengan ID " << keranjang.getID() << " tidak ditemukan!" << endl;
               break;
          case 3:
               cout << "masukkan ID barang yang ingin dikurangi: ";
               keranjang.setID();
               keranjang.kurang();
               produk.tampilkan();
               if (keranjang.getFlag()) cout << "Barang dengan ID " << keranjang.getID() << " berhasil dikurangi!" << endl;
               else cerr << "Barang dengan ID " << keranjang.getID() << " tidak ditemukan!" << endl;
               break;
          case 4:  
               produk.filter();
               if (keranjang.getStatusKeranjang()) keranjang.tampilkan();
               break;
          case 5:
               produk.tampilkan();
               keranjang.tampilkan();
               keranjang.setStatusKeranjang(true);
               break;
          case 6:
               if (keranjang.getStatusKeranjang())
               {
                    produk.tampilkan();
                    keranjang.setStatusKeranjang(false);
               }
               else
               {
                    produk.tampilkan();
                    cout << "Masukkan angka yang valid\n";
               }
               break;
               
          case 7:
               if (keranjang.getStatusKeranjang())transaksi.checkout();
               else
               {
                    produk.tampilkan();
                    cout << "Masukkan angka yang valid\n";
               }
               break;
     
          default:
               produk.tampilkan();
               cerr << "Masukkan angka yang valid\n";
               break;
          }
     }
     return 0;
}
/*
!     ..............
!            ..,;:ccc,.
!               ......''';lx0.
!     .....''''..........,:ld;
!                .';;;:::;,,.x,
!           ..'''.            0Xxoc:,.  ...
!       ....                ,ONkc;,;cok0dc',.
!      .                   OMo           ':ddo.
!                         dMc               :OO;
!                         OM.                 .:o.
!                         ;Wd
!                          ;XO,
!                            ,d00dlc;,..
!                                ..',;:cd00d::,.
!                                         .:d;.':;.
!                                           'd,  .'
!                                              ;l   ..
!                                              .o
!                                                c
!                                                 .'
!                                                  .

*/
