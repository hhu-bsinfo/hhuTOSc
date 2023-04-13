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

#ifndef __BumpAllocator_include__
#define __BumpAllocator_include__

#include "kernel/Allocator.h"


class BumpAllocator : Allocator {
    
private:
      unsigned char *next;
      unsigned int allocations;

      BumpAllocator(Allocator &copy); // Verhindere Kopieren

public:
      BumpAllocator () { }

      void init ();        
      void dump_free_memory ();
      void* alloc (uint64_t req_size);
      void free (void *ptr);

};

#endif
