/*****************************************************************************
 *                                                                           *
 *                              C O R O U T I N E                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Koroutinen-Konzepts.               *
 *                  Die Koroutinen sind miteinander verkettet, weswegen die  *
 *                  Klasse Coroutine ein Subtyp von 'Chain' ist.             *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext der Koroutine  *
 *                  eingerichtet. Mit 'start' wird ein Koroutine aktiviert.  *
 *                  Das Umschalten auf die naechste Koroutine erfolgt durch  *
 *                  Aufruf von 'switchToNext'.                               *
 *                                                                           *
 *                  Um bei einem Koroutinenwechsel den Kontext sichern zu    *
 *                  koennen, enthaelt jedes Koroutinenobjekt eine Struktur   *
 *                  CoroutineState, in dem die Werte der nicht-fluechtigen   *
 *                  Register gesichert werden koennen.                       *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 13.08.2020                     *
 *****************************************************************************/

#ifndef __Coroutine_include__
#define __Coroutine_include__

#include "kernel/corouts/CoroutineState.h"
#include "lib/Chain.h"

class Coroutine : public Chain {
    
private:
    Coroutine(const Coroutine &copy); // Verhindere Kopieren

private:
    struct CoroutineState regs;

public:
    Coroutine (unsigned int* stack);
    
    // Coroutine aktivieren
    void start ();
    
    // Auf die naechste Coroutine umschalten
    void switchToNext ();
    
    // Methode der Coroutine, muss in Sub-Klasse implementiert werden
    virtual void run () = 0;
    
    // Verweis auf nächste Coroutine setzen
    void setNext (Chain* next);

 };

#endif
