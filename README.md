# Aufgabe 2: Speicherverwaltung

## Lernziel1. Verstehen wie eine Speichervwaltung funktioniert
## A2.1: Bump-Allocator
In dieser Aufgabe soll ein sehr einfacher sogenannter Bump-Allocator implementiert werden, um zunächst die Integration in das System zu verstehen sowie die Anbindung an die Programmiersprache. Dieser Allokator kennt lediglich den Heap-Anfang, das Heap-Ende und merkt sich in der Variablen `next` die aktuelle Adresse im Heap, ab welcher der Speicher frei ist. Bei jeder Allokation wird `next` um die gewünschte Anzahl Bytes weitergesetzt, sofern nicht das Heap-Ende erreicht ist, siehe Abbildung.

![Bump-Allocator](https://github.com/mschoett/hhuTOSc/blob/aufgabe-2/heap.jpg)

Die Heapgröße ist fest auf 1 MB eingestellt, im Speicherbereich 3 – 4 MB. Bei einer Speicherfreigabe passiert nichts. Bauen Sie die Vorgabe in Ihr System ein und stellen Sie sicher, dass der Heap möglichst bald in der Einstiegsfunktion des Betriebssystems initialisiert wird.Zur Überprüfung der Implementierung sollen einfache Tests geschrieben werden. Weitere Information hierzu finden sich in den nachfolgenden Hinweisen zur jeweiligen Programmiersprache.

In der Datei `BumpAllocator.cc` soll die Bump-Speicherverwaltung implementiert werden. Die C++Operatoren für `new` und `delete` sind überschrieben und rufen die entsprechenden Funktionen auf.In `Globals.cc/.h` gibt es drei neue globale Variablen: `total_mem` wird in `Allocator.cc` gesetzt und enthält die RAM-Kapazität des Rechners (fest auf 8 MB eingestellt). Zudem gibt es für jeden Allokator ein statisches Objekt, für diese Aufgabe BumpAllocator allocator.
In `boot.asm` wird nun der Label `_ZdlPv` auskommentiert, welcher bisher bei einem `delete` angesprungen wurde. Nun wird `delete` im jeweiligen Allokator aufgerufen. Als Tests sollen in `HeapDemo.cc` Instanzen einer eigenen Klasse sowie Arrays von Objekten und/oder primitiven Datentypen angelegt und freigegeben werden. In folgenden Dateien müssen Quelltexte einfügt werden: `user/aufgabe2/HeapDemo.cc` und `kernel/allocator/BumpAllocator.cc`.


