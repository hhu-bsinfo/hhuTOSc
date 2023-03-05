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


#include "lib/Types.h"
#include "kernel/CPU.h"
#include "devices/PCSPK.h"
#include "devices/CGA_Stream.h"
#include "kernel/allocator/BumpAllocator.h"
#include "kernel/allocator/LinkedListAllocator.h"
#include "kernel/interrupts/IntDispatcher.h"
#include "kernel/interrupts/PIC.h"
#include "devices/Keyboard.h"
#include "kernel/threads/Scheduler.h"
#include "devices/PIT.h"
#include "devices/VGA_Stream.h"


extern CPU                  cpu;        
extern PCSPK                pcspk;      // PC-Lautsprecher
extern CGA_Stream           kout;       // Ausgabe-Strom fuer Kernel
//extern VGA_Stream           kout;       // VGA-Ausgabe-Strom fuer Kernel
extern uint64_t             total_mem;  // RAM total
//extern BumpAllocator    allocator;       
extern LinkedListAllocator  allocator;       
extern IntDispatcher        intdis;     // Unterbrechungsverteilung
extern PIC                  pic;        // Interrupt-Controller
extern Keyboard             kb;         // Tastatur
extern Scheduler            scheduler;  // Scheduler
extern PIT                  pit;        // Zeitgeber & Systemtime

#endif
