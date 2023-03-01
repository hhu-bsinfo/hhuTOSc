;*****************************************************************************
;*                                                                           *
;*                            C O R O U T I N E                              *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Beschreibung:    Assemblerdarstellung der 'struct CoroutineState' aus     *
;*                  CoroutineState.h                                         *
;*                                                                           *
;*                  Die Reihenfolge der Registerbezeichnungen muss unbedingt *
;*                  mit der von 'struct CoroutineState' uebereinstimmen.     *
;*                                                                           *
;* Autor:           Olaf Spinczyk, TU Dortmund                               *
;*****************************************************************************

%include "kernel/corouts/Coroutine.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL Coroutine_switch]
[GLOBAL Coroutine_start]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; COROUTINE_START : Startet die erste Coroutine ueberhaupt.
;
; C Prototyp: void Coroutine_start (struct CoroutineState* regs);

Coroutine_start:

; *
; * Hier muss Code eingefuegt werden
; *


; COROUTINE_SWITCH : Coroutinenumschaltung. Der aktuelle Registersatz wird
;                    gesichert und der Registersatz der neuen Coroutine
;                    wird in den Prozessor eingelesen.
;
; C Prototyp: void Coroutine_switch (struct CoroutineState* regs_now,
;                                    struct CoroutineState* reg_then);
;
; Achtung: Die Parameter werden von rechts nach links uebergeben.
;
Coroutine_switch:

; *
; * Hier muss Code eingefuegt werden
; *

