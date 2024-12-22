#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void updateKamar()
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

  printf("Masukkan ID Kamar yang ingin diupdate: ");
  scanf("%d", &id);

  for (int i = 0; i < count; i++)
  {
    if (kamars[i].idKamar == id)
    {
      if (kamars[i].countPasien > 0)
      {
        printf("Kamar dengan ID %d masih memiliki pasien. Tidak boleh diupdate.\n", id);
        return;
      }
      printf("Masukkan Tipe Kamar (1: Standard, 2: VIP): ");
      scanf(" %d", &kamars[i].tipeKamar);
      printf("Masukkan Kapasitas Baru: ");
      scanf("%d", &kamars[i].maxPasien);
      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf("Kamar dengan ID %d tidak ditemukan!\n", id);
    return;
  }

  file = fopen(FILE_NAME, "w");
  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%d,%d,%d,%d\n", kamars[i].idKamar, kamars[i].tipeKamar, kamars[i].countPasien, kamars[i].maxPasien);
  }
  fclose(file);

  printf("Kamar %d berhasil diupdate!\n", id);
}
