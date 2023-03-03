/*****************************************************************************
 *                                                                           *
 *                  S E M A P H O R E D E M O                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Beispiel für Semaphore.                                  *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 21.8.2016                       *
 *****************************************************************************/
#ifndef __semaphore_demo_include__
#define __semaphore_demo_include__


#include "kernel/threads/Thread.h"


class SemaphoreDemo : public Thread {
    
private:
    SemaphoreDemo (const SemaphoreDemo &copy); // Verhindere Kopieren

public:
    SemaphoreDemo () : Thread() { }

    // Einstieg in die Anwendung
    void run ();

 };

#endif
