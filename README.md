# Algoritma Pencarian (Balanced Tree / AVL)

Pada modul ini, seluruh data yang sebelumnya menggunakan *linked list* (Modul 9) dimodifikasi dan disimpan menjadi **dua buah AVL Tree** untuk:
1. **Tree berdasarkan NIK**  
2. **Tree berdasarkan NAMA (lowercase)**

Tujuan dari praktikum ini adalah memahami bagaimana data dapat dicari dengan cepat menggunakan struktur pohon yang seimbang (balanced), serta menerapkan pencarian berbasis **prefix**.

---

## 🎯 Tujuan Praktikum
- Menerapkan struktur data **AVL Tree** untuk menyimpan dan mengelola data.
- Melakukan pencarian berdasarkan **prefix** pada field NIK dan NAMA.
- Mengimplementasikan menu interaktif seperti pada Modul IX (Input, Edit, Hapus, Cari, Exit).
- Menggunakan data dari file **CSV** sebagai sumber input.
- Memahami balancing pada AVL (rotasi kiri, kanan, LR, RL).

---

## 🗂 Struktur Data
Program ini menggunakan struktur `Data` yang terdiri dari:

```c
typedef struct Data {
    char nik[20];
    char nama[50];
    char jK [20];
} Data;

---

## Cara Menjalankan Program

```
gcc 2201020130.c -o buku.exe
---

```
buku data1.csv
---
