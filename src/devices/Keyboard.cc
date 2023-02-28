/*****************************************************************************
 *                                                                           *
 *                                  K E Y B O A R D                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Treiber für den Tastaturcontroller des PCs.              *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#include "devices/Keyboard.h"

/* Tabellen fuer ASCII-Codes (Klassenvariablen) intiialisieren */

unsigned char Keyboard::normal_tab[] =
{
   0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 225, 39, '\b',
   0, 'q', 'w', 'e', 'r', 't', 'z', 'u', 'i', 'o', 'p', 129, '+', '\n',
   0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 148, 132, '^', 0, '#',
   'y', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '-', 0,
   '*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '-',
   0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, '<', 0, 0
};

unsigned char Keyboard::shift_tab[] =
{
   0, 0, '!', '"', 21, '$', '%', '&', '/', '(', ')', '=', '?', 96, 0,
   0, 'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O', 'P', 154, '*', 0,
   0, 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 153, 142, 248, 0, 39,
   'Y', 'X', 'C', 'V', 'B', 'N', 'M', ';', ':', '_', 0,
   0, 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '>', 0, 0
};

unsigned char Keyboard::alt_tab[] =
{
   0, 0, 0, 253, 0, 0, 0, 0, '{', '[', ']', '}', '\\', 0, 0,
   0, '@', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '~', 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 230, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '|', 0, 0
};

unsigned char Keyboard::asc_num_tab[] =
{
   '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', ','
};
unsigned char Keyboard::scan_num_tab[] =
{
   8, 9, 10, 53, 5, 6, 7, 27, 2, 3, 4, 11, 51
};


/*****************************************************************************
 * Methode:         Keyboard::key_decoded                                    *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Interpretiert die Make- und Break-Codes der Tastatur.    *
 *                                                                           *
 * Rueckgabewert:   true bedeutet, dass das Zeichen komplett ist             *
 *                  false es fehlen noch Make- oder Break-Codes.             *
 *****************************************************************************/
bool Keyboard::key_decoded () {
    bool done = false;

    // Die Tasten, die bei der MF II Tastatur gegenueber der aelteren
    // AT Tastatur hinzugekommen sind, senden immer erst eines von zwei
    // moeglichen Prefix Bytes.
    if (code == prefix1 || code == prefix2) {
        prefix = code;
        return false;
    }

    // Das Loslassen einer Taste ist eigentlich nur bei den "Modifier" Tasten
    // SHIFT, CTRL und ALT von Interesse, bei den anderen kann der Break-Code
    // ignoriert werden.
    if (code & break_bit) {
        code &= ~break_bit;     // Der Break-Code einer Taste ist gleich dem
                                // Make-Code mit gesetzten break_bit.
        switch (code) {
            case 42:
            case 54:
                gather.shift (false);
                break;
            case 56:
                if (prefix == prefix1)
                    gather.alt_right (false);
                else
                    gather.alt_left (false);
                break;
            case 29:
                if (prefix == prefix1)
                    gather.ctrl_right (false);
                else
                    gather.ctrl_left (false);
                break;
        }

        // Ein Prefix gilt immer nur fuer den unmittelbar nachfolgenden Code.
        // Also ist es jetzt abgehandelt.
        prefix = 0;

        // Mit einem Break-Code kann man nichts anfangen, also false liefern.
        return false;
    }

    // Eine Taste wurde gedrueckt. Bei den Modifier Tasten wie SHIFT, ALT,
    // NUM_LOCK etc. wird nur der interne Zustand geaendert. Durch den
    // Rueckgabewert 'false' wird angezeigt, dass die Tastatureingabe noch
    // nicht abgeschlossen ist. Bei den anderen Tasten werden ASCII
    // und Scancode eingetragen und ein 'true' fuer eine erfolgreiche
    // Tastaturabfrage zurueckgegeben, obwohl genaugenommen noch der Break-
    // code der Taste fehlt.

    switch (code) {
        case 42:
        case 54:
            gather.shift (true);
            break;
        case 56:
            if (prefix == prefix1)
                gather.alt_right (true);
            else
                gather.alt_left (true);
            break;
        case 29:
            if (prefix == prefix1)
                gather.ctrl_right (true);
            else
                gather.ctrl_left (true);
            break;
        case 58:
            gather.caps_lock (!gather.caps_lock ());
            set_led (led::caps_lock, gather.caps_lock());
            break;
        case 70:
            gather.scroll_lock (!gather.scroll_lock ());
            set_led (led::scroll_lock, gather.scroll_lock());
            break;
        case 69: // Numlock oder Pause ?
            if (gather.ctrl_left ()) { // Pause Taste
                // Auf alten Tastaturen konnte die Pause-Funktion wohl nur
                // ueber Ctrl+NumLock erreicht werden. Moderne MF-II Tastaturen
                // senden daher diese Codekombination, wenn Pause gemeint ist.
                // Die Pause Taste liefert zwar normalerweise keinen ASCII-
                // Code, aber Nachgucken schadet auch nicht. In jedem Fall ist
                // die Taste nun komplett.
                get_ascii_code ();
                done = true;
            }
            else { // NumLock
                gather.num_lock (!gather.num_lock());
                set_led (led::num_lock, gather.num_lock ());
            }
            break;
	
        default: // alle anderen Tasten
            // ASCII-Codes aus den entsprechenden Tabellen auslesen, fertig.
            get_ascii_code ();
            done = true;
        }

    // Ein Prefix gilt immer nur fuer den unmittelbar nachfolgenden Code.
    // Also ist es jetzt abgehandelt.
    prefix = 0;

    if (done)
        return true;    // Tastaturabfrage abgeschlossen
    else
        return false;
}


/*****************************************************************************
 * Methode:         Keyboard::get_ascii_code                                 *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Ermittelt anhand von Tabellen aus dem Scancode und den   *
 *                  gesetzten Modifier-Bits den ASCII-Code der Taste.        *
 *****************************************************************************/
void Keyboard::get_ascii_code () {
    // Sonderfall Scancode 53: Dieser Code wird sowohl von der Minustaste
    // des normalen Tastaturbereichs, als auch von der Divisionstaste des
    // Ziffernblocks gesendet. Damit in beiden Faellen ein Code heraus-
    // kommt, der der Aufschrift entspricht, muss im Falle des Ziffern-
    // blocks eine Umsetzung auf den richtigen Code der Divisionstaste
    // erfolgen.
    if (code == 53 && prefix == prefix1) { // Divisionstaste des Ziffernblocks
        gather.ascii ('/');
        gather.scancode (Key::scan::div);
    }

    // Anhand der Modifierbits muss die richtige Tabelle ausgewaehlt
    // werden. Der Einfachheit halber hat NumLock Vorrang vor Alt,
    // Shift und CapsLock. Fuer Ctrl gibt es keine eigene Tabelle
    else if (gather.num_lock () && !prefix && code>=71 && code<=83) {
        // Bei eingeschaltetem NumLock und der Betaetigung einer der
	    // Tasten des separaten Ziffernblocks (Codes 71-83), sollen 
	    // nicht die Scancodes der Cursortasten, sondern ASCII- und
	    // Scancodes der ensprechenden Zifferntasten geliefert werden.
	    // Die Tasten des Cursorblocks (prefix == prefix1) sollen
	    // natuerlich weiterhin zur Cursorsteuerung genutzt werden
	    // koennen. Sie senden dann uebrigens noch ein Shift, aber das
	    // sollte nicht weiter stoeren.
	    gather.ascii (asc_num_tab[code-71]);
	    gather.scancode (scan_num_tab[code-71]);
    }
    else if (gather.alt_right ()) {
        gather.ascii (alt_tab[code]);
	    gather.scancode (code);
    }
    else if (gather.shift ()) {
	    gather.ascii (shift_tab[code]);
	    gather.scancode (code);
    }
    else if (gather.caps_lock ()) {
        // Die Umschaltung soll nur bei Buchstaben gelten
	    if ((code>=16 && code<=26) || (code>=30 && code<=40)
		|| (code>=44 && code<=50)) {
            gather.ascii (shift_tab[code]);
            gather.scancode (code);
        }
	    else {
            gather.ascii (normal_tab[code]);
            gather.scancode (code);
        }
    }
    else {
        gather.ascii (normal_tab[code]);
        gather.scancode (code);
    }
}


/*****************************************************************************
 * Konstruktor:     Keyboard::Keyboard                                       *
 *---------------------------------------------------------------------------*
 * Beschreibung:     Initialisierung der Tastatur: alle LEDs werden ausge-   *
 *                   schaltet und die Wiederholungsrate auf maximale         *
 *                   Geschwindigkeit eingestellt.                            *
 *****************************************************************************/
Keyboard::Keyboard () :
   ctrl_port (0x64), data_port (0x60) {
   // alle LEDs ausschalten (bei vielen PCs ist NumLock nach dem Booten an)
   set_led (led::caps_lock, false);
   set_led (led::scroll_lock, false);
   set_led (led::num_lock, false);

   // maximale Geschwindigkeit, minimale Verzoegerung
   set_repeat_rate (0, 0);  
}


/*****************************************************************************
 * Methode:         Keyboard::key_hit                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Diese Methode soll einen Tastendruck zurueckliefern.     *
 *                  Hierzu soll die Tastatur in einer Schleife "gepollt"     *
 *                  werden, bis ein Zeichen eingegebn wurde.                 *
 *                                                                           *
 *                  Das Byte von der Tastatur soll in dem Attribut 'code'    *
 *                  (siehe Keyboard.h) gespeichert werden. Die Dekodierung   *
 *                  soll mithilfe der vorgegebenen Funktion 'key_decoded'    *
 *                  erfolgen.                                                *
 *                                                                           *
 * Rückgabewert:    Wenn der Tastendruck abgeschlossen ist und ein Scancode, *
 *                  sowie gegebenenfalls ein ASCII-Code emittelt werden      * 
 *                  konnte, werden diese in 'gather' (siehe Keyboard.h)      *
 *                  zurueckgeliefert. Anderenfalls liefert key_hit () einen  *
 *                  ungueltigen Wert zurueck, was mit Key::valid ()          *
 *                  ueberprueft werden kann.                                 *
 *****************************************************************************/
Key Keyboard::key_hit () {
    Key invalid;  // nicht explizit initialisierte Tasten sind ungueltig
         
    /* Hier muss Code eingefuegt werden. */

    return invalid;
}


/*****************************************************************************
 * Methode:         Keyboard::reboot                                         *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Fuehrt einen Neustart des Rechners durch.                *
 *****************************************************************************/
void Keyboard::reboot () {
    int status;

    // Dem BIOS mitteilen, dass das Reset beabsichtigt war
    // und kein Speichertest durchgefuehrt werden muss.
    *(unsigned short*) 0x472 = 0x1234;

    // Der Tastaturcontroller soll das Reset ausloesen.
    do {
        status = ctrl_port.inb ();      // warten, bis das letzte Kommando
    } while ((status & inpb) != 0);     // verarbeitet wurde.
    ctrl_port.outb (cpu_reset);         // Reset
}


/*****************************************************************************
 * Methode:         Keyboard::set_repeat_rate                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstellen der Wiederholungsrate der Tastatur.           *
 *                                                                           *
 * Parameter:                                                                *
 *      delay:      Bestimmt, wie lange eine Taste gedrueckt werden muss,    *
 *                  bevor die Wiederholung einsetzt. Erlaubt sind Werte      *
 *                  zw. 0 (minimale Wartezeit) und 3 (maximale Wartezeit).   *
 *      speed:      Bestimmt, wie schnell die Tastencodes aufeinander folgen *
 *                  sollen. Erlaubt sind Werte zwischen 0 (sehr schnell)     *
 *                  und 31 (sehr langsam).                                   *
 *****************************************************************************/
void Keyboard::set_repeat_rate (int speed, int delay) {

    /* Hier muss Code eingefuegt werden. */

}


/*****************************************************************************
 * Methode:         Keyboard::set_led                                        *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setzt oder loescht die angegebene Leuchtdiode.           *
 *                                                                           *
 * Parameter:                                                                *
 *      led:        Welche LED? (caps_lock, num_lock, scroll_lock)           *
 *      on:         0 = aus, 1 = an                                          *
 *****************************************************************************/
void Keyboard::set_led (char led, bool on) {

    /* Hier muss Code eingefuegt werden. */

}
