/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers  *
 *                  welcher kooperative Threads in einer 'readQueue' ver-    *
 *                  waltet.                                                  *
 *                                                                           *
 *                  Der Scheduler wird mit 'schedule' gestartet. Neue Threads*
 *                  können mit 'ready' hinzugefügt werden. Ein Thread muss   *
 *                  die CPU freiwillig mit 'yield' abgeben, damit andere auch*
 *                  rechnen koennen. Ein Thread kann sich selbst mit 'exit'  *
 *                  terminieren. Ein Thread kann einen anderen Thread mit    *
 *                  'kill' beenden.                                          *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 21.12.2018                     *
 *****************************************************************************/


#ifndef __Scheduler_include__
#define __Scheduler_include__

#include "kernel/threads/Dispatch.h"
#include "kernel/threads/Thread.h"
#include "lib/Queue.h"

class Scheduler : public Dispatcher {
    
private:
    Scheduler (const Scheduler &copy); // Verhindere Kopieren
     
private:
    Queue readyQueue;   // auf die CPU wartende Threads
   
public:
    Scheduler () {}

    // Scheduler starten
    void schedule ();
    
    // Thread in ReadyQueue eintragen
    void ready (Thread* that);
    
    // Thread terminiert sich selbst
    void exit ();

    // Thread mit 'Gewalt' terminieren
    void kill (Thread* that);

    // CPU freiwillig abgeben und Auswahl des naechsten Threads
    void yield ();
};

#endif
