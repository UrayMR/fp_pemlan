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

void pasienMenu();
void createPasien();
void displayPasiens();
void updatePasien();
void deletePasien();
void searchPasien();
void sortPasiens();
int isDuplicatePasienId(int id);

void bubbleSort(Pasien arr[], int n, int choice, int ascending);
void selectionSort(Pasien arr[], int n, int choice, int ascending);
void insertionSort(Pasien arr[], int n, int choice, int ascending);

#endif
