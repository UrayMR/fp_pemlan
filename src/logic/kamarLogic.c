#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void kamarMenu()
{
  int choice;
  do
  {
    printf("\n------------------\n");
    printf("\n--- Kamar Menu ---\n");
    printf("\n------------------\n");
    printf("1. Tambah Kamar\n");
    printf("2. Tampilkan Semua Kamar\n");
    printf("3. Update Kamar\n");
    printf("4. Hapus Kamar\n");
    printf("5. Cari Kamar\n");
    printf("6. Urutkan Kamar\n");
    printf("0. Kembali\n");
    printf("Pilih: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      createKamar();
      break;
    case 2:
      displayKamars();
      break;
    case 3:
      updateKamar();
      break;
    case 4:
      deleteKamar();
      break;
    case 5:
      searchKamar();
      break;
    case 6:
      sortKamars();
      break;
    case 0:
      printf("Kembali ke menu utama...\n");
      break;
    default:
      printf("Pilihan tidak valid!\n");
    }
  } while (choice != 0);
}

void createKamar()
{
  FILE *file = fopen(FILE_NAME, "a");
  if (!file)
  {
    printf("Gagal membuka file!\n");
    return;
  }

  Kamar kamar;
  printf("Masukkan ID Kamar: ");
  scanf("%d", &kamar.idKamar);
  printf("Masukkan Tipe Kamar (1: Standard, 2: VIP):");
  scanf(" %d", &kamar.tipeKamar);
  printf("Masukkan Kapasitas: ");
  scanf("%d", &kamar.maxPasien);

  kamar.countPasien = 0; // Default

  fprintf(file, "%d,%d,%d,%d\n", kamar.idKamar, kamar.tipeKamar, kamar.countPasien, kamar.maxPasien);
  printf("Kamar %d - %d berhasil ditambahkan!\n", kamar.idKamar, kamar.tipeKamar);
  fclose(file);
}

void displayKamars()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File kosong atau tidak ditemukan.\n");
    return;
  }

  Kamar kamar;
  printf("\n--- Daftar Kamar ---\n");
  printf("ID | Tipe Kamar | Kapasitas\n");
  while (fscanf(file, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
  {
    printf("%d | %d | %d / %d\n", kamar.idKamar, kamar.tipeKamar, kamar.countPasien, kamar.maxPasien);
  }
  fclose(file);
}

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
      printf("Masukkan Tipe Kamar: (0: Tidak ada kamar, 1: Standard, 2: VIP)");
      scanf(" %d", &kamars[i].tipeKamar);
      printf("Masukkan Kapasitas Baru: ");
      scanf("%d", &kamars[i].maxPasien);
      kamars[i].countPasien = 0; // otomatis mengembalikan count Pasien ke 0
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

void searchKamar()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  int id, found = 0;
  Kamar kamar;

  printf("Masukkan ID Kamar yang dicari: ");
  scanf("%d", &id);

  while (fscanf(file, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
  {
    if (kamar.idKamar == id)
    {
      printf("Kamar ditemukan!\n");
      printf("Id Kamar: %d | Tipe Kamar: %d | Kapasitas: %d / %d\n", kamar.idKamar, kamar.tipeKamar, kamar.countPasien, kamar.maxPasien);
      found = 1;
      break;
    }
  }
  fclose(file);

  if (!found)
  {
    printf("Kamar tidak ditemukan!\n");
  }
}

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
