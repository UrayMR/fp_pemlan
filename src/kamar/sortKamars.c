#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void sortKamars()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Kamar kamars[MAX_KAMAR];
  int count = 0;

  // Membaca data kamar dari file
  while (fscanf(file, "%d,%d,%d,%d\n", &kamars[count].idKamar, &kamars[count].tipeKamar, &kamars[count].countPasien, &kamars[count].maxPasien) != EOF)
  {
    count++;
  }
  fclose(file);

  if (count == 0)
  {
    printf("Tidak ada data kamar yang tersedia!\n");
    return;
  }

  int choice;
  printf("\n--- Pilih Opsi Sort ---\n");
  printf("1. Sort berdasarkan ID (Ascending)\n");
  printf("2. Sort berdasarkan Nama Kamar (Ascending)\n");
  printf("Pilih: ");
  scanf("%d", &choice);

  // Sorting menggunakan algoritma Bubble Sort sederhana
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 0; j < count - i - 1; j++)
    {
      if (choice == 1)
      {
        // Sort berdasarkan ID (Ascending)
        if (kamars[j].idKamar > kamars[j + 1].idKamar)
        {
          Kamar temp = kamars[j];
          kamars[j] = kamars[j + 1];
          kamars[j + 1] = temp;
        }
      }
      else if (choice == 2)
      {
        // Sort berdasarkan Tipe Kamar (Ascending)
        if (kamars[j].tipeKamar > kamars[j + 1].tipeKamar)
        {
          Kamar temp = kamars[j];
          kamars[j] = kamars[j + 1];
          kamars[j + 1] = temp;
        }
      }
    }
  }

  printf("\n--- Data Kamar Setelah Sorting ---\n");
  printf("ID | Tipe Kamar | Kapasitas\n");
  for (int i = 0; i < count; i++)
  {
    printf("%d | %d | %d / %d\n", kamars[i].idKamar, kamars[i].tipeKamar, kamars[i].countPasien, kamars[i].maxPasien);
  }
}
