/*****************************************************************************
 *                                                                           *
 *                        B U M P A L L O C A T O R                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Eine sehr einfache Heap-Verwaltung, welche freigegebenen *
 *                  Speicher nicht mehr nutzen kann.                         *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 3.3.2022                        *
 *****************************************************************************/

#include <stddef.h>
#include "kernel/Globals.h"
#include "kernel/allocator/LinkedListAllocator.h"


/*****************************************************************************
 * Methode:         BumpAllocator::init                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    BumpAllokartor intitialisieren.                          *
 *****************************************************************************/
void BumpAllocator::init() {

     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         BumpAllocator::dump_free_memory                          *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ausgabe der Freispeicherinfos. Zu Debuggingzwecken.      *
 *****************************************************************************/
void BumpAllocator::dump_free_memory() {
    
     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         BumpAllocator::alloc                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einen neuen Speicherblock allozieren.                    * 
 *****************************************************************************/
void * BumpAllocator::alloc(uint64_t req_size) {

     /* Hier muess Code eingefuegt werden */

}


/*****************************************************************************
 * Methode:         BumpAllocator::free                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Nicht implementiert.                                     *
 *****************************************************************************/
void BumpAllocator::free(void *ptr) {
    kout << "   mm_free: ptr= " << hex << (uint64_t)ptr << ", not supported" << endl;
}

