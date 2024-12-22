#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"
#include "model/kamar.h"

#define FILE_NAME "pasien.csv"
#define KAMAR_FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void deletePasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  Pasien *pasiens = NULL;
  Kamar kamars[MAX_KAMAR];
  int count = 0;
  int kamarCount = 0;
  int id;
  int found = 0;
  int deletedKamarId = -1;

  // Read all pasien data
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

  printf("Masukkan ID Pasien yang ingin dihapus: ");
  scanf("%d", &id);

  // Read all kamar data
  FILE *kamarFile = fopen(KAMAR_FILE_NAME, "r");
  if (!kamarFile)
  {
    printf("Gagal membuka file kamar!\n");
    free(pasiens);
    return;
  }

  while (fscanf(kamarFile, "%d,%d,%d,%d\n",
                &kamars[kamarCount].idKamar,
                &kamars[kamarCount].tipeKamar,
                &kamars[kamarCount].countPasien,
                &kamars[kamarCount].maxPasien) != EOF)
  {
    kamarCount++;
  }
  fclose(kamarFile);

  // Delete pasien and get kamar ID
  file = fopen(FILE_NAME, "w");
  for (int i = 0; i < count; i++)
  {
    if (pasiens[i].idPasien != id)
    {
      fprintf(file, "%d,%s,%d,%s,%d\n",
              pasiens[i].idPasien,
              pasiens[i].namaPasien,
              pasiens[i].umur,
              pasiens[i].penyakit,
              pasiens[i].idKamar);
    }
    else
    {
      found = 1;
      deletedKamarId = pasiens[i].idKamar;
    }
  }
  fclose(file);

  // Update kamar count if pasien found
  if (found)
  {
    // Find and update kamar
    for (int i = 0; i < kamarCount; i++)
    {
      if (kamars[i].idKamar == deletedKamarId)
      {
        kamars[i].countPasien--;
        break;
      }
    }

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

    printf("Pasien dengan ID %d berhasil dihapus!\n", id);
  }
  else
  {
    printf("Pasien dengan ID %d tidak ditemukan!\n", id);
  }

  free(pasiens);
}