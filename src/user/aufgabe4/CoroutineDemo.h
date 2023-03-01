/*****************************************************************************
 *                                                                           *
 *                      C O R O U T I N E D E M O                            *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Einstieg in eine Anwendung.                              *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 15.8.2016                       *
 *****************************************************************************/
#ifndef __coroutinedemo_include__
#define __coroutinedemo_include__


class CoroutineDemo {
    
private:
    CoroutineDemo (const CoroutineDemo &copy); // Verhindere Kopieren

public:
    CoroutineDemo () { }

    // Koroutine-Startmethode
    void main ();

 };

#endif
