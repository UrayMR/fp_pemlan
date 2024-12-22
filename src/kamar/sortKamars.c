#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

// Fungsi untuk melakukan bubble sort pada data kamar
void bubbleSortKamar(Kamar kamars[], int count, int choice, int ascending)
{
  for (int i = 0; i < count - 1; i++)
  {
    for (int j = 0; j < count - i - 1; j++)
    {
      int compare = 0;
      if (choice == 1)
        compare = kamars[j].idKamar > kamars[j + 1].idKamar;
      else if (choice == 2)
        compare = kamars[j].tipeKamar > kamars[j + 1].tipeKamar;
      else if (choice == 3)
        compare = kamars[j].countPasien > kamars[j + 1].countPasien;
      else if (choice == 4)
        compare = kamars[j].maxPasien > kamars[j + 1].maxPasien;

      if ((ascending && compare) || (!ascending && !compare))
      {
        Kamar temp = kamars[j];
        kamars[j] = kamars[j + 1];
        kamars[j + 1] = temp;
      }
    }
  }
}

// Fungsi untuk melakukan insertion sort pada data kamar
void insertionSortKamar(Kamar kamars[], int count, int choice, int ascending)
{
  for (int i = 1; i < count; i++)
  {
    Kamar key = kamars[i];
    int j = i - 1;
    int compare = 0;
    while (j >= 0)
    {
      if (choice == 1)
        compare = kamars[j].idKamar > key.idKamar;
      else if (choice == 2)
        compare = kamars[j].tipeKamar > key.tipeKamar;
      else if (choice == 3)
        compare = kamars[j].countPasien > key.countPasien;
      else if (choice == 4)
        compare = kamars[j].maxPasien > key.maxPasien;

      if ((ascending && compare) || (!ascending && !compare))
      {
        kamars[j + 1] = kamars[j];
        j--;
      }
      else
      {
        break;
      }
    }
    kamars[j + 1] = key;
  }
}

// Fungsi untuk melakukan selection sort pada data kamar
void selectionSortKamar(Kamar kamars[], int count, int choice, int ascending)
{
  for (int i = 0; i < count - 1; i++)
  {
    int minIdx = i;
    for (int j = i + 1; j < count; j++)
    {
      int compare = 0;
      if (choice == 1)
        compare = kamars[j].idKamar < kamars[minIdx].idKamar;
      else if (choice == 2)
        compare = kamars[j].tipeKamar < kamars[minIdx].tipeKamar;
      else if (choice == 3)
        compare = kamars[j].countPasien < kamars[minIdx].countPasien;
      else if (choice == 4)
        compare = kamars[j].maxPasien < kamars[minIdx].maxPasien;

      if ((ascending && compare) || (!ascending && !compare))
      {
        minIdx = j;
      }
    }
    Kamar temp = kamars[minIdx];
    kamars[minIdx] = kamars[i];
    kamars[i] = temp;
  }
}

// Fungsi sort kamar
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

  int choice, order = 0, algorithm = 0;
  while (1)
  {
    printf("\n--- Pilih Opsi Sort ---\n");
    printf("1. Sort berdasarkan ID\n");
    printf("2. Sort berdasarkan Tipe Kamar\n");
    printf("3. Sort berdasarkan Jumlah Pasien\n");
    printf("4. Sort berdasarkan Kapasitas Maksimum\n");
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

  while (algorithm < 1 || algorithm > 3)
  {
    printf("1. Bubble Sort\n");
    printf("2. Insertion Sort\n");
    printf("3. Selection Sort\n");
    printf("Pilih algoritma: ");
    if (scanf("%d", &algorithm) != 1 || (algorithm < 1 || algorithm > 3))
      printf("Input tidak valid. Silakan coba lagi.\n");
    while (getchar() != '\n')
      ; // Clear input buffer
  }

  // Ascending jika order = 1, descending jika order = 2
  int ascending = (order == 1);

  // Inisiai waktu eksekusi untuk sorting
  clock_t start, end;
  double cpu_time_used;

  start = clock();
  if (algorithm == 1)
    bubbleSortKamar(kamars, count, choice, ascending);
  else if (algorithm == 2)
    insertionSortKamar(kamars, count, choice, ascending);
  else if (algorithm == 3)
    selectionSortKamar(kamars, count, choice, ascending);
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("\n--- Data Kamar Setelah Sorting ---\n");
  printf("%-3s | %-10s | %-10s\n", "ID", "Tipe Kamar", "Kapasitas");
  for (int i = 0; i < count; i++)
  {
    printf("%-3d | %-10d | %-3d / %-3d\n", kamars[i].idKamar, kamars[i].tipeKamar, kamars[i].countPasien, kamars[i].maxPasien);
  }
  printf("Waktu eksekusi: %f detik\n", cpu_time_used);
}
