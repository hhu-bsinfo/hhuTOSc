/*****************************************************************************
 *                                                                           *
 *                   H E L L O W O R L D T H R E A D                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ein einfacher Thread.                                    *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 16.12.2016                      *
 *****************************************************************************/
#ifndef __hello_world_thread_include__
#define __hello_world_thread_include__


#include "kernel/threads/Thread.h"


class HelloWorldThread : public Thread {
    
private:
    HelloWorldThread (const HelloWorldThread &copy); // Verhindere Kopieren

public:
    HelloWorldThread () : Thread () { }

    // Thread-Startmethode
    void run ();

 };

#endif
