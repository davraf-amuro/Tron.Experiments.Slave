#include "oled_decorator.h"

OledDecorator::OledDecorator(Adafruit_SSD1306& display)
    : display(display), row1(""), row2(""), row3(""), row4("") {
}

void OledDecorator::render() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(row1);
    display.setCursor(0, 8);
    display.println(row2);
    display.setCursor(0, 16);
    display.println(row3);
    display.setCursor(0, 24);
    display.println(row4);
    display.display();
}

void OledDecorator::SetRow1(String text) {
    row1 = text;
}

void OledDecorator::SetRow2(String text) {
    row2 = text;
}

void OledDecorator::SetRow3(String text) {
    row3 = text;
}

void OledDecorator::SetRow4(String text) {
    row4 = text;
}