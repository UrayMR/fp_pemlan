#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    int roomNumber;
    char name[25];
    int age;
    char illness[100];
} Patient;

Patient patients[MAX_PATIENTS];
int patientCount = 0;

void addPatient() {
    if (patientCount >= MAX_PATIENTS) {
        printf("Kapasitas pasien penuh!\n");
        return;
    }

    printf("Masukkan nomor kamar: ");
    scanf("%d", &patients[patientCount].roomNumber);
    getchar(); // Membersihkan buffer input

    printf("Masukkan nama pasien: ");
    fgets(patients[patientCount].name, 25, stdin);
    strtok(patients[patientCount].name, "\n"); // Menghapus newline

    printf("Masukkan usia pasien: ");
    scanf("%d", &patients[patientCount].age);
    getchar(); // Membersihkan buffer input

    printf("Masukkan penyakit pasien: ");
    fgets(patients[patientCount].illness, 100, stdin);
    strtok(patients[patientCount].illness, "\n"); // Menghapus newline

    patientCount++;
    printf("Data pasien berhasil ditambahkan!\n");
}

void displayPatients() {
    if (patientCount == 0) {
        printf("Belum ada pasien yang terdaftar.\n");
        return;
    }

    printf("Daftar Pasien:\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < patientCount; i++) {
        printf("Kamar %d: %s, Usia %d, Penyakit: %s\n",
               patients[i].roomNumber,
               patients[i].name,
               patients[i].age,
               patients[i].illness);
    }
    printf("----------------------------------------------------\n");
}

void searchPatient() {
    int roomNumber;
    printf("Masukkan nomor kamar yang ingin dicari: ");
    scanf("%d", &roomNumber);

    for (int i = 0; i < patientCount; i++) {
        if (patients[i].roomNumber == roomNumber) {
            printf("Pasien sudah ditemukan✅!n");
            printf("Nama: %s\n", patients[i].name);
            printf("Usia: %d\n", patients[i].age);
            printf("Penyakit: %s\n", patients[i].illness);
            return;
        }
    }
    printf("Pasien dengan nomor kamar %d tidak ditemukan🤦.\n", roomNumber);
}

void showMenu() {
    printf("Menu Rumah Sakit kelompok 1:\n");
    printf("1. Silahkan tambah Data Pasien\n");
    printf("2. Tampilkan Semua Pasien\n");
    printf("3. Cari Pasien Berdasarkan Nomor Kamar\n");
    printf("4. Keluar\n");
    printf("Pilih menu: ");
}

int main() {
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);
        getchar(); // Membersihkan buffer input

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                displayPatients();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                printf("Terimakasih telah menggunakan sistem rumah sakit kami 😊😊.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba kembali 👌.\n");
        }
    } while (choice != 4);

    return 0;
}
