// LCD_wrapper.cpp

#include "LCD_wrapper.h"
#include "LCD.hpp"

struct LCD_Wrapper {
    LCD* lcd_cpp;
};

LCD* LCD_create(void* portdata, void* portctrlRW, void* portctrlEN, void* portctrlRS) {
	LCD_Wrapper* lcd_wrapper = new LCD_Wrapper;
	lcd_wrapper->lcd_cpp = new LCD(static_cast<GPIO_TypeDef*>(portdata), static_cast<GPIO_TypeDef*>(portctrlRW),
			static_cast<GPIO_TypeDef*>(portctrlEN), static_cast<GPIO_TypeDef*>(portctrlRS));
	return lcd_wrapper->lcd_cpp;
}

void LCD_initCtrlPins(LCD* lcd, uint16_t ctrlRW, uint16_t ctrlEN, uint16_t ctrlRS) {
	lcd->initCtrlPins(ctrlRW, ctrlEN, ctrlRS);
}

void LCD_initDataPins(LCD* lcd, uint16_t val4, uint16_t val5, uint16_t val6, uint16_t val7) {
	lcd->initDataPins(val4, val5, val6, val7);
}

void LCD_print(LCD* lcd, const char* message) {
	std::string str(message);
	lcd->printLCD(str);
}

int LCD_printFormatted(LCD* lcd, const char* format, ...) {
	char buffer[100];
	int n;
	// Format the string using the given format and variable arguments
	va_list args;
	va_start(args, format);
	n = vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);

	// Print the formatted string to the LCD display
	if ( n>0) {
		std::string str(buffer);
		lcd->printLCD(str);
	}
	return n;

}

void LCD_setCursor(LCD* lcd, int x, int y) {
	lcd->setCursor(x, y);
}

void LCD_Begin(LCD* lcd, int cols, int rows) {
	lcd->Begin(cols, rows);
}

void LCD_createChar(LCD* lcd, uint8_t location, uint8_t charmap[]) {
	lcd->createChar(location, charmap);
}

void LCD_noAutoscroll(LCD* lcd) {
	lcd->noAutoscroll();
}

void LCD_autoscroll(LCD* lcd) {
	lcd->autoscroll();
}

void LCD_leftToRight(LCD* lcd) {
	lcd->leftToRight();
}

void LCD_rightToLeft(LCD* lcd) {
	lcd->rightToLeft();
}

void LCD_scrollDisplayLeft(LCD* lcd) {
	lcd->scrollDisplayLeft();
}

void LCD_scrollDisplayRight(LCD* lcd) {
	lcd->scrollDisplayRight();
}

void LCD_noDisplay(LCD* lcd) {
	lcd->noDisplay();
}

void LCD_display(LCD* lcd) {
	lcd->display();
}

void LCD_noCursor(LCD* lcd) {
	lcd->noCursor();
}

void LCD_cursor(LCD* lcd) {
	lcd->cursor();
}

void LCD_clear(LCD* lcd) {
	lcd->clear();
}

void LCD_home(LCD* lcd) {
	lcd->home();
}
