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
     cout <<BRIGHT_CYAN<< '+' << setfill('-') << setw(w1) << '+' << setw(w2) << '+' << setw(w2) << '+' << RESET_TEXT<< endl;
     cout << '|' << setfill(' ') << setw(w1) << right << "ID|" << setw(w2) << right << "Nama Barang|" << setw(w2) <<right<< "Harga|" << endl;
     cout << '+' << setfill('-')  << setw(w1) << '+' << setw(w2) << '+'<< setw(w2) << '+' << endl;
}

void Kasir::menu() 
{
    int totalWidth = w1 + w2 * 2;

    cout << '+' << string(totalWidth-1, '-') << '+' << endl;
    cout << '|' << setw(totalWidth-1) << left << " Tambah ke Keranjang (1)" << '|' << endl;
    cout << '+' << string(totalWidth-1, '-') << '+' << endl;
    cout << '|' << setw(totalWidth-1) << left << " Hapus dari Keranjang (2)" << '|' << endl;
    cout << '+' << string(totalWidth-1, '-') << '+' << endl;
    cout << '|' << setw(totalWidth-1) << left << " Kurangi Barang (3)" << '|' << endl;
    cout << '+' << string(totalWidth-1, '-') << '+' << endl;
    cout << '|' << setw(totalWidth-1) << left << " Filter Barang (4)" << '|' << endl;
    cout << '+' << string(totalWidth-1, '-') << '+' << endl;
    cout << '|' << setw(totalWidth-1) << left << " Keranjang & CheckOut (5)" << '|' << endl;
    cout << '+' << string(totalWidth-1, '-') << '+' << endl;
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
          int rupiahku = to_int(arrayData[2]);
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                      << setw(w2) << arrayData[1] 
                                      << setw(w2) << Rupiah(rupiahku) + '|' << endl;
     }
     file.close();
}

string Kasir::Rupiah(int angka) {
     string hasil;
     string angkaStr = to_string(angka);
     int len = angkaStr.length();
     int count = 0;
 
     for (int i = len - 1; i >= 0; i--) {
         hasil = angkaStr[i] + hasil;
         count++;
         if (count % 3 == 0 && i != 0) {
             hasil = '.' + hasil;
         }
     }
 
     return hasil;
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
     int totalWidth = w1 + w2 * 2;
     while (getline(data, container))
     {
          parse();
          container = arrayData[0]; //* mengubah elemen (cth: "lost") menjadi array ('l', 'o', 's', 't') 
          int Harga = to_int(arrayData[2]);
          if (container[0] == pilihan) cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                    << setw(w2) << arrayData[1] 
                                    << setw(w2) << Rupiah(Harga) + '|'<< endl;

     }
     data.close();
     menu();
}


//*CHILD2 
void Keranjang::head()
{
    cout << setw(w1+5) <<right<< '+' << setfill('-')  << setw(w1) << '+' << setw(w2-20) << '+'<< setw(w2-15) << '+' << endl;
    cout << setfill(' ') << setw(w1+5) <<right<< '|' <<setfill(' ') <<setw(w1)<<right << "ID|" << setw(w2-20) << "Nama Barang|" << setw(w2-15) << "Jumlah|" << endl;
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

     cout << setw(w1+5) << '+' << setfill('-') << setw(w1) << "+" << setw(w2+6) << "+" << endl;
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
          int nande = to_int(arrayData[2]);
          int subtotal = 0;
          cout << '|' << setfill(' ') << setw(w1) << arrayData[0]
                                      << setw(w2) << arrayData[1]
                                      << setw(w2) << 'x' + arrayData[3] +  "       " + Rupiah(nande) + '|' << endl; //! butuh perbaikan
                                      subtotal = to_int(arrayData[3]) * nande;
                                      jumlah += subtotal;
     }
     keranjang.close();

     cout << '|' << setfill(' ') << setw(w1+w2) << "Total|" << setw(w2) << Rupiah(jumlah) + '|' << endl;
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
     else if (pilihan == 3) kelolaPembayaran(); //* +print struk, +bersihkan isi keranjang.txt
}

void Transaksi::kelolaPembayaran(){
     int totalHarga = 0;
     int kurang;
   
     cout << "Masukan Uang Anda : \n";
     cin >> uang;

     ifstream keranjang("keranjang.txt");
     while (getline(keranjang, container))
     {
         parse();
     int hargaCheckout = to_int(arrayData[2]); 
     int jumlahBarang = to_int(arrayData[3]); 
         int subtotal = hargaCheckout * jumlahBarang; 
         totalHarga += subtotal; 
     }
     keranjang.close();

     if (uang < totalHarga) {
          selisih = totalHarga - uang;
          cout << "Uang Anda Kurang " << Rupiah(selisih) << endl;
          cout << "Masukkan Uang Tambahan: ";
          cin >> kurang;
          cin.ignore();
          uang += kurang;
          while (uang < totalHarga) {
               cout << "Masih kurang. Silakan bayar dengan cukup." << endl;
               cout << "Masukkan uang kembali: ";
               cin >> uang;
               cin.ignore();
               uang += kurang;
           }
      }
  
      if (uang > totalHarga) {
          selisih = uang - totalHarga;
          cout << "Kembalian Anda: " << Rupiah(selisih) << endl;
      } else if (uang == totalHarga) {
          cout << "Uang Anda pas." << endl;
          uangPas = true;
      }
  
   inputStruk();
}
void Transaksi::inputStruk(){
     char pilihanStruk;
     int noStruk = 0;
     cout << "Mau Cetak Struk Atau Ngga ? (y/n)";
     cin.ignore();
     cin >> pilihanStruk;
     pilihanStruk = tolower(pilihanStruk);
     
     if (pilihanStruk == 'y')
     {
          noStruk++;
          struk();
     }else if(pilihanStruk == 'n')
     {
          cout << "Terima Kasih Telah Berbelanja";
               
        ofstream kosongkan("keranjang.txt", ios::trunc);
       kosongkan.close();
          tampilkan();
     }
}
void Transaksi::struk(){
     string nama,kode,harga,jlh;
     int totalHarga = 0;
     int noStruk = 00234;
     cout << "Masukan Nama Pegawai : \n";
     cin >> nama;
     
     loading();
     time_t now = time(0);           
     tm *ltm = localtime(&now);      // Konversi ke local time
     stringstream ss;
     ss << 1900 + ltm->tm_year << "/"
     << 1 + ltm->tm_mon << "/"
     << ltm->tm_mday;
     string tanggal = ss.str();

     ofstream nota("struk.txt");
     nota << "========================================\n";
     nota << "           TOKO SERBA ADA AHTONG        \n";
     nota << "       Jl. Pembangunan No.123 Medan     \n";
     nota << "           Telp. (62) 8227211872        \n";
     nota << "========================================\n";
     nota << "Kasir : "+ nama +"           "<<right<<" Tgl: "+tanggal+" \n";
     nota << "Struk : " << noStruk << endl;
     nota << "----------------------------------------\n";
     nota << left << setw(5)  << "No"
          << setw(14) << "Nama Barang"
          << setw(5)  << "Qty"
          << setw(7)  << "Harga"
          << setw(10) << "Subtotal" << endl;
     nota << "----------------------------------------\n";
 
     ifstream keranjang("keranjang.txt");
     int no = 1;
     while (getline(keranjang, container)) {
         stringstream obj(container);
         getline(obj, kode, '|');
         getline(obj, nama, '|');
         getline(obj, harga, '|');
         getline(obj, jlh, '|');
          
          int jlhStruk = to_int(jlh) ;
          int hargaStruk = to_int(harga);
          int subtotal2;
          subtotal2 = jlhStruk * hargaStruk; 
          totalHarga += subtotal2;
          
          nota << left << setw(5)  << no++
          << setw(14) << nama
          <<left<< setw(3)  << jlh
          <<right << setw(7)  << Rupiah(hargaStruk)
          <<right << setw(9) << Rupiah(subtotal2) << endl;
     }
 
     nota << "----------------------------------------\n";
     nota << right << setw(29) << "Total: Rp" << setw(9) << Rupiah(totalHarga) << endl;
     nota << right << setw(29) << "Uang : Rp" << setw(9) << Rupiah(uang) << endl;
     if (uangPas == true)
     {
          nota << right << setw(29) << "Kembalian : "<< setw(9) <<"0" << endl;
     }else if (uangPas == false)
     {
          nota << right << setw(29) << "Kembalian : " << setw(9) << selisih << endl;
     }
     nota << "========================================\n";
     nota << "Terima kasih telah berbelanja di Ahtong\n";
     nota << "========================================\n";
 
     keranjang.close();
     nota.close();
     
     system("start struk.txt");
     
     ofstream kosongkan("keranjang.txt", ios::trunc);
     kosongkan.close();
     
 }
 void Transaksi::loading() {
    const int total = 50;

    cout << "Memproses transaksi.";
    for (int i = 0; i < total; ++i) {
        cout << ".";
        cout.flush(); 
        Sleep(100);   
    }
    cout << "Selesai!" << endl;
}