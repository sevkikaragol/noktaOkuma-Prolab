#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <ctype.h>
struct sayi{

    float x;
    float y;
    float z;
    int r;
    int g;
    int b;

};
int boslukkontrol(char *buffer){

    int i;
    int x=0;
    int sonuc=0;
    for(i=0;buffer[i]!='\n';i++){
    if(buffer[i]==' '){
    sonuc=sonuc+1;
    }
    }
    if(sonuc==5) x=1 ;
    else
    if(sonuc==0){ x=0;
    }
    else if(sonuc>=2 && sonuc<5){
    x=2;
    }
    if(!isdigit(buffer[0])){
    x=5;
    }

    return x;




}
int rgb(char *sevk){

    FILE *dosya;
    dosya=fopen(sevk,"r");
    if(dosya==NULL){
    printf("Dosya acilamadi.");
    }
    struct sayi *noktalar;
    int boyut=52*sizeof(int);
    noktalar=malloc(1*boyut);
    fseek(dosya,0,SEEK_SET);
    char buffer[100];
    int sayac=0,yer=0,x=0;
    int kontrol=1;
    fseek(dosya,0,SEEK_SET);
    while(!feof(dosya)){
    yer=ftell(dosya);
    fgets(buffer,50,dosya);
    if(isdigit(buffer[0])) break;
    }
    fseek(dosya,yer,SEEK_SET);
    while(!feof(dosya)){
    noktalar=realloc(noktalar,42*(sayac+1));
    yer=ftell(dosya);
    fgets(buffer,100,dosya);
    x=boslukkontrol(buffer);
    if(x==1){
     fseek(dosya,yer,SEEK_SET);
     fscanf(dosya,"%f %f %f",&(noktalar+sayac)->x,&(noktalar+sayac)->y,&(noktalar+sayac)->z);
     fscanf(dosya,"%d %d %d",&(noktalar+sayac)->r,&(noktalar+sayac)->g,&(noktalar+sayac)->b);

     sayac++;
     }
          else if(x==2){
        kontrol=0;
     }
     else if(x!=1 && x!=2 && x!=0 && x!=5){
        break;
     }
     }

    free(noktalar);
    return kontrol;


}
void ister5(char *sevk){
    FILE *dosya;
    dosya=fopen(sevk,"r");
    FILE *dosya2;
    dosya2=fopen("asciioutput.nkt","ab");
    if(dosya==NULL){
        printf("Dosya acilamadi.");
    }
    struct sayi *noktalar;
    int bellek=(52*sizeof(int));
    noktalar=malloc(1*bellek);
    fseek(dosya,0,SEEK_SET);
    char buffer[100];
    int sayac=0,yer=0,i,j,x=0;
    double toplamuzaklik=0;
    double mesafe;
    while(!feof(dosya)){
        noktalar=realloc(noktalar,42*(sayac+1));
        yer=ftell(dosya);
        fgets(buffer,50,dosya);
        x=boslukkontrol(buffer);
        if(x==1){
        fseek(dosya,yer,SEEK_SET);
        fscanf(dosya,"%f %f %f",&(noktalar+sayac)->x,&(noktalar+sayac)->y,&(noktalar+sayac)->z);
        fscanf(dosya,"%d %d %d",&(noktalar+sayac)->r,&(noktalar+sayac)->g,&(noktalar+sayac)->b);
        sayac++;
        }

         else if(x!=1 && x!=2 && x!=0 && x!=5){
            break;
        }
    }

    int karsilastirma=0;
    for(i=0;i<sayac-1;i++){
        for(j=i+1;j<sayac-2;j++){
        mesafe=sqrt(pow((noktalar[i].x-noktalar[j].x),2)+pow((noktalar[i].y-noktalar[j].y),2)+pow((noktalar[i].z-noktalar[j].z),2));
        toplamuzaklik=toplamuzaklik+mesafe;
        karsilastirma++;
    }
    }
    printf("Ascii ortalama=%lf\n",toplamuzaklik/karsilastirma);

    fprintf(dosya2,"Ortalama=%lf",toplamuzaklik/karsilastirma);

    free(noktalar);

}
void asciiokuma(char *sevk){

    FILE *dosya;
    dosya=fopen(sevk,"r");
    FILE *dosya2;
    dosya2=fopen("asciioutput.nkt","ab");
    if(dosya==NULL){
        printf("Dosya okunamadi.");
    }
    struct sayi *noktalar;
    int bellek=52*sizeof(int);
    noktalar=malloc(1*bellek);
    fseek(dosya,0,SEEK_SET);
    char buffer[100];
    int sayac=0,yer=0;
    int x=0,i,j;
    float mesafe=0;
    float eny=1000,enu=0;
    int eny1=0;
    int eny2=0;
    int enu1=0;
    int enu2=0;
    while(!feof(dosya)){
        noktalar=realloc(noktalar,42*(sayac+1));
        yer=ftell(dosya);
        fgets(buffer,50,dosya);
        x=boslukkontrol(buffer);
        if(x==1){
        fseek(dosya,yer,SEEK_SET);
        fscanf(dosya,"%f %f %f",&(noktalar+sayac)->x,&(noktalar+sayac)->y,&(noktalar+sayac)->z);
        fscanf(dosya,"%d %d %d",&(noktalar+sayac)->r,&(noktalar+sayac)->g,&(noktalar+sayac)->b);
        sayac++;
        }

         else if(x!=1 && x!=2 && x!=0 && x!=5){
            break;
        }
    }

    for(i=0;i<sayac-1;i++){
        for(j=i+1;j<sayac-2;j++){
        mesafe=sqrt(pow((noktalar[i].x-noktalar[j].x),2)+pow((noktalar[i].y-noktalar[j].y),2)+pow((noktalar[i].z-noktalar[j].z),2));
        if(mesafe<eny){
            eny=mesafe;
            eny1=i;
            eny2=j;
        }
        else if(mesafe>enu){
            enu=mesafe;
            enu1=i;
            enu2=j;
        }
    }
    }
        printf("\n");
        printf("%d.nokta %f %f %f %d %d %d\n",eny1,(noktalar+eny1)->x,(noktalar+eny1)->y,(noktalar+eny1)->z,(noktalar+eny1)->r,(noktalar+eny1)->g,(noktalar+eny1)->b);
        printf("%d.nokta %f %f %f %d %d %d\n",eny2,(noktalar+eny2)->x,(noktalar+eny2)->y,(noktalar+eny2)->z,(noktalar+eny2)->r,(noktalar+eny2)->g,(noktalar+eny2)->b);
        printf("%d.nokta %f %f %f %d %d %d\n",enu1,(noktalar+enu1)->x,(noktalar+enu1)->y,(noktalar+enu1)->z,(noktalar+enu1)->r,(noktalar+enu1)->g,(noktalar+enu1)->b);
        printf("%d.nokta %f %f %f %d %d %d\n",enu2,(noktalar+enu2)->x,(noktalar+enu2)->y,(noktalar+enu2)->z,(noktalar+enu2)->r,(noktalar+enu2)->g,(noktalar+enu2)->b);

        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",eny1,(noktalar+eny1)->x,(noktalar+eny1)->y,(noktalar+eny1)->z,(noktalar+eny1)->r,(noktalar+eny1)->g,(noktalar+eny1)->b);
        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",eny2,(noktalar+eny2)->x,(noktalar+eny2)->y,(noktalar+eny2)->z,(noktalar+eny2)->r,(noktalar+eny2)->g,(noktalar+eny2)->b);
        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",enu1,(noktalar+enu1)->x,(noktalar+enu1)->y,(noktalar+enu1)->z,(noktalar+enu1)->r,(noktalar+enu1)->g,(noktalar+enu1)->b);
        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",enu2,(noktalar+enu2)->x,(noktalar+enu2)->y,(noktalar+enu2)->z,(noktalar+enu2)->r,(noktalar+enu2)->g,(noktalar+enu2)->b);

        free(noktalar);

}
void kup(char *sevk){

    FILE *dosya;
    dosya=fopen(sevk,"r");
    FILE *dosya2;
    dosya2=fopen("asciioutput.nkt","ab");
    if(dosya==NULL){
        printf("Dosya acilamadi.");
    }
    struct sayi *noktalar;
    int bellek=52*sizeof(int);
    noktalar=malloc(1*bellek);
    fseek(dosya,0,SEEK_SET);
    char buffer[100];
    int sayac=0,yer=0,x=0;
    int i;
    while(!feof(dosya)){
        noktalar=realloc(noktalar,42*(sayac+1));
        yer=ftell(dosya);
        fgets(buffer,50,dosya);
        x=boslukkontrol(buffer);
        if(x==1){
        fseek(dosya,yer,SEEK_SET);
    fscanf(dosya,"%f %f %f",&(noktalar+sayac)->x,&(noktalar+sayac)->y,&(noktalar+sayac)->z);
    fscanf(dosya,"%d %d %d",&(noktalar+sayac)->r,&(noktalar+sayac)->g,&(noktalar+sayac)->b);

        sayac++;
    }

     else if(x!=1 && x!=2 && x!=0 && x!=5){
        break;
        }
    }
        float xek=1000,xeb=0;
        float yek=1000,yeb=0;
        float zek=1000,zeb=0;
        for(i=0;i<sayac;i++){
            if(xek>(noktalar+i)->x){
            xek=(noktalar+i)->x;}
            if(yek>(noktalar+i)->y){
            yek=(noktalar+i)->y;}
            if(zek>(noktalar+i)->z){
            zek=(noktalar+i)->z;}
            if(xeb<(noktalar+i)->x){
            xeb=(noktalar+i)->x;}
            if(yeb<(noktalar+i)->y){
            yeb=(noktalar+i)->y;}
            if(zeb<(noktalar+i)->z){
            zeb=(noktalar+i)->z;}
        }

    float xkenar=xeb-xek;
    float ykenar=yeb-yek;
    float zkenar=zeb-zek;
    float maxkenar=xkenar;
    if(ykenar>maxkenar) maxkenar=ykenar;
    if(zkenar>maxkenar) maxkenar=zkenar;
        printf("\nAscii\n");
        printf("\n Alt taban\n");
        printf("%f %f %f\n",xek+maxkenar,yek,zek);
        printf("%f %f %f\n",xek,yek,zek);
        printf("%f %f %f\n",xek,yek+maxkenar,zek);
        printf("%f %f %f\n",xek+maxkenar,yek+maxkenar,zek);
        printf("Ust taban\n");
        printf("\n%f %f %f",xek+maxkenar,yek,zek+maxkenar);
        printf("\n%f %f %f",xek,yek,zek+maxkenar);
        printf("\n%f %f %f",xek,yek+maxkenar,zek+maxkenar);
        printf("\n%f %f %f\n",xek+maxkenar,yek+maxkenar,zek+maxkenar);

        fprintf(dosya2,"\n%f %f %f",xek+maxkenar,yek,zek);
        fprintf(dosya2,"\n%f %f %f",xek,yek,zek);
        fprintf(dosya2,"\n%f %f %f",xek,yek+maxkenar,zek);
        fprintf(dosya2,"\n%f %f %f",xek+maxkenar,yek+maxkenar,zek);
        fprintf(dosya2,"\n%f %f %f",xek+maxkenar,yek,zek+maxkenar);
        fprintf(dosya2,"\n%f %f %f",xek,yek,zek+maxkenar);
        fprintf(dosya2,"\n%f %f %f",xek,yek+maxkenar,zek+maxkenar);
        fprintf(dosya2,"\n%f %f %f\n",xek+maxkenar,yek+maxkenar,zek+maxkenar);

    free(noktalar);

}
void kure(char *sevk){

    FILE *dosya;
    dosya=fopen(sevk,"r");
    FILE *dosya2;
    dosya2=fopen("asciioutput.nkt","ab");
    if(dosya==NULL){
        printf("Dosya acilamadi.");
    }
    struct sayi *noktalar;
    int bellek=52*sizeof(int);
    noktalar=malloc(1*bellek);
    fseek(dosya,0,SEEK_SET);
    char buffer[100];
    int sayac=0,yer=0,x=0,i;
    float mesafe=0;
    while(!feof(dosya)){
        noktalar=realloc(noktalar,42*(sayac+1));
        yer=ftell(dosya);
        fgets(buffer,50,dosya);
        x=boslukkontrol(buffer);
        if(x==1){
        fseek(dosya,yer,SEEK_SET);
        fscanf(dosya,"%f %f %f",&(noktalar+sayac)->x,&(noktalar+sayac)->y,&(noktalar+sayac)->z);
        fscanf(dosya,"%d %d %d",&(noktalar+sayac)->r,&(noktalar+sayac)->g,&(noktalar+sayac)->b);
        sayac++;
        }

         else if(x!=1 && x!=2 && x!=0 && x!=5){
            break;
        }
    }
    float mx,my,mz;
    float r;
    printf("Kure merkez noktalarini giriniz:(x,y,z) giriniz:");
    scanf("%f %f %f",&mx,&my,&mz);
    printf("\nKullanicidan alinan x degeri:%f",mx);
    printf("\nKullanicidan alinan x degeri:%f",my);
    printf("\nKullanicidan alinan x degeri:%f",mz);
    printf("\nKurenin yaricap degerini giriniz:");
    scanf("%f",&r);
    printf("\nKullanicidan alinan r degeri:%f",r);
    fprintf(dosya2,"\nKullanicidan alinan x degeri:%f",mx);
    fprintf(dosya2,"\nKullanicidan alinan y degeri:%f",my);
    fprintf(dosya2,"\nKullanicidan alinan z degeri:%f",mz);
    fprintf(dosya2,"\nKullanicidan alinan r degeri:%f",r);
    printf("\nKurenin icinde kalan noktalar:\n");
    fprintf(dosya2,"\nKurenin icinde kalan noktalar:\n");
    for(i=0;i<sayac-1;i++){
        mesafe=sqrt(pow(((noktalar+i)->x-mx),2)+pow(((noktalar+i)->y-my),2)+pow(((noktalar+i)->z-mz),2));
        if(mesafe<r){
            printf("%f %f %f %d %d %d\n",(noktalar+i)->x,(noktalar+i)->y,(noktalar+i)->z,(noktalar+i)->r,(noktalar+i)->g,(noktalar+i)->b);
            fprintf(dosya2,"%f %f %f %d %d %d\n",(noktalar+i)->x,(noktalar+i)->y,(noktalar+i)->z,(noktalar+i)->r,(noktalar+i)->g,(noktalar+i)->b);
        }
    }




    free(noktalar);


}
void binaryokuma(char *sevk){

    FILE *dosya;
    dosya = fopen(sevk, "r");
    FILE *dosya2;
    dosya2 = fopen("binaryoutput.nkt", "ab");
if (dosya == NULL){
    printf("Dosya acilamadi\n");
}
    char buffer[300];
    int satir=0,sayac=0;
    int i=1;
    int ctr=0;
    int j;
    float mesafe=0,eny=1000,enu=0;
    int eny1=0,eny2=0;
    int enu1=0,enu2=0;
    struct sayi *noktalar;
    int bellek=(i*50);
    noktalar=malloc(1*bellek);
    while(fgets(buffer,300,dosya)){
    satir++;
    if(satir==5){
    while (1)   {
    ctr++;
    size_t kontrol = fread(&noktalar[sayac], sizeof(struct sayi),1, dosya);
    sayac++;
    noktalar=realloc(noktalar,((i+1)*(bellek)));
    i++;
    if(kontrol==0){
        sayac--;
        i--;
    break;
    }
    }
    }
    }
    for(i=0;i<ctr-1;i++){
        for(j=i+1;j<ctr-2;j++){
        mesafe=sqrt(pow((noktalar[i].x-noktalar[j].x),2)+pow((noktalar[i].y-noktalar[j].y),2)+pow((noktalar[i].z-noktalar[j].z),2));
        if(mesafe<eny){
            eny=mesafe;
            eny1=i;
            eny2=j;
        }
        else if(mesafe>enu){
            enu=mesafe;
            enu1=i;
            enu2=j;
        }
    }
    }
       printf("\n");
       printf("%d.nokta %f %f %f %d %d %d\n",eny1,(noktalar+eny1)->x,(noktalar+eny1)->y,(noktalar+eny1)->z,(noktalar+eny1)->r,(noktalar+eny1)->g,(noktalar+eny1)->b);
        printf("%d.nokta %f %f %f %d %d %d\n",eny2,(noktalar+eny2)->x,(noktalar+eny2)->y,(noktalar+eny2)->z,(noktalar+eny2)->r,(noktalar+eny2)->g,(noktalar+eny2)->b);
        printf("%d.nokta %f %f %f %d %d %d\n",enu1,(noktalar+enu1)->x,(noktalar+enu1)->y,(noktalar+enu1)->z,(noktalar+enu1)->r,(noktalar+enu1)->g,(noktalar+enu1)->b);
        printf("%d.nokta %f %f %f %d %d %d\n",enu2,(noktalar+enu2)->x,(noktalar+enu2)->y,(noktalar+enu2)->z,(noktalar+enu2)->r,(noktalar+enu2)->g,(noktalar+enu2)->b);

        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",eny1,(noktalar+eny1)->x,(noktalar+eny1)->y,(noktalar+eny1)->z,(noktalar+eny1)->r,(noktalar+eny1)->g,(noktalar+eny1)->b);
        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",eny2,(noktalar+eny2)->x,(noktalar+eny2)->y,(noktalar+eny2)->z,(noktalar+eny2)->r,(noktalar+eny2)->g,(noktalar+eny2)->b);
        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",enu1,(noktalar+enu1)->x,(noktalar+enu1)->y,(noktalar+enu1)->z,(noktalar+enu1)->r,(noktalar+enu1)->g,(noktalar+enu1)->b);
        fprintf(dosya2,"%d.nokta %f %f %f %d %d %d\n",enu2,(noktalar+enu2)->x,(noktalar+enu2)->y,(noktalar+enu2)->z,(noktalar+enu2)->r,(noktalar+enu2)->g,(noktalar+enu2)->b);


    free(noktalar);

}
void kup_binary(char *sevk){

    FILE *dosya;
    dosya = fopen(sevk, "r");
    FILE *dosya2;
    dosya2 = fopen("binaryoutput.nkt", "ab");
    if (dosya == NULL){
    printf("Dosya acilamadi.\n");
}
    char buffer[200];
    int satir=0,sayac=0;
    int i=1,ctr=0;
    struct sayi *noktalar;
    int bellek=(i*50);
    noktalar=malloc(1*bellek);
    while(fgets(buffer,200,dosya)){
    satir++;
    if(satir==5){
    while (1)   {
    ctr++;
    size_t kontrol = fread(&noktalar[sayac], sizeof(struct sayi),1, dosya);
    sayac++;
    noktalar=realloc(noktalar,((i+1)*(bellek)));
    i++;
    if(kontrol==0){
        sayac--;
        i--;
    break;
    }
    }
    }
    }
        float xek=1000,xeb=0;
        float yek=1000,yeb=0;
        float zek=1000,zeb=0;
        for(i=0;i<ctr-1;i++){
            if(xek>(noktalar+i)->x){
            xek=(noktalar+i)->x;}
            if(yek>(noktalar+i)->y){
            yek=(noktalar+i)->y;}
            if(zek>(noktalar+i)->z){
            zek=(noktalar+i)->z;}
            if(xeb<(noktalar+i)->x){
            xeb=(noktalar+i)->x;}
            if(yeb<(noktalar+i)->y){
            yeb=(noktalar+i)->y;}
            if(zeb<(noktalar+i)->z){
            zeb=(noktalar+i)->z;}
        }
    float xkenar=xeb-xek;
    float ykenar=yeb-yek;
    float zkenar=zeb-zek;
    float maxkenar=xkenar;
    if(ykenar>maxkenar) maxkenar=ykenar;
    if(zkenar>maxkenar) maxkenar=zkenar;

        printf("\nBinary\n");
        printf("\n Alt taban\n");
        printf("\n%f %f %f ",xek+maxkenar,yek,zek);
        printf("\n%f %f %f ",xek,yek,zek);
        printf("\n%f %f %f ",xek,yek+maxkenar,zek);
        printf("\n%f %f %f ",xek+maxkenar,yek+maxkenar,zek);
        printf("\n Ust taban");
        printf("\n%f %f %f ",xek+maxkenar,yek,zek+maxkenar);
        printf("\n%f %f %f ",xek,yek,zek+maxkenar);
        printf("\n%f %f %f ",xek,yek+maxkenar,zek+maxkenar);
        printf("\n%f %f %f \n",xek+maxkenar,yek+maxkenar,zek+maxkenar);

        fprintf(dosya2,"\n%f %f %f ",xek+maxkenar,yek,zek);
        fprintf(dosya2,"\n%f %f %f ",xek,yek,zek);
        fprintf(dosya2,"\n%f %f %f ",xek,yek+maxkenar,zek);
        fprintf(dosya2,"\n%f %f %f ",xek+maxkenar,yek+maxkenar,zek);
        fprintf(dosya2,"\n%f %f %f ",xek+maxkenar,yek,zek+maxkenar);
        fprintf(dosya2,"\n%f %f %f ",xek,yek,zek+maxkenar);
        fprintf(dosya2,"\n%f %f %f ",xek,yek+maxkenar,zek+maxkenar);
        fprintf(dosya2,"\n%f %f %f \n",xek+maxkenar,yek+maxkenar,zek+maxkenar);
    free(noktalar);

}
void kure_binary(char *sevk){

    FILE *dosya;
    FILE *dosya2;
    dosya2=fopen("binaryoutput.nkt","ab");
    dosya = fopen(sevk, "r");
if (dosya == NULL){
    printf("Dosya acilamadi.\n");
}
    char buffer[200];
    int satir=0,sayac=0,ctr=0;
    int i=1;
    struct sayi *noktalar;
    int bellek=(i*50);
    noktalar=malloc((1*bellek));
    while(fgets(buffer,200,dosya)){
    satir++;
    if(satir==5){
    while (1)   {
    ctr++;
    size_t kontrol = fread(&noktalar[sayac], sizeof(struct sayi),1, dosya);
    sayac++;
    noktalar=realloc(noktalar,((i+1)*(bellek)));
    i++;
    if(kontrol==0){
        sayac--;
        i--;
    break;
    }
    }
    }
    }
        float mx,my,mz;
    float r;
    float mesafe;
    printf("Kure merkez noktalarini giriniz:(x,y,z) giriniz:");
    scanf("%f %f %f",&mx,&my,&mz);
    printf("\nKullanicidan alinan x degeri:%f",mx);
    printf("\nKullanicidan alinan x degeri:%f",my);
    printf("\nKullanicidan alinan x degeri:%f",mz);
    printf("\nKurenin yaricap degerini giriniz:");
    scanf("%f",&r);
    printf("\nKullanicidan alinan r degeri:%f",r);
    fprintf(dosya2,"\nKullanicidan alinan x degeri:%f",mx);
    fprintf(dosya2,"\nKullanicidan alinan y degeri:%f",my);
    fprintf(dosya2,"\nKullanicidan alinan z degeri:%f",mz);
    fprintf(dosya2,"\nKullanicidan alinan r degeri:%f",r);
    printf("\nKurenin icinde kalan noktalar:\n");
     fprintf(dosya2,"\nKurenin icinde kalan noktalar:\n");
    for(i=0;i<sayac-1;i++){
        mesafe=sqrt(pow(((noktalar+i)->x-mx),2)+pow(((noktalar+i)->y-my),2)+pow(((noktalar+i)->z-mz),2));
        if(mesafe<r){
            printf("%f %f %f %d %d %d\n",(noktalar+i)->x,(noktalar+i)->y,(noktalar+i)->z,(noktalar+i)->r,(noktalar+i)->g,(noktalar+i)->b);
            fprintf(dosya2,"%f %f %f %d %d %d\n",(noktalar+i)->x,(noktalar+i)->y,(noktalar+i)->z,(noktalar+i)->r,(noktalar+i)->g,(noktalar+i)->b);
        }
    }
    free(noktalar);


}
void ister5_binary(char *sevk){

    FILE *dosya;
    dosya = fopen(sevk, "r");
    FILE *dosya2;
    dosya2 = fopen("binaryoutput.nkt", "ab");
if (dosya == NULL){
    printf("Dosya acilamadi.\n");
}
    char buffer[200];
    int satir=0,sayac=0,ctr=0;
    int i=1,j;
    struct sayi *noktalar;
    int bellek=i*50;
    noktalar=malloc(1*bellek);
    while(fgets(buffer,200,dosya)){
    satir++;
    if(satir==5){
    while (1)   {
    ctr++;
    size_t kontrol = fread(&noktalar[sayac], sizeof(struct sayi),1, dosya);
    sayac++;
    noktalar=realloc(noktalar,((i+1)*(bellek)));
    i++;
    if(kontrol==0){
        sayac--;
        i--;
    break;
    }
    }
    }
    }
    double toplamuzaklik=0,mesafe=0;
    int karsilastirma=0;
    for(i=0;i<ctr-1;i++){
        for(j=i+1;j<ctr-2;j++){
        mesafe=sqrt(pow((noktalar[i].x-noktalar[j].x),2)+pow((noktalar[i].y-noktalar[j].y),2)+pow((noktalar[i].z-noktalar[j].z),2));
        toplamuzaklik=toplamuzaklik+mesafe;
        karsilastirma++;
    }
    }
    printf("\n");
    printf("Binary uzaklik ortalamasi=%lf\n",toplamuzaklik/karsilastirma);
    fprintf(dosya2,"Ortalama=%lf\n",toplamuzaklik/karsilastirma);


    free(noktalar);

}
void rgb_baski(char *sevk){

    FILE *dosya;
    dosya=fopen(sevk,"r");
    if(dosya==NULL){
        printf("Dosya acilamadi.");
    }
    struct sayi *noktalar;
    int bellek=52*sizeof(int);
    noktalar=malloc(1*bellek);
    fseek(dosya,0,SEEK_SET);
    char buffer[100];
    int sayac=0;
    int yer=0;
    int x=0;
    while(!feof(dosya)){
        noktalar=realloc(noktalar,41*(sayac+1));
        yer=ftell(dosya);
        fgets(buffer,50,dosya);
        x=boslukkontrol(buffer);
        if(x==1){
        fseek(dosya,yer,SEEK_SET);
        fscanf(dosya,"%f %f %f",&(noktalar+sayac)->x,&(noktalar+sayac)->y,&(noktalar+sayac)->z);
        fscanf(dosya,"%d %d %d",&(noktalar+sayac)->r,&(noktalar+sayac)->g,&(noktalar+sayac)->b);
        sayac++;
        }

        else if(x==2){
            printf("%s dosyasinin %d.satirinda Rgb bilgileri eksiktir.",sevk,sayac);
            break;
        }
         else if(x!=1 && x!=2 && x!=0 && x!=5){
            break;
        }
    }

    free(noktalar);
}
int main()
{
    DIR *folder;
    struct dirent *giris;
    char dosyadi[25][100];
    int dosyasayisi=0;
    int i;
    folder = opendir(".");
    if(folder == NULL)
    {
        printf("Dizin okunamiyor.");
        return(1);
    }
    while ((giris = readdir (folder)) != NULL)
    {
        int boyut = strlen(giris->d_name);
        if (boyut > 4&&giris->d_name[boyut- 4] == '.' &&giris->d_name[boyut- 3] == 'n' &&giris->d_name[boyut - 2] == 'k' &&giris->d_name[boyut- 1] == 't'){
            strcpy(dosyadi[dosyasayisi],giris->d_name);
            dosyasayisi++;
        }
    }
    char buffer[100];
    int satir=0;
    int sayac=0;
    char veri[25][100];
    int verisayaci=0;
    FILE *dosya;
    for(i=0;i<dosyasayisi;i++){
       dosya=fopen(dosyadi[i],"r");
    while(!feof(dosya)){
        satir=0;
        fgets(buffer,50,dosya);
        buffer[strlen(buffer)-1]='\0';
        if(strcmp(buffer,"# Noktalar dosya format")==0) sayac++;
        if(strcmp(buffer,"VERSION 1")==0) sayac++;
        if(strcmp(buffer,"ALANLAR x y z r g b")==0) sayac++;
        if(strcmp(buffer,"DATA ascii")==0) sayac++;
        else if(strcmp(buffer,"DATA binary")==0) sayac++;
        }
    if(sayac==4){
        strcpy(veri[verisayaci],dosyadi[i]);
        verisayaci++;
    }
    sayac=0;
    }

    int secim=0;
    satir=0;
    while(secim!=-1){

        printf("\nISLEMLER\n");
        printf("\n1)Dosya Kontrolu");
        printf("\n2)En Yakin/Uzak Noktalar");
        printf("\n3)Kup");
        printf("\n4)Kure");
        printf("\n5)Nokta Uzakliklari Ortalama");
        printf("\nProgramdan cikis yapmak icin -1'e basiniz.");
        printf("\nYapmak istediginiz islem nedir?:");

        scanf("%d",&secim);
         switch(secim){
    case 1:
        printf("Hatasiz dosyalar:\n");
        for(i=0;i<verisayaci;i++){
        dosya=fopen(veri[i],"r");
    while(!feof(dosya)){
        satir++;
        fgets(buffer,50,dosya);
        buffer[strlen(buffer)-1]='\0';
        FILE *dosya;
        FILE *dosya2;
        dosya=fopen("asciioutput.nkt","a");
        dosya2=fopen("binaryoutput.nkt","a");
        if(strcmp(buffer,"DATA ascii")==0){
        if(rgb(veri[i])==1){
        printf("\n%s\n",veri[i]);
        fprintf(dosya,"Hatasiz dosya=%s\n",veri[i]);
        fprintf(dosya2,"Hatasiz dosya=%s\n",veri[i]);
                    }
        else{
           rgb_baski(veri[i]);
           fprintf(dosya,"Hatali dosya=%s\n",veri[i]);
           fprintf(dosya2,"Hatali dosya=%s\n",veri[i]);
        }
        }
        else if(strcmp(buffer,"DATA binary")==0){
            printf("%s\n",veri[i]);
            fprintf(dosya,"Hatasiz dosya=%s\n",veri[i]);
            fprintf(dosya2,"Hatasiz dosya=%s\n",veri[i]);
        }
        if(satir==5){
            break;
        }
        }
            satir=0;
        }
    printf("\n***************************************************************");
    break;
    case 2:
    for(i=0;i<verisayaci;i++){
    dosya=fopen(veri[i],"r");
    while(!feof(dosya)){
        satir++;
        fgets(buffer,50,dosya);
        buffer[strlen(buffer)-1]='\0';
        if(strcmp(buffer,"DATA ascii")==0){
            if(rgb(veri[i])==1){
            asciiokuma(veri[i]);
        }
        }
        else if(strcmp(buffer,"DATA binary")==0){
        binaryokuma(veri[i]);
        }
        if(satir==5){
            break;
        }
        }
            satir=0;
        }
    printf("\n***************************************************************");
        break;
        case 3:
    for(i=0;i<verisayaci;i++){
        dosya=fopen(veri[i],"r");
        while(!feof(dosya)){
        satir++;
        fgets(buffer,50,dosya);
        buffer[strlen(buffer)-1]='\0';
        if(strcmp(buffer,"DATA ascii")==0){
            if(rgb(veri[i])==1){
            kup(veri[i]);
        }
        }
        else if(strcmp(buffer,"DATA binary")==0){
        kup_binary(veri[i]);
        }
        if(satir==5){
            break;
        }
        }
        satir=0;
        }
        printf("\n***************************************************************");
        break;
    case 4:
    for(i=0;i<verisayaci;i++){
        dosya=fopen(veri[i],"r");
        while(!feof(dosya)){
            satir++;
            fgets(buffer,50,dosya);
            buffer[strlen(buffer)-1]='\0';
            if(strcmp(buffer,"DATA ascii")==0){
            if(rgb(veri[i])==1){
            kure(veri[i]);
        }
        }
        else if(strcmp(buffer,"DATA binary")==0){
        kure_binary(veri[i]);
        }
    if(satir==5){
        break;
    }
    }
        satir=0;
        }
    printf("\n***************************************************************");
        break;
       case 5:
    for(i=0;i<verisayaci;i++){
        dosya=fopen(veri[i],"r");
        while(!feof(dosya)){

            satir++;
            fgets(buffer,50,dosya);
            buffer[strlen(buffer)-1]='\0';
            if(strcmp(buffer,"DATA ascii")==0){
            if(rgb(veri[i])==1){
                ister5(veri[i]);
            }
             }
            else if(strcmp(buffer,"DATA binary")==0){
                ister5_binary(veri[i]);
                    }
                if(satir==5){
                    break;
                }
                }
                satir=0;
            }
            printf("\n***************************************************************");
        break;
    case -1:
        printf("cikis yapildi.");
        break;
        default:
        printf("\nHatali bir giris yaptiniz.Lutfen tekrar deneyiniz.");
        break;
         }
    }
    return 0;
}
