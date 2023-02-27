/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Startroutine, wird direkt vom Bootlader angesprungen,    *
 *                  nachdem dieser in den Protected Mode geschaltet hat und  *
 *                  die GDT und IDT initalisiert hat.                        *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/TextDemo.h"
#include "user/SoundDemo.h"


int main() {
    /* Hier muess Code eingefuegt werden */

    // Bildschirm loeschen.
    
    // Startmeldung ausgeben

    text_demo();
    
    sound_demo();

    while (1);
    return 0;
 }
