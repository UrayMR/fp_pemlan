#ifndef KAMAR_H
#define KAMAR_H

// Inisiasi struktur data Kamar
typedef struct
{
  int idKamar;
  int tipeKamar;   // 1 untuk kamar biasa, 2 untuk kamar VIP
  int countPasien; // Banyaknya pasien
  int maxPasien;   // Maksimal pasien
} Kamar;

// Deklarasi fungsi-fungsi yang akan digunakan agar bisa dipanggil di file lain
int min(int a, int b);

void kamarMenu();
void createKamar();
void displayKamars();
void updateKamar();
void deleteKamar();
void searchKamar();
void sortKamars();
int isDuplicateKamarId(int id);

void bubbleSortKamar(Kamar kamars[], int count, int choice, int ascending);
void insertionSortKamar(Kamar kamars[], int count, int choice, int ascending);
void selectionSortKamar(Kamar kamars[], int count, int choice, int ascending);

int sequentialSearchKamar(Kamar kamars[], int count, int key);
int jumpSearchKamar(Kamar kamars[], int count, int key);
void helperSortKamar(Kamar arr[], int n);

#endif
