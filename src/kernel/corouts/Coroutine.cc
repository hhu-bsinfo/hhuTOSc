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

#include "kernel/corouts/Coroutine.h"

// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++
// entsprechen.
extern "C"
{
    void Coroutine_start  (struct CoroutineState* regs);
    void Coroutine_switch (struct CoroutineState* regs_now,
                           struct CoroutineState* reg_then);
    
}


/*****************************************************************************
 * Prozedur:        Coroutine_init                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bereitet den Kontext der Koroutine fuer den ersten       *
 *                  Aufruf vor.                                              *
 *****************************************************************************/
void Coroutine_init (struct CoroutineState* regs, unsigned int* stack,
                     void (*kickoff)(Coroutine*), void* object) {
    
    register unsigned int **sp = (unsigned int**)stack;
    
    // Stack initialisieren. Es soll so aussehen, als waere soeben die
    // eine Funktion aufgerufen worden, die als Parameter den Zeiger
    // "object" erhalten hat.
    // Da der Funktionsaufruf simuliert wird, kann fuer die Ruecksprung-
    // adresse nur ein unsinniger Wert eingetragen werden. Die aufgerufene
    // Funktion muss daher dafuer sorgen, dass diese Adresse nie benoetigt
    // wird, sie darf also nicht terminieren, sonst kracht's.
    
    *(--sp) = (unsigned int*)object;    // Parameter
    *(--sp) = (unsigned int*)0x131155; // Ruecksprungadresse
    
    // Nun legen wir noch die Adresse der Funktion "kickoff" ganz oben auf
    // den Stack. Wenn dann bei der ersten Aktivierung dieser Koroutine der
    // Stackpointer so initialisiert wird, dass er auf diesen Eintrag
    // verweist, genuegt ein ret, um die Funktion kickoff zu starten.
    // Genauso sollen auch alle spaeteren Threadwechsel ablaufen.
    
    *(--sp) = (unsigned int*)kickoff;   // Adresse
    
    // Initialisierung der Struktur ThreadState mit den Werten, die die
    // nicht-fluechtigen Register beim ersten Starten haben sollen.
    // Wichtig ist dabei nur der Stackpointer.
    
    regs->ebx = 0;
    regs->esi = 0;
    regs->edi = 0;
    regs->ebp = 0;
    regs->esp = sp;
}


/*****************************************************************************
 * Funktion:        kickoff                                                  *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Funktion zum Starten einer Korutine. Da diese Funktion   *
 *                  nicht wirklich aufgerufen, sondern nur durch eine        *
 *                  geschickte Initialisierung des Stacks der Koroutine      *
 *                  angesprungen wird, darf er nie terminieren. Anderenfalls *
 *                  wuerde ein sinnloser Wert als Ruecksprungadresse         * 
 *                  interpretiert werden und der Rechner abstuerzen.         *
 *****************************************************************************/
void kickoff (Coroutine* object) {
    object->run();
    
    // object->run() kehrt hoffentlich nie hierher zurueck
    for (;;) {}
}


/*****************************************************************************
 * Methode:         Coroutine::Coroutine                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Initialer Kontext einer Koroutine einrichten.            *
 *                                                                           *
 * Parameter:                                                                *
 *      stack       Stack für die neue Koroutine                             *
 *****************************************************************************/
Coroutine::Coroutine (unsigned int* stack) {
    Coroutine_init (&regs, stack, kickoff, this);
 }


/*****************************************************************************
 * Methode:         Coroutine::switchToNext                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Auf die nächste Koroutine umschalten.                    *
 *****************************************************************************/
void Coroutine::switchToNext () {

    /* hier muss Code eingefügt werden */

}


/*****************************************************************************
 * Methode:         Coroutine::start                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Aktivierung der Koroutine.                               *
*****************************************************************************/
void Coroutine::start () {
    
    /* hier muss Code eingefügt werden */
    
}


/*****************************************************************************
 * Methode:         Coroutine::start                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Verweis auf nächste Koroutine setzen.                    *
 *****************************************************************************/
void Coroutine::setNext (Chain* next) {

    /* hier muss Code eingefügt werden */

}
