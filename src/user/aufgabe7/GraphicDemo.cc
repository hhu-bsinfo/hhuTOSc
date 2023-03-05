/*****************************************************************************
 *                                                                           *
 *                  G R A P H I C D E M O                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Graphicdemo.                                             *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.2.2023                       *
 *****************************************************************************/

#include "devices/VGA.h"
#include "kernel/Globals.h"
#include "user/aufgabe7/GraphicDemo.h"


/*****************************************************************************
 * Methode:         GraphicDemo::run                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hauptthread der Anwendung.                               *
 *****************************************************************************/
void GraphicDemo::run () {
   
    kout.drawLine(0, 0, kout.xres, kout.yres, RGB_24(100,100,255));
    kout.drawLine(0, kout.yres, kout.xres, 0, RGB_24(255,0,0));
   
    // selbst terminieren
    scheduler.exit ();
}
