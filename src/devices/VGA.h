/*****************************************************************************
 *                                                                           *
 *                                  L F B G                                  *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Der Grafikmodus wird durch grub beim Booten einge-       *
 *                  schaltet und ist in 'boot/boot.asm' konfiguriert. Die    *
 *                  Informationen werden in boot/Multiboot.c ausgelesen und  *
 *                  hier zur Verfuegung gestellt.                            *
 *                                                                           *
 *                  Hier gibt es die Möglichkeit Text zeilenweise als Stream *
 *                  auszugeben, wie bei CGA sowie weitere Zeichenfunktionen. *
 *                                                                           *
 * Autor:           Michael Schoettner, HHU, 8.7.2022                        *
 *                                                                           *
 *                  Der Code fuer das Zeichnen der Linie ist von Alan Wolfe  *
 *         https://blog.demofox.org/2015/01/17/bresenhams-drawing-algorithms *
 *                                                                           *
 *                  Der Code fuer das Zeichnen der Kreise ist von L. Szary   *
 * https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles *
 *****************************************************************************/

#ifndef __VGA_include__
#define __VGA_include__

#include "devices/CGA.h"
#include "devices/fonts/Fonts.h"
#include "lib/Types.h"


// Hilfsfunktionen um Farbwerte fuer einen Pixel zu erzeugen
#define RGB_24(r,g,b) (uint32_t) ((r << 16) + (g << 8) + b )

#define BUFFER_INVISIBLE 0
#define BUFFER_VISIBLE   1


class VGA {
    
private:
    VGA (const VGA &copy);  // Verhindere Kopieren

    // Hilfsfunktion fuer drawString
    void drawMonoBitmap   ( uint32_t x, uint32_t y, 
                            uint32_t width, uint32_t height, 
                            uint8_t  *bitmap, uint32_t col);

    void setPixelDirect     (uint8_t *ptr, uint32_t col);
    void drawLineSingleAxis (uint8_t *pixel, int majorAxisPixelMovement, int dx, uint32_t color);
    void drawLineMajorAxis  (uint8_t *pixel, int majorAxisPixelMovement,
                             int minorAxisPixelMovement, int dx, int dy, uint32_t color);    

public:
    uint64_t lfb;             // Adresse des Linearen Framebuffers
    uint64_t hfb;			  // Adresse des versteckten Buffers (optional, fuer Animationen)
    uint32_t xres, yres;      // Aufloesung in Pixel
    uint32_t pitch;           // Anzahl bytes pro Zeile, meist gilt pitch = xres 
    uint32_t bpp;             // Farbtiefe (Bits per Pixel)
    uint32_t mode; 			  // Zeichnenmodus: im sichtbaren = 1 oder unsichtbaren = 0 Puffer 

    uint32_t  t_xpos, t_ypos; // Text-Cursor-Position für Textausgabe mit 'gout'
    uint32_t  t_color;        // Farbe fuer Stream-Textausgabe
    Font      *t_fnt;         // Font for text output using 'print'
    uint32_t  t_line_space;   // Abstand zwischen Textzeilen in Pixel 
   
    bool graphic_mode_active; // Sind wir im Grafikmodus?

    
    VGA ();
    
    void clear            ();
    void drawPixel        ( uint32_t x, uint32_t y, uint32_t col);
    
    void drawLine         ( uint32_t x1, uint32_t y1, 
                            uint32_t x2, uint32_t y2, uint32_t col);
                           
    void drawFilledCircle ( uint32_t x0, uint32_t y0, uint32_t r, uint32_t col);

    void drawBitmap       ( uint32_t x, uint32_t y, uint32_t width, uint32_t height, 
                            uint8_t *bitmap, uint32_t bpp
                          );
                           
    void drawString       (Font *fnt, uint32_t x, uint32_t y, uint32_t col, char *str, uint32_t len);
    
    // stellt ein, ob in den sichtbaren Puffer gezeichnet wird
    void setDrawingBuff( int v);
    
    // kopiert 'hfb' nach 'lfb'
    void copyHiddenToVisible();
    
    // Zeigt ab, ob der Grafikmodus aktiv ist
    bool isGraphicOn() { return graphic_mode_active; }

    // Anzeige von 'n' Zeichen im Grafikmodus ab der aktuellen Cursorposition
    void print (char* string, uint32_t n);
    
    // Setze Cursor fuer 'print'
    void setpos(unsigned int char_x, unsigned int char_y);
    
    // Speicher Infos über den Grafik-Modus, wird von 'Multiboot.c' aufgerufen
    void set_graphic_infos(uint64_t lfb, uint32_t xres, uint32_t yres, uint32_t pitch, uint32_t bpp);  
    
    // Anzeige eines Zeichens mit Attribut an einer bestimmten Stelle; 'attrib' nicht implementiert
    void show (uint32_t t_x, uint32_t t_y, char character, uint8_t attrib);

    // Hilfsfunktion zur Erzeugung eines Attribut-Bytes (nocht nicht implementiert)
    uint8_t attribute (CGA::color bg, CGA::color fg, bool blink);

};

#endif
