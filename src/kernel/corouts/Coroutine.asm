;*****************************************************************************
;*                                                                           *
;*                  C O R O U T I N E                                        *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Beschreibung:    Assemblerfunktionen zum Starten des ersten Koroutine und *
;*                  zum Umschalten zwischen Koroutinen.                      *
;*                                                                           *
;* Autor:           Michael, Schoettner, HHU, 6.02.2023                      *
;*****************************************************************************


; EXPORTIERTE FUNKTIONEN

[GLOBAL Coroutine_start]
[GLOBAL Coroutine_switch]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]
[BITS 64]


; Coroutine_start: Startet die erste Koroutine
;
; C Prototyp:      void Coroutine_start  (void* context);
Coroutine_start:
; *
; * Hier muss Code eingefuegt werden
; *


;        
; Coroutine_switch: Coroutinenumschaltung. Der aktuelle Registersatz wird
;                   gesichert und der Registersatz der neuen Coroutine
;                   wird in den Prozessor geladen.
;
; C Prototyp:       void Coroutine_switch (void* context_now, void *context_then);
Coroutine_switch:
; *
; * Hier muss Code eingefuegt werden
; *
