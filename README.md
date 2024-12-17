# 🌐 **Final Project Pemrograman Lanjut (C) - CMake dengan MinGW**

Kelompok 10: 
Ferdy Ashari Putra (Hadir)
ferry irwansyah (hadir)


Berikut adalah dokumentasi untuk setup dan build project **Sistem Manajemen Pasien dan Kamar Pasien di sebuah Rumah Sakit** menggunakan **CMake** dengan generator **MinGW Makefiles**.

---

## 📝 **Prerequisites**

Pastikan perangkat Anda memiliki perangkat lunak berikut sebelum memulai:

- **MinGW**: Pastikan sudah terinstal dan ditambahkan ke `PATH`. Instal dari [MinGW Installer](http://www.mingw.org/).
Video tutorial Install MinGW untuk VSCode : https://www.youtube.com/watch?v=JsO58opI3SQ

- **CMake**: Pastikan sudah terinstal (minimal versi 3.15, versi terbaru lebih baik) dan ditambahkan ke `PATH`. Instal dari [CMake Official Website](https://cmake.org/download/). 
Note: - Pastikan download cmake yang windows installer dengan tipe file .msi
      - Untuk memasukkan ke path ikuti cara yang sama seperti MinGW.
      - Folder untuk CMAKE biasanya adalah "C:\Program Files\CMake\bin"

---

## ⚙️ **Setup dan Build Project**

### **1. Clone Repository**

Clone repository proyek ke perangkat Anda dan navigasi ke direktori proyek:

```bash
git clone https://github.com/UrayMR/fp_pemlan.git
cd fp_pemlan
```

---

### **2. Struktur Folder**

Pastikan struktur folder proyek mengikuti hierarki berikut:

```
fp_pemlan/
├── build/               # Folder untuk output build
├── include/             # Folder untuk file header/struct
│   └── Model
|       ├── kamar.h
│       └── pasien.h
├── src/                 # Folder untuk file sumber
│   ├── main.c
│   └── logic/           # Folder untuk menyimpan logika fungsi
│       ├── kamarLogic.c
│       └── pasienLogic.c
│   
├── CMakeLists.txt       # File konfigurasi CMake
└── README.md            # Dokumentasi proyek
```

---

### **3. Konfigurasi CMake**

Buka file `CMakeLists.txt` di root proyek Anda dan pastikan isinya seperti ini:

```cmake
# Versi minimum CMake
cmake_minimum_required(VERSION 3.15)

# Nama proyek
project(SistemManajemenPasien VERSION 1.0 LANGUAGES C)

# Set standar C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")

# Direktori header
include_directories(${PROJECT_SOURCE_DIR}/include)

# Daftar file sumber
set(SOURCES
    src/main.c
    src/logic/kamarLogic.c
    src/logic/pasienLogic.c
)

# Tambahkan executable
add_executable(app ${SOURCES})
```

---

### **4. Buat Folder Build**

Buat folder `build` **apabila tidak ada** untuk menampung file hasil build:

```bash
mkdir build
cd build
```

---

### **5. Generate Makefiles dengan CMake**

Jalankan perintah berikut untuk menghasilkan file Makefile menggunakan generator `MinGW Makefiles`:

```bash
cmake -G "MinGW Makefiles" ..
```

**Output yang berhasil**:

- Anda akan melihat pesan seperti:
  ```
  -- The C compiler identification is GNU
  -- Configuring done
  -- Generating done
  -- Build files have been written to: <path_to_project>/build
  ```

Jika ada error, pastikan:

- **MinGW** dan **CMake** sudah ditambahkan ke `PATH`.
- Direktori proyek memiliki struktur yang benar.

---

### **6. Build Proyek**

Setelah file Makefile dihasilkan, jalankan perintah berikut untuk build proyek:

```bash
cmake --build .
```

Atau gunakan **MinGW Makefiles** secara langsung:

```bash
mingw32-make
```

**Output yang berhasil**:

- Jika build berhasil, file executable `app.exe` akan dihasilkan di folder `build`.

---

### **7. Jalankan Program**

Setelah proses build selesai, jalankan program dengan perintah berikut:

```bash
./app.exe
```

---

## 🎯 **Troubleshooting**

### **1. CMake Tidak Ditemukan**

Jika Anda mendapatkan error:

```
The "cmake" command is not found in PATH.
```

Pastikan **CMake** sudah terinstal dan ditambahkan ke `PATH`.  
Cek versi CMake dengan:

```bash
cmake --version
```

---

### **2. MinGW Tidak Ditemukan**

Jika Anda mendapatkan error:

```
CMake Error: The C compiler "C:/path_to_mingw/bin/gcc.exe" is not able to compile a simple test program.
```

Pastikan **MinGW** sudah terinstal dan ditambahkan ke `PATH`.  
Cek versi GCC dengan:

```bash
gcc --version
```

---

### **3. File Tidak Terdeteksi**

Jika file baru tidak terdeteksi setelah Anda menambahkannya, pastikan Anda memperbarui daftar file di `CMakeLists.txt` pada bagian `set(SOURCES ...)`.

---

## 🤝 **Kontribusi**

Jika Anda adalah anggota tim proyek, gunakan panduan berikut untuk mengelola kontribusi Anda:

1. **Buat Branch Baru**  
   Buat branch baru untuk setiap fitur atau perubahan:

   ```bash
   git checkout -b nama_anda
   ```

2. **Commit Perubahan**  
   Lakukan commit setelah selesai mengedit:

   ```bash
   git add .
   git commit -m "Menambahkan fitur <nama_fitur>" // Isi Message Hanya Contoh
   ```

3. **Push ke Remote Repository**  
   Push branch Anda ke GitHub:

   ```bash
   git push origin nama_anda
   ```

4. **Pull Pembaruan Terbaru**  
   Pull dari branch Main ke branch anda:

   ```bash
   git checkout nama_anda
   git push origin main
   ```

---

Terima kasih sudah mengikuti panduan ini! Jika ada pertanyaan atau kendala, jangan ragu untuk bertanya. 😊
