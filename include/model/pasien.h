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

int compareByIdAsc(Pasien a, Pasien b);
int compareByIdDesc(Pasien a, Pasien b);
int compareByNameAsc(Pasien a, Pasien b);
int compareByNameDesc(Pasien a, Pasien b);
int compareByAgeAsc(Pasien a, Pasien b);
int compareByAgeDesc(Pasien a, Pasien b);
int compareByRoomIdAsc(Pasien a, Pasien b);
int compareByRoomIdDesc(Pasien a, Pasien b);

void bubbleSort(Pasien arr[], int n, int (*compare)(Pasien, Pasien));
void selectionSort(Pasien arr[], int n, int (*compare)(Pasien, Pasien));
void insertionSort(Pasien arr[], int n, int (*compare)(Pasien, Pasien));

#endif
