#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"

#define FILE_NAME "pasien.csv"

// Fungsi untuk mengecek apakah id pasien sudah ada atau belum
int isDuplicatePasienId(int id)
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("Gagal membuka file!\n");
    return 0;
  }

  Pasien pasien;
  // Membaca file baris per baris
  while (fscanf(file, "%d,%s,%d,%s,%d\n", &pasien.idPasien, pasien.namaPasien, &pasien.umur, pasien.penyakit, &pasien.idKamar) != EOF)
  {
    // Jika id pasien sudah ada, return 1
    if (pasien.idPasien == id)
    {
      fclose(file);
      return 1;
    }
  }
  fclose(file);
  return 0;
}