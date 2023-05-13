/**
 * @mainpage LCD Library for STM32 Microcontroller
 *
 * @section intro Introduction
 * The LCD library for STM32 Microcontroller provides a convenient way to drive a text-based LCD display
 * using STM32 microcontrollers. This library is based on the existing C code from the LiquidCrystal library,
 * but with additional enhancements and modifications to better suit the STM32 platform.
 *
 * This library offers a different initialization method that allows the digital lines (data lines) to be
 * on the same port while the control signals can be on different ports. It also provides support for multiple
 * LCD displays connected to the same microcontroller.
 *
 * One notable feature of this library is the modified print override, which ensures that the printed data
 * is directed specifically to the targeted LCD display without interfering with other print destinations
 * such as console or UART implementations.
 *
 * @section usage Usage
 * To use the LCD library in your STM32 project, include the appropriate header files and link against
 * the library during the compilation process. Refer to the documentation and examples for detailed instructions
 * on how to integrate and utilize the library's functionality in your code.
 *
 * @section resources Resources
 * - GitHub Repository: [link to the GitHub repository]
 * - Documentation: [link to the online documentation]
 *
 * @section license License
 * This library is released under the [license name] license. Please refer to the license file provided
 * with the library for more information.
 *
 * @section contact Contact
 * For any inquiries or support, please contact the development team at olekrisek@gmail.com.
 */


#ifndef LCD_WRAPPER_H
#define LCD_WRAPPER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LCD LCD;

/**
 * @brief Creates an instance of the LCD object.
 *
 * @param portdata Pointer to the GPIO port for data pins.
 * @param portctrlRW Pointer to the GPIO port for RW control pin.
 * @param portctrlEN Pointer to the GPIO port for EN control pin.
 * @param portctrlRS Pointer to the GPIO port for RS control pin.
 * @return Pointer to the created LCD object.
 */
LCD* LCD_create(void* portdata, void* portctrlRW, void* portctrlEN, void* portctrlRS);

/**
 * @brief Initializes the control pins of the LCD.
 *
 * @param lcd Pointer to the LCD object.
 * @param ctrlRW GPIO pin number for the RW control pin.
 * @param ctrlEN GPIO pin number for the EN control pin.
 * @param ctrlRS GPIO pin number for the RS control pin.
 */
void LCD_initCtrlPins(LCD* lcd, uint16_t ctrlRW, uint16_t ctrlEN, uint16_t ctrlRS);

/**
 * @brief Initializes the data pins of the LCD.
 *
 * @param lcd Pointer to the LCD object.
 * @param val4 GPIO pin number for D4 data pin.
 * @param val5 GPIO pin number for D5 data pin.
 * @param val6 GPIO pin number for D6 data pin.
 * @param val7 GPIO pin number for D7 data pin.
 */
void LCD_initDataPins(LCD* lcd, uint16_t val4, uint16_t val5, uint16_t val6, uint16_t val7);

/**
 * @brief Prints the given message on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 * @param message The message to be printed.
 */
void LCD_print(LCD* lcd, const char* message);

/**
 * @brief Print formatted string to LCD display.
 *
 * This function allows printing a formatted string to the LCD display using a
 * format string and variable arguments, similar to the `printf` function.
 *
 * @param lcd Pointer to the LCD object.
 * @param format Format string specifying the output format.
 * @param ... Additional arguments to be formatted and printed.
 *
 * @return The number of characters printed on the LCD display.
 */

int LCD_printFormatted(LCD* lcd, const char* format, ...);

/**
 * @brief Outputs a character to the LCD display.
 *
 * This function writes a character to the LCD display.
 * If the character is 0, the function returns without performing any action.
 * Otherwise, it writes the character to the display and increments the internal counter.
 *
 * @param ch The character to be written to the display.
 *
 * @return None
 */

void LCD_putch(LCD* lcd, uint8_t ch) ;


/**
 * @brief Sets the cursor position on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 * @param x The column position (0-based).
 * @param y The row position (0-based).
 */
void LCD_setCursor(LCD* lcd, int x, int y);

/**
 * @brief Initializes the LCD with the specified number of columns and rows.
 *
 * @param lcd Pointer to the LCD object.
 * @param cols Number of columns.
 * @param rows Number of rows.
 */
void LCD_Begin(LCD* lcd, int cols, int rows);

/**
 * @brief Creates a custom character for the LCD.
 *
 * @param lcd Pointer to the LCD object.
 * @param location The CGRAM location for the character (0-7).
 * @param charmap Array of 8 bytes representing the character pattern.
 */
void LCD_createChar(LCD* lcd, uint8_t location, uint8_t charmap[]);

/**
 * @brief Disables autoscroll on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_noAutoscroll(LCD* lcd);

/**
 * @brief Enables autoscroll on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_autoscroll(LCD* lcd);

/**
 * @brief Sets the text direction to left-to-right on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_leftToRight(LCD* lcd);

/**
 * @brief Sets the text direction to right-to-left on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_rightToLeft(LCD* lcd);

/**
 * @brief Scrolls the display to the left on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_scrollDisplayLeft(LCD* lcd);

/**
 * @brief Scrolls the display to the right on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_scrollDisplayRight(LCD* lcd);

/**
 * @brief Turns off the display on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_noDisplay(LCD* lcd);

/**
 * @brief Turns on the display on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_display(LCD* lcd);

/**
 * @brief Turns off the cursor on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_noCursor(LCD* lcd);

/**
 * @brief Turns on the cursor on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_cursor(LCD* lcd);

/**
 * @brief Clears the LCD screen.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_clear(LCD* lcd);

/**
 * @brief Moves the cursor to the home position on the LCD.
 *
 * @param lcd Pointer to the LCD object.
 */
void LCD_home(LCD* lcd);




#ifdef __cplusplus
}
#endif

#endif /* LCD_WRAPPER_H */
