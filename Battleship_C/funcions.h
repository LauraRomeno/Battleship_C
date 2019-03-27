/*---------------------------------------------------------------------------
|	Autor: Laura Romero Huete
|          laura.romeroH@estudiants.urv.cat
|	Data: Enero 2016                 Versio: 1.0
|----------------------------------------------------------------------------|
|	Nom: fitxer_text1.c
|   Descripcio del Programa:    Aquest programa mostra les capçaleres de les
|                               funcions demanades al nivell 1 i 2
|
| ---------------------------------------------------------------------------*/
/* Incloure llibreries estandard */
#ifndef FUNCIONS_H_INCLUDED
#define FUNCIONS_H_INCLUDED

/*definicioó de constants*/
#define FITXER_RECORDS "podium.txt"
#define FITXER_JOC "partida.bin"
#define NUM 25
#define NOM 20

/*definició d'estructures*/
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

bool emmagatzema_joc (char nomf[], int dim, int num_jugadors, jugador_tipus taula_j);

bool recupera_joc (char nomf[], int *dim, int *num_jugadors, jugador_tipus *taula_j);

void jugar(int dim, char *f, int *c, char taulell_llancament[][DIM_MAX], int res);

void nova_jugada(int dim, coor_tipus coor[]);

void inicia_taulells(int dim, char taulell_vaixells[][DIM_MAX]);

int disparas(int dim, char f, int c, char taulell_vaixells[][DIM_MAX], int jugadors, jugador_tipus taula_j);

bool recupera_records(char nomf[], int *num_records, record_tipus record[NUM], int imprimir);

bool emmagatzema_records(char nomf[], int *num_records, record_tipus taula[NUM]);

bool afegir_record(char nomf[], record_tipus record[NUM], int *num_records, int puntuacio);


#endif
