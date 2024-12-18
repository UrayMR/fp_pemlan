#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "pasien.csv"
#define MAX_PASIEN 100

typedef struct {
    int idPasien;
    char nama[50];
    int usia;
    int idKamar;
} Pasien;

int main() {
    pasienMenu();
    return 0;
}

void pasienMenu() {
    int choice;
    do {
        printf("\n-------------------\n");
        printf("--- Pasien Menu ---\n");
        printf("-------------------\n");
        printf("1. Tambah Pasien\n");
        printf("2. Tampilkan Semua Pasien\n");
        printf("3. Update Pasien\n");
        printf("0. Kembali\n");
        printf("Pilih: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            createPasien();
            break;
        case 2:
            displayPasiens();
            break;
        case 3:
            updatePasien();
            break;
        case 0:
            printf("Kembali ke menu utama...\n");
            break;
        default:
            printf("Pilihan tidak valid!\n");
        }
    } while (choice != 0);
}

void createPasien() {
    FILE *file = fopen(FILE_NAME, "a");
    if (!file) {
        printf("Gagal membuka file!\n");
        return;
    }

    Pasien pasien;
    printf("Masukkan ID Pasien: ");
    scanf("%d", &pasien.idPasien);
    printf("Masukkan Nama Pasien: ");
    scanf(" %49[^\n]", pasien.nama);
    printf("Masukkan Usia: ");
    scanf("%d", &pasien.usia);
    printf("Masukkan ID Kamar: ");
    scanf("%d", &pasien.idKamar);

    fprintf(file, "%d,%s,%d,%d\n", pasien.idPasien, pasien.nama, pasien.usia, pasien.idKamar);
    printf("Pasien %s berhasil ditambahkan!\n", pasien.nama);
    fclose(file);
}

void displayPasiens() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("File kosong atau tidak ditemukan.\n");
        return;
    }

    Pasien pasien;
    printf("\n--- Daftar Pasien ---\n");
    printf("ID | Nama           | Usia | ID Kamar\n");
    while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasien.idPasien, pasien.nama, &pasien.usia, &pasien.idKamar) != EOF) {
        printf("%d | %-15s | %d | %d\n", pasien.idPasien, pasien.nama, pasien.usia, pasien.idKamar);
    }
    fclose(file);
}

void updatePasien() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("File tidak ditemukan!\n");
        return;
    }

    Pasien pasiens[MAX_PASIEN];
    int count = 0;
    int id, found = 0;

    while (fscanf(file, "%d,%49[^\n,],%d,%d\n", &pasiens[count].idPasien, pasiens[count].nama, &pasiens[count].usia, &pasiens[count].idKamar) != EOF) {
        count++;
    }
    fclose(file);

    printf("Masukkan ID Pasien yang ingin diupdate: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (pasiens[i].idPasien == id) {
            printf("Masukkan Nama Baru: ");
            scanf(" %49[^\n]", pasiens[i].nama);
            printf("Masukkan Usia Baru: ");
            scanf("%d", &pasiens[i].usia);
            printf("Masukkan ID Kamar Baru: ");
            scanf("%d", &pasiens[i].idKamar);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Pasien dengan ID %d tidak ditemukan!\n", id);
        return;
    }

    file = fopen(FILE_NAME, "w");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d,%d\n", pasiens[i].idPasien, pasiens[i].nama, pasiens[i].usia, pasiens[i].idKamar);
    }
    fclose(file);

    printf("Pasien %d berhasil diupdate!\n", id);

    return 0;
}