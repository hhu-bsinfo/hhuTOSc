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
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/
#ifndef __Allocator_include__
#define __Allocator_include__

#include "lib/Types.h"


class Allocator {
    
private:
      Allocator(Allocator &copy); // Verhindere Kopieren

public:
      uint64_t heap_start;
      uint64_t heap_end;
      uint64_t heap_size;
      bool     initialized;

      Allocator ();

      virtual void init () = 0;        
      virtual void dump_free_memory () = 0;
      virtual void* alloc (uint64_t req_size) = 0;
      virtual void free (void *ptr) = 0;

};

#endif
