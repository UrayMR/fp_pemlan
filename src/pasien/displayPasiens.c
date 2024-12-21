#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"
#define MAX_PASIEN 100

void displayPasiens()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File kosong atau tidak ditemukan.\n");
    return;
  }

  Pasien pasien;
  printf("\n--- Daftar Pasien ---\n");
  printf("ID | Nama           | Usia | ID Kamar\n");
  while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasien.idPasien, pasien.namaPasien, &pasien.umur, &pasien.idKamar) != EOF)
  {
    printf("%d | %-15s | %d | %d\n", pasien.idPasien, pasien.namaPasien, pasien.umur, pasien.idKamar);
  }
  fclose(file);
}