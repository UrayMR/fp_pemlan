#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"
#include "model/kamar.h"

#define FILE_NAME "pasien.csv"

void createPasien()
{
  FILE *file = fopen(FILE_NAME, "a");
  if (!file)
  {
    printf("Gagal membuka file!\n");
    return;
  }

  Pasien pasien;

  displayKamars();

  printf("Masukkan ID Kamar: ");
  scanf("%d", &pasien.idKamar);

  printf("\nMasukkan ID Pasien: ");
  scanf("%d", &pasien.idPasien);

  if (isDuplicatePasienId(pasien.idPasien))
  {
    printf("ID Pasien sudah ada!\n");
    fclose(file);
    return;
  }

  printf("Masukkan Nama Pasien: ");
  scanf(" %49[^\n]", pasien.namaPasien);
  printf("Masukkan Usia: ");
  scanf("%d", &pasien.umur);

  fprintf(file, "%d,%s,%d,%d\n", pasien.idPasien, pasien.namaPasien, pasien.umur, pasien.idKamar);
  printf("Pasien %s berhasil ditambahkan!\n", pasien.namaPasien);
  fclose(file);
}