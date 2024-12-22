#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

void displayPasiens()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File kosong atau tidak ditemukan.\n");
    return;
  }

  Pasien *pasiens = NULL;
  int count = 0;

  printf("\n--- Daftar Pasien ---\n");
  printf("ID  | Nama            | Usia | ID Kamar\n");
  while (1)
  {
    pasiens = realloc(pasiens, (count + 1) * sizeof(Pasien));
    if (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, &pasiens[count].idKamar) == EOF)
      break;
    printf("%-3d | %-15s | %-4d | %d\n", pasiens[count].idPasien, pasiens[count].namaPasien, pasiens[count].umur, pasiens[count].idKamar);
    count++;
  }
  fclose(file);

  free(pasiens);
}