/*****************************************************************************
 *                                                                           *
 *                  C O R O U T I N E L O O P                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Loop ist eine Koroutine, die nichts weiter tut als einen *
 *                  Zaehler hochzuzaehlen und diesen auf dem Bildschirm      *
 *                  anzuzeigen und dann auf die naechste Koroutine umzu-     *
 *                  schalten.				 	 	 	                            			 *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 13.05.2023                      *
 *****************************************************************************/

#ifndef __coroutineloop_include__
#define __coroutineloop_include__

#include "kernel/corouts/Coroutine.h"
#include "lib/Types.h"


class CoroutineLoop : public Coroutine {
    
private:
    int id;

    CoroutineLoop (const CoroutineLoop &copy); // Verhindere Kopieren
    
public:
    // Gibt der Loop einen Stack und eine Id.
    CoroutineLoop (uint32_t i) : Coroutine () { id = i; }

    // Zaehlt einen Zaehler hoch und gibt ihn auf dem Bildschirm aus.
    void run ();
};

#endif
