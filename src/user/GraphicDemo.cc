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
 * Methode:         GraphicDemo::linInterPol1D                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Farbwert in einer Dimension interpoliert berechnen.      *
 *****************************************************************************/
int GraphicDemo::linInterPol1D(int x, int xr, int l, int r) {
    return ((((l>>16)*(xr-x)+(r>>16)*x)/xr)<<16)
    |(((((l>>8)&0xFF)*(xr-x)+((r>>8)&0xFF)*x)/xr)<<8)
    |(((l&0xFF)*(xr-x)+(r&0xFF)*x)/xr);
}


/*****************************************************************************
 * Methode:         GraphicDemo::linInterPol2D                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Farbwert in zwei Dimensionen interpoliert berechnen.     *
 *****************************************************************************/
int GraphicDemo::linInterPol2D(int x, int y, int lt, int rt, int lb, int rb) {
    return linInterPol1D(y, kout.yres,
                         linInterPol1D(x, kout.xres, lt, rt),
                         linInterPol1D(x, kout.xres, lb, rb) );
}


/*****************************************************************************
 * Methode:         GraphicDemo::run                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hauptthread der Anwendung.                               *
 *****************************************************************************/
void GraphicDemo::run () {
    kout.clear ();

    // Farbverlauf zeichnen  
    for (uint32_t y=0; y < kout.yres; y++) {
        for (uint32_t x=0; x < kout.xres; x++) {
            kout.drawPixel(x, y, linInterPol2D(x, y, 0x0000FF, 0x00FF00, 0xFF0000, 0xFFFF00));
        }
    }

    kout << "hhuTOS 0.7" << endl;
    kout << "==========" << endl << endl;
    kout << "Wir sind jetzt im Grafikmodus!" << endl;
    
    // selbst terminieren
    scheduler.exit ();
}
