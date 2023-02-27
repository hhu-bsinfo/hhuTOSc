/*****************************************************************************
 *                                                                           *
 *                           T E X T D E M O                                 *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Testausgaben für den CGA-Treiber.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 26.10.2018                       *
 *****************************************************************************/

#include "kernel/Globals.h"


void text_demo() {
   kout.clear ();

   kout << "Test der Zahlenausgabefunktion:" << endl;
   kout.setpos(0,2);

   kout << "  | dec | hex | bin   |" << endl;
   kout << "  ---------------------" << endl;
   for (int i = 0; i < 17; i++) {
      kout.setpos(2, i + 4);
      kout << "| ";
      kout << dec << i;
      kout.flush();
      kout.setpos(8, i + 4);
      kout << "| ";
      kout << hex << i;
      kout.flush();
      kout.setpos(14, i + 4);
      kout << "| ";
      kout << bin << i;
      kout.flush();
      kout.setpos(22, i + 4);
      kout << "| " << endl;
   }
   kout << endl;
}
