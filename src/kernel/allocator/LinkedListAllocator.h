/*****************************************************************************
 *                                                                           *
 *                  L I N K E D L I S T A L L O C A T O R                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einfache Speicherverwaltung, welche den freien Speicher  *
 *                  mithilfe einer einfach verketteten Liste verwaltet.      *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.6.2020                        *
 *****************************************************************************/

#ifndef __LinkedListAllocator_include__
#define __LinkedListAllocator_include__

#include "kernel/Allocator.h"


// Format eines freien Blocks
struct free_block {
    unsigned int size;
    struct free_block *next;
};


class LinkedListAllocator : Allocator {
    
private:
      // freie Bloecke werden verkettet
      struct free_block *free_start;

      LinkedListAllocator(Allocator &copy); // Verhindere Kopieren

public:
      LinkedListAllocator () { }

      void init ();        
      void dump_free_memory ();
      void* alloc (uint64_t req_size);
      void free (void *ptr);

};

#endif
