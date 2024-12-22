#ifndef PATIENT_H
#define PATIENT_H

typedef struct
{
  int idPasien;
  char namaPasien[50];
  int umur;
  char penyakit[100];
  int idKamar;
} Pasien;

int min(int a, int b);

void pasienMenu();
void createPasien();
void displayPasiens();
void updatePasien();
void deletePasien();
void searchPasien();
void sortPasiens();
int isDuplicatePasienId(int id);

void bubbleSortPasien(Pasien arr[], int n, int choice, int ascending);
void selectionSortPasien(Pasien arr[], int n, int choice, int ascending);
void insertionSortPasien(Pasien arr[], int n, int choice, int ascending);

int sequentialSearchPasien(Pasien pasiens[], int count, int key);
int jumpSearchPasien(Pasien pasiens[], int count, int key);
void helperSortPasien(Pasien arr[], int n);

#endif
