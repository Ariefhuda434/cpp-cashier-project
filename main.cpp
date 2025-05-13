#include<iostream>
#include "header.h"

using namespace std;


int main()
{
     Produk produk;
     Keranjang keranjang;
     Transaksi transaksi;
     Kasir obj1;
     int pilihan;
     obj1.open();
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
               break;
          case 2:
               cout << "masukkan ID barang yang ingin dihapus: ";
               keranjang.setID();
               keranjang.hapus();
               produk.tampilkan();
               break;
          case 3:
               cout << "masukkan ID barang yang ingin dihapus: ";
               keranjang.setID();
               keranjang.kurang();
               produk.tampilkan();
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
                    cout << "Masukkan angka yang valid";
               }
               break;
               
          case 7:
               if (keranjang.getStatusKeranjang())transaksi.checkout();
               else
               {
                    produk.tampilkan();
                    cout << "Masukkan angka yang valid";
               }
               break;
     
          default:
               produk.tampilkan();
               cout << "Masukkan angka yang valid";
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
