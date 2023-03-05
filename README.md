# Aufgabe 7: Eine eigene BS-Erweiterung / Anwendung

## Lernziele
1. Eine Anwendung schreiben
2. Alternativ eine Betriebssystem-Komponente entwickeln

## Mögliche Themenrichtunge
- Grafikdemo (multithreaded)
- Retro-Spiel (z.B. Snake, Pacman, ...)
- einfache Shell (Beispiele für Befehle: clear, time, meminfo, ...) 
- Scheduler mit Prioriäten (mit einer Demo)


## Vorgabe
Die Dateien in der Vorgabe umfassen eine Reihe von Zusatzfunktionen.

### Grafikfunktionen 
Vorhanden sind nur sehr grundlegende Grafik-Funktionen, inkl. einer Text-Ausgabe mit einer Schriftart. Weitere Funktionen sollen je nach Anwendung ergänzt werden. 

Ob das System im Grafik- oder Textmodus startet wird in `boot/boot.asm`durch die die Konstante `TEXT_MODE` festgelegt. Wenn diese Konstante aukommentiert wird, so schaltet `grub` direkt in den Grafikmodus (800x600 mit 32 Bit pro Pixel). Eine alternative Grafikauflösung kann durch die Konstanten `MULTIBOOT_GRAPHICS_*` in  `boot/boot.asm` eingestellt werden. Mögliche Auflösungen sollten sich an dem VESA-Standard orientieren, siehe hier: https://en.wikipedia.org/wiki/VESA_BIOS_Extensions

Folgende Dateien sind für die Grafik-Unterstützung in der Vorgabe:
- `VGA`: Zeichenfunktionen
- `VGA_Stream`: Textausgabe über den Stream-Operator `<<` im Grafikmodus 
- `fonts/*`: Bitmap-Fonts für die Textausgabe im Grafikmodus
- `user/aufgabe7/GrafikDemo`: Zeigt Ausgaben im Grafikmodus