/*****************************************************************************
 *                                                                           *
 *                          D I S P A T C H E R                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung des Dispatchers.                         *
 *                  Der Dispatcher verwaltet den 'active'-Pointer, der den   *
 *                  jeweils aktiven Thread angibt. Mit 'start()' wird der    *
 *                  'active' Pointer initialisiert und der erste Thread ge-  *
 *                  startet, alle weiteren Kontextwechsel werden mit         *
 *                  'dispatch()' ausgeloest. 'get_active()' liefert den      * 
 *                  'active' Pointer zurueck.                                *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "kernel/threads/Dispatch.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         Dispatcher::start                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Thread starten.                                          *
 *                                                                           *
 * Parameter:                                                                *
 *      first       Zu startender Thread.                                    *
 *****************************************************************************/
void Dispatcher::start (Thread& first) {
    if (!active) {
        active = &first;
        active->start ();
    }
}


/*****************************************************************************
 * Methode:         Dispatcher::dispatch                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Auf einen gegebenen Thread wechseln.                     *
 *                                                                           *
 * Parameter:                                                                *
 *      next        Thread der die CPU erhalten soll.                        *
 *****************************************************************************/
void Dispatcher::dispatch (Thread& next) {
    Thread* current = active;
    active = &next;
    current->switchTo (next);
}
