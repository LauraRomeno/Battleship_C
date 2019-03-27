/*---------------------------------------------------------------------------
|	Autor: Laura Romero Huete
|          laura.romeroH@estudiants.urv.cat
|	Data: Enero 2016                 Versio: 1.0
|----------------------------------------------------------------------------|
|	Nom: fitxer_text1.c
|   Descripcio del Programa:    Aquest programa inclou les funcions donandes
| ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define DIM_MAX     10
#define DIM_MIN     8

enum orientacio
{
    HORITZONTAL = 0,
    VERTICAL = 1
};

enum casella
{
    CASELLA_BUIDA = '?',
    CASELLA_AIGUA = '.',
    CASELLA_VAIXELL = '@',
    CASELLA_VAIXELL_TOCAT = 'X',
    CASELLA_AIGUA_TOCADA = '-'
};

enum tret
{
    ERROR = -1,
    REPETIT = 0,
    AIGUA = 1,
    TOCAT = 2,
    ENFONSAT = 3
};

/** capçaleres funcions */
/** =========================================================================
    acció inicia_taulell (dim:enter, var taulell_vaixells:taula de caràcters);

    - Inicialitza la disposició dels vaixells dins del taulell de vaixells.

    - Paràmetres formals:
        dim: (per valor) dimensió del taulell, ha de ser > DIM_MIN i < DIM_MAX.
            Abans de fer la crida, s'ha de validar que dim sigui correcte.
        taulell_vaixells: (per referència) taula de dues dimensions
            DIM_MAX x DIM_MAX. La mida del taulell real dependrà del
            paràmetre dim: dim x dim.
    =========================================================================*/
extern void inicia_taulell (int dim, char taulell_vaixells[][DIM_MAX]);

/** =========================================================================
    acció inicia_taulell_fix(dim:enter,var taulell_vaixells:taula de caràcter);

    - Inicialitza la disposició dels vaixells dins del taulell de vaixells
        sempre amb la mateixa configuració. Serveix per a fer proves.

    - Paràmetres formals:
        dim: (per valor) dimensió del taulell, ha de ser > 8 i < DIM_MAX.
            Abans de fer la crida, s'ha de validar que dim sigui correcte.
        taulell_vaixells: (per referència) taula de dues dimensions
            DIM_MAX x DIM_MAX. La mida del taulell real dependrà del
            paràmetre dim: dim x dim.
    =========================================================================*/
extern void inicia_taulell_fix (int dim, char taulell_vaixells[][DIM_MAX]);

/** =========================================================================
    funció dispara (f:caràcter, c:enter, var taulell_vaixells:taula de caràcters)
        retorna enter;

    - Retorna el resultat del llançament (REPETIT-0, AIGUA-1...) i
        actualitza el taulell de vaixells amb les anotacions pertinents:
        CASELLA_VAIXELL_TOCAT o CASELLA_AIGUA_TOCADA.
        Si hi ha un error en la fila o columna, o en el contingut de la casella,
        retorna ERROR.

    - Paràmetres formals:
        fila: (per valor) lletra de la fila, en majuscules. Ha de ser
            correcta d'acord amb les dimensions del taulell.
        col: (per valor) número de la columna, ha de ser correcte d'acord
            amb les dimensions del taulell.
        Abans de fer la crida, s'ha de validar que fila i col siguin correctes!
        taulell_vaixells: (per referència) taula de dues dimensions
            DIM_MAX x DIM_MAX.
    =========================================================================*/
extern int dispara (char fila, int col, char t[][DIM_MAX]);


