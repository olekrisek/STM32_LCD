/**
 * @file LCD_wrapper.cpp
 * @brief Wrapper functions for interfacing with an LCD display.
 */

#include "LCD_wrapper.h"
#include "LCD.hpp"

/**
 * @struct LCD_Wrapper
 * @brief Wrapper structure to hold an instance of the LCD class.
 */
struct LCD_Wrapper {
    LCD* lcd_cpp; /**< Pointer to the LCD object */
};

/**
 * @brief Create an LCD object and return a pointer to it.
 *
 * This function creates an LCD object by instantiating the LCD class.
 * The provided port data and control pins are used to initialize the LCD.
 * Returns a pointer to the created LCD object.
 *
 * @param portdata Pointer to the data port
 * @param portctrlRW Pointer to the RW control port
 * @param portctrlEN Pointer to the EN control port
 * @param portctrlRS Pointer to the RS control port
 *
 * @return Pointer to the created LCD object
 */
LCD* LCD_create(void* portdata, void* portctrlRW, void* portctrlEN, void* portctrlRS) {
    LCD_Wrapper* lcd_wrapper = new LCD_Wrapper;
    lcd_wrapper->lcd_cpp = new LCD(static_cast<GPIO_TypeDef*>(portdata),
                                    static_cast<GPIO_TypeDef*>(portctrlRW),
                                    static_cast<GPIO_TypeDef*>(portctrlEN),
                                    static_cast<GPIO_TypeDef*>(portctrlRS));
    return lcd_wrapper->lcd_cpp;
}

/**
 * @brief Initialize control pins of the LCD.
 *
 * This function initializes the control pins of the LCD, including
 * the control read/write (RW), control enable (EN), and control register select (RS) pins.
 *
 * @param lcd Pointer to the LCD object
 * @param ctrlRW The control pin for read/write signal
 * @param ctrlEN The control pin for enable signal
 * @param ctrlRS The control pin for register select signal
 *
 * @return None
 */
void LCD_initCtrlPins(LCD* lcd, uint16_t ctrlRW, uint16_t ctrlEN, uint16_t ctrlRS) {
    lcd->initCtrlPins(ctrlRW, ctrlEN, ctrlRS);
}

/**
 * @brief Initialize data pins of the LCD.
 *
 * This function initializes the data pins of the LCD, including
 * the individual data pins used for communication with the LCD module.
 *
 * @param lcd Pointer to the LCD object
 * @param val4 The value for data pin 4
 * @param val5 The value for data pin 5
 * @param val6 The value for data pin 6
 * @param val7 The value for data pin 7
 *
 * @return None
 */
void LCD_initDataPins(LCD* lcd, uint16_t val4, uint16_t val5, uint16_t val6, uint16_t val7) {
    lcd->initDataPins(val4, val5, val6, val7);
}

/**
 * @brief Print a message to the LCD display.
 *
 * This function prints a given message to the LCD display.
 *
 * @param lcd Pointer to the LCD object
 * @param message The message to be printed on the display
 *
 * @return None
 */
void LCD_print(LCD* lcd, const char* message) {
    std::string str(message);
    lcd->printLCD(str);
}

/**
 * @brief Print a formatted message to the LCD display.
 *
 * This function prints a formatted message to the LCD display using the provided format string
 * and variable arguments. The formatted message is printed to the LCD display if the formatting
 * is successful.
 *
 * @param lcd Pointer to the LCD object
 * @param format The format string for the message
 * @param ... Variable arguments to be formatted
 *
 * @return The number of characters printed on success, or a negative value on failure
 */
int LCD_printFormatted(LCD* lcd, const char* format, ...) {
    char buffer[100];
    int n;

    // Format the string using the given format and variable arguments
    va_list args;
    va_start(args, format);
    n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // Print the formatted string to the LCD display
    if (n > 0) {
        std::string str(buffer);
        lcd->printLCD(str);
    }

    return n;
}

/**
 * @brief Write a character to the LCD display.
 *
 * This function writes a character to the LCD display.
 *
 * @param lcd Pointer to the LCD object
 * @param ch The character to be written
 *
 * @return None
 */
void LCD_putch(LCD* lcd, uint8_t ch) {
    lcd->putch(ch);
}

/**
 * @brief Set the cursor position on the LCD display.
 *
 * This function sets the cursor position on the LCD display
 * using the specified column (x) and row (y) coordinates.
 *
 * @param lcd Pointer to the LCD object
 * @param x The column position (0-based index)
 * @param y The row position (0-based index)
 *
 * @return None
 */
void LCD_setCursor(LCD* lcd, int x, int y) {
    lcd->setCursor(x, y);
}

/**
 * @brief Initialize the LCD display with the specified number of columns and rows.
 *
 * This function initializes the LCD display with the specified number of
 * columns and rows. It configures the display to operate in the given size.
 *
 * @param lcd Pointer to the LCD object
 * @param cols Number of columns in the display
 * @param rows Number of rows in the display
 *
 * @return None
 */
void LCD_Begin(LCD* lcd, int cols, int rows) {
    lcd->Begin(cols, rows);
}

/**
 * @brief Create a custom character on the LCD display.
 *
 * This function creates a custom character on the LCD display using the
 * provided character location and character map data.
 *
 * @param lcd Pointer to the LCD object
 * @param location The location (0-7) to store the custom character
 * @param charmap The character map data defining the custom character
 *
 * @return None
 */
void LCD_createChar(LCD* lcd, uint8_t location, uint8_t charmap[]) {
    lcd->createChar(location, charmap);
}

/**
 * @brief Disable autoscroll on the LCD display.
 *
 * This function disables the autoscroll feature on the LCD display.
 * It prevents the display from automatically scrolling when new text is added.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_noAutoscroll(LCD* lcd) {
    lcd->noAutoscroll();
}

/**
 * @brief Enable autoscroll on the LCD display.
 *
 * This function enables the autoscroll feature on the LCD display.
 * It allows the display to automatically scroll when new text is added.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_autoscroll(LCD* lcd) {
    lcd->autoscroll();
}

/**
 * @brief Set the text direction on the LCD display to left-to-right.
 *
 * This function sets the text direction on the LCD display to left-to-right.
 * It ensures that subsequent characters are displayed from left to right.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_leftToRight(LCD* lcd) {
    lcd->leftToRight();
}

/**
 * @brief Set the text direction on the LCD display to right-to-left.
 *
 * This function sets the text direction on the LCD display to right-to-left.
 * It ensures that subsequent characters are displayed from right to left.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_rightToLeft(LCD* lcd) {
    lcd->rightToLeft();
}

/**
 * @brief Scroll the display content to the left.
 *
 * This function scrolls the content on the LCD display to the left.
 * It shifts the display content to the left by one position.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_scrollDisplayLeft(LCD* lcd) {
    lcd->scrollDisplayLeft();
}

/**
 * @brief Scroll the display content to the right.
 *
 * This function scrolls the content on the LCD display to the right.
 * It shifts the display content to the right by one position.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_scrollDisplayRight(LCD* lcd) {
    lcd->scrollDisplayRight();
}

/**
 * @brief Turn off the display on the LCD.
 *
 * This function turns off the display on the LCD.
 * It clears the display and turns off the cursor.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_noDisplay(LCD* lcd) {
    lcd->noDisplay();
}

/**
 * @brief Turn on the display on the LCD.
 *
 * This function turns on the display on the LCD.
 * It displays the cursor and any previously written content.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_display(LCD* lcd) {
    lcd->display();
}

/**
 * @brief Hide the cursor on the LCD display.
 *
 * This function hides the cursor on the LCD display.
 * The cursor is not visible, but the content is still displayed.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_noCursor(LCD* lcd) {
    lcd->noCursor();
}

/**
 * @brief Show the cursor on the LCD display.
 *
 * This function shows the cursor on the LCD display.
 * The cursor is displayed and can be used for navigation.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_cursor(LCD* lcd) {
    lcd->cursor();
}

/**
 * @brief Clear the LCD display.
 *
 * This function clears the content on the LCD display.
 * It removes all characters and sets the cursor to the home position.
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_clear(LCD* lcd) {
    lcd->clear();
}

/**
 * @brief Set the cursor to the home position.
 *
 * This function sets the cursor position to the home position on the LCD display.
 * The home position is the top-left corner of the display (column 0, row 0).
 *
 * @param lcd Pointer to the LCD object
 *
 * @return None
 */
void LCD_home(LCD* lcd) {
    lcd->home();
}
