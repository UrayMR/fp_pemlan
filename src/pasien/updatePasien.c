#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"
#include "model/kamar.h"

#define FILE_NAME "pasien.csv"

void updatePasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Pasien *pasiens = NULL;
  int count = 0;
  int id, found = 0;

  while (1)
  {
    pasiens = realloc(pasiens, (count + 1) * sizeof(Pasien));
    if (fscanf(file, "%d,%49[^\n,],%d,%[^\n,],%d\n",
               &pasiens[count].idPasien,
               pasiens[count].namaPasien,
               &pasiens[count].umur,
               pasiens[count].penyakit,
               &pasiens[count].idKamar) == EOF)
      break;
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
      printf("Masukkan Penyakit Baru: ");
      scanf(" %99[^\n]", pasiens[i].penyakit);

      int newKamarId;
      while (1)
      {
        printf("Masukkan ID Kamar Baru: ");
        scanf("%d", &newKamarId);

        FILE *kamarFile = fopen("kamars.csv", "r");
        if (!kamarFile)
        {
          printf("Gagal membuka file kamar!\n");
          free(pasiens);
          return;
        }

        Kamar kamar;
        int kamarFound = 0;
        while (fscanf(kamarFile, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
        {
          if (kamar.idKamar == newKamarId)
          {
            kamarFound = 1;
            if (kamar.countPasien < kamar.maxPasien)
            {
              pasiens[i].idKamar = newKamarId;
              fclose(kamarFile);
              break;
            }
            else
            {
              printf("Kamar dengan ID %d sudah penuh. Silakan masukkan ID kamar lain.\n", newKamarId);
            }
          }
        }
        fclose(kamarFile);

        if (kamarFound && pasiens[i].idKamar == newKamarId)
        {
          break;
        }
        else if (!kamarFound)
        {
          printf("ID Kamar tidak ditemukan. Silakan masukkan ID kamar lain.\n");
        }
      }

      found = 1;
      break;
    }
  }

  if (!found)
  {
    printf("Pasien dengan ID %d tidak ditemukan!\n", id);
    free(pasiens);
    return;
  }

  file = fopen(FILE_NAME, "w");
  for (int i = 0; i < count; i++)
  {
    fprintf(file, "%d,%s,%d,%s,%d\n",
            pasiens[i].idPasien,
            pasiens[i].namaPasien,
            pasiens[i].umur,
            pasiens[i].penyakit,
            pasiens[i].idKamar);
  }
  fclose(file);

  printf("Pasien %d berhasil diupdate!\n", id);
  free(pasiens);
}