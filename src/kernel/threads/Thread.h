/*****************************************************************************
 *                                                                           *
 *                                 T H R E A D                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Thread-Konzepts.                   *
 *                                                                           *
 *                  Im Konstruktor wird Speicher für den Stack reserviert    *
 *                  sowie der initiale Kontext des Threads eingerichtet.     * 
 *                  Mit 'start' wird ein Thread aktiviert. Das Umschalten    * 
 *                  auf den naechsten Thread erfolgt durch 'switchTo'.       *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 16.12.2016                     *
 *****************************************************************************/

#ifndef __Thread_include__
#define __Thread_include__

#include "lib/Chain.h"
#include "lib/Types.h"

class Thread : public Chain {
    
private:
    Thread(const Thread &copy); // Verhindere Kopieren

private:
    uint64_t * stack;        // pointer auf Stack des Threads
    uint64_t   context; 	 // Stack-Zeiger auf gesicherten Kontext

public:
    unsigned int tid;       // Thread-ID (wird automatisch vergeben)
    
    Thread ();
    ~Thread ();
   
    // Thread aktivieren
    void start ();

    // Umschalten auf Thread 'next'
    void switchTo (Thread& next);

    // Methode des Threads, muss in Sub-Klasse implementiert werden
    virtual void run () = 0;
    
 };

#endif
