# Aufgabe 3: Interrupts

## Lernziele

1. Funktionsweise des Interrupt-Controllers verstehen
2. Behandlung von Interrupts implementieren, am Beispiel der Tastatur
3. Kritische Abschnitte (Synchronisierung) verstehen und einsetzen
## A3.1: Programmable Interrupt Controller (PIC)
In dieser Aufgabe soll die Interrupt-Verarbeitung aktiviert und anhand der Tastatur geprüft werden. 

Zunächst müssen die leeren Methoden in der Klasse `PIC` implementiert werden.  In der Funktion `int_disp` (in `IntDispatcher.cc`) soll vorerst eine Textausgabe eingefügt werden, welche ausgibt, dass ein Interrupt aufgetreten ist und welche Vektor-Nummer dieser hat.

Anschliessend soll die Methode `plugin` in `Keyboard.cc` programmiert werden. Hier muss der Interrupt der Tastatur am PIC mit `pic.allow` freigeschaltet werden. Die Methode `trigger` kann vorerst leer bleiben, muss aber schon vorhanden sein.

In `main` muss die ISR der Tastatur mit `kb.plugin` registriert werden und danach muessen die Interrupts an der CPU  mit `cpu.enable_int()` zugelassen werden.

Wenn nun das System startet sollte bei jedem Drücken und Loslassen einer Taste eine Textmeldung von `int_disp` zu sehen sein. Dies funktioniert allerdings nu einige wenige Male. Wenn die Zeichen nicht vom Tastaturcontroller abgeholt werden, läuft der Tastaturpuffer irgendwann voll. Sobald der Puffer voll ist, sendet der Tastaturcontroller keine Interrupts mehr. 
In folgenden Dateien muss Code implementiert werden: `devices/Keyboard.cc`, und `main.cc`,`kernel/interupts/PIC.cc` und `kernel/interrupts/IntDispatcher.cc`.


*Allgemeine Hinweise:*- *Während der Behandlung einer Unterbrechung braucht man sich um unerwünschte Interrupts nicht zu sorgen. Der Prozessor schaltet diese nämlich automatisch aus, wenn er mit der Behandlung beginnt, und lässt sie erst wieder zu, wenn die Unterbrechungsbehandlung beendet wird. Zudem nutzen wir nur einen Prozessor-Kern.*- *Die Interrupt-Verarbeitung kann nur funktionieren, wenn hhuTOS auch läuft. Sobald hhuTOS die* `main`*-Funktion verlässt, ist das Verhalten bei Auftreten eines Interrupts undefiniert. Ein Betriebssystem sollte eben nicht plötzlich enden :-)*


**Beispielausgaben in** `int_disp`

![IRQ1](https://github.com/mschoett/hhuTOSc/blob/aufgabe-3/img/irq1.jpg)


## A3.2: Weiterleitung von Interrupts an die Geräte-Treiber
In dieser Aufgabe soll eine Infrastruktur geschaffen werden, um Interrupts, welche in `int_disp` (siehe Aufgabe A3.1) entgegengenommen werden, an eine Interrupt-Service-Routine (ISR) in einem Treiber weiterzuleiten.
Ein Treiber muss hierfür eine ISR implementieren und registrieren. Die Schnittstelle der ISR besteht „nur“ aus der `trigger`-Funktion. Zu beachten ist, dass der Interrupt-Dispatcher mit Vektor-Nummern arbeitet und nicht IRQ-Nummern wie der PIC.

Zur Verwaltung von Treiberobjekten dient die Klasse `IntDispatcher`, die für jeden möglichenInterrupt einen Zeiger auf ein ISR-Objekt bereithält (verwaltet im Array `map`). Die Schnittstelle für einen Interrupt-Handler wird in der abstrakten Klasse `ISR` definiert. In der neuen Vorgabe erweitert die Klasse `Keyboard` schon die Klasse `ISR`.
In der Klasse `IntDispatcher` soll die Methode assign ein übergebenes ISR-Objekt im Array `map`registrieren. Die Methode `report` soll von `int_disp` gerufen werden, um die Methode `trigger` einer registrierten ISR-Instanz aufrufen, sofern vorhanden. Falls keine ISR registriert wurde, so soll eine Fehlermeldung ausgegeben werden und das System gestoppt werden.
In der Klasse `Keyboard` soll die Methode `plugin` erweitert werden und die eigene Instanz mithilfe von `assign` (in der Klasse `IntDispatcher`) registrieren. Die notwendige Vektor-Nummer ist in `IntDispatcher` definiert. 
 
Des Weiteren soll eine Text-Ausgabe in die Methode `trigger` eingebaut werden, um zu prüfen, ob die Tastaturinterrupts hier ankommen.
In folgenden Dateien muss Code implementiert werden: `devices/Keyboard.cc` und`kernel/interrupts/IntDispatcher.cc`.

**Beispielausgaben in** `Keyboard::trigger`

![IRQ2](https://github.com/mschoett/hhuTOSc/blob/aufgabe-3/img/irq2.jpg)


## A3.3: Tastaturabfrage per Interrupt
Nun soll die Funktion `trigger` in Keyboard implementiert werden. Bei jedem Interrupt soll in `trigger`die Funktion `key_hit` aufgerufen werden. Hier wird geprüft, ob ein Zeichen erfolgreich dekodiert wurde. Wenn dies der Fall ist, so soll der ASCII-Code des Zeichens in der neuen Variable `lastkey` gespeichert werden, welche später von Anwendungen ausgelesen werden kann. In `lib/Input.cc` sind zwei Beispielfunktionen welche `lastkey` verwenden, beispielsweise warten bis der Benutzer die Taste Return gedrückt hat.

Falls `key_hit` in Aufgabe 1 so realisiert wurde, dass in einer Endlos-Schleife Daten von der Tastatur eingelesen werden, bis ein Zeichen erfolgreich dekodiert wurde, so muss diese Endlos-Schleife entfernt werden. Es sollen nun bei jedem Interrupt nur so viele Bytes von der Tastatur eingelesen werden, wie unmittelbar vorhanden sind. Wir wollen nicht den Interrupt blockieren durch aktives Warten auf weitere Bytes.

Zudem soll `trigger` ein erfolgreich dekodiertes Zeichen an einer festen Position (mit `kout.setpos()`) auf dem Bildschirm anzeigen. 
*Hinweise:*- *Die PS/2-Maus hängt ebenfalls am Keyboard-Controller, verwendet aber IRQ12. Da wir keinen Handler für IRQ12 haben, kann es sein, dass wenn IRQ1 auftritt noch Daten von der Maus abzuholen sind. Dies können Sie anhand des* `AUXB`*-Bits im Statusregister erkennen.*- *Ferner tritt unter Qemu manchmal direkt ein IRQ1 nach dem Start auf, ohne eine Tastatureingabe. Das ist auf echter Hardware nicht der Fall. Daher unter Qemu bitte ignorieren.*

**Beispielausgaben in** `Keyboard::trigger` **an einer festen Position**

![IRQ3](https://github.com/mschoett/hhuTOSc/blob/aufgabe-3/img/irq3.jpg)


## A3.4: kritische Abschnitte
Es soll ein Testprogramm in geschrieben werden, welches in einer Endlosschleife an einer festen Position Text-Ausgaben mach, zeilenweise die Zahlen 0 - 9.
Es sollte nun möglich sein, durch das Drücken von Tasten die Ausgabe "durcheinander" bringen zu können. Was passiert hier? Wie kann dies vermieden werden?*Tipp: Für die Synchronisierung / Implementierung eines kritischen Abschnitts gibt es nützliche Funktionen in der Klasse* `CPU`.

**Beispielausgaben "Durcheinander" ohne Synchronisierung**

![IRQ4](https://github.com/mschoett/hhuTOSc/blob/aufgabe-3/img/irq4.jpg)


