#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


int height(Node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(Data d) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = d;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int getBalance(Node *n) {
    if (!n) return 0;
    return height(n->left) - height(n->right);
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}


void toLowerStr(char *dest, const char *src) {
    int i = 0;
    while (src[i]) {
        dest[i] = tolower(src[i]);
        i++;
    }
    dest[i] = '\0';
}

int compareNama(char *nama1, char *nama2) {
    char temp1[50], temp2[50];
    toLowerStr(temp1, nama1);
    toLowerStr(temp2, nama2);
    return strcmp(temp1, temp2);
}


Node* insertByNIK(Node* node, Data d) {
    if (!node) return newNode(d);

    int cmp = strcmp(d.nik, node->data.nik);

    if (cmp < 0)
        node->left = insertByNIK(node->left, d);
    else if (cmp > 0)
        node->right = insertByNIK(node->right, d);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(d.nik, node->left->data.nik) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(d.nik, node->right->data.nik) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(d.nik, node->left->data.nik) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(d.nik, node->right->data.nik) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


Node* insertByNama(Node* node, Data d) {
    if (!node) return newNode(d);

    int cmp = compareNama(d.nama, node->data.nama);

    if (cmp < 0)
        node->left = insertByNama(node->left, d);
    else if (cmp > 0)
        node->right = insertByNama(node->right, d);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    
    if (balance > 1 && compareNama(d.nama, node->left->data.nama) < 0)
        return rightRotate(node);

    if (balance < -1 && compareNama(d.nama, node->right->data.nama) > 0)
        return leftRotate(node);

    if (balance > 1 && compareNama(d.nama, node->left->data.nama) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && compareNama(d.nama, node->right->data.nama) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}



void prefixSearchNIK(Node *root, char *prefix) {
    if (!root) return;
    
    prefixSearchNIK(root->left, prefix);

    if (strncmp(root->data.nik, prefix, strlen(prefix)) == 0)
        printf("NIK: %-10s | Nama: %-20s | JK: %s\n",
            root->data.nik, root->data.nama, root->data.jk);

    prefixSearchNIK(root->right, prefix);
}

void prefixSearchNama(Node *root, char *prefix) {
    if (!root) return;

    prefixSearchNama(root->left, prefix);

    char lowerNama[50];
    toLowerStr(lowerNama, root->data.nama);

    if (strncmp(lowerNama, prefix, strlen(prefix)) == 0)
        printf("NIK: %-10s | Nama: %-20s | JK: %s\n",
            root->data.nik, root->data.nama, root->data.jk);

    prefixSearchNama(root->right, prefix);
}



void loadCSV(Node **treeNIK, Node **treeNama, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("File %s tidak ditemukan!\n", filename);
        return;
    }

    char line[256];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        Data d;
        char *token = strtok(line, ";");
        if (!token) continue;
        strcpy(d.nik, token);

        token = strtok(NULL, ";");
        if (!token) continue;
        strcpy(d.nama, token);

        token = strtok(NULL, ";");
        if (!token) {
            strcpy(d.jk, "-"); 
        } else {

            token[strcspn(token, "\r\n")] = 0;
            strcpy(d.jk, token);
        }

        *treeNIK = insertByNIK(*treeNIK, d);
        *treeNama = insertByNama(*treeNama, d);
        count++;
    }

    printf("Berhasil memuat %d data dari %s\n", count, filename);
    fclose(fp);
}


// ===================== MENU ======================

void menu(Node **treeNIK, Node **treeNama) {
    while (1) {
        char pilih;
        printf("\nWelcome\n");
        printf("==============\n");
        printf("Input Data (I)\n");
        printf("Edit Data (E)\n");
        printf("Hapus Data (H)\n");
        printf("Cari Data (C)\n");
        printf("Berhenti Program (B)\n");
        printf("Pilihan Anda: ");

        if (scanf(" %c", &pilih) != 1) break;
        pilih = toupper(pilih);

        if (pilih == 'C') {
            char key[50], val[50];
            printf("Masukan keyword (NIK atau NAMA) spasi nilai_yang_dicari: ");
            // Contoh input: NIK 9011 atau NAMA grayesi
            scanf("%s %s", key, val);

            // Ubah keyword dan value ke lowercase untuk pencarian
            char lowerKey[50], lowerVal[50];
            toLowerStr(lowerKey, key);
            toLowerStr(lowerVal, val);

            if (strcmp(lowerKey, "nik") == 0) {
                printf("\nHasil pencarian NIK prefix '%s':\n", val);
                printf("--------------------------------------------------\n");
                prefixSearchNIK(*treeNIK, lowerVal); // Cari NIK persis seperti input angka
                printf("--------------------------------------------------\n");

            } else if (strcmp(lowerKey, "nama") == 0) {
                printf("\nHasil pencarian NAMA prefix '%s':\n", val);
                printf("--------------------------------------------------\n");
                prefixSearchNama(*treeNama, lowerVal);
                printf("--------------------------------------------------\n");
            } else {
                printf("Keyword salah! Gunakan 'NIK' atau 'NAMA'.\n");
            }
        }

        else if (pilih == 'B') {
            printf("Program berhenti.\n");
            break;
        }

        else {
            printf("Fitur Input/Edit/Hapus belum diimplementasikan di kode ini.\n");
        }
    }
}



int main() {
    Node *treeNIK = NULL;
    Node *treeNama = NULL;

    loadCSV(&treeNIK, &treeNama, "data1.csv");

    menu(&treeNIK, &treeNama);

    return 0;
}
