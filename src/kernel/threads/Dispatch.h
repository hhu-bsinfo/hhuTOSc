/*****************************************************************************
 *                                                                           *
 *                          D I S P A T C H E R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung des Dispatchers.                         *
 *                  Der Dispatcher verwaltet den 'active'-Pointer, der den   *
 *                  jeweils aktiven Thread angibt. Mit 'start()' wird der    *
 *                  'active' Pointer initialisiert und der erste Thread ge-  *
 *                  startet, alle weiteren Kontextwechsel werden mit         *
 *                  'dispatch()' ausgeloest. 'get_active()' liefert den      * 
 *                  'active' Pointer zurueck.                                *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/
#ifndef __dispatch_include__
#define __dispatch_include__

#include "kernel/threads/Thread.h"

class Dispatcher {
    
private:
    Thread* active;     // aktiver Thread

    Dispatcher(const Dispatcher &copy); // Verhindere Kopieren

public:
    Dispatcher () : active (0) {}
    void start (Thread& first);
    void dispatch (Thread& next);
    Thread* get_active () { return active; }
};

#endif
