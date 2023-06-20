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

#include "devices/VGA_Stream.h"


/*****************************************************************************
 * Methode:         VGA_Stream::flush                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Methode zur Ausgabe des Pufferinhalts der Basisklasse    *
 *                  StringBuffer. Die Methode wird implizit aufgerufen,      *
 *                  sobald der Puffer voll ist, kann aber auch explizit      *
 *                  verwendet werden, um eine Ausgabe zu erzwingen.          *
 *****************************************************************************/
void VGA_Stream::flush () {
    print (buffer, pos);
    pos = 0;
 }

