#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void displayKamars()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File kosong atau tidak ditemukan.\n");
    return;
  }

  Kamar kamar;
  printf("\n--- Daftar Kamar ---\n");
  printf("%-3s | %-10s | %-10s\n", "ID", "Tipe Kamar", "Kapasitas");
  while (fscanf(file, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
  {
    printf("%-3d | %-10d | %-3d / %-3d\n", kamar.idKamar, kamar.tipeKamar, kamar.countPasien, kamar.maxPasien);
  }
  fclose(file);
}
