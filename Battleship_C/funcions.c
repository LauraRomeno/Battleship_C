/*---------------------------------------------------------------------------
|	Autor: Laura Romero Huete
|          laura.romeroH@estudiants.urv.cat
|	Data: Enero 2016                 Versio: 1.0
|----------------------------------------------------------------------------|
|	Nom: fitxer_text1.c
|   Descripcio del Programa:    Aquest programa inclou les funcions demanades als nivells 1 i 2
|
| ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "vaixells.h"

#define FITXER_RECORDS "podium.txt"
#define FITXER_JOC "partida.bin"
#define NUM 25
#define NOM 20

typedef struct
{
char nom[NOM];
int num;
}record_tipus;

typedef struct
{
char fila;
int col;
}coor_tipus;

typedef struct
{
int trets_fets, vaixells_enfonsats, resultat;
char taulell_vaixells[DIM_MAX][DIM_MAX], taulell_llancaments[DIM_MAX][DIM_MAX];
}jugador_tipus;

bool emmagatzema_joc (char nomf[], int dim, int num_jugadors, jugador_tipus taula_j)
{
FILE *joc;
char nom_jugador[NOM];

printf("\nIntrodueix el teu nom: ");
scanf(" %s", nom_jugador);

joc=fopen(nomf,"wb");

fwrite(&nom_jugador, sizeof(nom_jugador), 1, joc);
fwrite(&dim, sizeof(int), 1, joc);
fwrite(&num_jugadors, sizeof(int), 1, joc);
fwrite(&taula_j.trets_fets, sizeof(int), 1, joc);
fwrite(&taula_j.vaixells_enfonsats, sizeof(int), 1, joc);
fwrite(&taula_j.resultat, sizeof(int), 1, joc);
fwrite(&taula_j.taulell_llancaments, sizeof(taula_j.taulell_llancaments), 1, joc);
fwrite(&taula_j.taulell_vaixells, sizeof(taula_j.taulell_vaixells), 1, joc);

fclose(joc);

return true;
}

bool recupera_joc (char nomf[], int *dim, int *num_jugadors, jugador_tipus *taula_j)
{
FILE *joc;
char nom_jugador[NOM];

joc=fopen(nomf,"rb");

fread(&nom_jugador, sizeof(nom_jugador), 1, joc);
fread(&*dim, sizeof(int), 1, joc);
fread(&*num_jugadors, sizeof(int), 1, joc);
fread(&(*taula_j).trets_fets, sizeof(int), 1, joc);
fread(&(*taula_j).vaixells_enfonsats, sizeof(int), 1, joc);
fread(&(*taula_j).resultat, sizeof(int), 1, joc);
fread(&(*taula_j).taulell_llancaments, sizeof((*taula_j).taulell_llancaments), 1, joc);
fread(&(*taula_j).taulell_vaixells, sizeof((*taula_j).taulell_vaixells), 1, joc);

fclose(joc);
return true;
}

void jugar(int dim, char *f, int *c, char taulell_llancament[][DIM_MAX], int res)
{
char max;
int j, p;

switch (dim)
{
    case 8: max='H';
    break;
    case 9: max='I';
    break;
    case 10: max='J';
    break;
}
if (res==2)
{   j=(float)*f-65;
    p=*c-1;
    if((j>0)&&(taulell_llancament [j-1][p]=='?')) *f=(char)j-1+65;
    else
    {   if ((j<(dim-1))&&(taulell_llancament [j+1][p]=='?')) *f=(char)j+1+65;
        else
        {   if ((p>0)&&(taulell_llancament[j][p-1]=='?')) *c=p-1;
            else *c=p+1;
        }
    }
}
else
{

    *c=1+rand()%(dim+1-1);
    *f='A'+rand()%(max+1-'A');

j=(float)*f-65;
p=*c-1;

while (taulell_llancament [j][p]!='?')
{   *c=1+rand()%(dim+1-1);
    *f='A'+rand()%(max+1-'A');
    j=(float)*f-65;
    p=*c-1;
}
}/*tenca l'else*/
}

void nova_jugada(int dim, coor_tipus coor[])
{
char f='Z', lletra='Z';
int c=20;
switch (dim)
{
    case 8: lletra='H';
    break;
    case 9: lletra='I';
    break;
    case 10: lletra='J';
    break;
}
    while ((f>lletra)||(f<'A'))
    {printf("\nIntrodueix el caracter per la cordenada: ");
    scanf(" %c", &f);
    }
    while ((c>dim)||(c<1))
    {printf("\nIntrodueix el numero per la cordenada: ");
    scanf("%i", &c);
    }

    coor[0].fila=f;
    coor[0].col=c;
}

void inicia_taulells(int dim, char taulell_vaixells[][DIM_MAX])
{
int opcio=0;

while ((opcio<1)||(opcio>2))
{
printf("\nTipus de taulell(1-Fixe, 2-Aleatori): ");
scanf("%i", &opcio);
}
if (opcio==1) (inicia_taulell_fix (dim, taulell_vaixells));
if (opcio==2) (inicia_taulell(dim, taulell_vaixells));

}

int disparas(int dim, char f, int c, char taulell_vaixells[][DIM_MAX], int jugadors, jugador_tipus taula_j)
{
int i, j, p, k, mida, res, res_total=0, num_disp, puntuacio=0;
int fila, columna, fila1, fila2, col1, col2, max2;
char taulell_llancaments[DIM_MAX][DIM_MAX], lletres[DIM_MAX], LLETRA, seguir, nomf[NUM];
bool correcte=true;

coor_tipus coordenades[1];
mida = dim;

i=0;
srand (time(NULL));
LLETRA='A';

for(i=0; i<=DIM_MAX;i++)
{
    lletres[i]= LLETRA;
    LLETRA++;

}   /*Omple el taulell llancaments amb ? */
if (jugadors==2)
{

for (j=0; j<mida; j++)
{
    for (c=0; c<mida; c++)
    {   taulell_llancaments[j][c]='?';
    }
}
i=0;
num_disp=0;
res=0;
}
else
{   i=taula_j.vaixells_enfonsats;
    num_disp=taula_j.trets_fets;
    res_total=taula_j.resultat;
    for(k=0; k<DIM_MAX; k++)
    {
    strcpy(taulell_llancaments[k],taula_j.taulell_llancaments[k]);
    }
    taulell_vaixells=taula_j.taulell_vaixells;
    mida = dim;

}
printf("res: %i", res_total);
while((jugadors!=0)&&(jugadors!=1))
{
printf("\nIndica numero de jugadors(0-maquina, 1-usuari): ");
scanf("%i", &jugadors);
}

f='\0';
c=0;
seguir='1';
while ((i<10)&&(seguir=='1'))
    {
        /* Imprime el taulell a la pantalla */
        printf("\n  ");
        for (j=0; j<mida; j++) {printf("%i ", j+1 );}

        printf("\n");
         for (j=0; j<mida; j++)
        {
            /* Primer taulell */
            printf("\n%c ", lletres[j] );
            for (k=0; k<mida; k++)
            {   printf("%c ",taulell_llancaments[j][k]);
            }
        }
        printf("\n");

        if (jugadors==0) jugar(dim, &f, &c, taulell_llancaments, res);
        else {
                j=(float)f-65;
                p=c-1;

                while (taulell_llancaments [j][p]!='?')
                {   nova_jugada(dim, coordenades);
                    c=coordenades[0].col;
                    f=coordenades[0].fila;
                    j=(float)f-65;
                    p=c-1;

                }
             }

        res = dispara (f, c, taulell_vaixells);
        printf("\nResultat (%c,%d): %d", f, c, res);

j=(float)f-65;
p=c-1;

    switch(res)
{
    case 3: taulell_llancaments[j][p]='@';
        /*-------*/
	fila=(float)f-65;
	columna=c-1;
    max2=dim-1;

	col1=columna-1; if (col1<0) col1=0;
	while((col1!=0) && (taulell_llancaments[fila][col1]=='@')) {col1=col1-1;}
	col2=columna+1; if (col2>max2) col2=max2;
	while((col2!=max2) && (taulell_llancaments[fila][col2]=='@')) {col2=col2+1;}

	fila1=fila-1; if (fila1<0) fila1=0;
	while((fila1!=0)&&(taulell_llancaments[fila1][columna]=='@')) {fila1=fila1-1;}
	fila2=fila+1; if (fila2>max2) fila2=max2;
	while((fila2!=max2) && (taulell_llancaments[fila2][columna]=='@')) {fila2=fila2+1;}

	for (fila=fila1; fila<=fila2; fila++)
		{
		for (columna=col1; columna<=col2; columna++)
			{
			if (taulell_llancaments[fila][columna]=='?') taulell_llancaments[fila][columna]='.';
			}
		}
		/*--------------*/


    break;
    case 2: taulell_llancaments[j][p]='@';
    break;
    case 1: taulell_llancaments[j][p]='.';
    break;
    case 0:
    break;
}
        if (res==3) i++;
        res_total=res_total+res;
        num_disp++;

        seguir='2';
        while((seguir!='1')&&(seguir!='0'))
            {   printf("\n(1-Continuar, 0-Guargar): ");
                scanf(" %c", &seguir);
            }
    }
    if (seguir=='0') {
            taula_j.trets_fets=num_disp;
            taula_j.vaixells_enfonsats=i;
            taula_j.resultat=res_total;
            for(k=0; k<DIM_MAX; k++)
            {
               strcpy(taula_j.taulell_vaixells[k],taulell_vaixells[k]);
            }
            for(k=0; k<DIM_MAX; k++)
            {
               strcpy(taula_j.taulell_llancaments[k],taulell_llancaments[k]);
            }
            nomf[0]='a';
            strcpy(nomf, FITXER_JOC);

            correcte=emmagatzema_joc(nomf, dim, jugadors, taula_j);
            if (correcte==true) printf("\nJoc guardat correctament!");
            else printf("\nERROR AL GUARDAR JOC!");
            puntuacio=0;
    }
    else {
    puntuacio=(100*((float)mida/(float)num_disp)*(float)res_total);
    printf("\nPuntuacio de la partida: %i", puntuacio);
    }
    return puntuacio;
}

bool recupera_records(char nomf[], int *num_records, record_tipus record[NUM], int imprimir)
{
FILE *fitxer;
int i;
i=0;

fitxer=fopen(nomf, "r");
if (fitxer==NULL)   {  printf("\nEncara no hi ha records registrats.");
                    }
else{   if(!ftell(fitxer)) printf("Encara no hi ha records registrats.");
        else {
        fscanf(fitxer, "%s", record[i].nom);
        fscanf(fitxer, "%d", &record[i].num);
        while (!feof(fitxer))
        {   if (imprimir==1)
            {
            printf("\n %s", record[i].nom);
            printf("\t %d", record[i].num);
            }
            i++;
            fscanf(fitxer, "%s", record[i].nom);
            fscanf(fitxer, "%d", &record[i].num);
        }
        *num_records=i;
fclose(fitxer);
    }
}
return (true);

}

bool emmagatzema_records(char nomf[], int *num_records, record_tipus taula[NUM])
{
FILE *fitxer;
int i;
i=0;
    fitxer=fopen(nomf, "w");

        for (i=0; i<*num_records; i++)
        {
        fprintf(fitxer, "%s\t%i\n", taula[i].nom, taula[i].num);
        }
        fclose(fitxer);
return(true);
}




