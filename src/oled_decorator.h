#ifndef OLED_DECORATOR_H
#define OLED_DECORATOR_H

#include <Adafruit_SSD1306.h>

class OledDecorator {
public:
    OledDecorator(Adafruit_SSD1306& display);
    void render();
    void SetRow1(String text);
    void SetRow2(String text);
    void SetRow3(String text);
    void SetRow4(String text);

private:
    Adafruit_SSD1306& display;
    String row1;
    String row2;
    String row3;
    String row4;
};

#endif // OLED_DECORATOR_H