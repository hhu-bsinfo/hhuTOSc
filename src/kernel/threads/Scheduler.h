/*****************************************************************************
 *                                                                           *
 *                          S C H E D U L E R                                *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines einfachen Zeitscheiben-Schedulers  *
 *                  welcher praeemptive Threads in einer 'readQueue' ver-    *
 *                  waltet.                                                  *
 *                                                                           *
 *                  Der Scheduler wird mit 'schedule' gestartet. Neue Threads*
 *                  können mit 'ready' hinzugefügt werden. Ein Thread muss   *
 *                  die CPU freiwillig mit 'yield' abgeben, damit andere auch*
 *                  rechnen koennen. Ein Thread kann sich selbst mit 'exit'  *
 *                  terminieren. Ein Thread kann einen anderen Thread mit    *
 *                  'kill' beenden. Ein erzwungener Threadwechsel erfolgt    *
 *                  mit der Funktion 'preempt', welche von der Timer-ISR     *
 *                  aufgerufen wird.                                         *
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
    
    // Scheduler wird evt. von einer Unterbrechung vom Zeitgeber gerufen,
    // bevor er initialisiert wurde
    bool  initialized;
    
public:
    Scheduler ();

    // Scheduler initialisiert?
    // Zeitgeber-Unterbrechung kommt evt. bevor der Scheduler fertig
    // intiialisiert wurde!
    bool isInitialized() { return initialized; }
    
    // ruft nur der Idle-Thread (erster Thread der vom Scheduler gestartet wird)
    void setInitialized() { initialized = true; }

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
    
    // Thread umschalten; wird aus der ISR des PITs gerufen
    void preempt ();

    // Umschalten auf naechsten Thread, aber den 
    // Aufrufer nicht in die Ready-Queue einfuegen
    void block ();
    
    // 'that' wieder in die Ready-Queue einfuegen
    void deblock (Thread &that);

};

#endif
