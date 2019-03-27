/*---------------------------------------------------------------------------
|	Autor: Laura Romero Huete
|          laura.romeroH@estudiants.urv.cat
|	Data: Enero 2016                 Versio: 1.0
|----------------------------------------------------------------------------|
|	Nom: fitxer_text1.c
|   Descripcio del Programa:    Aquest programa mostra el menú amb les
|                               opcions i demana a l'usuari que n'entri una.
|
| ---------------------------------------------------------------------------*/
/* Incloure llibreries estandard */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "vaixells.h"
#include "funcions.h"
#include "altres_funcions.h"
#include "tipus.h"

#define FITXER_RECORDS "podium.txt"
#define FITXER_JOC "partida.bin"
#define NUM 25
#define NOM 20



int main()
{
/* Declaracio de variables del programa */
int opcio_m, partida_guardada, dim, c=0, num_records=0, resultat, k, jugadors;
char taulell[DIM_MAX][DIM_MAX], f='Z', nomf[NUM];
record_tipus record[NUM];
bool correcte=false;
FILE *joc;
jugador_tipus taula_j;

/* Codi de l'algorisme */

opcio_m=0;
partida_guardada=0;

nomf[0]='a';
strcpy (nomf, FITXER_RECORDS);

correcte=recupera_records (nomf, &num_records, record, 0);

while ((opcio_m!=4)||(opcio_m<1)||(opcio_m>4)||(partida_guardada==0))
    {   printf("\nTria una opcio introduint el numero corresponent:\t");
        printf("\n1-Crear un nou joc.");
        printf("\n2-carregar joc emmagatzemat.");
        printf("\n3-Veure podium.");
        printf("\n4-Sortir del joc.\n");
        scanf("%i", &opcio_m);

switch(opcio_m)
    {case 1:    opcio_m=0;
                /*------crea un nou joc------*/

                printf("\nIndica les dimensions del taulell(8, 9, 10): ");
                scanf("%i", &dim);
                while (dim<8 || dim>10) {
                    printf("\nIndica les dimensions del taulell(8, 9, 10): ");
                    scanf("%i", &dim);
                }
                inicia_taulells(dim, taulell);

                /*---------------------------*/
                while ((opcio_m<1)||(opcio_m>2))
                {
                printf("\nDespres de crear el joc que vols fer?");
                printf("\n1-Jugar partida.");
                printf("\n2-Emagatzemar partida\n");
                scanf("%i", &opcio_m);

                switch(opcio_m)
                {   case 1: partida_guardada=1;
                        resultat=disparas(dim, f, c, taulell, 2, taula_j);
                        if (resultat==0) break ;  /* guardem partida */
                        if ((num_records<25)||(resultat>record[num_records-1].num))
                        {
                            correcte=afegir_record( nomf, record, &num_records, resultat);
                            if (correcte==true) printf("\nCorrecte afegir!");
                        }

                    break;

                    case 2:
                            while((jugadors!=0)&&(jugadors!=1))
                            {
                            printf("\nIndica numero de jugadors(0-maquina, 1-usuari): ");
                            scanf("%i", &jugadors);
                            }
                            taula_j.trets_fets=0;
                            taula_j.vaixells_enfonsats=0;
                            taula_j.resultat=0;

                            for(k=0; k<DIM_MAX; k++)
                            {
                            strcpy(taula_j.taulell_vaixells[k],taulell[k]);
                            }
                            for(k=0; k<DIM_MAX; k++)
                            {
                            strcpy(taula_j.taulell_llancaments[k],taulell[k]);
                            }
                            nomf[0]='a';
                            strcpy (nomf, FITXER_JOC);
                            correcte=emmagatzema_joc(nomf, dim, jugadors, taula_j);
                            if (correcte==true) printf("\nJoc guardat correctament!");
                            else printf("\nERROR AL GUARDAR JOC!");

                            partida_guardada=1;
                    break;

                }
     break;
     case 2:    joc=fopen("partida.bin", "r");
                if (joc==NULL)  {printf("\nNo tens cap partida gurdada!\n");
                                break;
                                }
                else {  nomf[0]='a';
                        strcpy (nomf, FITXER_JOC);
                        correcte=recupera_joc(nomf, &dim, &jugadors, &taula_j);

                         if (correcte==true) printf("\nJoc carregat correctament!");
                         else printf("\nERROR AL carregar JOC!");

                     }
                printf("\nDespres de carregar el joc emmagatzemat que vols fer?");
                printf("\n1-Jugar partida.");
                printf("\n2-Emagatzemar partida.\n");
                scanf("%i", &opcio_m);

                switch(opcio_m)
                {   case 1: partida_guardada=1;
                        printf("menu vaixells enfonsats:%i", taula_j.vaixells_enfonsats);
                        resultat=disparas(dim, f, c, taulell, jugadors, taula_j);
                        correcte=emmagatzema_records(nomf, &num_records, &record[NUM]);
                        if (correcte==true) printf("\nCorrecte!");

                    break;
                    case 2: printf("\nOpcio 2");
                            partida_guardada=1;
                    break;
                }

     break;
     case 3:    partida_guardada=1;

                correcte=recupera_records (nomf, &num_records, record, 1);

                if (correcte==true) printf("\nCorrecte!");
                else printf("\nIncorrecte");
     break;
     case 4: return 0;
    }

    }
    }/*tanca el while*/

return 0;   /* Retorna al S.O. sense cap error */
}







