/*****************************************************************************
 *                                                                           *
 *                  G R A P H I C D E M O                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Graphicdemo.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.2.2023                       *
 *****************************************************************************/
#ifndef __graphic_demo_include__
#define __graphic_demo_include__


#include "kernel/threads/Thread.h"


class GraphicDemo : public Thread {
    
private:
    GraphicDemo (const GraphicDemo &copy); // Verhindere Kopieren

public:
    GraphicDemo () : Thread() { }

    // Einstieg in die Anwendung
    void run ();

 };

#endif
