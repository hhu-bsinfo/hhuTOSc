// Jakob Falke, oostubs
// Github: https://gitlab.cs.fau.de/um15ebek/oostubs

// Schriften in Form von Rastergrafiken (separate Datein)
// Generiert mit cpi2fnt
// Keine Proportionalschriften
// Monochrome Speicherung: 1 Bit pro Pixel
// Je nach Breite wird auf Bytegrenzen aufgerundet:
//  8 Pixel -> 1 Byte; 12 Pixel -> 2 Byte

#ifndef __FONTS_H__
#define __FONTS_H__


class Font
{
public:
    virtual unsigned char* getChar(int c) const = 0;
    virtual unsigned int get_char_width() const = 0;
    virtual unsigned int get_char_height() const = 0;
};


template<unsigned int width, unsigned int height, unsigned char* data>
class FontInstance : public Font
{
    const unsigned int char_width;
    const unsigned int char_height;
    const unsigned int char_mem_size;
    unsigned char* font_data;
public:
    FontInstance() : char_width(width), char_height(height), char_mem_size((((char_width + (8 >> 1)) / 8) * char_height)), font_data(data) { }
    inline unsigned char* getChar(int c) const {
        return &font_data[char_mem_size * c];
    }
    inline unsigned int get_char_width() const {
        return char_width;
    }
    inline unsigned int get_char_height() const {
        return char_height;
    }
};


extern unsigned char fontdata_8x16[];
extern unsigned char fontdata_8x8[];
extern unsigned char acorndata_8x8[];
extern unsigned char fontdata_pearl_8x8[];
extern unsigned char fontdata_sun_12x22[];
extern unsigned char fontdata_sun_8x16[];


typedef FontInstance<8,16,fontdata_8x16> Font_8x16;
typedef FontInstance<8,8,fontdata_8x8> Font_8x8;
typedef FontInstance<8,8,acorndata_8x8> Font_acorn_8x8;
typedef FontInstance<8,8,fontdata_pearl_8x8> Font_pearl_8x8;
typedef FontInstance<12,22,fontdata_sun_12x22> Font_sun_12x22;
typedef FontInstance<8,16,fontdata_sun_8x16> Font_sun_8x16;

extern Font_8x16	       std_font_8x16;
extern Font_8x8		       std_font_8x8;
extern Font_acorn_8x8	   acorn_font_8x8;
extern Font_pearl_8x8	   pearl_font_8x8;
extern Font_sun_12x22	   sun_font_12x22;
extern Font_sun_8x16	   sun_font_8x16;

#endif
