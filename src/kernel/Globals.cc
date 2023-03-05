/*****************************************************************************
 *                                                                           *
 *                               G L O B A L S                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Globale Variablen des Systems.                           *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/

#include "kernel/Globals.h"

CPU                   cpu;        
PCSPK                 pcspk;      // PC-Lautsprecher
//CGA_Stream            kout;       // Ausgabe-Strom fuer Kernel
VGA_Stream            kout;       // VGA-Ausgabe-Strom fuer Kernel
uint64_t              total_mem;  // RAM total
//BumpAllocator         allocator;       
LinkedListAllocator   allocator;       
IntDispatcher         intdis;     // Unterbrechungsverteilung
PIC                   pic;        // Interrupt-Controller
Keyboard              kb;         // Tastatur
Scheduler             scheduler;  // Scheduler
PIT                   pit(10000); // Zeitgeber (10ms) & Systemtime

