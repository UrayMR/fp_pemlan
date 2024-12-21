#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"
#define MAX_PASIEN 100

void searchPasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  int id, found = 0;
  Pasien pasien;

  printf("Masukkan ID Pasien yang ingin dicari: ");
  scanf("%d", &id);

  while (fscanf(file, "%d,%s,%d,%d\n", &pasien.idPasien, pasien.namaPasien, &pasien.umur, &pasien.idKamar) != EOF)
  {
    if (pasien.idPasien == id)
    {
      printf("Pasien sudah ditemukan✅!\n");
      printf("ID Pasien: %s\n", pasien.idPasien);
      printf("Nama: %s\n", pasien.namaPasien);
      printf("Usia: %d\n", pasien.umur);
      printf("Penyakit: %s\n", pasien.penyakit);
      printf("ID Kamar: %d\n", pasien.idKamar);
      found = 1;
      break;
    }
  }
  fclose(file);

  if (!found)
  {
    printf("Pasien dengan ID %d tidak ditemukan🤦.\n", id);
  }
}