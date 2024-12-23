#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model/pasien.h"
#include "model/kamar.h"

#define FILE_NAME "pasien.csv"
#define KAMAR_FILE_NAME "kamars.csv"
#define MAX_KAMAR 100

void updatePasien()
{
  FILE *file = fopen(FILE_NAME, "r");
  if (!file)
  {
    printf("File tidak ditemukan!\n");
    return;
  }

  // Inisiasi variabel pasiens dan count
  Pasien *pasiens = NULL;
  int count = 0;
  int id, found = 0;
  int oldKamarId = -1;
  int newKamarId = -1;

  while (1)
  {
    // Realokasi memori untuk pasien
    pasiens = realloc(pasiens, (count + 1) * sizeof(Pasien));

    // Membaca data pasien dari file
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
    // Jika ID pasien ditemukan
    if (pasiens[i].idPasien == id)
    {
      oldKamarId = pasiens[i].idKamar;
      printf("Masukkan Nama Baru: ");
      scanf(" %49[^\n]", pasiens[i].namaPasien);
      printf("Masukkan Usia Baru: ");
      scanf("%d", &pasiens[i].umur);
      printf("Masukkan Penyakit Baru: ");
      scanf(" %99[^\n]", pasiens[i].penyakit);

      while (1)
      {
        printf("Masukkan ID Kamar Baru: ");
        scanf("%d", &newKamarId);

        // Memanggil file kamar, karena pasien dan kamar saling bersinambungan
        FILE *kamarFile = fopen("kamars.csv", "r");
        if (!kamarFile)
        {
          printf("Gagal membuka file kamar!\n");
          free(pasiens);
          return;
        }

        Kamar kamar;
        int kamarFound = 0;

        // Jika newKamarId sama dengan oldKamarId, tidak perlu cek kapasitas
        if (newKamarId == oldKamarId)
        {
          kamarFound = 1;
          pasiens[i].idKamar = newKamarId;
        }
        else
        {
          // Membaca data kamar dari file
          while (fscanf(kamarFile, "%d,%d,%d,%d\n", &kamar.idKamar, &kamar.tipeKamar, &kamar.countPasien, &kamar.maxPasien) != EOF)
          {
            if (kamar.idKamar == newKamarId)
            {
              if (kamar.countPasien >= kamar.maxPasien)
              {
                printf("Kamar dengan ID %d sudah penuh. Silakan masukkan ID kamar lain.\n", newKamarId);
                kamarFound = 0;
              }
              else
              {
                kamarFound = 1;
                pasiens[i].idKamar = newKamarId;
              }
              break;
            }
          }
        }
        fclose(kamarFile);

        // Jika kamar tidak ditemukan maka pasien tidak bisa dipindahkan
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

  // Menulis data pasien baru ke file
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

  // Update kamar countPasien
  FILE *kamarFile = fopen(KAMAR_FILE_NAME, "r+");
  if (!kamarFile)
  {
    printf("Gagal membuka file kamar!\n");
    free(pasiens);
    return;
  }

  Kamar kamars[MAX_KAMAR];
  int kamarCount = 0;

  // Membaca data kamar dari file
  while (fscanf(kamarFile, "%d,%d,%d,%d\n", &kamars[kamarCount].idKamar, &kamars[kamarCount].tipeKamar, &kamars[kamarCount].countPasien, &kamars[kamarCount].maxPasien) != EOF)
  {
    kamarCount++;
  }

  // Update countPasien
  for (int i = 0; i < kamarCount; i++)
  {
    if (kamars[i].idKamar == oldKamarId)
    {
      kamars[i].countPasien--;
    }
    if (kamars[i].idKamar == newKamarId)
    {
      kamars[i].countPasien++;
    }
  }

  // Menulis data kamar baru ke file
  freopen(KAMAR_FILE_NAME, "w", kamarFile);
  for (int i = 0; i < kamarCount; i++)
  {
    fprintf(kamarFile, "%d,%d,%d,%d\n", kamars[i].idKamar, kamars[i].tipeKamar, kamars[i].countPasien, kamars[i].maxPasien);
  }
  fclose(kamarFile);

  printf("Pasien %d berhasil diupdate!\n", id);
  free(pasiens);
}