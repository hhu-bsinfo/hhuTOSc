/*****************************************************************************
 *                                                                           *
 *                             S E M A P H O R E                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung von Sempahor-Objekten.                   *
 *                                                                           *
 * Autor:           Michael Schoettner, 2.9.2016                             *
 *****************************************************************************/

#ifndef __Semaphore_include__
#define __Semaphore_include__


#include "lib/Types.h"
#include "lib/Queue.h"
#include "lib/SpinLock.h"


class Semaphore {

private:
    Semaphore (const Semaphore &copy); // Verhindere Kopieren
    
    // Queue fuer wartende Threads.
    Queue waitQueue;
    SpinLock lock;

    uint64_t counter;

public:
    // Konstruktor: Initialisieren des Semaphorzaehlers
    Semaphore (uint64_t c) : counter (c) {}

    // 'Passieren': Warten auf das Freiwerden eines kritischen Abschnitts.
    void p ();

    // 'Vreigeben': Freigeben des kritischen Abschnitts.
    void v ();
 };

#endif
