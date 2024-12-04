#include "oled_ssd1315.h"

OledDecorator::OledDecorator(U8G2_SSD1306_128X64_NONAME_F_HW_I2C& display)
    : display(display), row1(""), row2(""), row3(""), row4("") {
}

void OledDecorator::setStyle(Style style) {
    _style = style;
}

void OledDecorator::setRow1(String text) { setRow1(text, false); }
void OledDecorator::setRow2(String text) { setRow2(text, false); }
void OledDecorator::setRow3(String text) { setRow3(text, false); }
void OledDecorator::setRow4(String text) { setRow4(text, false); }

void OledDecorator::setRow1(String text, bool renderNow) {
    row1 = text;
    if (renderNow) { render(); }
}

void OledDecorator::setRow2(String text, bool renderNow) {
    row2 = text;
    if (renderNow) { render(); }
}

void OledDecorator::setRow3(String text, bool renderNow) {
    row3 = text;
    if (renderNow) { render(); }
}

void OledDecorator::setRow4(String text, bool renderNow) {
    row4 = text;
    if (renderNow) { render(); }
}

void OledDecorator::clearRows() {
    row1 = "";
    row2 = "";
    row3 = "";
    row4 = "";
}

void OledDecorator::render() {
    display.clearBuffer();   

    display.setFont(u8g2_font_spleen5x8_mf);
    display.drawStr(0, 10, row1.c_str());
    display.setFont(u8g2_font_spleen5x8_mf);
    display.drawStr(0, 24, row2.c_str());
    display.setFont(u8g2_font_spleen5x8_mf);
    display.drawStr(0, 38, row3.c_str());
    display.setFont(u8g2_font_spleen5x8_mf);
    display.drawStr(0, 50, row4.c_str());

    display.sendBuffer();
}

/*
    la sezione gialla va da 1 a 23
    i font _tn non li ho capiti
    x minima = 0, y minima = 10
    u8g2_font_ncenB08_tr
    - u8g2_font_ = costante per i fonto
    - ncen = nome del font
    - B = bold, R = regular
    - 08 = dimensione del font
    - tr = truetype, tf = fixed, me = extended, mr = regular
      , te = extended, tu = unicode, tn = non so, mn = non so
      , he = extended, hf = fixed, ht = truetype
    - streamline_content_files_t  = simboli

*/
