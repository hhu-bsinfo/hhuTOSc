/*****************************************************************************
 *                                                                           *
 *                              S P I N L O C K                              *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung eines Spinlocks mithilfe der cmpxchg     *
 *					Instruktion. 											 *
 *                                                                           *
 * Autor:           Michael Schoettner, 2.2.2018                             *
 *****************************************************************************/

#include "lib/SpinLock.h"
#include "kernel/Globals.h"


/*****************************************************************************
 * Methode:         CAS				                                         *
 *---------------------------------------------------------------------------*
 * Parameter:       *ptr 	Adresse der Variable des Locks				     * 
 *        			old		Wert gegen den verglichen wird				     * 
 *        			_new	Wert der gesetzt werden soll				     * 
 *  																		 *
 * Beschreibung:    Semantik der Funktion CAS = Cmompare & Swap:		     * 
 *						if old == *ptr then									 *
 *   					    *ptr := _new									 *
 *  					return prev											 *
 *****************************************************************************/
static inline unsigned long CAS(unsigned long *ptr, unsigned long old, unsigned long _new)
{
    unsigned long prev;

    /*
        AT&T/UNIX assembly syntax

        The 'volatile' keyword after 'asm' indicates that the instruction 
        has important side-effects. GCC will not delete a volatile asm if 
        sit is reachable.
     */
    asm volatile("lock;"                            /* prevent race conditions with other cores        */
                 "cmpxchg %1, %2;"                  /* %1 = _new; %2 = *ptr          */
                                                    /* constraints */
                 : "=a"(prev)                       /* output: =a: RAX -> prev (%0))                             */
                 : "r"(_new), "m"(*ptr), "a"(old)   /* input = %1, %2, %3 (r=register, m=memory, a=accumlator = eax  */
                 : "memory");                       /* ensures assembly block will not be moved by gcc */
    return prev; // return pointer instead of prev to prevent unnecessary second call
}


/*****************************************************************************
 * Methode:         SpinLock::acquire                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lock belegen.    									     * 
 *****************************************************************************/
void SpinLock::acquire() {
    while (CAS(ptr, 0, 1) != 0);
}


/*****************************************************************************
 * Methode:         SpinLock::release                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Lock freigeben.    									     * 
 *****************************************************************************/
void SpinLock::release() {
    lock = 0;
}


