/*****************************************************************************
 *                                                                           *
 *                       C O R O U T I N E S T A T E                         *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Die Struktur CoroutineState dient dazu, bei einem        *
 *                  Koroutinenwechsel die Werte der nicht-fluechtigen        *
 *                  Register zu sichern. Beim GNU C Compiler sind eax, ecx   *
 *                  und edx fluechtige Register, die bei Funktionsaufrufen   * 
 *                  und somit auch bei einem Koroutinenwechsel keine spaeter *
 *                  noch benoetigten Werte haben duerfen. Daher muss in der  * 
 *                  Struktur CoroutineState auch kein Platz fuer sie bereit- *
 *                  gestellt werden.                                         *
 *                                                                           *
 * Achtung:         Fuer den Zugriff auf die Elemente von                    *
 *                  struct CoroutineState aus einer Assemblerfunktion        *
 *                  heraus werden in der Datei Coroutine.inc Namen fuer die  *
 *                  benoetigten Abstaende der einzelnen Elemente zum Anfang  * 
 *                  der Struktur definiert. Damit dann auch auf die richtigen*
 *                  Elemente zugegriffen wird, sollten sich die Angaben von  * 
 *                  CoroutineState.h und Coroutine.inc exakt entsprechen.    *
 *                  Wer also CoroutineState.h aendert, muss auch             *
 *                  Coroutine.inc anpassen (und umgekehrt.)                  *
 *                                                                           *
 * Autor:           Olaf Spinczyk, TU Dortmund                               *
 *****************************************************************************/

#ifndef __CoroutineState_include__
#define __CoroutineState_include__

struct CoroutineState {
    void *ebx;
    void *esi;
    void *edi;
    void *ebp;
    void *esp;
};

#endif

