/*****************************************************************************
 *                                                                           *
 *                  C O R O U T I N E                                        *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Koroutinen-Konzepts.               *
 *                                                                           *
 *                  Die Koroutinen sind miteinander verkettet, weswegen die  *
 *                  Klasse Coroutine ein Subtyp von 'Chain' ist.             *
 *                                                                           *
 *                  Im Konstruktor wird der initialie Kontext der Koroutine  *
 *                  eingerichtet. Mit 'start' wird ein Koroutine aktiviert.  *
 *                  Das Umschalten auf die naechste Koroutine erfolgt durch  *
 *                  Aufruf von 'switchToNext'.                               *
 *                                                                           *
 *                  Bei einem Koroutinenwechsel werden die Register auf dem  *
 *                  Stack gesichert. Die Instanzvariable 'context' zeigt auf *
 *                  den letzten hierfuer genutzten Stackeintrag.             *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 13.01.2023                     *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "kernel/corouts/Coroutine.h"

// Funktionen, die auf der Assembler-Ebene implementiert werden, muessen als
// extern "C" deklariert werden, da sie nicht dem Name-Mangeling von C++
// entsprechen.
extern "C"
{
    void Coroutine_start  (void* context);
    void Coroutine_switch (void* context_now, void *context_then);
}


/*****************************************************************************
 * Prozedur:        Coroutine_init                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bereitet den Kontext der Koroutine fuer den ersten       *
 *                  Aufruf vor.                                              *
 *****************************************************************************/
void Coroutine_init (uint64_t *stackptr, uint64_t *stack,
                     void (*kickoff)(Coroutine*), void* object) {
    
    uint64_t **sp = (uint64_t**)stack;

    // Stack initialisieren. Es soll so aussehen, als waere soeben die
    // eine Funktion aufgerufen worden, die als Parameter den Zeiger
    // "object" erhalten hat.
    // Da der Funktionsaufruf simuliert wird, kann fuer die Ruecksprung-
    // adresse nur ein unsinniger Wert eingetragen werden. Die aufgerufene
    // Funktion muss daher dafuer sorgen, dass diese Adresse nie benoetigt
    // wird, sie darf also nicht terminieren, sonst kracht's.
    *(--sp) = (uint64_t *)0x131155; // Ruecksprungadresse
    
    // Nun legen wir noch die Adresse der Funktion "kickoff" ganz oben auf
    // den Stack. Wenn dann bei der ersten Aktivierung dieser Koroutine der
    // Stackpointer so initialisiert wird, dass er auf diesen Eintrag
    // verweist, genuegt ein ret, um die Funktion kickoff zu starten.
    // Genauso sollen auch alle spaeteren Coroutinen-Wechsel ablaufen.
    
    *(--sp) = (uint64_t *)kickoff;  // Adresse

    // Nun sichern wir noch alle relevanten Register auf dem Stack
    *(--sp) = (uint64_t *)0;    	// r8
    *(--sp) = (uint64_t *)0;   		// r9
    *(--sp) = (uint64_t *)0;   		// r10
    *(--sp) = (uint64_t *)0;   		// r11
    *(--sp) = (uint64_t *)0;   		// r12
    *(--sp) = (uint64_t *)0;   		// r13
    *(--sp) = (uint64_t *)0;   		// r14
    *(--sp) = (uint64_t *)0;   		// r15
    *(--sp) = (uint64_t *)0;   		// rax
    *(--sp) = (uint64_t *)0;   		// rbx
    *(--sp) = (uint64_t *)0;   		// rcx
    *(--sp) = (uint64_t *)0;   		// rdx

    *(--sp) = (uint64_t *)0;   		// rsi
    *(--sp) = (uint64_t *)object; 	// rdi -> 1. Param fuer 'kickoff'
    *(--sp) = (uint64_t *)0;   		// rbp
    *(--sp) = (uint64_t *)cpu.getflags(); // flags

    // Zum Schluss speichern wir den Zeiger auf den zuletzt belegten
    // Eintrag auf dem Stack in 'stackptr'. Daruber gelangen wir in 
    // Coroutine_start an die noetigen Register     
    *stackptr = (uint64_t)sp;		// aktuellen Stack-Zeiger speichern
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
Coroutine::Coroutine (uint64_t *stack) {
    Coroutine_init (&context, stack, kickoff, this);
 }


/*****************************************************************************
 * Methode:         Coroutine::switchToNext                          	     *
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
