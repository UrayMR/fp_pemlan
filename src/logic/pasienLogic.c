#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"
#define MAX_PASIEN 100

int pasienCount = 0;

void pasienMenu()
{
    int choice;
    do
    {
        printf("\n-------------------\n");
        printf("\n--- Pasien Menu ---\n");
        printf("\n-------------------\n");
        printf("1. Tambah Pasien\n");
        printf("2. Tampilkan Semua Pasien\n");
        printf("3. Update Pasien\n");
        printf("4. Hapus Pasien\n");
        printf("5. Cari Pasien\n"); 
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createPasien();
            break;
        case 2:
            displayPasiens();
            break;
        case 3:
            updatePasien();
            break;
        case 4:
            deletePasien();
            break;
        case 5:
            searchPasien();
            break;
        case 0:
            printf("Kembali ke menu utama...\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (choice != 0);
}

void searchPasien()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    int id, found = 0;
    Pasien pasien;

    printf("Masukkan ID Pasien yang ingin dicari: ");
    scanf("%d", &id);

    while (fscanf(file, "%d,%s,%d,%d\n", &pasien.idPasien, pasien.namaPasien, &pasien.umur, &pasien.idKamar) != EOF)
    {
        if (pasien.idPasien == id)
        {
            printf("Pasien sudah ditemukan✅!\n");
            printf("ID Pasien: %s\n", pasien.idPasien);
            printf("Nama: %s\n", pasien.namaPasien);
            printf("Usia: %d\n", pasien.umur);
            printf("Penyakit: %s\n", pasien.penyakit);
            printf("ID Kamar: %d\n", pasien.idKamar);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found)
    {
        printf("Pasien dengan ID %d tidak ditemukan🤦.\n", id);
    }
}

void createPasien()
{
    FILE *file = fopen(FILE_NAME, "a");
    if (!file)
    {
        printf("Gagal membuka file!\n");
        return;
    }

    Pasien pasien;
    printf("Masukkan ID Pasien: ");
    scanf("%d", &pasien.idPasien);
    printf("Masukkan Nama Pasien: ");
    scanf(" %49[^\n]", pasien.namaPasien);
    printf("Masukkan Usia: ");
    scanf("%d", &pasien.umur);
    printf("Masukkan ID Kamar: ");
    scanf("%d", &pasien.idKamar);

    fprintf(file, "%d,%s,%d,%d\n", pasien.idPasien, pasien.namaPasien, pasien.umur, pasien.idKamar);
    printf("Pasien %s berhasil ditambahkan!\n", pasien.namaPasien);
    fclose(file);
}

void displayPasiens()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        printf("File kosong atau tidak ditemukan.\n");
        return;
    }

    Pasien pasien;
    printf("\n--- Daftar Pasien ---\n");
    printf("ID | Nama           | Usia | ID Kamar\n");
    while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasien.idPasien, pasien.namaPasien, &pasien.umur, &pasien.idKamar) != EOF)
    {
        printf("%d | %-15s | %d | %d\n", pasien.idPasien, pasien.namaPasien, pasien.umur, pasien.idKamar);
    }
    fclose(file);
}

void updatePasien()
{
    FILE *file = fopen(FILE_NAME, "r");
    if (!file)
    {
        printf("File tidak ditemukan!\n");
        return;
    }

    Pasien pasiens[MAX_PASIEN];
    int count = 0;
    int id, found = 0;

    while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, &pasiens[count].idKamar) != EOF)
    {
        count++;
    }
    fclose(file);

    printf("Masukkan ID Pasien yang ingin diupdate: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++)
    {
        if (pasiens[i].idPasien == id)
        {
            printf("Masukkan Nama Baru: ");
            scanf(" %49[^\n]", pasiens[i].namaPasien);
            printf("Masukkan Usia Baru: ");
            scanf("%d", &pasiens[i].umur);
            printf("Masukkan ID Kamar Baru: ");
            scanf("%d", &pasiens[i].idKamar);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Pasien dengan ID %d tidak ditemukan!\n", id);
        return;
    }

    file = fopen(FILE_NAME, "w");
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%d,%s,%d,%d\n", pasiens[i].idPasien, pasiens[i].namaPasien, pasiens[i].umur, pasiens[i].idKamar);
    }
    fclose(file);

    printf("Pasien %d berhasil diupdate!\n", id);

void deletePasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Pasien pasien[MAX_PASIEN];
  int count = 0;
  int id;
  int found = 0;

  while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].namaPasien, &pasiens[count].umur, &pasiens[count].idKamar) != EOF)
  {
    count++;
  }
  fclose(file);

  printf("Masukkan ID Pasien yang ingin dihapus: ");
  scanf("%d", &id);

  file = fopen(FILE_NAME, "w");
  for (int i = 0; i < count; i++)
  {
    if (pasien[i].idPasien != id)
    {
      fprintf(tempFile, "%d,%s,%d,%d\n", pasiens[i].idPasien, pasiens[i].namaPasien, pasiens[i].umur, pasiens[i].idKamar);
    }
    else
    {
      found = 1;
    }
  }
  fclose(file);

  if (found)
  {
    printf("Pasien dengan ID %d berhasil dihapus!\n", id);
  }
  else
  {
    printf("Pasien dengan ID %d tidak ditemukan!\n", id);
  }
}
}