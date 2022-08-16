#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define IPLENGTH 4
#define MAXLINE 16

typedef struct tnode *Treeptr;

typedef struct tnode
{
    unsigned char ipadresa[IPLENGTH];
    int brojpaketa;
    Treeptr lijevo;
    Treeptr desno;
} Treenode;

int poredjenjeip(unsigned char ip1[],unsigned char ip2[])
{

    int i;
    for(i=0; i<IPLENGTH; i++)
    {
        if(ip1[i]>ip2[i])
            return 1;
        if(ip1[i]<ip2[i])
            return -1;
    }
    return 0;

}

Treeptr kreirajnovicvor(unsigned char ipadr[])
{

    Treeptr temp = (Treeptr)malloc(sizeof(Treenode));

    int i;
    for(i=0; i<IPLENGTH; i++)
        temp->ipadresa[i]=ipadr[i];
    temp->brojpaketa=1;
    temp->lijevo = temp->desno = NULL;
}
Treeptr kreiraj(Treeptr ptr, unsigned char ipadr[])
{

    if(ptr == NULL)
        return kreirajnovicvor(ipadr);

    if(poredjenjeip(ptr->ipadresa,ipadr)==1)
        ptr->lijevo = kreiraj(ptr->lijevo,ipadr);

    else if(poredjenjeip(ptr->ipadresa,ipadr)==-1)
        ptr->desno = kreiraj(ptr->desno,ipadr);

    else
        ptr->brojpaketa++;


    return ptr;
}

//provjera da li se proslijedjeni string sastoji od cifara
int validirajbroj(char *str)
{
    while(*str)
    {
        if(!isdigit(*str))
            return 0;
        str++;
    }
    return 1;
}

int validacijaip(char *ipadr)
{
    int i, vrijednostokteta, tacke=0;
    char temp[strlen(ipadr)];
    strncpy(temp,ipadr,strlen(ipadr));
    temp[strlen(ipadr)-1] = '\0';

    char *oktet;
    if(temp == NULL)
        return 0;

    oktet=strtok(temp,"."); //izdvoji prvi oktet iz stringa

    if(oktet==NULL)
        return 0;
    while(oktet)
    {
        if(!validirajbroj(oktet))
        {
            printf("IP adresa sadrzi znak koji nije cifra\n");
            return 0;
        }
        vrijednostokteta = atoi(oktet); //pretvori oktet u cijeli broj
        if(vrijednostokteta>=0 && vrijednostokteta<=255)
        {
            oktet = strtok(NULL, ".");//izdvajanje sljedeceg okteta iz stringa
            if(oktet!=NULL)
                tacke++;
        }
        else
        {
            printf("IP adresa sadrzi oktet koji je izvan opsega 0-255\n");
            return 0;
        }
    }
    if(tacke!=3)
    {
        printf("IP adresa sadrzi vise od 4 okteta\n");
        return 0;
    }
    return 1;
}

void ispisi(Treeptr ptr)
{
    if(ptr!=NULL)
    {
        int i;

        ispisi(ptr->lijevo);

        for(i=0; i<IPLENGTH; i++)
            printf("%d ",ptr->ipadresa[i]);
        printf(" %d\n", ptr->brojpaketa);

        ispisi(ptr->desno);


    }
}

int parseip(char ipstring[],unsigned char ipadr[])
{


     if(validacijaip(ipstring) == 0)
     return 0;

    char oktet[4];
    int i,j=0,k=0;
    int duzinastringa= strlen(ipstring);
    for(i=0; ipstring[i]!='\0'; i++)
    {
        if(ipstring[i]!='.')
        {
            oktet[k++]=ipstring[i];
        }
        if(ipstring[i]=='.' || i==duzinastringa-1)
        {
            oktet[k]='\0';
            k=0;
            ipadr[j++]= atoi(oktet);
        }
    }


    return 1;
}

int main()
{
   int c,j;
    char line[MAXLINE];
    char upisanaipadresa[MAXLINE];
    unsigned char adresa[IPLENGTH];
    Treeptr korijen = NULL;
    i=0;
    printf("Unesite IP adrese:\n");
    while((c=getchar())!= EOF){
       if(c!='\n' && i!=MAXLINE-1)
        upisanaipadresa[i++] = c;
       if(c=='\n'){
        upisanaipadresa[i]='\0';
        if((j=parseip(upisanaipadresa,adresa))==1){
        if(korijen==NULL)
        korijen = kreiraj(korijen,adresa);
        else
           kreiraj(korijen,adresa);
        }

        i=0;
       }

    }
    ispisi(korijen);















    return 0;
}
