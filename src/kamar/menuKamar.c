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
