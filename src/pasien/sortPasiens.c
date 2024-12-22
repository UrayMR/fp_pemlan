#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

void bubbleSort(Pasien arr[], int n, int choice, int ascending)
{
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      int compare = 0;
      if (choice == 1)
        compare = arr[j].idPasien > arr[j + 1].idPasien;
      else if (choice == 2)
        compare = strcmp(arr[j].namaPasien, arr[j + 1].namaPasien) > 0;
      else if (choice == 3)
        compare = arr[j].umur > arr[j + 1].umur;
      else if (choice == 4)
        compare = arr[j].idKamar > arr[j + 1].idKamar;

      if ((ascending && compare) || (!ascending && !compare))
      {
        Pasien temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void selectionSort(Pasien arr[], int n, int choice, int ascending)
{
  for (int i = 0; i < n - 1; i++)
  {
    int minIdx = i;
    for (int j = i + 1; j < n; j++)
    {
      int compare = 0;
      if (choice == 1)
        compare = arr[j].idPasien < arr[minIdx].idPasien;
      else if (choice == 2)
        compare = strcmp(arr[j].namaPasien, arr[minIdx].namaPasien) < 0;
      else if (choice == 3)
        compare = arr[j].umur < arr[minIdx].umur;
      else if (choice == 4)
        compare = arr[j].idKamar < arr[minIdx].idKamar;

      if ((ascending && compare) || (!ascending && !compare))
      {
        minIdx = j;
      }
    }
    Pasien temp = arr[minIdx];
    arr[minIdx] = arr[i];
    arr[i] = temp;
  }
}

void insertionSort(Pasien arr[], int n, int choice, int ascending)
{
  for (int i = 1; i < n; i++)
  {
    Pasien key = arr[i];
    int j = i - 1;
    int compare = 0;
    while (j >= 0)
    {
      if (choice == 1)
        compare = arr[j].idPasien > key.idPasien;
      else if (choice == 2)
        compare = strcmp(arr[j].namaPasien, key.namaPasien) > 0;
      else if (choice == 3)
        compare = arr[j].umur > key.umur;
      else if (choice == 4)
        compare = arr[j].idKamar > key.idKamar;

      if ((ascending && compare) || (!ascending && !compare))
      {
        arr[j + 1] = arr[j];
        j--;
      }
      else
      {
        break;
      }
    }
    arr[j + 1] = key;
  }
}

void sortPasiens()
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

  int choice, order, method;
  while (1)
  {
    printf("\n--- Pilih Kolom Sort ---\n");
    printf("1. ID\n");
    printf("2. Nama\n");
    printf("3. Usia\n");
    printf("4. ID Kamar\n");
    printf("Pilih kolom: ");
    if (scanf("%d", &choice) == 1 && (choice >= 1 && choice <= 4))
      break;
    else
      printf("Input tidak valid. Silakan coba lagi.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
  }

  while (order < 1 || order > 2)
  {
    printf("1. Ascending\n");
    printf("2. Descending\n");
    printf("Pilih urutan: ");
    if (scanf("%d", &order) != 1 || (order < 1 || order > 2))
      printf("Input tidak valid. Silakan coba lagi.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
  }

  while (method < 1 || method > 3)
  {
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("Pilih algoritma: ");
    if (scanf("%d", &method) != 1 || (method < 1 || method > 3))
      printf("Input tidak valid. Silakan coba lagi.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
  }

  int ascending = (order == 1);
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  if (method == 1)
    bubbleSort(pasiens, count, choice, ascending);
  else if (method == 2)
    selectionSort(pasiens, count, choice, ascending);
  else if (method == 3)
    insertionSort(pasiens, count, choice, ascending);
  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("\n--- Data Pasien Setelah Sorting ---\n");
  printf("%-3s | %-15s | %-4s | %-8s\n", "ID", "Nama", "Usia", "ID Kamar");
  for (int i = 0; i < count; i++)
  {
    printf("%-3d | %-15s | %-4d | %-8d\n", pasiens[i].idPasien, pasiens[i].namaPasien, pasiens[i].umur, pasiens[i].idKamar);
  }

  printf("\nWaktu eksekusi sorting: %f detik\n", cpu_time_used);

  free(pasiens);
}