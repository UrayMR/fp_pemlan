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

#endif
