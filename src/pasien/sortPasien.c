#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"
#define MAX_PASIEN 100

void sortPasiens()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Pasien pasiens[MAX_PASIEN];
  int count = 0;

  // Membaca data pasien dari file
  while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, &pasiens[count].idKamar) != EOF)
  {
    count++;
  }
  fclose(file);

  if (count == 0)
  {
    printf("Tidak ada data pasien yang tersedia!\n");
    return;
  }

  int choice;
  printf("\n--- Pilih Opsi Sort ---\n");
  printf("1. Sort berdasarkan ID (Ascending)\n");
  printf("2. Sort berdasarkan Nama (Ascending)\n");
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
        if (pasiens[j].idPasien > pasiens[j + 1].idPasien)
        {
          Pasien temp = pasiens[j];
          pasiens[j] = pasiens[j + 1];
          pasiens[j + 1] = temp;
        }
      }
      else if (choice == 2)
      {
        // Sort berdasarkan Nama (Ascending)
        if (strcmp(pasiens[j].namaPasien, pasiens[j + 1].namaPasien) > 0)
        {
          Pasien temp = pasiens[j];
          pasiens[j] = pasiens[j + 1];
          pasiens[j + 1] = temp;
        }
      }
    }
  }

  printf("\n--- Data Pasien Setelah Sorting ---\n");
  printf("ID | Nama           | Usia | ID Kamar\n");
  for (int i = 0; i < count; i++)
  {
    printf("%d | %-15s | %d | %d\n", pasiens[i].idPasien, pasiens[i].namaPasien, pasiens[i].umur, pasiens[i].idKamar);
  }
}