/*---------------------------------------------------------------------------
|	Autor: Laura Romero Huete
|          laura.romeroH@estudiants.urv.cat
|	Data: Enero 2016                 Versio: 1.0
|----------------------------------------------------------------------------|
|	Nom: fitxer_text1.c
|   Descripcio del Programa:    Aquest programa mostra les capçaleres de
|                               funcions no demanades
| ---------------------------------------------------------------------------*/
#ifndef ALTRES_FUNCIONS_H_INCLUDED
#define ALTRES_FUNCIONS_H_INCLUDED

#define FITXER_RECORDS "podium.txt"
#define FITXER_JOC "partida.bin"
#define NUM 25
#define NOM 20
#include "funcions.h"

bool afegir_record(char nomf[], record_tipus record[NUM], int *num_records, int puntuacio);

#endif
