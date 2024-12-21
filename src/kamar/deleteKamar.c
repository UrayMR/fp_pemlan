#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void deleteKamar()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Kamar kamars[MAX_KAMAR];
  int count = 0;
  int id;
  int found = 0;

  while (fscanf(file, "%d,%d,%d,%d\n", &kamars[count].idKamar, &kamars[count].tipeKamar, &kamars[count].countPasien, &kamars[count].maxPasien) != EOF)
  {
    count++;
  }
  fclose(file);

  printf("Masukkan ID Kamar yang ingin dihapus: ");
  scanf("%d", &id);

  file = fopen(FILE_NAME, "w");
  for (int i = 0; i < count; i++)
  {
    if (kamars[i].idKamar != id)
    {
      fprintf(file, "%d,%d,%d,%d\n", kamars[i].idKamar, kamars[i].tipeKamar, kamars[i].countPasien, kamars[i].maxPasien);
    }
    else
    {
      found = 1;
    }
  }
  fclose(file);

  if (found)
  {
    printf("Kamar dengan ID %d berhasil dihapus!\n", id);
  }
  else
  {
    printf("Kamar dengan ID %d tidak ditemukan!\n", id);
  }
}
