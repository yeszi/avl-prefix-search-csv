# 🌳 Student Data Search Engine (AVL Tree)

![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Structure](https://img.shields.io/badge/Data_Structure-AVL_Tree-green?style=for-the-badge)
![Course](https://img.shields.io/badge/Modul-12-orange?style=for-the-badge)

> **Tugas Praktikum Struktur Data - Modul 12** > Implementasi algoritma pencarian cepat menggunakan *Balanced Binary Search Tree* (AVL).

---

## 📖 Deskripsi Project

Project ini adalah transformasi dari sistem pendataan berbasis *Linked List* (Modul 9) menjadi sistem berbasis **AVL Tree**. Tujuan utamanya adalah meningkatkan efisiensi pencarian data mahasiswa.

Sistem ini memuat data dari file CSV ke dalam **dua pohon AVL sekaligus**:
1. 🔢 **Tree NIK:** Data diurutkan dan diseimbangkan berdasarkan Nomor Induk Kependudukan.
2. 👤 **Tree NAMA:** Data diurutkan dan diseimbangkan berdasarkan Nama (case-insensitive).

Dengan struktur ini, kompleksitas pencarian menjadi **O(log n)**, jauh lebih cepat dibandingkan pencarian linear pada Linked List **O(n)**.

---

## ✨ Fitur Utama

* **Dual AVL Tree Storage:** Data disimpan redundan dalam dua pohon terpisah untuk fleksibilitas pencarian.
* **Auto-Balancing:** Mengimplementasikan rotasi otomatis (Left, Right, Left-Right, Right-Left) untuk menjaga pohon tetap seimbang.
* **Prefix Search:** Fitur pencarian canggih (seperti *autocomplete*).
    * Cari `NIK 19` → Muncul semua angkatan 19.
    * Cari `NAMA Budi` → Muncul Budi Santoso, Budi Hartono, dll.
* **CSV Data Loader:** Membaca data eksternal (`data1.csv`) secara otomatis saat program dijalankan.
* **Interactive Menu:** Antarmuka CLI yang user-friendly.

---

## 🛠️ Struktur Data

Program ini menggunakan `struct` custom untuk menyimpan informasi mahasiswa:

```c
typedef struct Data {
    char nik[20];   
    char nama[50];  
    char jk[10];   
} Data;

typedef struct Node {
    Data data;
    int height;
    struct Node *left, *right;
} Node;
