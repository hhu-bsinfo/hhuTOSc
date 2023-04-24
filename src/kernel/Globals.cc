/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 8.7.2022                             *
 *****************************************************************************/

#include "kernel/Globals.h"

uint64_t              systime=0;  // wird all 10ms hochgezaehlt
PIT                   pit(10000); // Zeitgeber (10ms)
