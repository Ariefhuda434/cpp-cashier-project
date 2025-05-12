#ifndef HEADER_H
#define HEADER_H
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstdio>
#include<ctime>
#include<windows.h>
using namespace std;

const string RESET_TEXT      = "\033[0m";

const string BLACK_TEXT      = "\033[0;30m";
const string RED_TEXT        = "\033[0;31m";
const string GREEN_TEXT      = "\033[0;32m";
const string YELLOW_TEXT     = "\033[0;33m";
const string BLUE_TEXT       = "\033[0;34m";
const string MAGENTA_TEXT    = "\033[0;35m";
const string CYAN_TEXT       = "\033[0;36m";
const string WHITE_TEXT      = "\033[0;37m";

const string BRIGHT_BLACK    = "\033[1;30m";
const string BRIGHT_RED      = "\033[1;31m";
const string BRIGHT_GREEN    = "\033[1;32m";
const string BRIGHT_YELLOW   = "\033[1;33m";
const string BRIGHT_BLUE     = "\033[1;34m";
const string BRIGHT_MAGENTA  = "\033[1;35m";
const string BRIGHT_CYAN     = "\033[1;36m";
const string BRIGHT_WHITE    = "\033[1;37m";

const string BG_RED = "\033[41m";
const string BG_GREEN = "\033[42m";
const string RESET = "\033[0m";
const string BG_CYAN = "\033[46m"; // Cyan background
const string BG_YELLOW = "\033[43m"; // Yellow background


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
          void open();
          string Rupiah(int);
          
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
          int uang,selisih;
          bool uangPas = false;
          bool metodeIs = false;
          public:
          void head() override;
          void gantiMetode();
          void checkout();
          void kelolaPembayaran();
          void inputStruk();
          void struk();
          void loading();
};
#endif
