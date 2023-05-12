
#include "lcd.hpp"


/*********** mid level commands, for sending data/cmds */



 /**

 @brief LCD constructor.
 @param portdata Pointer to the GPIO port for data communication.
 @param portctrlRW Pointer to the GPIO port for the RW control line.
 @param portctrlEN Pointer to the GPIO port for the EN control line.
 @param portctrlRS Pointer to the GPIO port for the RS control line.
 @retval None
 */

    LCD::LCD(GPIO_TypeDef* portdata, GPIO_TypeDef* portctrlRW, GPIO_TypeDef* portctrlEN, GPIO_TypeDef* portctrlRS) {
        vPortData = portdata;
        vPortCtrlRW = portctrlRW;
        vPortCtrlEN = portctrlEN;
        vPortCtrlRS = portctrlRS;
    }

/**

    @brief Initializes the data pins of the LCD.
    @param val4 Value for data pin 4.
    @param val5 Value for data pin 5.
    @param val6 Value for data pin 6.
    @param val7 Value for data pin 7.
    @retval None
    */

    void LCD::initDataPins(uint16_t val4, uint16_t val5, uint16_t val6, uint16_t val7) {
        d4 = val4;
        d5 = val5;
        d6 = val6;
        d7 = val7;
        _data_pins[0] = d4;
        _data_pins[1] = d5;
        _data_pins[2] = d6;
        _data_pins[3] = d7;
    }

/**

    @brief Initializes the control pins of the LCD.
    @param ctrlRW Value for the control pin RW.
    @param ctrlEN Value for the control pin EN.
    @param ctrlRS Value for the control pin RS.
    @retval None
    */

    void LCD::initCtrlPins(uint16_t ctrlRW, uint16_t ctrlEN, uint16_t ctrlRS) {
        vCtrlRW = ctrlRW;
        vCtrlEN = ctrlEN;
        vCtrlRS = ctrlRS;
    }

/**

    @brief Prints the specified message on the LCD.
    @param message The message to be printed on the LCD.
    @retval None
    */

    size_t LCD::printLCD(const std::string& message) {
    	if (message.length() == 0) return 0;
    	  size_t n=0;
    	  for (size_t i = 0; i < message.length(); i++) {
    	    if (write(message[i])) n++;
    	    else break;
    	  }
    	  return n;
    }

    /**
     * @brief Print formatted string to LCD display.
     *
     * This method allows printing a formatted string to the LCD display using a
     * format string and variable arguments, similar to the `printf` function.
     *
     * @param format Format string specifying the output format.
     * @param ... Additional arguments to be formatted and printed.
     *
     * @return The number of characters printed on the LCD display.
     */
    int LCD::printFormatted(const char* format, ...) {
        // Buffer to store the formatted string
    	char buffer[100];
    	int n;
    	// Format the string using the given format and variable arguments
    	va_list args;
    	va_start(args, format);
    	n = vsnprintf(buffer, sizeof(buffer), format, args);
    	va_end(args);

    	// Print the formatted string to the LCD display
    	if ( n > 0 ) {
    		printLCD(buffer);
    	}
    	return n;
    }



/**

    @brief Sets the cursor position on the LCD.
    @param x The X-coordinate of the cursor position.
    @param y The Y-coordinate of the cursor position.
    @retval None
    */

    void LCD::setCursor(uint8_t x, uint8_t y) {
    	const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
    	  if ( y >= max_lines ) {
    	    y = max_lines - 1;    // we count rows starting w/0
    	  }
    	  if ( y >= _numlines ) {
    	    y = _numlines - 1;    // we count rows starting w/0
    	  }

    	  command(LCD_SETDDRAMADDR | (x + _row_offsets[y]));
    }

    /**

    @brief Creates a custom character and assigns it to the specified CGRAM location.
    @param location The location in CGRAM where the custom character will be stored (0-7).
    @param charmap An array representing the character pattern (8 bytes) to be assigned to the location.
    @retval None
    */
    // Allows us to fill the first 8 CGRAM locations
    // with custom characters
    void LCD::createChar(uint8_t location, uint8_t charmap[]) {
      location &= 0x7; // we only have 8 locations 0-7
      command(LCD_SETCGRAMADDR | (location << 3));
      for (int i=0; i<8; i++) {
        write(charmap[i]);
      }
    }

    /**

    @brief Disables autoscrolling of text, causing it to be left-justified from the cursor position.
    @retval None
    */

    void LCD::noAutoscroll(void) {
      _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
      command(LCD_ENTRYMODESET | _displaymode);
    }


    /**

    @brief Enables autoscrolling of text, causing it to be right-justified from the cursor position.
    @retval None
    */
    void LCD::autoscroll(void) {
      _displaymode |= LCD_ENTRYSHIFTINCREMENT;
      command(LCD_ENTRYMODESET | _displaymode);
    }

    /**

    @brief Sets the text flow direction to right-to-left.
    @retval None
    */
    void LCD::rightToLeft(void) {
      _displaymode &= ~LCD_ENTRYLEFT;
      command(LCD_ENTRYMODESET | _displaymode);
    }


    /**

    @brief Sets the text flow direction to left-to-right.
    @retval None
    */

    void LCD::leftToRight(void) {
      _displaymode |= LCD_ENTRYLEFT;
      command(LCD_ENTRYMODESET | _displaymode);
    }

    /**

    @brief Scrolls the display to the left without changing the RAM contents.
    @retval None
    */
    void LCD::scrollDisplayLeft(void) {
      command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
    }

    /**

    @brief Scrolls the display to the right without changing the RAM contents.
    @retval None
    */
    void LCD::scrollDisplayRight(void) {
      command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
    }

    /**
     * @brief Turns off the display.
     */
    void LCD::noDisplay(void) {
        _displaycontrol &= ~LCD_DISPLAYON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    /**
     * @brief Turns on the display.
     */
    void LCD::display(void) {
        _displaycontrol |= LCD_DISPLAYON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    /**
     * @brief Turns off the underline cursor.
     */
    void LCD::noCursor(void) {
        _displaycontrol &= ~LCD_CURSORON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    /**
     * @brief Turns on the underline cursor.
     */
    void LCD::cursor(void) {
        _displaycontrol |= LCD_CURSORON;
        command(LCD_DISPLAYCONTROL | _displaycontrol);
    }

    /**
	 * @brief Clears the display and sets the cursor position to zero.
	 */
    void LCD::clear(void)
    {
        command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
        HAL_Delay(2);  // this command takes a long time!
    }

    /**
	 * @brief Sets the cursor position to zero.
	 */
    void LCD::home(void)
    {
        command(LCD_RETURNHOME);  // set cursor position to zero
        HAL_Delay(2);  // this command takes a long time!
    }

    /**
     * @brief Enables the RCC clock for the GPIO ports used by the LCD.
     *
     * This method selectively enables the RCC (Reset and Clock Control) clock for the GPIO ports
     * used by the LCD. It ensures that the necessary RCC clock is enabled for each GPIO port
     * associated with the LCD's data and control pins.
     */
    void LCD::enableClock(void) {
        enableClock2(vPortData);
        if (vPortCtrlRW != vPortData) enableClock2(vPortCtrlRW);
        if (vPortCtrlRS != vPortCtrlRW) enableClock2(vPortCtrlRS);
        if (vPortCtrlEN != vPortCtrlRS) enableClock2(vPortCtrlEN);
    }

    /**
     * @brief Enables the RCC clock for the specified GPIO port.
     *
     * This method enables the RCC clock for the specified GPIO port, allowing the use of GPIO pins
     * on that port. It checks the `_port` parameter and calls the corresponding `__HAL_RCC_GPIOx_CLK_ENABLE()`
     * macro to enable the RCC clock for the specific GPIO port.
     *
     * @param _port Pointer to the GPIO port to enable the RCC clock for.
     *
     * @note If you have a GPIO port that is not listed in the code snippet, you need to add an additional
     *       `else if` condition to enable the RCC clock for that port.
     */
    void LCD::enableClock2(GPIO_TypeDef* _port) {
        if (_port == GPIOA)
            __HAL_RCC_GPIOA_CLK_ENABLE();
        else if (_port == GPIOB)
            __HAL_RCC_GPIOB_CLK_ENABLE();
        else if (_port == GPIOC)
            __HAL_RCC_GPIOC_CLK_ENABLE();
        else if (_port == GPIOD)
            __HAL_RCC_GPIOD_CLK_ENABLE();
        else if (_port == GPIOE)
            __HAL_RCC_GPIOE_CLK_ENABLE();
        else if (_port == GPIOF)
            __HAL_RCC_GPIOF_CLK_ENABLE();

        // if you have a port that is not listed add it below the other else ifs
    }


/**

    @brief Begins the LCD initialization with the specified number of columns and rows.
    @param cols The number of columns on the LCD.
    @param rows The number of rows on the LCD.
    @retval None
    */

    void LCD::Begin ( int cols, int rows ) {
    	if (rows > 1) {
    	    _displayfunction |= LCD_2LINE;
    	  }
    	  _numlines = rows;
    	 setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

    	 // for some 1 line displays you can select a 10 pixel high font
    	   if ((dotsize != LCD_5x8DOTS) && (rows == 1)) {
    	     _displayfunction |= LCD_5x10DOTS;
    	   }

    	   //Initializing GPIO Pins
    	   enableClock();

    	   GPIO_InitTypeDef gpio_init;
    	   gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    	   gpio_init.Mode = GPIO_MODE_OUTPUT_PP;

    	   // RS:
    	   gpio_init.Pin = vCtrlRS;
    	   HAL_GPIO_Init(vPortCtrlRS, &gpio_init);

    	   // RW:
    	   gpio_init.Pin = vCtrlRW;
    	   HAL_GPIO_Init(vPortCtrlRW, &gpio_init);

    	   // EN
    	   gpio_init.Pin = vCtrlEN;
    	   HAL_GPIO_Init(vPortCtrlEN, &gpio_init);

    	   // Data

    	   if(_fourbit_mode)
    	     gpio_init.Pin = _data_pins[0] | _data_pins[1] | _data_pins[2] | _data_pins[3];
    	   else
    	     gpio_init.Pin = _data_pins[0] | _data_pins[1] | _data_pins[2] | _data_pins[3] |
    	                     _data_pins[4] | _data_pins[5] | _data_pins[6] | _data_pins[7];

    	   HAL_GPIO_Init(vPortData, &gpio_init);

    	   // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    	   // according to datasheet, we need at least 40ms after power rises above 2.7V
    	   // so we'll wait 50 just to make sure
    	   HAL_Delay(50);

    	   // Now we pull both RS and R/W low to begin commands
    	   HAL_GPIO_WritePin(vPortCtrlRS, vCtrlRS, GPIO_PIN_RESET);
    	   HAL_GPIO_WritePin(vPortCtrlEN, vCtrlEN, GPIO_PIN_RESET);

    	   if (vCtrlRW != 255) {
    	     HAL_GPIO_WritePin(vPortCtrlRW, vCtrlRW, GPIO_PIN_RESET);
    	   }

    	   //put the LCD into 4 bit or 8 bit mode
    	   if (! (_displayfunction & LCD_8BITMODE)) {
    	     // this is according to the hitachi HD44780 datasheet
    	     // figure 24, pg 46

    	     // we start in 8bit mode, try to set 4 bit mode
    	     write4bits(0x03);
    	     HAL_Delay(5); // wait min 4.1ms

    	     // second try
    	     write4bits(0x03);
    	     HAL_Delay(5); // wait min 4.1ms

    	     // third go!
    	     write4bits(0x03);
    	     HAL_Delay(1);

    	     // finally, set to 4-bit interface
    	     write4bits(0x02);
    	   } else {
    	     // this is according to the hitachi HD44780 datasheet
    	     // page 45 figure 23

    	     // Send function set command sequence
    	     command(LCD_FUNCTIONSET | _displayfunction);
    	     HAL_Delay(5);  // wait more than 4.1ms

    	     // second try
    	     command(LCD_FUNCTIONSET | _displayfunction);
    	     HAL_Delay(1);

    	     // third go
    	     command(LCD_FUNCTIONSET | _displayfunction);
    	   }

    	   // finally, set # lines, font size, etc.
    	   command(LCD_FUNCTIONSET | _displayfunction);

    	   // turn the display on with no cursor or blinking default
    	   _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    	   display();

    	   // clear it off
    	   clear();

    	   // Initialize to default text direction (for romance languages)
    	   _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    	   // set the entry mode
    	   command(LCD_ENTRYMODESET | _displaymode);

    }


 /**

    @brief Sets the row offsets for the LCD.
    @param row0 The offset for row 0.
    @param row1 The offset for row 1.
    @param row2 The offset for row 2.
    @param row3 The offset for row 3.
    @retval None
    */

    void LCD::setRowOffsets(int row0, int row1, int row2, int row3) {
      _row_offsets[0] = row0;
      _row_offsets[1] = row1;
      _row_offsets[2] = row2;
      _row_offsets[3] = row3;
    }

 /**

    @brief Sends a command value to the LCD.
    @param value The command value to be sent.
    @retval None
    */

    inline void LCD::command(uint8_t value) {
      send(value, GPIO_PIN_RESET);
    }

    /**

    @brief Writes a value to the LCD.
    @param value The value to be written.
    @return The number of bytes written.
    */

    inline size_t LCD::write(uint8_t value) {
      send(value, GPIO_PIN_SET);
      return 1; // assume sucess
    }

    /************ low level data pushing commands **********/
    /**

    @brief Sends a command or data value to the LCD.
    @param value The value to be sent.
    @param mode The mode indicating whether it is a command or data (GPIO_PinState).
    @retval None
    */

    // write either command or data, with automatic 4/8-bit selection
    void LCD::send(uint8_t value, GPIO_PinState mode) {
      HAL_GPIO_WritePin(vPortCtrlRS, vCtrlRS, mode);

      // if there is a RW pin indicated, set it low to Write
      if (vCtrlRW != 255) {
        HAL_GPIO_WritePin(vPortCtrlRW, vCtrlRW, GPIO_PIN_RESET);
      }

      if (_displayfunction & LCD_8BITMODE) {
        write8bits(value);
      } else {
        write4bits(value>>4);
        write4bits(value);
      }
    }

    /**

    @brief Generates a pulse on the enable pin of the LCD.
    @retval None
    */

    void LCD::pulseEnable(void) {
      HAL_GPIO_WritePin(vPortCtrlEN, vCtrlEN, GPIO_PIN_RESET);
      HAL_Delay(1);
      HAL_GPIO_WritePin(vPortCtrlEN, vCtrlEN, GPIO_PIN_SET);
      HAL_Delay(1);    // enable pulse must be >450ns
      HAL_GPIO_WritePin(vPortCtrlEN, vCtrlEN, GPIO_PIN_RESET);
      HAL_Delay(1);   // commands need > 37us to settle
    }

    /**

    @brief Writes the lower 4 bits of a value to the LCD.
    @param value The value whose lower 4 bits will be written.
    @retval None
    */

    void LCD::write4bits(uint8_t value) {
      for (int i = 0; i < 4; i++) {
        HAL_GPIO_WritePin(vPortData, _data_pins[i], ((value >> i) & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
      }

      pulseEnable();
    }

    /**

    @brief Writes an 8-bit value to the LCD.
    @param value The 8-bit value to be written.
    @retval None
    */

    void LCD::write8bits(uint8_t value) {
      for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(vPortData, _data_pins[i], ((value >> i) & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
      }

      pulseEnable();
    }


