/*****************************************************************************
 *                                                                           *
 *                         S O U N D D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Test für den PC-Lautsprecher-Treiber.                    *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                      *
 *****************************************************************************/

#include "kernel/Globals.h"

void sound_demo() {
   kout << "Test des PC-Lautsprechers: ";
   kout << "playing tetris ..." << endl;
   pcspk.tetris ();
 
   kout << "playing aerodynamic ..." << endl;
   pcspk.aerodynamic ();
}
