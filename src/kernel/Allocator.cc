/*****************************************************************************
 *                                                                           *
 *                            A L L O C A T O R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung. 'new' und 'delete' werden   *
 *                  durch Ueberladen der entsprechenden Operatoren           *
 *                  realisiert.                                              *
 *                                                                           *
 *        Heap:                                                              *
 *                    0x400000:	Start-Adresse der Heap-Verwaltung            *
 *                    0x4FFFFF: Ende: Letzte Adresse des phys. Speichers     *
 *                                                                           *
 * Achtung:         Benötigt einen PC mit mindestens 5 MB RAM!               *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 1.3.2022                        *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/Allocator.h"


#define MEM_SIZE_DEF        	 8*1024*1024 // Groesse des Speichers = 8 MB

#define HEAP_START           	 0x400000 	// Startadresse des Heaps
#define HEAP_SIZE	        	 2*1024*1024 	// Default-Groesse des Heaps

/*****************************************************************************
 * Konstruktor:     Allocator::Allocator                                     *
 *****************************************************************************/
Allocator::Allocator() {
   // Groesse des Hauptspeichers (kann über das BIOS abgefragt werden,
   // aber sehr umstaendlich, daher hier fest eingetragen
   total_mem = MEM_SIZE_DEF;

   heap_start = HEAP_START;
   heap_end   = HEAP_START + HEAP_SIZE;
   heap_size  = HEAP_SIZE;
}


/*****************************************************************************
 * Nachfolgend sind die Operatoren von C++, die wir hier ueberschreiben      *
 * und entsprechend 'mm_alloc' und 'mm_free' aufrufen.                       *
 *****************************************************************************/
void* operator new ( size_t size ) {
     return allocator.alloc(size);
}

void* operator new[]( size_t count ) {
    return allocator.alloc(count);
}

void operator delete ( void* ptr )  {
    allocator.free(ptr);
}
 
void operator delete[] ( void* ptr ) {
    allocator.free(ptr);
}

void operator delete(void*ptr, unsigned int sz) {
    allocator.free(ptr);
}

void operator delete(void*ptr, unsigned long sz) {
    allocator.free(ptr);
}
