/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef __Globals_include__
#define __Globals_include__

#include "kernel/CPU.h"
#include "devices/PCSPK.h"
#include "devices/CGA_Stream.h"

extern CPU              cpu; 
extern CGA_Stream       kout;       // Ausgabe-Strom fuer Kernel
extern PCSPK            pcspk;      // PC-Lautsprecher

#endif
