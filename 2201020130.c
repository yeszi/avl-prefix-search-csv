#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Data {
    char nik[20];
    char nama[50];
    char alamat[100];
} Data;

typedef struct Node {
    Data data;
    int height;
    struct Node *left, *right;
} Node;


// ===================== AVL TREE UTILITY ======================

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


// ===================== COMPARE KEY ======================
// AVL berdasarkan NIK → string compare
// AVL berdasarkan NAMA → lowercase compare

char lower(char c) {
    return tolower(c);
}

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++)
        str[i] = tolower(str[i]);
}


// ===================== INSERT NODE ======================

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

    char nama1[50], nama2[50];
    strcpy(nama1, d.nama);
    strcpy(nama2, node->data.nama);
    toLowerStr(nama1);
    toLowerStr(nama2);

    int cmp = strcmp(nama1, nama2);

    if (cmp < 0)
        node->left = insertByNama(node->left, d);
    else if (cmp > 0)
        node->right = insertByNama(node->right, d);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && cmp < 0)
        return rightRotate(node);

    if (balance < -1 && cmp > 0)
        return leftRotate(node);

    if (balance > 1 && cmp > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && cmp < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


// ===================== PREFIX SEARCH ======================

void prefixSearchNIK(Node *root, char *prefix) {
    if (!root) return;

    prefixSearchNIK(root->left, prefix);

    if (strncmp(root->data.nik, prefix, strlen(prefix)) == 0)
        printf("NIK: %s | Nama: %s | Alamat: %s\n",
            root->data.nik, root->data.nama, root->data.alamat);

    prefixSearchNIK(root->right, prefix);
}

void prefixSearchNama(Node *root, char *prefix) {
    if (!root) return;

    prefixSearchNama(root->left, prefix);

    char lowerNama[50];
    strcpy(lowerNama, root->data.nama);
    toLowerStr(lowerNama);

    if (strncmp(lowerNama, prefix, strlen(prefix)) == 0)
        printf("NIK: %s | Nama: %s | Alamat: %s\n",
            root->data.nik, root->data.nama, root->data.alamat);

    prefixSearchNama(root->right, prefix);
}


// ===================== CSV LOADING ======================

void loadCSV(Node **treeNIK, Node **treeNama, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("CSV tidak ditemukan!\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        Data d;
        char *token = strtok(line, ",");
        if (!token) continue;
        strcpy(d.nik, token);

        token = strtok(NULL, ",");
        strcpy(d.nama, token);

        token = strtok(NULL, ",");
        strcpy(d.alamat, token);

        *treeNIK = insertByNIK(*treeNIK, d);
        *treeNama = insertByNama(*treeNama, d);
    }

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

        scanf(" %c", &pilih);
        pilih = toupper(pilih);

        if (pilih == 'C') {
            char key[50], val[50];
            printf("Masukan keyword (NIK/NAMA) spasi nilai: ");
            scanf("%s %s", key, val);

            toLowerStr(key);
            toLowerStr(val);

            if (strcmp(key, "nik") == 0) {
                printf("\nHasil pencarian NIK prefix '%s':\n", val);
                prefixSearchNIK(*treeNIK, val);

            } else if (strcmp(key, "nama") == 0) {
                printf("\nHasil pencarian nama prefix '%s':\n", val);
                prefixSearchNama(*treeNama, val);
            }
        }

        else if (pilih == 'B') {
            printf("Program berhenti.\n");
            break;
        }

        else {
            printf("Fitur ini bisa kamu lengkapi sendiri (Input/Edit/Hapus).\n");
        }
    }
}


// ===================== MAIN ======================

int main() {
    Node *treeNIK = NULL;
    Node *treeNama = NULL;

    loadCSV(&treeNIK, &treeNama, "data.csv");

    menu(&treeNIK, &treeNama);

    return 0;
}
