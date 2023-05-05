/*****************************************************************************
 *                                                                           *
 *                                M A I N                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstiegsfunktion in unser Betriebsystem ist 'main'.     * 
 *                  Diese Funktion wird vom Bootlader angesprungen.          *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 11.01.2023                      *
 *****************************************************************************/

#include "kernel/Globals.h"
#include "user/aufgabe3/KeyboardDemo.h"

extern "C" void init_interrupts();     // in 'interrupts.asm' 


void aufgabe03() {
   // Keyboard & Interrupts testen
   keyboard_demo();
}


/*****************************************************************************
 * Funktion:        main                                                     *
 *---------------------------------------------------------------------------*
 * Beschreibung:    C-Einstiegsfunktion fuer hhuTOS.                         *
 *****************************************************************************/
int main() {

   // Heapverwaltung initialisieren

   // IDT & PIC initialisieren
   init_interrupts();     // in 'interrupts.asm' 

   // Tastatur-Unterbrechungsroutine 'einstoepseln'

   // Interrupt-Verarbeitung durch CPU erlauben 




   aufgabe03();
    
      
   while (1) ; // wir kehren nicht zum Bootlader zurueck
   return 0;
}
