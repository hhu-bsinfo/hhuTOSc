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
 *                  Im Konstruktor wird Speicher für den Stack reserviert    *
 *                  sowie der initiale Kontext des Threads eingerichtet.     * 
 *                  Mit 'start' wird ein Koroutine aktiviert. Das Umschalten *
 *                  auf die naechste Koroutine erfolgt durch 'switch2next'.  *
 *                                                                           *
 *                  Bei einem Koroutinenwechsel werden die Register auf dem  *
 *                  Stack gesichert. Die Instanzvariable 'context' zeigt auf *
 *                  den letzten hierfuer genutzten Stackeintrag.             *
 *                                                                           *
 * Autor:           Michael, Schoettner, HHU, 15.05.2023                     *
 *****************************************************************************/

#ifndef __Coroutine_include__
#define __Coroutine_include__

#include "lib/Chain.h"
#include "lib/Types.h"


class Coroutine : public Chain {
    
private:
    Coroutine(const Coroutine &copy); // Verhindere Kopieren

private:
    uint64_t *stack;    // Anfang des Speichers fuer den Stack
    uint64_t context; 	// Adresse des letzten genutzten Stack-Eintrags   
public:
    Coroutine ();
    ~Coroutine ();
    
    // Coroutine aktivieren
    void start ();
    
    // Auf die naechste Coroutine umschalten
    void switch2next ();
    
    // Methode der Coroutine, muss in Sub-Klasse implementiert werden
    virtual void run () = 0;
    
    // Verweis auf nächste Coroutine setzen
    void setNext (Chain* next);

 };

#endif
