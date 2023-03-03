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

#ifndef __SpinLock_include__
#define __SpinLock_include__


class SpinLock {

private:
    SpinLock (const SpinLock &copy); // Verhindere Kopieren

    unsigned long lock;
    unsigned long* ptr;

public:
    SpinLock () : lock(0), ptr(&lock) {}

    void acquire();
    
    void release();
};

#endif
