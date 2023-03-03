/*****************************************************************************
 *                                                                           *
 *                  S E M A L O O P T H R E A D                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Demo eines Threads. Schleife die Zahlen ausgibt.         *
 *                                                                           *
 * Autor:           Michael Schoettner, 10.7.2022                            *
 *****************************************************************************/

#ifndef __semaloopthread_include__
#define __semaloopthread_include__

#include "kernel/threads/Thread.h"

class SemaLoopThread : public Thread {
    
private:
    int id;

    SemaLoopThread (const SemaLoopThread &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    SemaLoopThread (int i) : Thread () { id = i; }

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif
