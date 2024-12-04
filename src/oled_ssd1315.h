#ifndef OLED_SSD1315_H
#define OLED_SSD1315_H

#include <U8g2lib.h>

class OledDecorator {
public:
    OledDecorator(U8G2_SSD1306_128X64_NONAME_F_HW_I2C& display);
    void render();

    enum Style {
        STYLE_1ROWS,
        STYLE_2ROWS,
        STYLE_3ROWS,
        STYLE_4ROWS     
    };
    void setStyle(Style style);
    void setRow1(String text);
    void setRow1(String text, bool renerNow);
    void setRow2(String text);
    void setRow2(String text, bool renerNow);
    void setRow3(String text);
    void setRow3(String text, bool renerNow);
    void setRow4(String text);
    void setRow4(String text, bool renerNow);
    void clearRows();

private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C& display;    
    String row1, row2, row3, row4;
    Style _style = STYLE_4ROWS;
    void render4rows();
    void render3rows();
    void render2rows();
    void render1rows();
};

#endif // OLED_DECORATOR_H