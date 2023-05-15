/*****************************************************************************
 *                                                                           *
 *                              C H A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung einer einfach verketteten Liste von      *
 *                  Chain Objekten.                                          *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#ifndef __Chain_include__
#define __Chain_include__

class Chain {
    
private:
    Chain(const Chain &copy); // Verhindere Kopieren

public:
    Chain* next;

    Chain() {}
};

#endif
