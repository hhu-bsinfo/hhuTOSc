/*****************************************************************************
 *                                                                           *
 *                  G R A P H I C D E M O                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Graphicdemo.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 20.6.2023                       *
 *****************************************************************************/
#ifndef __graphic_demo_include__
#define __graphic_demo_include__


#include "kernel/threads/Thread.h"


class GraphicDemo : public Thread {
    
private:
    GraphicDemo (const GraphicDemo &copy); // Verhindere Kopieren
    
    int linInterPol1D(int x, int xr, int l, int r);
    int linInterPol2D(int x, int y, int lt, int rt, int lb, int rb);


public:
    GraphicDemo () : Thread() { }

    // Einstieg in die Anwendung
    void run ();

 };

#endif
