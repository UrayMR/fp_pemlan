#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"
#define MAX_PASIEN 100

void deletePasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Pasien pasiens[MAX_PASIEN];
  int count = 0;
  int id;
  int found = 0;

  while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, &pasiens[count].idKamar) != EOF)
  {
    count++;
  }
  fclose(file);

  printf("Masukkan ID Pasien yang ingin dihapus: ");
  scanf("%d", &id);

  file = fopen(FILE_NAME, "w");
  for (int i = 0; i < count; i++)
  {
    if (pasiens[i].idPasien != id)
    {
      fprintf(file, "%d,%s,%d,%d\n", pasiens[i].idPasien, pasiens[i].namaPasien, pasiens[i].umur, pasiens[i].idKamar);
    }
    else
    {
      found = 1;
    }
  }
  fclose(file);

  if (found)
  {
    printf("Pasien dengan ID %d berhasil dihapus!\n", id);
  }
  else
  {
    printf("Pasien dengan ID %d tidak ditemukan!\n", id);
  }
}