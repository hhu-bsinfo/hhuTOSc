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

; Nicht-fluechtige Register des Intel 80386 Prozessors

; Die folgenden Angaben belegen ebx_offset mit dem Wert 0, esi_offset mit 4
; edi_offset mit 8 usw. Dies entspricht den Abstaenden der Elemente ebx, esi,
; edi usw. der Struktur CoroutineState zum Anfang der Struktur (in Bytes).

[ABSOLUTE 0]
ebx_offset:	resd 1
esi_offset:	resd 1
edi_offset:	resd 1
ebp_offset:	resd 1
esp_offset:	resd 1
