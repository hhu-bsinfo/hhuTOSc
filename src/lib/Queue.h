/*****************************************************************************
*                                                                           *
*                              Q U E U E                                    *
*                                                                           *
*---------------------------------------------------------------------------*
* Beschreibung:    Implementierung einer einfach verketteten Liste von      *
*                  Chain Objekten. Die Implementierung ist etwas trickreich *
*                  'tail' verweist naemlich nicht, wie oft ueblich, auf das *
*                  letzte Element der Liste, sondern auf den 'next' Zeiger  *
*                  des letzten Elements, bzw., solange die Liste noch leer  *
*                  ist, auf den 'head' Zeiger der Liste. Dadurch muss beim  *
*                  Anfuegen eines Elements an die Liste nicht ueberprueft   *
*                  werden, ob bereits Elemente in ihr enthalten sind. Beim  *
*                  Entfernen von Elementen kann auf die Fallunterscheidung  *
*                  allerdings nicht verzichtet werden.                      *
*                                                                           *
* Autor:           Olaf Spinczyk, TU Dortmund                               *
*****************************************************************************/

#ifndef __Queue_include__
#define __Queue_include__

#include "lib/Chain.h"

class Queue {
    
private:
    Queue(const Queue &copy); // Verhindere Kopieren

protected:
    Chain* head;
    Chain** tail;

public:
    Queue () { head = 0; tail = &head; }
    void enqueue (Chain* item);
    Chain* dequeue ();
    void remove (Chain*);
 };

#endif

