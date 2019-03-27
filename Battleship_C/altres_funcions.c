/*---------------------------------------------------------------------------
|	Autor: Laura Romero Huete
|          laura.romeroH@estudiants.urv.cat
|	Data: Enero 2016                 Versio: 1.0
|----------------------------------------------------------------------------|
|	Nom: fitxer_text1.c
|   Descripcio del Programa:    Aquest programa inclou altres funcions no demanades
|
| ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "menu.h"
#include "funcions.h"


#define FITXER_RECORDS "podium.txt"
#define FITXER_JOC "partida.bin"
#define NUM 25
#define NOM 20


bool afegir_record(char nomf[], record_tipus record[NUM], int *num_records, int puntuacio)
{
record_tipus taula[NUM];
int i, j, fet;
bool correcte;
char nom[NOM];

j=0; fet=0;
printf("\nIntrodueix el nom: ");
scanf("%s", nom);

for(i=0; i<*num_records; i++)
{
    if (puntuacio>record[i].num && fet==0)
    {
        taula[j].num=puntuacio;
        strcpy(taula[j].nom, nom);
        j++;
        fet=1;
    }
    if (j==25) break;
    taula[j].num=record[i].num;
    strcpy(taula[j].nom, record[i].nom);
    j++;
}
if(*num_records==0)
{
taula[j].num=puntuacio;
strcpy(taula[j].nom, nom);
j=1;
}
*num_records=j;
for(i=0; i<*num_records; i++)
{
    record[i].num=taula[i].num;
    strcpy(record[i].nom, taula[i].nom);
}

    correcte=emmagatzema_records(nomf, &*num_records, record);
    if (correcte==true) printf("\nCorrecte emagatzema!");

return true;
}
