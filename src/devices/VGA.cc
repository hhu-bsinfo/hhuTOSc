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
 * Autor:           Michael Schoettner, HHU, 26.6.2023                       *
 *****************************************************************************/

#include "devices/VGA.h"
#include "kernel/Globals.h"
#include "devices/fonts/Fonts.h"


/*****************************************************************************
 * Konstruktor:     VGA::VGA                                                 *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Initialisierung verschiedener Instanzvariablen.          *
 *****************************************************************************/
VGA::VGA () { 
   // Variablen Für Textausgabe mit Stream-Operator, siehe 'print' 
   t_xpos    = 0;
   t_ypos    = 0;        
   t_fnt     = &std_font_8x8;
   t_color   = RGB_24(0, 255, 0);
   t_line_space = 2;
}


/*****************************************************************************
 * Konstruktor:     VGA::set_graphic_infos                                   *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setter, um die Grafik-Modus-Infos zu speichern. Wird in  *
 *                  'Multiboot.c' gerufen, bevor 'main' angesprungen wird.   *
 *****************************************************************************/
void VGA::set_graphic_infos(uint64_t lfb, uint32_t xres, uint32_t yres, 
                            uint32_t pitch, uint32_t bpp) {
   this->lfb   = lfb;
   this->xres  = xres;
   this->yres  = yres;
   this->pitch = pitch;
   this->bpp   = bpp;
   graphic_mode_active = true;
}  


/*****************************************************************************
 * Methode:         VGA::attribute                                           *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Hilfsfunktion zur Erzeugung eines Attribut-Bytes aus     *
 *                  Hintergrund- und Vordergrundfarbe und der Angabe, ob das *
 *                  Zeichen blinkend darzustellen ist.                       *
 *                                                                           *
 *                  Funktion ist nur aus Kompatibilitaetsgruenden zu CGA da  *
 *                  Liefert aber immer 0 zurueck.                            *
 *                                                                           *
 * Parameter:                                                                *
 *      bg          Background color                                         *
 *      fg          Foreground color                                         *
 *      blink       ywa/no                                                   *
 *****************************************************************************/
uint8_t VGA::attribute (CGA::color bg, CGA::color fg, bool blink) {
   return 0;
}


/*****************************************************************************
 * Methode:         VGA::show                                                *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige eines Zeichens an einer bestimmten Stelle auf    *
 *                  dem Bildschirm. Das CGA-Attribut wird ignoriert.         *
 *                                                                           *
 * Parameter:                                                                *
 *      x,y         Position des Zeichens                                    *
 *      character   Das auszugebende Zeichen                                 *
 *      attrib      Attributbyte fuer das Zeichen                            *
 *****************************************************************************/
void VGA::show (uint32_t x, uint32_t y, char character, uint8_t attrib) {
    int t_xpos_saved = t_xpos;
    int t_ypos_saved = t_ypos;
    
    setpos(x, y);
    
    drawMonoBitmap( t_xpos, t_ypos, 
                    t_fnt->get_char_width(), t_fnt->get_char_height(),
                    t_fnt->getChar( character ), RGB_24(255,255,255));

    setpos(t_xpos_saved, t_ypos_saved);
}


/*****************************************************************************
 * Methode:         VGA::drawBitmap                                          *
 *---------------------------------------------------------------------------*
 * Parameter:       x,y     Startpunkt ab dem Bitmap ausgegeben wird.        *
 *                  width   Breite der Bitmap in Pixel                       *
 *                  height  Hoehe der Bitmap in Pixel                        *
 *                  bitmap  Zeiger auf Pixel der Bitmap                      *
 *                  bpp     Bits per Pixel der Bitmap                        *
 *                                                                           *
 * Beschreibung:    Gibt die gegebene Rastergrafik an der Position           *
 *                  x,y zeilenweise aus. (x,y) ist der linke obere Punkt;    *
 *****************************************************************************/
void VGA::drawBitmap ( uint32_t x, uint32_t y, uint32_t width, uint32_t height, 
                       uint8_t *bitmap, uint32_t bpp ) {

    uint32_t  xpos = x;
    uint32_t  ypos = y;
    uint32_t  r,g,b;
    uint32_t  idx = 0;
  
    for (y=0; y<height; ++y) {
        for (x=0; x<width; ++x) {
            r = bitmap[idx];
            g = bitmap[idx+1];
            b = bitmap[idx+2];
            drawPixel(xpos + x, ypos + y, RGB_24(r,g,b));
            idx += bpp;
        }
    }
}


/*****************************************************************************
 * Methode:         VGA::setpos                                              *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Setze Cursor fuer 'print'. Funktioniert nur fuer eine    *
 *                  nicht-proportionale Schrift.                             *
 *                                                                           *
 * Parameter:                                                                *
 *      char_x      x-Position in Zeichen                                    *
 *      char_y      y-Position in Zeichen                                    *   
 *****************************************************************************/
void VGA::setpos(uint32_t char_x, uint32_t char_y) {
   if (isGraphicOn()==false) return ;

   uint32_t t_line_height = t_fnt->get_char_height() + t_line_space;

   t_xpos = char_x * t_fnt->get_char_width();
   if (t_xpos > (xres - t_fnt->get_char_width()) ) {
	   t_xpos = xres - t_fnt->get_char_width(); 
   }
   
   t_ypos = char_y * t_line_height;
   if (t_ypos > (yres - t_line_height) ) {
	   t_ypos = yres - t_line_height; 
   }
}


/*****************************************************************************
 * Methode:         VGA::print                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Anzeige von 'n' Zeichen ab der aktuellen Cursorposition  *
 *                  '\n' fuer Zeilenvorschub.                                *
 *                                                                           *
 * Parameter:                                                                *
 *      string      Auszugebende Zeichenkette                                *
 *      n           Laenger der Zeichenkette                                 *
 *****************************************************************************/
void VGA::print (char* string, uint32_t n) {

   if (isGraphicOn()==false) return ;

   uint32_t t_line_height = t_fnt->get_char_height() + t_line_space;

   while(n) {
	   switch (*string) {
            case '\n':
                t_xpos = 0;
                t_ypos += t_line_height;
                break;
            default:
          		drawMonoBitmap( t_xpos, t_ypos, 
          		                t_fnt->get_char_width(), t_fnt->get_char_height(),
                                t_fnt->getChar( *string ), t_color);

                t_xpos += t_fnt->get_char_width();
                
                if (t_xpos >= xres) {
                    t_xpos =  0;
                    t_ypos += t_line_height;
                }
                break;
        }
        string++;
        
        if (t_ypos >= yres) {
//            scrollup();
            t_ypos -= t_line_height;
        }
        n--;
   }
}


/*****************************************************************************
 * Methode:         VGA::drawMonoBitmap                                     *
 *---------------------------------------------------------------------------*
 * Parameter:       x,y     Startpunkt ab dem Text ausgegeben wird.          *
 *                  width   Breite in Pixel                                  *
 *                  height  Hoehe in Pixel                                   *
 *                  bitmap  Zeiger auf Pixel der monochromen Rastergrafik    *
 *                  col     Farbe der Pixel                                  *
 *                                                                           *
 * Beschreibung:    Gibt die gegebene monochrome Rastergrafik an der Position*
 *                  x,y zeilenweise aus. (x,y) ist der linke obere Punkt;    *
 *                  ist in der bitmap eine '1', so wird ein Pixel mit der    *
 *                  Farbe col ausgegeben, ansonsten bei '0' nichts.          *
 *                  Diese Funktion basiert auf dem Format der Fonts, welche  *
 *                  mit cpi2fnt (AmigaOS) erzeugt wurden. Das Format erklaert*
 *                  sich in den C-Dateien in fonts/ von selbst.              *
 *****************************************************************************/
inline void VGA::drawMonoBitmap( uint32_t x, uint32_t y, uint32_t width,
                                 uint32_t height, uint8_t *bitmap, 
                                 uint32_t color) {
    // Breite in Bytes
    uint16_t width_byte = width/8 + ((width%8 != 0) ? 1 : 0);

	if (isGraphicOn()==false) return ;
    
    for(uint32_t yoff=0; yoff<height; ++yoff) {
        int xpos=x;
        int ypos=y+yoff;
        for(uint32_t xb=0; xb < width_byte; ++xb) {
            for( int src=7; src>=0; --src) {
          		if ((1 << src) & *bitmap) {
                   drawPixel(xpos, ypos, color);
                }
                xpos++;
            }
            bitmap++;
        }
    }
}


/*****************************************************************************
 * Methode:         VGA::drawString                                          *
 *---------------------------------------------------------------------------*
 * Parameter:       fnt     Schrift                                          *
 *                  x,y     Startpunkt ab dem Text ausgegeben wird.          *
 *                  col     Farbe des Textes                                 *
 *                  str     Zeiger auf Zeichenkette                          *
 *                  len     Laenge der Zeichenkette                          *
 *                                                                           *
 * Beschreibung:    Gibt eine Zeichenkette mit gewaehlter Schrift an der     *
 *                  Position x,y aus.                                        *
 *****************************************************************************/
void VGA::drawString(Font *fnt, uint32_t x, uint32_t y,  
                      uint32_t col, char* str, uint32_t len) {
    uint32_t i;
        
    for (i = 0; i < len; ++i) {
		drawMonoBitmap(x, y, fnt->get_char_width(), fnt->get_char_height(),
                       fnt->getChar( *(str+i) ), col);
        x += fnt->get_char_width();
    }
}


/*****************************************************************************
 * Methode:         VGA::drawPixel                                           *
 *---------------------------------------------------------------------------*
 * Parameter:       x, y    Koordinaten des Pixels                           *
 *                  col     Farbe                                            *
 *                                                                           *
 * Beschreibung:    Zeichnen eines Pixels.                                   *
 *****************************************************************************/
void VGA::drawPixel(uint32_t x, uint32_t y,uint32_t col) {
    uint8_t *ptr = (uint8_t *) lfb;
    
	if (isGraphicOn()==false) return ;
    
    // Pixel ausserhalb des sichtbaren Bereichs?
    if (x<0 || x>=xres || y<0 || y>yres)
        return;
    
    // Adresse des Pixels berechnen und Inhalt schreiben
    switch (bpp) {
        case 8:
            ptr += (x+y*xres);
            *ptr = col;
            return;
        case 15:
        case 16:
            ptr += (2*x+2*y*xres);
            *ptr = col;
            return;
        case 24:
            ptr += (3*x+3*y*xres);
            *ptr = (col & 0xFF); ptr++;
            *ptr = ((col>>8) & 0xFF); ptr++;
            *ptr = ((col>>16) & 0xFF); ptr++;
            return;
        case 32:
            ptr += (4*x+4*y*xres);
            *ptr = (col & 0xFF); ptr++;
            *ptr = ((col>>8) & 0xFF); ptr++;
            *ptr = ((col>>16) & 0xFF); ptr++;
            return;
    }
}


/*****************************************************************************
 * Methode:         VGA::setPixelDirect                                      *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Zeichnen eines Pixels an der gegebenen Adresse.          *
 *****************************************************************************/
void VGA::setPixelDirect(uint8_t *ptr, uint32_t col) {

	if (isGraphicOn()==false) return ;
   
    // Adresse des Pixels berechnen und Inhalt schreiben
    switch (bpp) {
        case 8:
            *ptr = col;
            return;
        case 15:
        case 16:
            *ptr = col;
            return;
        case 24:
            *ptr = (col & 0xFF); ptr++;
            *ptr = ((col>>8) & 0xFF); ptr++;
            *ptr = ((col>>16) & 0xFF); ptr++;
            return;
        case 32:
            *ptr = (col & 0xFF); ptr++;
            *ptr = ((col>>8) & 0xFF); ptr++;
            *ptr = ((col>>16) & 0xFF); ptr++;
            return;
    }
}


/*****************************************************************************
 * Methode:         VGA::clear                                               *
 *---------------------------------------------------------------------------*
 * Beschreibung:    Bildschirm loeschen.                                     *
 *****************************************************************************/
void VGA::clear() {
    uint32_t *ptr = (uint32_t *)lfb;
    uint32_t i;

    
	if (isGraphicOn()==false) return ;
    
    setpos(0,0);
    
    switch (bpp) {
        case 8:
            for (i=0; i < ((xres/4)*yres); i++)
               *(ptr++) = 0;
            return;
        case 15:
        case 16:
            for (i=0; i < (2*(xres/4)*yres); i++)
               *(ptr++) = 0;
            return;
        case 24:
            for (i=0; i < (3*(xres/4)*yres); i++)
               *(ptr++) = 0;
            return;
        case 32:
            for (i=0; i < (4*(xres/4)*yres); i++)
               *(ptr++) = 0;
            return;
    }
}

