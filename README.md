# Aufgabe 3: Eingabe von Geräte

## Lernziele

1. Hardwarenahe Programmierung (Tastatur)
## A3.1: Tastatur (ohne Interrupts)
Damit eine Interaktion mit dem Betriebssystem möglich wird benötigen wir einen Tastatur-Treiber. In dieser Aufgabe verwenden wir die Tastatur ohne Interrupts. In main soll die Tastatur in einer Endlos-Schleife abgefragt werden und die Eingaben auf dem CGA-Bildschirm zur Kontrolle ausgegeben werden. Beginnen Sie mit der Funktion `key_hit`:
- Prüfen Sie zunächst in einer Schleife, ob ein Datenbyte von der Tastatur vorliegt. Hierzu muss im Control-Port geprüft werden, ob das Bit `OUTB` gesetzt ist.- Lesen Sie anschließend das Datenbyte über den Daten-Port ein und speichern Sie das gelesene Byte in der gegebenen Variable code.- Verwenden Sie die vorgegeben Funktion `key_decoded` um jeweils ein gelesenes Datenbyte zu übersetzen. Jedoch müssen Sie zuvor prüfen, ob das Datenbyte nicht von einer PS/2 Maus stammt. Dies wird über das Bit `AUXB` im Control-Register angezeigt. Beim Aufruf von `key_decoded` müssen Sie das das Datenbyte nicht übergeben, dies ist bereits in der Variablen `code` gespeichert.
- Wenn `key_decoded` true zurückgibt wurde eine Taste komplett dekodiert und in der Variablen `gather` gespeichert. Geben Sie in diesem Fall `gather` (Typ `Key`) zurück oder ansonsten `invalid`. 

Danach soll die Funktion `set_repeate_rate` implementiert werden. Zum Schluss können Sie die Funktion `set_led` implementieren (optional).

Namen von benötigten Variablen und Konstanten:- Control-Port: `ctrl_port`- Daten-Port: `data_port`- OUTB: `outb`- AUXB: `auxb`
Die Befehle für die Implementierung von `set_led` finden Sie in `Keyboard.h`. Warten und prüfen Sie nach dem Absenden eines Befehls die Antwort auf `kbd_reply::ack`. 
In folgenden Dateien müssen Quelltexte einfügt werden: `user/KeyboardDemo.cc` und`devices/Keyboard.cc`

*Achtung:Die Methoden zur Ansteuerung der LEDs und der Tastaturwiederholrate funktionieren nur richtig auf echter Hardware. Beachten Sie die Kommentare im Quelltext der Vorgabe, sowie die Datei* `HinweiseTastatur.pdf`.


## A3.2: Programmable Interrupt Controller (PIC)
In dieser Aufgabe soll die Interrupt-Verarbeitung aktiviert und anhand der Tastatur geprüft werden. Zunächst muss der PIC programmiert werden, um den Interrupt für die Tastatur zuzulassen. Zudem muss der Prozessor Interrupts vom PIC annehmen, was mithilfe der Funktion `cpu.enable_int` gemacht wird. Wenn dies funktioniert, müsste automatisch bei jedem Drücken und Loslassen einer Taste die Funktion `int_disp`, der Interrupt-Dispatcher in C aufgerufen werden, da die Interrupt-Vektortabelle im Assembler-Code (siehe Vorgabe) entsprechend initialisiert wurde.
Mit einer Ausgabe in `int_disp` kann dieser Schritt leicht getestet werden, zumindest einige Male. Wenn die Zeichen nicht vom Tastaturcontroller abgeholt werden, läuft der Tastaturpuffer irgendwann voll. Sobald der Puffer voll ist, sendet der Tastaturcontroller keine Interrupts mehr. Deshalb kann es durchaus passieren, dass zunächst nur für ein oder zwei Tastendrücke Interrupts auftreten.

In der Datei `IntDispatcher.cc` soll in `int_disp eine Textausgabe eingefügt werden.
In `Keyboard.cc` soll in der Methode plugin die ISR der Tastatur in der Klasse `IntDispatcher`registriert werden sowie in der Klasse `PIC` die Interrupts von der Tastatur freigeschaltet werden. Die Methode `trigger` muss in der Klasse `Keyboard` als leere Methode schon vorhanden sein, damit der Compiler keine Fehlermeldung ausgibt.In `main.cc` soll plugin von der Tastatur aufgerufen werden und danach die Interruptverarbeitung durch die CPU, mithilfe der CPU-Klasse, freigeschaltet werden.In folgenden Dateien muss Code implementiert werden: `devices/Keyboard.cc`, und `main.cc`,`kernel/interupts/PIC.cc` und `kernel/interrupts/IntDispatcher.cc`.


*Allgemeine Hinweise:*- *Während der Behandlung einer Unterbrechung braucht man sich um unerwünschte Interrupts nicht zu sorgen. Der Prozessor schaltet diese nämlich automatisch aus, wenn er mit der Behandlung beginnt, und lässt sie erst wieder zu, wenn die Unterbrechungsbehandlung beendet wird. Zudem nutzen wir nur einen Prozessor-Kern.*- *Die Interrupt-Verarbeitung kann nur funktionieren, wenn HHUos auch läuft. Sobald HHUos die main-Funktion verlässt, ist das Verhalten bei Auftreten eines Interrupts undefiniert. Ein Betriebssystem sollte eben nicht plötzlich enden :-)*


**Beispielausgaben in int_disp, C/C++**

![Bump-Allocator](https://github.com/mschoett/hhuTOSc/blob/aufgabe-2/img/bump_allocator.jpg)



## A3.3: Weiterleitung von Interrupts an die Geräte-Treiber
In dieser Aufgabe soll eine Infrastruktur geschaffen werden, um Interrupts, welche in `int_disp` (siehe Aufgabe A3.1) entgegengenommen werden, an eine Interrupt-Service-Routine (ISR) in einem Treiber weiterzuleiten.
Ein Treiber muss hierfür eine ISR implementieren und registrieren. Die Schnittstelle der ISR besteht „nur“ aus der `trigger`-Funktion. Zu beachten ist, dass der Interrupt-Dispatcher mit Vektor-Nummern arbeitet und nicht IRQ-Nummern wie der PIC.

Zur Verwaltung von Treiberobjekten dient die Klasse `IntDispatcher`, die für jeden möglichenInterrupt einen Zeiger auf ein ISR-Objekt bereithält (verwaltet im Array `map`). Die Schnittstelle für einen Interrupt-Handler wird in der abstrakten Klasse `ISR` definiert. In der neuen Vorgabe erweitert die Klasse `Keyboard` schon die Klasse `ISR`.
In der Klasse `IntDispatcher` soll die Methode assign ein übergebenes ISR-Objekt im Array `map`registrieren. Die Methode `report` soll von `int_disp` gerufen werden, um die Methode `trigger` einer registrierten ISR-Instanz aufrufen, sofern vorhanden. Falls keine ISR registriert wurde, so soll eine Fehlermeldung ausgegeben werden und das System gestoppt werden.
In der Klasse `Keyboard` soll die Methode plugin die eigene Instanz mithilfe von assign (in derKlasse `IntDispatcher`) registrieren. Die notwendige Vektor-Nummer ist in `IntDispatcher` definiert. Zudem muss der IRQ der Tastatur (definiert in `PIC.h`) im PIC mithilfe von `allow` freigeschaltet werden. 
Des Weiteren soll eine Text-Ausgabe in die Methode `trigger` eingebaut werden, um zu prüfen, ob die Tastaturinterrupts hier ankommen.
In folgenden Dateien muss Code implementiert werden: `devices/Keyboard.cc` und`kernel/interrupts/IntDispatcher.cc`.


## A3.4: Tastaturabfrage per Interrupt
Nun soll die Funktion `trigger` in Keyboard implementiert werden und mithilfe von `key_hit` bei jedem Tastendruck das entsprechende Zeichen an einer festen Position auf dem Bildschirm dargestellt werden. Die Ausgabe des Zeichens soll direkt in `trigger` erfolgen.
Der ASCII-Code der zuletzt gedrückten Taste soll zudem in der neuen Variable `lastkey` gespeichert werden, welche später von Anwendungen ausgelesen werden kann. In `lib/Input.cc` sind zwei Beispielfunktionen welche `lastkey` verwenden, beispielsweise warten bis der Benutzer die Taste Return gedrückt hat.Optional: Die Tastenkombination "Ctrl-Alt-Delete" soll ein Reboot auslösen. Dies ist auch in `trigger` zu realisieren.
*Hinweise:*- *Die PS/2-Maus hängt ebenfalls am Keyboard-Controller, verwendet aber IRQ12. Da wir keinen Handler für IRQ12 haben, kann es sein, dass wenn IRQ1 auftritt noch Daten von der Maus abzuholen sind. Dies können Sie anhand des* `AUXB`*-Bits im Statusregister erkennen.*- *Ferner tritt unter Qemu manchmal direkt ein IRQ1 nach dem Start auf, ohne eine Tastatureingabe. Das ist auf echter Hardware nicht der Fall. Daher unter Qemu bitte ignorieren.*


