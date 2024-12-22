#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

// fungsi sequential search
int sequentialSearchPasien(Pasien pasiens[], int count, int key)
{
  for (int i = 0; i < count; i++)
  {
    if (pasiens[i].idPasien == key)
      return i;
  }
  return -1;
}

// Fungsi jump search
int jumpSearchPasien(Pasien pasiens[], int count, int key)
{
  // Untuk array kecil menggunakan sequential search karena lebih cepat
  if (count <= 3)
  {
    for (int i = 0; i < count; i++)
    {
      if (pasiens[i].idPasien == key)
        return i;
    }
    return -1;
  }

  // Menginisiasi loncatan
  int step = (int)sqrt(count);
  int prev = 0;

  // Jumping ke blok yang benar hingga menemukan blok yang lebih besar dari key
  while (prev < count && pasiens[min(step, count - 1)].idPasien < key)
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
  while (prev >= 0 && prev < count)
  {
    if (pasiens[prev].idPasien == key)
      return prev;
    if (pasiens[prev].idPasien > key)
      break;
    prev++;
  }

  return -1;
}

// Fungsi untuk mengurutkan data pasien dengan metode insertion sort sebelum melakukan jump search
void helperSortPasien(Pasien arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    Pasien key = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j].idPasien > key.idPasien)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

// Fungsi untuk mencari pasien
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
    // realokasi memori untuk menambahkan data pasien
    pasiens = realloc(pasiens, (count + 1) * sizeof(Pasien));

    // membaca data pasien dari file
    if (fscanf(file, "%d,%49[^\n,],%d,%99[^\n,],%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, pasiens[count].penyakit, &pasiens[count].idKamar) == EOF)
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

  // Mengurutkan data jika menggunakan jump search
  if (method == 2)
  {
    printf("Mengurutkan data...\n");
    helperSortPasien(pasiens, count);
    printf("Data telah diurutkan.\n");

    // Mengecek apakah data sudah terurut dengan benar
    for (int i = 0; i < count - 1; i++)
    {
      if (pasiens[i].idPasien > pasiens[i + 1].idPasien)
      {
        printf("Warning: Data tidak tersortir dengan benar!\n");
        free(pasiens);
        return;
      }
    }
  }

  // Menghitung waktu eksekusi pencarian
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