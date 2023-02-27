/*****************************************************************************
 *                                                                           *
 *                           O U T S T R E A M                               *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Die Klasse OutStream enthaelt die Definition des         *
 *                  << Operators fuer die wichtigsten der vordefinierten     *
 *                  Datentypen und realisiert somit die bekannte Ausgabe-    *
 *                  funktion der C++ iO_Stream Bibliothek. Zur Zeit wird     *
 *                  die Darstellung von Zeichen, Zeichenketten und ganzen    * 
 *                  Zahlen unterstuetzt. Ein weiterer << Operator erlaubt    *
 *                  die Verwendung von Manipulatoren.                        *
 *                                                                           *
 *                  Neben der Klasse OutStream sind hier auch die            *
 *                  Manipulatoren hex, dec, oct und bin fuer die Wahl der    *
 *                  Basis bei der Zahlendarstellung, sowie endl fuer den     * 
 *                  Zeilenumbruch definiert.                                 *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *                  Aenderungen von Michael Schoettner, HHU, 06.04.20        *
 *****************************************************************************/
#ifndef __OutStream_include__
#define __OutStream_include__

#include "lib/StringBuffer.h"

class OutStream : public StringBuffer {
    
private:
      OutStream(const OutStream &copy); // Verhindere Kopieren

public:
      int base;   // Basis des Zahlensystems: z.B. 2, 8, 10 oder 16

      OutStream () : StringBuffer () { base = 10; }   // initial Dezimalsystem

      virtual void flush () = 0;                    // weiterhin undefiniert

      // OPERATOR << : Umwandlung des angegebenen Datentypes in eine
      //               Zeichenkette.

      // Darstellung eines Zeichens (trivial)
      OutStream& operator << (char c);
      OutStream& operator << (unsigned char c);

      // Darstellung einer nullterminierten Zeichenkette
      OutStream& operator << (char* string);

      //  Darstellung ganzer Zahlen im Zahlensystem zur Basis base
      OutStream& operator << (short ival);
      OutStream& operator << (unsigned short ival);
      OutStream& operator << (int ival);
      OutStream& operator << (unsigned int ival);
      OutStream& operator << (long ival);
      OutStream& operator << (unsigned long ival);

      // Darstellung eines Zeigers als hexadezimale ganze Zahl
      OutStream& operator << (void* ptr);

      // Aufruf einer Manipulatorfunktion
      OutStream& operator << (OutStream& (*f) (OutStream&));
    
};


//
// Manipulatorfunktionen
//
// Die folgenden Funktionen erhalten und liefern jeweils eine Referenz auf
// ein OutStream Objekt. Da die Klasse OutStream einen Operator << fuer
// derartige Funktionen definiert, koennen sie mit Hilfe dieses Operators
// aufgerufen und sogar in weitere Eingaben eingebettet werden.
// Aufgabe der Manipulatoren ist, die Darstellung der nachfolgenden Ausgaben
// zu beeinflussen, z.B durch die Wahl des Zahlensystems.

// Zeilenumbruch in Ausgabe einfuegen.
OutStream& endl (OutStream& os);

// Waehle binaeres Zahlensystem aus.
OutStream& bin (OutStream& os);

// Waehle oktales Zahlensystem aus.
OutStream& oct (OutStream& os);

// Waehle dezimales Zahlensystem aus.
OutStream& dec (OutStream& os);

// Waehle hexadezimales Zahlensystem aus.
OutStream& hex (OutStream& os);

#endif

