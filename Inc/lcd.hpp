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
 * - GitHub Repository: [https://github.com/olekrisek/STM32_LCD]
 * - Documentation: Doc/html folder of the project
 *
 * @section license License
 * This library is released under the GNU Lesser General Public License license. Please refer to the license file provided
 * with the library for more information.
 *
 * @section contact Contact
 * For any inquiries or support, please contact the development team at olekrisek@gmail.com.
 */


#ifndef LCD_H
#define LCD_H

#include "stm32l5xx_hal.h"
#include "stm32l5xx_ll_ucpd.h"
#include "stm32l5xx_ll_bus.h"
#include "stm32l5xx_ll_cortex.h"
#include "stm32l5xx_ll_rcc.h"
#include "stm32l5xx_ll_system.h"
#include "stm32l5xx_ll_utils.h"
#include "stm32l5xx_ll_pwr.h"
#include "stm32l5xx_ll_gpio.h"
#include "stm32l5xx_ll_dma.h"

#include "stm32l5xx_ll_exti.h"
#include <iostream>
#include <cstdarg>

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00


// low-level functions
void send(uint8_t, GPIO_PinState);
void write4bits(uint8_t);
void write8bits(uint8_t);
void pulseEnable(void);


#include <iostream>
#include <string>

class LCD {
public:
	LCD(GPIO_TypeDef* portdata, GPIO_TypeDef* portctrlRW, GPIO_TypeDef* portctrlEN, GPIO_TypeDef* portctrlRS);
    void initDataPins(uint16_t val4, uint16_t val5, uint16_t val6, uint16_t val7);
    void initCtrlPins(uint16_t ctrlRW, uint16_t ctrlEN, uint16_t ctrlRS) ;
    size_t printLCD(const std::string& message = "");
    int printFormatted(const char* format, ...);
    void putch(uint8_t ch) ;
    void setCursor(uint8_t x=0, uint8_t y=0);
    void Begin ( int cols, int rows );
    void createChar(uint8_t location, uint8_t charmap[]);
    void noAutoscroll(void) ;
    void autoscroll(void) ;
    void leftToRight(void);
    void rightToLeft(void);
	void scrollDisplayLeft(void);
	void scrollDisplayRight(void);
	void noDisplay(void);
	void display(void);
	void noCursor(void);
	void cursor(void);
	void clear(void);
	void home(void);


private:
    GPIO_TypeDef *vPortData;
    GPIO_TypeDef *vPortCtrlRW;
	GPIO_TypeDef *vPortCtrlEN;
	GPIO_TypeDef *vPortCtrlRS;
	uint16_t d4, d5, d6, d7;
	uint16_t _data_pins[8];
	uint16_t vCtrlRW, vCtrlEN, vCtrlRS;

	uint8_t _displayfunction;
	uint8_t _displaycontrol;
	uint8_t _displaymode;

	uint8_t _initialized;

	uint8_t _numlines;
	uint8_t _row_offsets[4];
	uint8_t _fourbit_mode = 1;
	uint8_t dotsize = LCD_5x8DOTS;

	void setRowOffsets(int row0, int row1, int row2, int row3);
	inline void command(uint8_t value) ;
	inline size_t write(uint8_t value);
	void send(uint8_t value, GPIO_PinState mode);
	void pulseEnable(void);
	void write4bits(uint8_t value);
	void write8bits(uint8_t value);
	// Enables the RCC clock for the GPIO ports used by the LCD.
	void enableClock(void);
	    // Enables the RCC clock for the specified GPIO port.
	void enableClock2(GPIO_TypeDef* _port);

};

#endif // LCD_H
