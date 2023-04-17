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
 *                  Aenderungen von Michael Schoettner, HHU, 1.8.16          *
 *****************************************************************************/

#include "lib/OutStream.h"


//
// Zeichen und Zeichenketten in Stream ausgeben
//
OutStream& OutStream::operator << (char c) {
    put(c);
    return *this;
}

OutStream& OutStream::operator << (uint8_t c) {
    return *this << (char) c;
}

OutStream& OutStream::operator << (char* string) {
    char* pos = string;
    while (*pos) {
        put (*pos);
        pos++;
    }
    return *this;
}

//
//  Ganzer Zahlen im Zahlensystem zur Basis base in Stream ausgeveb
//  Alle vorzeichenbehafteten Datentypen werden als long dargestellt,
//  Alle vorzeichenlosen als unsigned long.
OutStream& OutStream::operator << (int16_t ival) {
    return *this << (int64_t) ival;
}
  
OutStream& OutStream::operator << (uint16_t ival) {
    return *this << (uint64_t) ival;
}
  
OutStream& OutStream::operator << (int32_t ival) {
    return *this << (int64_t) ival;
}
  
OutStream& OutStream::operator << (uint32_t ival) {
    return *this << (uint64_t) ival;
}

// Darstellung eine vorzeichenbehafteten ganzen Zahl.
OutStream& OutStream::operator << (int64_t ival) {
    // Bei negativen Werten wird ein Minuszeichen ausgegeben.
    if (ival < 0) {
        put ('-');
        ival = -ival;
    }
    // Dann wird der Absolutwert als vorzeichenlose Zahl ausgegeben.
    return *this << (uint64_t) ival;
}

// Darstellung einer vorzeichenlosen ganzen Zahl.
OutStream& OutStream::operator << (uint64_t ival) {
    uint64_t div;
    char digit;
   
    if (base == 8)
        put ('0');         // oktale Zahlen erhalten eine fuehrende Null
    else if (base == 16) {
        put ('0');         // hexadezimale Zahlen ein "0x"
        put ('x');
    }

    // Bestimmung der groessten Potenz der gewaehlten Zahlenbasis, die
    // noch kleiner als die darzustellende Zahl ist.
    for (div = 1; ival/div >= (uint64_t) base; div *= base);

    // ziffernweise Ausgabe der Zahl
    for (; div > 0; div /= (uint64_t) base) {
        digit = ival / div;
        if (digit < 10)
                put ('0' + digit);
        else
                put ('a' + digit - 10);
        ival %= div;
    }
    return *this;
}

// Darstellung eines Zeigers als hexadezimale ganze Zahl
OutStream& OutStream::operator << (void* ptr) {
    int oldbase = base;
    base = 16;
    *this << (uint64_t) ptr;
    base = oldbase;
    return *this;
 }

//   Aufruf einer Manipulatorfunktion
OutStream& OutStream::operator << (OutStream& (*f) (OutStream&)) {
    return f(*this);
}

//
// Manipulatorfunktionen
//
// Die folgenden Funktionen erhalten und liefern jeweils eine Referenz auf
// ein OutStream Objekt. Da die Klasse O_Stream einen Operator << fuer
// derartige Funktionen definiert, koennen sie mit Hilfe dieses Operators
// aufgerufen und sogar in weitere Eingaben eingebettet werden.
// Aufgabe der Manipulatoren ist, die Darstellung der nachfolgenden Ausgaben
// zu beeinflussen, z.B durch die Wahl des Zahlensystems.

// Fuege einen Zeilenumbruch in die Ausgabe ein.
OutStream& endl (OutStream& os) {
    os << '\n';
    os.flush ();
    return os;
}

// Waehlt das binaere Zahlensystem aus.
OutStream& bin (OutStream& os) {
    os.base = 2;
    return os;
}

// Waehlt das oktale Zahlensystem aus.
OutStream& oct (OutStream& os) {
    os.base = 8;
    return os;
}

// Waehlt das dezimale Zahlensystem aus.
OutStream& dec (OutStream& os) {
    os.base = 10;
    return os;
}

// Waehlt das hexadezimale Zahlensystem aus.
OutStream& hex (OutStream& os) {
    os.base = 16;
    return os;
}

