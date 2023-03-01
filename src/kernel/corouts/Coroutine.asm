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
    mov rsp, [rdi]              ; 1. Parameter = Kontext der neue Koroutine
    popf
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8
	ret                         ; Coroutinenwechsel !


;        
; Coroutine_switch: Coroutinenumschaltung. Der aktuelle Registersatz wird
;                   gesichert und der Registersatz der neuen Coroutine
;                   wird in den Prozessor geladen.
;
; C Prototyp:       void Coroutine_switch (void* context_now, void *context_then);
Coroutine_switch:
    ;
    ; Register der aktuellen Koroutine auf ihrem Stack sichern
    ;
    push r8
    push r9
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
    pushf
    mov [rdi], rsp     ; sichere Stackpointer in 'context_now'
    
    ;
    ; Register der naechsten Koroutine laden
    ;
    mov rsp, [rsi]     ; lade Stackpointer von 'context_then'
    popf 
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop r9
    pop r8

	ret                ; Coroutinenwechsel !
