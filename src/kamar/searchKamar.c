#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

// Fungsi Sequential Search
int sequentialSearchKamar(Kamar kamars[], int count, int key)
{
  for (int i = 0; i < count; i++)
  {
    if (kamars[i].idKamar == key)
      return i;
  }
  return -1;
}

// Fungsi Jump Search
int jumpSearchKamar(Kamar kamars[], int count, int key)
{
  // Untuk array kecil menggunakan sequential search karena lebih cepat
  if (count <= 3)
  {
    for (int i = 0; i < count; i++)
    {
      if (kamars[i].idKamar == key)
        return i;
    }
    return -1;
  }

  // Menginisiasi loncatan
  int step = sqrt(count);
  int prev = 0;

  // Jumping ke blok yang benar hingga menemukan blok yang lebih besar dari key
  while (prev < count && kamars[min(step, count - 1)].idKamar < key)
  {
    // Update prev ke step (blok sebelumnya)
    prev = step;

    // Melakukan loncatan ke blok berikutnya hingga menemukan blok yang lebih besar dari key
    step += (int)sqrt(count);

    // Jika step lebih besar dari count, maka step diubah menjadi count - 1 agar tidak melebihi batas
    if (prev >= count)
      return -1;
  }

  // Melakukan sequential search pada blok yang benar setelah melakukan jump
  while (prev < count && kamars[prev].idKamar <= key)
  {
    if (kamars[prev].idKamar == key)
      return prev;
    if (kamars[prev].idKamar > key)
      break;
    prev++;
  }

  return -1;
}

// Fungsi untuk mengurutkan data kamar dengan metode insertion sort sebelum melakukan jump search
void helperSortKamar(Kamar arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    Kamar key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j].idKamar > key.idKamar)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

// Fungsi untuk mencari kamar
void searchKamar()
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

  int key, method;
  printf("Masukkan ID Kamar yang ingin dicari: ");
  scanf("%d", &key);

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

  // Mengurutkan data jika menggunakan jump search
  if (method == 2)
  {
    printf("Mengurutkan data...\n");
    helperSortKamar(kamars, count);
    printf("Data telah diurutkan.\n");

    // Validation check
    for (int i = 0; i < count - 1; i++)
    {
      if (kamars[i].idKamar > kamars[i + 1].idKamar)
      {
        printf("Warning: Data tidak tersortir dengan benar!\n");
        return;
      }
    }
  }

  // Melakukan perhitungan waktu eksekusi pencarian
  clock_t start, end;
  double cpu_time_used;
  int index = -1;

  start = clock();
  if (method == 1)
    index = sequentialSearchKamar(kamars, count, key);
  else if (method == 2)
    index = jumpSearchKamar(kamars, count, key);
  end = clock();

  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  if (index != -1)
  {
    printf("Kamar ditemukan!\n");
    printf("Id Kamar: %d | Tipe Kamar: %d | Kapasitas: %d / %d\n", kamars[index].idKamar, kamars[index].tipeKamar, kamars[index].countPasien, kamars[index].maxPasien);
  }
  else
  {
    printf("Kamar tidak ditemukan!\n");
  }

  printf("Waktu eksekusi: %f detik\n", cpu_time_used);
}
