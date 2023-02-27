/*****************************************************************************
 *                                                                           *
 *                                   C P U                                   *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Implementierung einer Abstraktion fuer den Prozessor.    *
 *                  Derzeit wird nur angeboten, Interrupts zuzulassen, zu    *
 *                  verbieten oder den Prozessor anzuhalten.                 *
 *                                                                           *
 * Autor:           Michael Schoettner, 30.7.16                              *
 *****************************************************************************/
#ifndef __CPU_include__
#define __CPU_include__


#include "lib/Types.h"


class CPU {
    
private:
    CPU(const CPU &copy);   // Verhindere Kopieren

public:
    CPU() {}

   // Interrupts erlauben
   inline void enable_int() {
      asm volatile("sti\n\t nop\n\t" : : : "memory");
   }

   /* Interrupts sperren
    * 
    * Rueckgabewert: true, wenn die Unterbrechungen zum Zeitpunkt des Aufrufs frei waren
    *                false, wenn sie schon gesperrt waren.
    */
   inline bool disable_int() {
      uintptr_t out;
	  asm volatile (
		"pushf\n\t"
		"pop %0\n\t"
		"cli\n\t"
		: "=r"(out)
		:
		: "memory"
	  );

	  bool enabled = (out & 0x200) != 0;
	  return enabled;
   }


   /* Prozessor einen Hinweis auf einen Spinloop geben und "kurz" anhalten
    *
    * Fördert die CPU Performance während eines Spinloops, indem ein kleiner
    * Moment gewartet wird und nicht auf den Speicher zugegriffen wird.
    */
   inline void pause() {
      asm volatile("pause\n\t" : : : "memory");
   }


   /* Prozessor bis zum nächsten Interrupt anhalten
    *
    *  Versetzt den Prozessor in den Haltezustand, aus dem er nur durch einen
    *  Interrupt wieder erwacht. Intern werden dazu die Interrupts mit \b sti
    *  freigegeben und der Prozessor mit \b hlt angehalten. Intel garantiert,
    *  dass die Befehlsfolge \b sti \b hlt atomar ausgeführt wird.
    */
   inline void idle() {
      asm volatile("sti\n\t hlt\n\t" : : : "memory");
   }
   
   
   /* Prozessor dauerhaft anhalten
    *
    *  Hält den Prozessor an. Intern werden dazu die Interrupts mit \b cli
    *  gesperrt und anschließend der Prozessor mit \b hlt angehalten. Da der
    *  Haltezustand nur durch einen Interrupt verlassen werden könnte, ist
    *  somit garantiert, dass die CPU bis zum nächsten Kaltstart "steht".
    *  Das Programm kehrt aus die() nie zurück. In einer
    *  Multiprozessorumgebung hat die Ausführung der Funktion nur
    *  Auswirkungen auf die CPU, die ihn ausführt. Die anderen CPUs laufen
    *  weiter.
    */
   inline void die() {
      asm volatile("cli\n\t hlt\n\t" : : : "memory");
   }


   /* Prozessor anhalten
    *
    *  Hält den Prozessor an. Intern wird dazu die \b hlt Instruktion ausgeführt.
    *  In diesem Zustand verbraucht der Prozessor sehr wenig Strom.
    *  Nur ein Interrupt kann den Prozessor aufwecken.
    */
   inline void halt() {
      asm volatile("hlt\n\t" : : : "memory");
   }

   /* Flag-Register zurueckgeben
    */
   inline uint64_t getflags() {
      uint64_t retval = 0;
      
      asm volatile("pushf;"
                   "pop %0;" : "=a" (retval) 
                  );
      return retval;
   }

};
#endif
