#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

int isDuplicateKamarId(int id)
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("Gagal membuka file!\n");
    return 0;
  }

  Kamar kamar;
  // Membaca file baris per baris
  while (fscanf(file, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
  {
    // Jika id kamar sudah ada, return 1
    if (kamar.idKamar == id)
    {
      fclose(file);
      return 1;
    }
  }
  fclose(file);
  return 0;
}
