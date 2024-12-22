#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

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
    printf("6. Urutkan Pasien\n");
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
    case 6:
      sortPasiens();
      break;
    case 0:
      printf("Kembali ke menu utama...\n");
      break;
    default:
      printf("Pilihan tidak valid!\n");
    }
  } while (choice != 0);
}