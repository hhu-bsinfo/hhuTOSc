/*****************************************************************************
 *                                                                           *
 *                     C G A _ S T R E A M                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Die Klasse CGA_Stream ermoeglicht die Ausgabe verschied. *
 *                  Datentypen als Zeichenketten auf dem CGA-Bildschirm eines*
 *                  PCs. Fuer weitergehende Formatierung oder spezielle      *
 *                  Effekte stehen die Methoden der Klasse CGA_Stream zur    *
 *                  Verfuegung.                                              *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 1.8.16          *
 *****************************************************************************/

#include "devices/CGA_Stream.h"


/*****************************************************************************
 * Methode:         CGA_Stream::flush                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Methode zur Ausgabe des Pufferinhalts der Basisklasse    *
 *                  StringBuffer. Die Methode wird implizit aufgerufen,      *
 *                  sobald der Puffer voll ist, kann aber auch explizit      *
 *                  verwendet werden, um eine Ausgabe zu erzwingen.          *
 *****************************************************************************/
void CGA_Stream::flush () {
    print (buffer, pos);
    pos = 0;
}

