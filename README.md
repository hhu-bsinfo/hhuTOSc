# Übungsblatt 1: Ausgabe auf Geräten

## Lernziele1. Kennenlernen der Entwicklungsumgebung
2. Einarbeiten in die Programmiersprache C++ 
3. Hardwarenahe Programmierung (CGA-Bildschirm und PC-Lautsprecher)## 1. Aufgabe: CGA-BildschirmFür Testausgaben und zur Erle ichterung der Fehlersuche soll das Betriebssystem zunächst Ausgabefunktionen für den Textbildschirm erhalten. Die Funktionsfähigkeit soll mit Hilfe eines aussagefähigen Testprogramms gezeigt werden, siehe Bildschirmfoto unten.
Dazu soll in main.cc in der Einstiegsfunktion main das Objekt kout für verschieden formatierte Ausgaben genutzt werden. Diese sollen ähnlich wie bei der C++ IO-Streams Bibliothek verwendet werden können. Damit die Ausgabefunktionen überall in HHUos genutzt werden kann, ist in der gegebenen Klasse Gobals, ein globales CGA_Stream-Objekt kout bereits definiert.
In folgenden Dateien müssen Quelltexte einfügt werden:
`main.cc`, `user/aufgabe1/TextDemo.cc` und `devices/CGA.cc`

*Beachten Sie die Kommentare im Quelltext der Vorgabe, sowie die Datei* `HinweiseCGA.pdf`


## 2. Aufgabe: LautsprecherIn dieser Aufgabe muss die Methode `PCSPK::delay` implementiert werden. Diese Methode ist für das Abspielen von Tönen notwendig, die eine gegebene Zeitdauer gespielt werden sollen. Da wir bisher keine Interrupts verarbeiten können und auch keine Systemzeit haben bietet es sich an den Zähler 0 des PIT hierfür zu verwenden. Sie können dann in einer Schleife fortlaufend den aktuellen Zählerstand auslesen, der mit 1,19 MHz dekrementiert wird und so näherungsweise die Ausführung, eine gegebene Zeit in Millisekunden, verzögern. 
Dies ist eine unsaubere Lösung die wir später ersetzen werden.*Beachten Sie die Kommentare im Quelltext der Vorgabe, sowie die Datei* `8254.pdf`.
Weitere Informationen zum PIT 8254 finden Sie hier: http://wiki.osdev.org/Programmable_Interval_Timer

In folgenden Dateien müssen Quelltexte einfügt werden:
`devices/PCSPK.cc` und `user/SoundDemo.cc`

### Bildschirmfoto zu Aufgabe 1

![CGA](https://github.com/mschoett/hhuTOSc/blob/aufgabe-1/cga.jpg?raw=true)

