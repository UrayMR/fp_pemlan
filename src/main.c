#include <stdio.h>
#include "model/kamar.h"

int main()
{
  int choice;

  do
  {
    printf("\n--- Menu Utama ---\n");
    printf("1. Menu Kamar\n");
    printf("0. Keluar\n");
    printf("Pilih: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      kamarMenu();
      break;
    case 0:
      printf("Keluar dari program...\n");
      break;
    default:
      printf("Pilihan tidak valid!\n");
    }
  } while (choice != 0);

  return 0;
}
