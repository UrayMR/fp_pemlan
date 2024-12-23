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

  // Inisiasi array kamars dengan MAX_KAMAR
  Kamar kamars[MAX_KAMAR];
  int count = 0;
  int id;
  int found = 0;

  // Membaca file kamars.csv dan menyimpannya ke array kamars
  while (fscanf(file, "%d,%d,%d,%d\n", &kamars[count].idKamar, &kamars[count].tipeKamar, &kamars[count].countPasien, &kamars[count].maxPasien) != EOF)
  {
    count++;
  }
  fclose(file);

  printf("Masukkan ID Kamar yang ingin dihapus: ");
  scanf("%d", &id);

  // Mengecek apakah kamar yang ingin dihapus memiliki pasien
  for (int i = 0; i < count; i++)
  {
    if (kamars[i].idKamar == id && kamars[i].countPasien > 0)
    {
      printf("Kamar dengan ID %d masih memiliki pasien. Silakan pindahkan pasien terlebih dahulu.\n", id);
      return;
    }
  }

  // Menghapus kamar dengan ID yang diinput
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
