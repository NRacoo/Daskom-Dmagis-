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
        StatusRAB statusRAB;
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
    
    void simpanDataVendor(){
        FILE *vendor;
        vendor = fopen("dataVendor.dat", "wb");

        if( vendor == NULL ){
            printf("Gagal memasukan data vendor");
            return;
        }
        fwrite(&jumlah_vendor, sizeof(jumlah_vendor), 1, vendor);
        fwrite(vendors, sizeof(Vendor), jumlah_vendor, vendor);
        fclose(vendor);
    }
    void muatDataVendor(){
        FILE *vendor;
        vendor = fopen("dataVendor.dat", "rb" );

        if (vendor == NULL){
            jumlah_vendor = 0;
            return;
        }
        fread(&jumlah_vendor, sizeof(jumlah_vendor), 1 , vendor);
        fread(vendors, sizeof(vendors), jumlah_vendor, vendor);
        fclose(vendor);
    }

    void muatDataSekolah(){
        FILE *sekolah;
        sekolah = fopen("dataSekolah.dat", "rb" );

        if (sekolah == NULL){
            jumlah_sekolah = 0;
            return;
        }
        fread(&jumlah_sekolah, sizeof(jumlah_sekolah), 1 , sekolah );
        fread(sekolahs, sizeof(Sekolah), jumlah_sekolah, sekolah);
        fclose(sekolah);

    }

    void simpanDataSekolah() {
        FILE *file = fopen("dataSekolah.dat", "wb");
        if (file == NULL) {
            printf("Gagal menyimpan data sekolah.\n");
            return;
        }
        fwrite(&jumlah_sekolah, sizeof(jumlah_sekolah), 1, file);
        fwrite(sekolahs, sizeof(Sekolah), jumlah_sekolah, file);
        fclose(file);
    }

    void tambahSekolah(){
        getchar();
        printf("Nama Sekolah:");gets(sekolahs[jumlah_sekolah].nama_sekolah);
        printf("Jumlah Siswa:\n");scanf("%d", &sekolahs[jumlah_sekolah].jumlah_siswa);
        sekolahs[jumlah_sekolah].sudahTerhubung = 0;
        jumlah_sekolah++;
        simpanDataSekolah();
        printf("Sekolah berhasil ditambahkan.\n");
    }

    void hapusSekolah(){
        getchar();
        char nama_sekolah[50];
        printf("Nama Sekolah:");gets(nama_sekolah);
        for (int i = 0; i < jumlah_sekolah; i++){
            if (strcmp(sekolahs[i].nama_sekolah, nama_sekolah) == 0){
                for (int j = i; j < jumlah_sekolah -1 ; j ++){
                    sekolahs[j] = sekolahs[j + 1];
                }
                jumlah_sekolah--;
                simpanDataSekolah();
                printf("Sekolah berhasil dihapus.\n");
                return;
            }
        }
        printf("Sekolah tidak ditemukan.\n");
    }

    void ubahSekolah(){
    getchar();
    char nama_sekolah[50];
    printf("Masukkan nama sekolah yang ingin diubah: ");
    gets(nama_sekolah);

    for (int i = 0; i < jumlah_sekolah; i++){
        if(strcmp(sekolahs[i].nama_sekolah, nama_sekolah) == 0){
            printf("Nama sekolah baru: ");
            gets(sekolahs[i].nama_sekolah);
            printf("Jumlah siswa baru: ");
            scanf("%d", &sekolahs[i].jumlah_siswa);
            simpanDataSekolah();
            printf("Data sekolah berhasil diubah.\n");
            return;
        }
    }
    printf("Sekolah tidak ditemukan.\n");
}

void lihatDataSekolah() {
    printf("\n--- Daftar Sekolah ---\n");
    if (jumlah_sekolah == 0) {
        printf("Belum ada data sekolah.\n");
        return;
    }
    for (int i = 0; i < jumlah_sekolah; i++) {
        printf("Nama: %s\n", sekolahs[i].nama_sekolah);
        printf("Jumlah Siswa: %d\n", sekolahs[i].jumlah_siswa);
        printf("Status Terhubung: %s\n", sekolahs[i].sudahTerhubung ? "Sudah Terhubung" : "Belum Terhubung");
        printf("--------------------------\n");
    }
}


    void lihatDataVendor(){
        sortingVendor();
        printf("Daftar Vendor: \n");
        for (int i = 0; i < jumlah_vendor; i ++){
            printf("- %s \n", vendors[i].nama_vendor);
        }
    }

    void hubungkanSekolah(){
        getchar();
        char namaVendor[50], namasekolah[50];
        printf("Nama Vendor:");gets(namaVendor);
        printf("Nama Sekolah:");gets(namasekolah);

        for (int i = 0; i < jumlah_vendor; i ++){
            if(strcmp(vendors[i].nama_vendor, namaVendor) == 0 && vendors[i].sekolahTerhubung == -1){
                for (int j = 0; j<jumlah_sekolah; j ++){
                    if(strcmp(sekolahs[j].nama_sekolah, namasekolah) == 0 && !sekolahs[j].sudahTerhubung){
                        vendors[i].sekolahTerhubung = j;
                        sekolahs[j].sudahTerhubung = 1;
                        simpanDataSekolah();
                        simpanDataVendor();
                        printf("Sekolah %s berhasil terhubung dengan vendor %s\n", sekolahs[j].nama_sekolah, vendors[i].nama_vendor);
                        return;
                    }
                }
            }
        }
    }




    void lihatDataKerjasama(){
        printf("\nDaftar Kerjasama Vendor dan Sekolah:\n");
        int ditemukan = 0;
        for(int i = 0; i < jumlah_vendor; i++){
            if(vendors[i].sekolahTerhubung != -1){
                printf("Vendor %s terhubung dengan Sekolah %s\n",
                    vendors[i].nama_vendor,
                    sekolahs[vendors[i].sekolahTerhubung].nama_sekolah);
                ditemukan = 1;
            }
        }
        if (!ditemukan) {
            printf("Belum ada kerjasama yang terhubung.\n");
        }
    }


    void ubahStatus() {
    getchar();
    char namaVendor[50];
    int pilihan, hari;
    sortingVendor();

    printf("Daftar Vendor:\n");
    for (int i = 0; i < jumlah_vendor; i++) {
        printf("- %s\n", vendors[i].nama_vendor);
    }

    printf("Nama Vendor: ");
    gets(namaVendor);

    for (int i = 0; i < jumlah_vendor; i++) {
        if (strcmp(vendors[i].nama_vendor, namaVendor) == 0) {
            if (vendors[i].jumlah_menu == 0) {
                printf("Vendor ini belum memiliki menu.\n");
                return;
            }

            printf("\n--- Daftar Menu Vendor %s ---\n", vendors[i].nama_vendor);
            for (int j = 0; j < vendors[i].jumlah_menu; j++) {
                printf("\nHari ke-%d:\n", j + 1);
                printf("  Karbohidrat: %s\n", vendors[i].menu[j].karbohidrat);
                printf("  Protein:     %s\n", vendors[i].menu[j].protein);
                printf("  Sayur:       %s\n", vendors[i].menu[j].sayur);
                printf("  Buah:        %s\n", vendors[i].menu[j].buah);
                printf("  Susu:        %s\n", vendors[i].menu[j].susu);
                printf("  Status RAB: ");
                switch (vendors[i].menu[j].statusRAB) {
                    case BELUM_DIAJUKAN: printf("BELUM DIAJUKAN\n"); break;
                    case SEDANG_DITINJAU: printf("SEDANG DITINJAU\n"); break;
                    case DISETUJUI: printf("DISETUJUI\n"); break;
                    case DITOLAK: printf("DITOLAK\n"); break;
                }
            }

            printf("\nPilih hari ke-berapa yang ingin diubah statusnya (1-%d): ", vendors[i].jumlah_menu);
            scanf("%d", &hari);

            if (hari < 1 || hari > vendors[i].jumlah_menu) {
                printf("Hari tidak valid.\n");
                return;
            }

            printf("\nPilih status RAB baru:\n");
            printf("1. SEDANG DITINJAU\n2. DISETUJUI\n3. DITOLAK\n");
            scanf("%d", &pilihan);

            if (pilihan >= 1 && pilihan <= 3) {
                vendors[i].menu[hari - 1].statusRAB = pilihan;
                simpanDataVendor();
                printf("Status RAB hari ke-%d berhasil diubah.\n", hari);
            } else {
                printf("Pilihan status tidak valid.\n");
            }
            return;
        }
    }

    printf("Vendor tidak ditemukan.\n");
}


void ubahKerjasama(){
    getchar();
    char namaVendor[50], sekolahBaru[50];
    printf("Nama Vendor yang ingin diubah hubungannya: ");
    gets(namaVendor);

    for(int i = 0; i < jumlah_vendor; i++){
        if(strcmp(vendors[i].nama_vendor, namaVendor) == 0){
            if(vendors[i].sekolahTerhubung == -1){
                printf("Vendor ini belum memiliki hubungan dengan sekolah.\n");
                return;
            }

            printf("Sekolah baru yang ingin dihubungkan: ");
            gets(sekolahBaru);

            for(int j = 0; j < jumlah_sekolah; j++){
                if(strcmp(sekolahs[j].nama_sekolah, sekolahBaru) == 0){
                    if(sekolahs[j].sudahTerhubung){
                        printf("Sekolah ini sudah terhubung dengan vendor lain.\n");
                        return;
                    }

                
                    sekolahs[vendors[i].sekolahTerhubung].sudahTerhubung = 0;

                    
                    vendors[i].sekolahTerhubung = j;
                    sekolahs[j].sudahTerhubung = 1;

                    simpanDataSekolah();
                    simpanDataVendor();
                    printf("Hubungan vendor %s berhasil diubah ke sekolah %s.\n", namaVendor, sekolahs[j].nama_sekolah);
                    return;
                }
            }

            printf("Sekolah baru tidak ditemukan.\n");
            return;
        }
    }

    printf("Vendor tidak ditemukan.\n");
}

    void tambahVendor(){
        getchar();
        printf ("-- Sign Up Vendor --\n");
        printf ("Nama Vendor: ");gets( vendors[jumlah_vendor].nama_vendor);
        printf ("Password: ");gets(vendors[jumlah_vendor].password);
        vendors[jumlah_vendor].sudahTerdaftar = 1;
        vendors[jumlah_vendor].sekolahTerhubung = -1;
        vendors[jumlah_vendor].jumlah_menu = 0;
        vendors[jumlah_vendor].statusRAB = BELUM_DIAJUKAN;
        jumlah_vendor++;
        simpanDataVendor();
        printf("Selamat anda telah terdaftar.\n");
    }


    void menuVendor(int id){
        int pilih;
        do {
            printf("\n--- Menu Vendor ---\n");
            printf("1. Tambah Menu\n");
            printf("2. Hapus Menu\n");
            printf("3. Lihat Menu\n");
            printf("4. Ajukan RAB\n");
            printf("0. Logout\n");scanf("%d", &pilih);

            switch(pilih){
                case 1:
                getchar();
                if(vendors[id].jumlah_menu < MAX_menu){
                    printf("Masukan nama menu hari ke-%d: \n", vendors[id].jumlah_menu +1);
                    printf("Karbohidrat:");gets( vendors[id].menu[vendors[id].jumlah_menu].karbohidrat);
                    printf("Protein:");gets( vendors[id].menu[vendors[id].jumlah_menu].protein);
                    printf("Sayur:");gets( vendors[id].menu[vendors[id].jumlah_menu].sayur);
                    printf("Buah:");gets( vendors[id].menu[vendors[id].jumlah_menu].buah);
                    printf("Susu:");gets( vendors[id].menu[vendors[id].jumlah_menu].susu);
                    vendors[id].menu[vendors[id].jumlah_menu].statusRAB = BELUM_DIAJUKAN;
                    vendors[id].jumlah_menu++;
                    simpanDataVendor();
                }else{
                    printf("Menu dalam 5 hari sudah penuh. \n");
                }
                break;
                case 2:
                if(vendors[id].jumlah_menu > 0){
                    vendors[id].jumlah_menu--;
                    printf("Menu hari terakhir dihapus.\n");
                    vendors[id].statusRAB = 0;
                }else{
                    printf("Belum ada menu.\n");
                }
                break;
                case 3:
                for(int i = 0; i < vendors[id].jumlah_menu; i++){
                    
                        printf("\nHari ke-%d:\n", i + 1);
                        printf("Karbohidrat: %s\n", vendors[id].menu[i].karbohidrat);
                        printf("Protein: %s\n", vendors[id].menu[i].protein);
                        printf("Sayur: %s\n", vendors[id].menu[i].sayur);
                        printf("Buah: %s\n", vendors[id].menu[i].buah);
                        printf("Susu: %s\n", vendors[id].menu[i].susu);

                        printf("Status RAB: ");
                        switch (vendors[id].menu[i].statusRAB) {
                            case BELUM_DIAJUKAN: printf("BELUM DIAJUKAN\n"); break;
                            case SEDANG_DITINJAU: printf("SEDANG DITINJAU\n"); break;
                            case DISETUJUI: printf("DISETUJUI\n"); break;
                            case DITOLAK: printf("DITOLAK\n"); break;
                        
                    }

                } if (vendors[id].jumlah_menu == 0){
                    printf("Belum ada menu.\n");
                }
                break;
                case 4:
                if (vendors[id].jumlah_menu == 0) {
                    printf("Belum ada menu yang dimasukkan.\n");
                } else {
                    printf("=== Daftar Menu dan Status RAB ===\n");
                    for (int i = 0; i < vendors[id].jumlah_menu; i++) {
                        printf("\nHari ke-%d:\n", i + 1);
                        printf("Karbohidrat: %s\n", vendors[id].menu[i].karbohidrat);
                        printf("Protein: %s\n", vendors[id].menu[i].protein);
                        printf("Sayur: %s\n", vendors[id].menu[i].sayur);
                        printf("Buah: %s\n", vendors[id].menu[i].buah);
                        printf("Susu: %s\n", vendors[id].menu[i].susu);

                        printf("Status RAB: ");
                        switch (vendors[id].menu[i].statusRAB) {
                            case BELUM_DIAJUKAN: printf("BELUM DIAJUKAN\n"); break;
                            case SEDANG_DITINJAU: printf("SEDANG DITINJAU\n"); break;
                            case DISETUJUI: printf("DISETUJUI\n"); break;
                            case DITOLAK: printf("DITOLAK\n"); break;
                        }
                    }

                    printf("\nMengajukan ulang RAB untuk menu yang BELUM DIAJUKAN atau DITOLAK...\n");
                    int jumlah_diajukan = 0;
                    for (int i = 0; i < vendors[id].jumlah_menu; i++) {
                        if (vendors[id].menu[i].statusRAB == BELUM_DIAJUKAN || vendors[id].menu[i].statusRAB == DITOLAK) {
                            vendors[id].menu[i].statusRAB = SEDANG_DITINJAU;
                            jumlah_diajukan++;
                        }
                    }

                    if (jumlah_diajukan > 0) {
                        printf("%d menu berhasil diajukan untuk ditinjau ulang.\n", jumlah_diajukan);
                        simpanDataVendor();
                    } else {
                        printf("Tidak ada menu yang bisa diajukan ulang.\n");
                    }
                }
                break;
                case 0:
                    printf("Logout Berhasil !\n");
                    simpanDataVendor();
                    return;
                default:
                    printf("Pilihan tidak valid.\n");
break;

        }
            }while(pilih != 0);
        

    }



    int login(){
        char nama[50], pass[20];
        int attempts = 3;

        while(attempts--){
            getchar();
            printf("\n--- Login ---\nNama: ");gets(nama);
            printf("Password: ");gets(pass);

            if(strcmp(nama, "admin") == 0 && strcmp(pass, "123") == 0) return -99;

            for(int i = 0; i < jumlah_vendor; i++){
                if(strcmp(nama, vendors[i].nama_vendor) == 0 && strcmp(pass, vendors[i].password) == 0) return i;
            }
        }
        printf("Login gagal. Silahkan coba lagi.\n");
        return -1;
    }

    int main (){
        int pilihmenu; 
        getchar(); 
        system("cls");
        muatDataSekolah();
        muatDataVendor();

        do{
            printf("\n-- Selamat Datang di: DMagis --\n ");
            printf("silahkan pilih menu\n");
            printf("1. Login admin\n");
            printf("2. Daftar Vendor\n");
            printf("3. Login Vendor\n");
            printf("0. Keluar\n");printf("Pilihan: \n"); scanf("%d", &pilihmenu);


            switch (pilihmenu)
            {
            case 1:{
                int id = login();
                if(id == -99){
                        int pilihAd;
                        do{
                            printf("-- menu Admin -- \n");
                            printf("1. Tambah Sekolah \n");
                            printf("2. Ubah Data Sekolah\n");
                            printf("3. Hapus Sekolah \n");
                            printf("4. Lihat Data \n");
                            printf("5. Hubungkan Kerjasama\n");
                            printf("6. Lihat kerjasama \n");
                            printf("7. Ubah Status RAB\n");
                            printf("8. Ubah Kerjasama\n");
                            printf("0. Logout\n");printf("Pilihan: \n");scanf("%d", &pilihAd);
                            
                            switch (pilihAd)
                            {
                            case 1:
                                tambahSekolah();
                                break;
                            case 2:
                                ubahSekolah();break;
                            case 3:
                                hapusSekolah();break;
                            case 4:{
                                int pilihan1;
                                printf("Pilih Data Yang ingin dilihat:\n");
                                printf("1. Data Sekolah\n");
                                printf("2. Data Vendor\n");
                                scanf("%d", &pilihan1);
                                if(pilihan1 == 1){
                                    lihatDataSekolah();
                                } else if(pilihan1 == 2){
                                    lihatDataVendor();
                                } else {
                                    printf("Pilihan tidak valid.\n");
                                }
                                break;
                            } break;
                            case 5:
                                hubungkanSekolah();break;
                            case 6:
                                lihatDataKerjasama();break;
                            case 7:
                                ubahStatus();break;
                            case 8:
                                ubahKerjasama();break;
                            case 0:
                                pilihmenu = 0; 
                                simpanDataSekolah();
                                printf("Logout Berhasil !");
                                
                            }
                        }
                        while(pilihAd != 0);
                        return 0;
                    }
                    break;
                }
                case 2:
                    tambahVendor();break;
                case 3:{
                    int id2 = login();
                    if(id2 >= 0 ){
                        menuVendor(id2);
                    }
                    
                }break;
                
                case 0:
                    pilihmenu = 0; 
                    simpanDataSekolah();
                    simpanDataVendor();
                    printf("Terimakasih telah berkunjung\n"); break;
            default:
                break;
            }
        }
        while(pilihmenu != 0);
        return 0;
    }