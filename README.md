# Aufgabe 2: Speicherverwaltung

## Lernziel1. Verstehen wie eine Speichervwaltung funktioniert
## A2.1: Bump-Allocator
In dieser Aufgabe soll ein sehr einfacher sogenannter Bump-Allocator implementiert werden, um zunächst die Integration in das System zu verstehen sowie die Anbindung an die Programmiersprache. Dieser Allokator kennt lediglich den Heap-Anfang, das Heap-Ende und merkt sich in der Variablen `next` die aktuelle Adresse im Heap, ab welcher der Speicher frei ist. Bei jeder Allokation wird `next` um die gewünschte Anzahl Bytes weitergesetzt, sofern nicht das Heap-Ende erreicht ist, siehe Abbildung.

<img src="https://github.com/mschoett/hhuTOSc/blob/aufgabe-2/heap.jpg" width="100">


Die Heapgröße ist fest auf 1 MB eingestellt, im Speicherbereich 3 – 4 MB. Bei einer Speicherfreigabe passiert nichts. Bauen Sie die Vorgabe in Ihr System ein und stellen Sie sicher, dass der Heap möglichst bald in der Einstiegsfunktion des Betriebssystems initialisiert wird.Zur Überprüfung der Implementierung sollen einfache Tests geschrieben werden. Weitere Information hierzufinden sich in den nachfolgenden Hinweisen zur jeweiligen Programmiersprache.













`main.cc`, `user/aufgabe1/TextDemo.cc` und `devices/CGA.cc`

*Beachten Sie die Kommentare im Quelltext der Vorgabe, sowie die Datei* `HinweiseCGA.pdf`


## 2. Aufgabe: LautsprecherIn dieser Aufgabe muss die Methode `PCSPK::delay` implementiert werden. Diese Methode ist für das Abspielen von Tönen notwendig, die eine gegebene Zeitdauer gespielt werden sollen. Da wir bisher keine Interrupts verarbeiten können und auch keine Systemzeit haben bietet es sich an den Zähler 0 des PIT hierfür zu verwenden. Sie können dann in einer Schleife fortlaufend den aktuellen Zählerstand auslesen, der mit 1,19 MHz dekrementiert wird und so näherungsweise die Ausführung, eine gegebene Zeit in Millisekunden, verzögern. 
Dies ist eine unsaubere Lösung die wir später ersetzen werden.*Beachten Sie die Kommentare im Quelltext der Vorgabe, sowie die Datei* `8254.pdf`.
Weitere Informationen zum PIT 8254 finden Sie hier: http://wiki.osdev.org/Programmable_Interval_Timer

In folgenden Dateien müssen Quelltexte einfügt werden:
`devices/PCSPK.cc` und `user/SoundDemo.cc`

### Bildschirmfoto zu Aufgabe 1

![CGA](https://github.com/mschoett/hhuTOSc/blob/aufgabe-1/cga.jpg?raw=true)

