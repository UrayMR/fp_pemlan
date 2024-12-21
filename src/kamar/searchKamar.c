#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void searchKamar()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  int id, found = 0;
  Kamar kamar;

  printf("Masukkan ID Kamar yang dicari: ");
  scanf("%d", &id);

  while (fscanf(file, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
  {
    if (kamar.idKamar == id)
    {
      printf("Kamar ditemukan!\n");
      printf("Id Kamar: %d | Tipe Kamar: %d | Kapasitas: %d / %d\n", kamar.idKamar, kamar.tipeKamar, kamar.countPasien, kamar.maxPasien);
      found = 1;
      break;
    }
  }
  fclose(file);

  if (!found)
  {
    printf("Kamar tidak ditemukan!\n");
  }
}
