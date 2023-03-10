/*****************************************************************************
 *                                                                           *
 *                                  P I C                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Mit Hilfe des PICs koennen Hardware-Interrupts (IRQs)    *
 *                  einzeln zugelassen oder unterdrueckt werden. Auf diese   *
 *                  Weise wird also bestimmt, ob die Unterbrechung eines     *
 *                  Geraetes ueberhaupt an den Prozessor weitergegeben wird. *
 *                  Selbst dann erfolgt eine Aktivierung der Unterbrechungs- *
 *                  routine nur, wenn der Prozessor bereit ist, auf Unter-   *
 *                  brechungen zu reagieren. Dies kann mit Hilfe der Klasse  *
 *                  CPU festgelegt werden.                                   *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/
#ifndef __PIC_include__
#define __PIC_include__

class PIC {
    
private:
    PIC(const PIC &copy); // Verhindere Kopieren
public:
    PIC() {}
         
public:
    // IRQ-Nummern von Geraeten
    enum {
       timer    = 0,   // Programmable Interrupt Timer (PIT)
       keyboard = 1    // Tastatur
    };

    // Freischalten der Weiterleitung eines IRQs durch den PIC an die CPU
    void allow (int irq);

    // Unterdruecken der Weiterleitung eines IRQs durch den PIC an die CPU
    void forbid (int irq);

    // Abfragen, ob die Weiterleitung fuer einen bestimmten IRQ unterdrueckt ist
    bool status (int interrupt_device);
 };

#endif
