#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

int sequentialSearchPasien(Pasien pasiens[], int count, int key)
{
  for (int i = 0; i < count; i++)
  {
    if (pasiens[i].idPasien == key)
      return i;
  }
  return -1;
}

int jumpSearchPasien(Pasien pasiens[], int count, int key)
{
  int step = sqrt(count);
  int prev = 0;

  while (pasiens[step].idPasien < key)
  {
    prev = step;
    step += sqrt(count);
    if (step >= count)
      return -1;
  }

  for (int i = prev; i < step; i++)
  {
    if (pasiens[i].idPasien == key)
      return i;
  }
  return -1;
}

void searchPasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Pasien *pasiens = NULL;
  int count = 0;

  while (1)
  {
    pasiens = realloc(pasiens, (count + 1) * sizeof(Pasien));
    if (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, &pasiens[count].idKamar) == EOF)
      break;
    count++;
  }
  fclose(file);

  if (count == 0)
  {
    printf("Tidak ada data pasien yang tersedia!\n");
    free(pasiens);
    return;
  }

  int method, keyInt;

  printf("Masukkan ID Pasien yang ingin dicari: ");
  scanf("%d", &keyInt);

  while (1)
  {
    printf("\n--- Pilih Metode Pencarian ---\n");
    printf("1. Sequential Search\n");
    printf("2. Jump Search\n");
    printf("Pilih metode: ");
    if (scanf("%d", &method) == 1 && (method == 1 || method == 2))
      break;
    else
      printf("Input tidak valid. Silakan coba lagi.\n");
    while (getchar() != '\n')
      ;
  }

  clock_t start, end;
  double cpu_time_used;
  int index = -1;

  start = clock();
  if (method == 1)
    index = sequentialSearchPasien(pasiens, count, keyInt);
  else if (method == 2)
    index = jumpSearchPasien(pasiens, count, keyInt);
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  if (index != -1)
  {
    printf("Pasien ditemukan!\n");
    printf("ID Pasien: %d\n", pasiens[index].idPasien);
    printf("Nama: %s\n", pasiens[index].namaPasien);
    printf("Usia: %d\n", pasiens[index].umur);
    printf("Penyakit: %s\n", pasiens[index].penyakit);
    printf("ID Kamar: %d\n", pasiens[index].idKamar);
  }
  else
  {
    printf("Pasien tidak ditemukan!\n");
  }

  printf("Waktu eksekusi: %f detik\n", cpu_time_used);

  free(pasiens);
}