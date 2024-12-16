#ifndef KAMAR_H
#define KAMAR_H

typedef struct
{
  int idKamar;
  int tipeKamar;   // 0 untuk belum dapat kamar, 1 untuk kamar biasa, 2 untuk kamar VIP
  int countPasien; // Banyaknya pasien
  int maxPasien;   // Maksimal pasien
} Kamar;

void kamarMenu();
void createKamar();
void displayKamars();
void updateKamar();
void deleteKamar();
void searchKamar();
void sortKamars();

#endif
