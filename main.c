#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 50
#define MAX_PEOPLE 100


/*
    w  : write only->onceden ayný isimde bir dosya bile olsa eskisini siler, run yapinca yenisini olusturur.
    r  : read only->dosyanin onceden var olmasi sarttir.
    a  : append->var olan dosyaya ekleme yapar.
    r+ : hem okuma hem yazma, onceden dosya var olmali.
    w+ : hem okuma hem yazma, onceden var olma sarti yok, sil bastan olusturur.
    a+ : onceden var olan bir dosyanin sonuna veri ekleme ve okuma islemleri yapar.
*/





typedef struct {
    char ad[MAX_NAME_LENGTH];
    char soyad[MAX_NAME_LENGTH];
    int yas;
} Kisi;


int main()
{

    FILE* file = fopen("islemler.txt","w");//proje harici bir dizinde isteniyorsa uzantisi yazilmali
    FILE* fp1 = fopen("islemler1.txt","w");
    FILE* fp2 = fopen("islemler1.txt","a");
    FILE* fp3 = fopen("islemler2.txt","w");
    FILE* fp4 = fopen("islemlerOgr.txt","r");

    if(file==NULL)printf("Dosya olusturulamadi!");
    else{
        printf("Dosya basariyla olusturuldu!\n");

        char metin[15] = "Eren-Sude";
        for(int i = 0; i<strlen(metin); i++) fputc(metin[i],file);//put char
        printf("%s basariyla yazdirildi!\n\n",metin);
    }


    if(fp1==NULL)printf("Dosya olusturulamadi!");
    else{
        printf("Dosya basariyla olusturuldu!\n");


        char metin[50] = "Eren-Sude-Yurtaslan-Ercan\n";
        char metin1[50] = "Eren-Sude-Yurtaslan-Ercan\n";
        char metin2[50] = "Eren-Sude-Yurtaslan-Ercan\n";
        fputs(metin, fp1);//put string
        fputs(metin1, fp1);//put string
        fputs(metin2, fp1);//put string
        printf("%s%s%stextleri basariyla yazdirildi!\n\n",metin,metin1,metin2);
    }

    if(fp2==NULL)printf("Dosya olusturulamadi!");
    else{

        printf("Lutfen text giriniz: ");
        char metin[50];
        gets(metin);
        fputs(metin, fp2);//put string
        printf("%s basariyla yazdirildi!\n\n",metin);

    }


    //FORMATLI VERI YAZMA
    if(fp3==NULL)printf("Dosya olusturulamadi!");
    else{

        printf("Lutfen ogrenci ad-soyad giriniz: ");
        char metin[50];
        gets(metin);
        //fputs(metin, fp1);//put string
        int not;
        printf("\Lutfen not giriniz: ");
        scanf("%d", &not);

        fprintf(fp3, "Ogrenci ad-soyad: %s\nNot: %d",metin,not);
        printf("Dosya basariyla yazdirildi!\n\n",metin);


    }


    //DOSYA OKUMA
    char ad[25];
    char ad1[25];
    char soyad[25];
    int not;

    if(fp4==NULL)printf("Dosya olusturulamadi!");
    else{
        fscanf(fp4, "%s", &ad);
        fscanf(fp4, "%s", &ad1);
        fscanf(fp4, "%s", &soyad);
        fscanf(fp4, "%d", &not);
    printf("Okunan ogrenci bilgileri:\n");
    printf("Ad: %s %s Soyad: %s not: %d \n\n\n", ad, ad1, soyad, not);
    }





//*****************************DOSYADAN AD-SOYAD-YAS BILGISI OKUMA ALGORITMASI(GELISMIS)*****************************//

  FILE *fp = fopen("kisiler.txt", "r");
    if (fp == NULL) {
        perror("Dosya acilamadi");
        return 1;
    }

    Kisi kisiler[MAX_PEOPLE];
    int kisi_sayisi = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), fp)) {
        char *token;
        char *tokens[MAX_NAME_LENGTH];
        int token_count = 0;

        // Satýrý parçala ve tüm tokenlarý dizide sakla
        token = strtok(line, " ");
        while (token != NULL) {
            tokens[token_count++] = token;
            token = strtok(NULL, " ");
        }

        // Son token yaþ, bir önceki token soyad, geri kalaný ad
        if (token_count >= 3) { // Ad, soyad ve yaþ olduðundan emin ol
            kisiler[kisi_sayisi].yas = atoi(tokens[token_count - 1]);
            strcpy(kisiler[kisi_sayisi].soyad, tokens[token_count - 2]);

            // Adý oluþtur
            strcpy(kisiler[kisi_sayisi].ad, tokens[0]);
            for (int i = 1; i < token_count - 2; i++) {
                strcat(kisiler[kisi_sayisi].ad, " ");
                strcat(kisiler[kisi_sayisi].ad, tokens[i]);
            }
        } else {
            strcpy(kisiler[kisi_sayisi].ad, "Bilinmiyor");
            strcpy(kisiler[kisi_sayisi].soyad, "Bilinmiyor");
            kisiler[kisi_sayisi].yas = 0;
        }
        kisi_sayisi++;
    }

    printf("*****************kisiler.txt DOSYASI KAYITLARI(GELISMIS ALGORITMA)*****************\n");


    /*for (int i = 0; i < kisi_sayisi; i++) {
        printf("Ad: %s, Soyad: %s, Yas: %d\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].yas);
    }*/


    int toplam_yas = 0;
    int max_yas = 0;
    int max_yas_indeksi = 0;

    for (int i = 0; i < kisi_sayisi; i++) {
        printf("Ad: %s, Soyad: %s, Yas: %d\n", kisiler[i].ad, kisiler[i].soyad, kisiler[i].yas);
        toplam_yas += kisiler[i].yas;
        if (kisiler[i].yas > max_yas) {
            max_yas = kisiler[i].yas;
            max_yas_indeksi = i;
        }
    }

    // Yaþ ortalamasýný hesapla ve yazdýr
    double yas_ortalama = (double)toplam_yas / kisi_sayisi;
    printf("\nTum kayitlarin yas ortalamasi: %.2f\n", yas_ortalama);

    // Yaþý en büyük olan kaydý yazdýr
    printf("Yasi en buyuk olan kisi: Ad: %s, Soyad: %s, Yas: %d\n",
           kisiler[max_yas_indeksi].ad,
           kisiler[max_yas_indeksi].soyad,
           kisiler[max_yas_indeksi].yas);

    printf("***************************************************************\n\n");






    //****************************FGETC() KULLANIMI****************************//

    FILE* fgetcp = fopen("loremipsum.txt","r");

    char charr;
    if (fgetcp == NULL) {
        perror("Dosya acilamadi");
        return 1;
    }else{
        charr=fgetc(fgetcp);
        while(charr != EOF){
            printf("%c", charr);
            charr=fgetc(fgetcp);
        }
    }
    //*************************************************************************//


    //*****************************DOSYADAN OGR AD-SOYAD-NOT BILGISI OKUMA ALGORITMASI*****************************//

    FILE* ogrOku = fopen("ogrenciler.txt","r");


    char adOgr[25];
    char soyadOgr[25];
    int notOgr;

    if (ogrOku == NULL) {
        perror("Dosya acilamadi");
        return 1;
    }else{
        int lines = 0;
        char ch = fgetc(ogrOku);
        while(ch!=EOF){
            if(ch=='\n'){
                lines++;
            }
            ch = fgetc(ogrOku);
        }
        lines++;

        printf("\n\nDosyada %d adet ogrenci vardir.", lines);
        int toplam = 0;

        rewind(ogrOku);//bu pointer, char dizisinin sonuna ulasti. Simdi basa dondurduk ki bastan her seyi yazdiralim, yoksa okuyamaz.
        for(int i = 0; i<lines; i++){
            fscanf(ogrOku, "%s", &adOgr);
            fscanf(ogrOku, "%s", &soyadOgr);
            fscanf(ogrOku, "%d", &notOgr);
            toplam += notOgr;
        }
        double average = (double)toplam/lines;
        printf("\nOgrencilerin not ortalamasi: %lf\n\n\n", average);


    }

    //**********************************************************************************************************//






    //*****************************DOSYADAN OGR AD-SOYAD-NOT BILGISI OKUMA ALGORITMASI-2(STATIK)*****************************//
    printf("*********************************5 ADET KAYIT*********************************\n\n");

    FILE* ogrOku1 = fopen("5ogr.txt", "r");
    char ogrAd1[5][25];
    char ogrSoyad1[5][25];
    int ogrNot1[5];

    if (ogrOku1 == NULL) {
        perror("Dosya acilamadi");
        return 1;
    }else{
        int toplam = 0;
        for(int i = 0; i<5; i++){
            fscanf(ogrOku1, "%s", &ogrAd1[i]);
            fscanf(ogrOku1, "%s", &ogrSoyad1[i]);
            fscanf(ogrOku1, "%d", &ogrNot1[i]);
            printf("AD: %s SOYAD: %s NOT: %d\n", ogrAd1[i], ogrSoyad1[i], ogrNot1[i]);
            toplam += ogrNot1[i];
        }
        double average = (double)toplam/5;
        printf("\nOgrencilerin not ortalamasi: %lf\n", average);
    }
    printf("******************************************************************************");


    //***********************************************************************************************************************//

    fclose(file);
    fclose(fp);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fgetcp);
    fclose(ogrOku);
    fclose(ogrOku1);

    return 0;
}
