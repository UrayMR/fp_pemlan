#include <string.h>
#include "model/pasien.h"

int compareByIdAsc(Pasien a, Pasien b)
{
  return a.idPasien - b.idPasien;
}

int compareByIdDesc(Pasien a, Pasien b)
{
  return b.idPasien - a.idPasien;
}

int compareByNameAsc(Pasien a, Pasien b)
{
  return strcmp(a.namaPasien, b.namaPasien);
}

int compareByNameDesc(Pasien a, Pasien b)
{
  return strcmp(b.namaPasien, a.namaPasien);
}

int compareByAgeAsc(Pasien a, Pasien b)
{
  return a.umur - b.umur;
}

int compareByAgeDesc(Pasien a, Pasien b)
{
  return b.umur - a.umur;
}

int compareByRoomIdAsc(Pasien a, Pasien b)
{
  return a.idKamar - b.idKamar;
}

int compareByRoomIdDesc(Pasien a, Pasien b)
{
  return b.idKamar - a.idKamar;
}
