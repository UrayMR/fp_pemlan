#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

int isDuplicatePasienId(int id)
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("Gagal membuka file!\n");
    return 0;
  }

  Pasien pasien;
  while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasien.idPasien, pasien.namaPasien, &pasien.umur, &pasien.idKamar) != EOF)
  {
    if (pasien.idPasien == id)
    {
      fclose(file);
      return 1;
    }
  }
  fclose(file);
  return 0;
}