/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 8.7.2022                             *
 *****************************************************************************/
#ifndef __Globals_include__
#define __Globals_include__

#include "devices/PIT.h"

extern uint64_t              systime;    // wird all 10ms hochgezaehlt
extern PIT                   pit;        // Zeitgeber
 
#endif
