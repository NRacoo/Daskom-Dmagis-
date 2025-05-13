#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_vendor 10
#define MAX_sekolah 10
#define MAX_menu 5

typedef enum {
    BELUM_DIAJUKAN,
    SEDANG_DITINJAU,
    DISETUJUI,
    DITOLAK
}StatusRAB;

typedef struct{
    char karbohidrat[50];
    char protein[50];
    char sayur[50];
    char buah[50];
    char susu[50];
}Menu;

typedef struct{
    char nama_vendor[50];
    char password[20];
    int sudahTerdaftar;
    int sekolahTerhubung;
    Menu menu[MAX_menu];
    int jumlah_menu;
    StatusRAB statusRAB;
}Vendor;

typedef struct{
    char nama_sekolah[50];
    int jumlah_siswa;
    int sudahTerhubung;
}Sekolah;

Vendor vendors[MAX_vendor]; Sekolah sekolahs[MAX_sekolah]; int jumlah_vendor = 0 ; int jumlah_sekolah = 0;

void sortingVendor(){
    for (int i = 0; i < jumlah_vendor -1 ; i ++){
        for (int j = i + 1 ; j < jumlah_vendor ; j ++){
            if (strcmp(vendors[i].nama_vendor, vendors[j].nama_vendor) > 0){
                Vendor temp = vendors[i];
                vendors[i] = vendors[j];
                vendors[j] = temp;
            }
        }
    }
}

void tambahSekolah(){
    printf("Nama Sekolah:");scanf("%s", sekolahs[jumlah_sekolah].nama_sekolah);
    printf("Jumlah Siswa:");scanf("%d", &sekolahs[jumlah_sekolah].jumlah_siswa);
    sekolahs[jumlah_sekolah].sudahTerhubung = 0;
    jumlah_sekolah++;
    printf("Sekolah berhasil ditambahkan.\n");
}

void hapusSekolah(){
    char nama_sekolah[50];
    printf("Nama Sekolah:");scanf("%s", nama_sekolah);
    for (int i = 0; i < jumlah_sekolah; i++){
        if (strcmp(sekolahs[i].nama_sekolah, nama_sekolah) == 0){
            for (int j = i; j < jumlah_sekolah -1 ; j ++){
                sekolahs[j] = sekolahs[j + 1];
            }
            jumlah_sekolah--;
            printf("Sekolah berhasil dihapus.\n");
            return;
        }
    }
    printf("Sekolah tidak ditemukan.\n");
}

void lihatDataVendor(){
    sortingVendor();
    printf("Daftar Vendpor: \n");
    for (int i = 0; i < jumlah_vendor; i ++){
        printf("- %s \n", vendors[i].nama_vendor);
    }
}

void hubungkanSekolah(){
    char namaVendor[50], namasekolah[50];
    printf("Nama Vendor:");scanf("%s", namaVendor);
    printf("Nama Sekolah:");scanf("%s", namasekolah);

    for (int i = 0; i < jumlah_vendor; i ++){
        if(strcmp(vendors[i].nama_vendor, namaVendor) == 0 && vendors[i].sekolahTerhubung == -1){
            for (int j = 0; j<jumlah_sekolah; j ++){
                if(strcmp(sekolahs[j].nama_sekolah, namasekolah) == 0 && !sekolahs[j].sudahTerhubung){
                    vendors[i].sekolahTerhubung = j;
                    sekolahs[j].sudahTerhubung = 1;
                    printf("Sekolah %s berhasil terhubung dengan vendor %s\n", sekolahs[j].nama_sekolah, vendors[i].nama_vendor);
                    return;
                }
            }
        }
    }
}




void lihatDataKerjasama(){
    printf("Daftar Kerjasama: \n");
    for(int i = 0; i < jumlah_vendor; i++){
        if(vendors[i].sekolahTerhubung != -1){
            printf("Vendor %s terhubung dengan Sekolah %s\n", vendors[i].nama_vendor, sekolahs[vendors[i].sekolahTerhubung].nama_sekolah);
        }
    }
}

void ubahStatus(){
    char namaVendor[50];
    int pilihan;
    printf("Nama Vendor: ");scanf("%s", namaVendor);

    for (int i = 0; i < jumlah_vendor; i++ ){
        if(strcmp(vendors[i].nama_vendor, namaVendor) == 0){
            printf("Pilih status RAB: 1. SEDANG DITINJAU 2. DISETUJUI 3. DITOLAK\n");
            scanf("%d", &pilihan);
            vendors[i].statusRAB = pilihan;
            printf("Status RAB berhasil diubah.\n");
            return;
        }
    }
    printf("Vendor tidak terdaftar. \n");
}

void tambahVendor(){
    printf ("-- Sign Up Vendor --\n");
    printf ("Nama Vendor: ");scanf("%s", vendors[jumlah_vendor].nama_vendor);
    printf ("Password: ");scanf("%s", vendors[jumlah_vendor].password);
    vendors[jumlah_vendor].sudahTerdaftar = 1;
    vendors[jumlah_vendor].sekolahTerhubung = -1;
    vendors[jumlah_vendor].jumlah_menu = 0;
    vendors[jumlah_vendor].statusRAB = BELUM_DIAJUKAN;
    jumlah_vendor++;
    printf("Selamat anda telah terdaftar.\n");
}


void menuVendor(int id){
    int pilih;
    do {
        printf("\n--- Menu Vendor ---\n", vendors[id].nama_vendor);
        printf("1. Tambah Menu\n");
        printf("2. Hapus Menu\n");
        printf("3. Lihat Menu\n");
        printf("4. Ajukan RAB\n");
        printf("0. Logout\n");scanf("%d", &pilih);

        switch(pilih){
            case 1:
            if(vendors[id].jumlah_menu < MAX_menu){
                printf("Masukan nama menu hari ke-%d: ", vendors[id].jumlah_menu +1);
                printf("Karbohidrat:");scanf("%s", vendors[id].menu[vendors[id].jumlah_menu].karbohidrat);
                printf("Protein:");scanf("%s", vendors[id].menu[vendors[id].jumlah_menu].protein);
                printf("Sayur:");scanf("%s", vendors[id].menu[vendors[id].jumlah_menu].sayur);
                printf("Buah:");scanf("%s", vendors[id].menu[vendors[id].jumlah_menu].buah);
                printf("Susu:");scanf("%s", vendors[id].menu[vendors[id].jumlah_menu].susu);
                vendors[id].jumlah_menu++;
                vendors[id].statusRAB = BELUM_DIAJUKAN;
            }else{
                printf("Menu dalam 5 hari sudah penuh. \n");
            }
            break;
            case 2:
            if(vendors[id].jumlah_menu > 0){
                vendors[id].jumlah_menu--;
                printf("Menu hari terakhir dihapus.\n");
            }else{
                printf("Belum ada menu.\n");
            }
            break;
            case 3:
            for(int i = 0; i < vendors[id].jumlah_menu; i++){
                printf("Hari ke-%d: %s\n", i + 1, vendors[id].menu[i].karbohidrat);
                printf("Protein: %s\n", vendors[id].menu[i].protein);
                printf("Sayur: %s\n", vendors[id].menu[i].sayur);
                printf("Buah: %s\n", vendors[id].menu[i].buah);
                printf("Susu: %s\n", vendors[id].menu[i].susu);
            } if (vendors[id].jumlah_menu == 0){
                printf("Belum ada menu.\n");
            }
            printf("Status RAB: ");
            switch(vendors[id].statusRAB){
                case BELUM_DIAJUKAN: printf("BELUM DIAJUKAN\n"); break;
                case SEDANG_DITINJAU: printf("SEDANG DITINJAU\n"); break;
                case DISETUJUI: printf("DISETUJUI\n"); break;
                case DITOLAK: printf("DITOLAK\n"); break;
            }
            break;
            case 4:
            vendors[id].statusRAB = SEDANG_DITINJAU;
            printf("RAB diterima.\n");
            break;
            case 0:
            printf("Logout berhasil.\n");break;
            default:
            printf("Pilihan tidak valid!\n");
    }
        }while(pilih != 0);
    

}

int login(){
    char nama[50], pass[20];
    int attempts = 3;

    while(attempts--){
        printf("\n--- Login ---\nNama: ");scanf("%s", &nama);
        printf("Password: ");scanf("%s", pass);

        if(strcmp(nama, "admin") == 0 && strcmp(pass, "123") == 0) return -99;

        for(int i = 0; i < jumlah_vendor; i++){
            if(strcmp(nama, vendors[i].nama_vendor) == 0 && strcmp(pass, vendors[i].password) == 0) return i;
        }
    }
    printf("Login gagal. Silahkan coba lagi.\n");
    return -1;
}
