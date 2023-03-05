/*****************************************************************************
 *                                                                           *
 *                  V G A _ S T R E A M                                      *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Die Klasse VGA_Stream ermoeglicht die Ausgabe verschied. *
 *                  Datentypen als Zeichenketten in einem VGA Grafik-Modus.  *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 7.7.2022                        *
 *****************************************************************************/
#ifndef __VESA_Stream_include__
#define __VESA_Stream_include__

#include "devices/VGA.h"
#include "lib/OutStream.h"

class VGA_Stream : public OutStream, public VGA {
    
private:
      VGA_Stream(VGA_Stream &copy); // Verhindere Kopieren

public:
      VGA_Stream () : OutStream(), VGA () { flush(); }

      // Methode zur Ausgabe des Pufferinhalts der Basisklasse StringBuffer.
      virtual void flush ();
};

#endif
