#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include<string.h>
struct kelimeler
{
    char *p;
    int kelimesayisi;
    struct kelimeler *next;
};
struct kelimeler *ilk=NULL;
//Onur hocadan yararlandik.
void bastir(struct kelimeler *p)
{
    p=ilk;
    int sayac=0;
    while(p!=NULL)
    {
        printf("%d.  %s  %d",sayac+1,p->p,(p->kelimesayisi));
        printf("\n");
        p=p->next;
        sayac++;
    }
}
//Onur hocadan yararlandik.
struct kelimeler * sonaEkle(struct kelimeler *r,char *p,int x)
{
    struct kelimeler *iter=r;
    while(iter->next!=NULL)
    {
        iter=iter->next;
    }
    struct kelimeler *degisken=(struct kelimeler *)malloc(sizeof(struct kelimeler));
    degisken->next=iter->next;
    iter->next=degisken;
    degisken->kelimesayisi=x;
    degisken->p=p;
    return r;
}

struct kelimeler * basaEkle(struct kelimeler *r,char *p,int x)
{
    if(r==NULL)
    {
        r=(struct kelimeler *)malloc(sizeof(struct kelimeler));
        r->next==NULL;
        ilk=r;
        r->p=p;
        r->kelimesayisi=x;
        return r;
    }
    if(r->kelimesayisi<x)
    {
        struct kelimeler *y=(struct kelimeler *)malloc(sizeof(struct kelimeler));
        y->p=p;
        y->kelimesayisi=x;
        y->next=r;
        ilk=y;
        return y;
    }

}
//https://www.youtube.com/watch?v=wDAf9Er6Qq8
struct kelimeler * arayaEkle(struct kelimeler *r,char *p,int x)
{
    struct kelimeler *iter=r;
    while(iter->next!=NULL&&iter->next->kelimesayisi>x)
    {
        iter=iter->next;
    }
    struct kelimeler *degisken=(struct kelimeler *)malloc(sizeof(struct kelimeler));
    degisken->next=iter->next;
    iter->next=degisken;
    degisken->kelimesayisi=x;
    degisken->p=p;
    return r;
}

struct kelimeler *siraliEkle(struct kelimeler *r,char *p,int x)
{
    if(r==NULL||r->kelimesayisi<x)
    {
        r=basaEkle(r,p,x);
        return r;
    }
    if(r->next!=NULL)
    {
        r=arayaEkle(r,p,x);
        return r;
    }
    if(r->next==NULL)
    {
        r=sonaEkle(r,p,x);
        return r;
    }
}

int main()
{
    setlocale(LC_ALL,"Turkish");
    FILE *dosya=fopen("X.txt","r");
    struct kelimeler *yeni;
    yeni=NULL;
    int sayac=1;
    int kelimesayisi=0;
    int kontrol=1;

    while(!feof(dosya))
    {
        int ctr=0;
        char *x=(char *)malloc(sizeof(char)*sayac);
        fscanf(dosya,"%s",x);
        printf("%s ",x);
        strlwr(x);
        FILE *dosya2=fopen("X.txt","r");
        while(!feof(dosya2))
        {
            char *y=(char *)malloc(sizeof(char)*kontrol);
            fscanf(dosya2,"%s",y);
            strlwr(y);
            kontrol++;
            if(strcmp(x,y)==0)
            {
                kelimesayisi++;
            }
        }
        kontrol=1;
        struct kelimeler *iter=yeni;


        while(iter!=NULL)
        {
            if(strcmp(iter->p,x)==0)
            {
                ctr++;
            }
            iter=iter->next;
        }
        if(ctr==0)
        {

            yeni=siraliEkle(yeni,x,kelimesayisi);
        }

        ctr=0;
        sayac++;
        kelimesayisi=0;
        fclose(dosya2);
    }

    printf("\n\n");
    bastir(yeni);
    fclose(dosya);

    return 0;
}
