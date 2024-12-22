#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/kamar.h"

#define FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

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

  // Melakukan cek duplikat ID Kamar
  if (isDuplicateKamarId(kamar.idKamar))
  {
    printf("ID Kamar sudah ada!\n");
    fclose(file);
    return;
  }

  printf("Masukkan Tipe Kamar (1: Standard, 2: VIP):");
  scanf(" %d", &kamar.tipeKamar);
  printf("Masukkan Kapasitas: ");
  scanf("%d", &kamar.maxPasien);

  kamar.countPasien = 0; // Default

  fprintf(file, "%d,%d,%d,%d\n", kamar.idKamar, kamar.tipeKamar, kamar.countPasien, kamar.maxPasien);
  printf("Kamar %d - %d berhasil ditambahkan!\n", kamar.idKamar, kamar.tipeKamar);
  fclose(file);
}
