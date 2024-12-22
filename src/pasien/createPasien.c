#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"
#include "model/kamar.h"

#define FILE_NAME "pasien.csv"
#define KAMAR_FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void createPasien()
{
  FILE *file = fopen(FILE_NAME, "a");
  if (!file)
  {
    printf("Gagal membuka file!\n");
    return;
  }

  // Inisiasi struktur data Pasien dan Kamar karena saling berhubungan
  Pasien pasien;
  Kamar kamars[MAX_KAMAR];
  int kamarCount = 0;
  int targetIndex = -1;

  // Menampilkan kamar data dulu sebelum menambahkan pasien
  displayKamars();

  printf("Masukkan ID Kamar: ");
  scanf("%d", &pasien.idKamar);
  while (getchar() != '\n')
    ; // Clear input buffer

  FILE *kamarFile = fopen(KAMAR_FILE_NAME, "r");
  if (!kamarFile)
  {
    printf("Gagal membuka file kamar!\n");
    fclose(file);
    return;
  }

  // Read all kamar data
  while (fscanf(kamarFile, "%d,%d,%d,%d\n",
                &kamars[kamarCount].idKamar,
                &kamars[kamarCount].tipeKamar,
                &kamars[kamarCount].countPasien,
                &kamars[kamarCount].maxPasien) != EOF)
  {
    // Jika idKamar yang diinputkan ditemukan, maka simpan indexnya
    if (kamars[kamarCount].idKamar == pasien.idKamar)
    {
      targetIndex = kamarCount;
    }
    kamarCount++;
  }
  fclose(kamarFile);

  // Jika idKamar tidak ditemukan, maka keluar dari fungsi
  if (targetIndex == -1)
  {
    printf("ID Kamar tidak ditemukan!\n");
    fclose(file);
    return;
  }

  // Jika kamar sudah penuh, maka keluar dari fungsi
  if (kamars[targetIndex].countPasien >= kamars[targetIndex].maxPasien)
  {
    printf("Kamar sudah penuh!\n");
    fclose(file);
    return;
  }

  printf("\nMasukkan ID Pasien: ");
  scanf("%d", &pasien.idPasien);
  while (getchar() != '\n')
    ; // Clear input buffer

  // Cek apakah ID Pasien sudah ada
  if (isDuplicatePasienId(pasien.idPasien))
  {
    printf("ID Pasien sudah ada!\n");
    fclose(file);
    return;
  }

  printf("Masukkan Nama Pasien: ");
  scanf(" %49[^\n]", pasien.namaPasien);
  while (getchar() != '\n')
    ; // Clear input buffer
  printf("Masukkan Usia: ");
  scanf("%d", &pasien.umur);
  while (getchar() != '\n')
    ; // Clear input buffer
  printf("Masukkan Penyakit: ");
  scanf(" %99[^\n]", pasien.penyakit);
  while (getchar() != '\n')
    ; // Clear input buffer

  // Menyimpan data pasien ke file
  fprintf(file, "%d,%s,%d,%s,%d\n",
          pasien.idPasien,
          pasien.namaPasien,
          pasien.umur,
          pasien.penyakit,
          pasien.idKamar);
  fclose(file);

  // Update kamar count dengan index yang sudah disimpan
  kamars[targetIndex].countPasien++;

  // Rewrite kamar file
  kamarFile = fopen(KAMAR_FILE_NAME, "w");
  for (int i = 0; i < kamarCount; i++)
  {
    fprintf(kamarFile, "%d,%d,%d,%d\n",
            kamars[i].idKamar,
            kamars[i].tipeKamar,
            kamars[i].countPasien,
            kamars[i].maxPasien);
  }
  fclose(kamarFile);

  printf("Pasien %s berhasil ditambahkan ke Kamar %d!\n", pasien.namaPasien, pasien.idKamar);
}