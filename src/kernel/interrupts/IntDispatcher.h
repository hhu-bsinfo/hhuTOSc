/*****************************************************************************
 *                                                                           *
 *                         I N T D I S P A T C H E R                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zentrale Unterbrechungsbehandlungsroutine des Systems.   *
 *                  Der Parameter gibt die Nummer des aufgetretenen          *
 *                  Interrupts an. Wenn eine Interrupt Service Routine (ISR) *
 *                  in der Map registriert ist, so wird diese aufgerufen.    *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef __IntDispatcher_include__
#define __IntDispatcher_include__

#include "kernel/ISR.h"


class IntDispatcher {
    
private:
    IntDispatcher(const IntDispatcher &copy); // Verhindere Kopieren
    
    enum { size = 256 };
    ISR* map[size];

public:
    // Vektor-Nummern
    enum {
        timer = 32,
        keyboard = 33
    };
    
    // Initialisierung der ISR map mit einer Default-ISR.
    IntDispatcher ();
    
    // Registrierung einer ISR. (Rueckgabewert: 0 = Erfolg, -1 = Fehler) 
    int assign (unsigned int vector, ISR& gate);
    
    // ISR fuer 'vector' ausfuehren
    int report (unsigned int vector);
    
};

#endif
