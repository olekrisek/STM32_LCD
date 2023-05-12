# LCD Library for STM32 Microcontrollers

This library provides a high-level interface for driving LCD text displays using STM32 microcontrollers. It is based on the existing C code from the LiquidCrystal library, with additional features and modifications specific to STM32 microcontrollers.

## Features

- Supports multiple ports for digital lines, allowing flexible pin assignment for data and control signals.
- Supports multiple LCD displays connected to the same microcontroller.
- changed the "print" override, to make it possible to direct output to selected display. 
- Both C++ class code, and a C-compatible wrapper implementation to allow calls both from C++ source and C source. 

## Usage

1. Include the necessary library files (`lcd.hpp` and `lcd.cpp`, `LCD_wrapper.cpp`, `LCD_wrapper.h` ) in your STM32 project.

2. Initialize the LCD display using the appropriate constructor, providing the GPIO port references for data and control signals.

3. Use the available methods to interact with the LCD display, such as writing text, setting the cursor position, creating custom characters, and controlling display settings.

4. Build and flash your STM32 project, ensuring that the LCD library is properly linked.

## Example

```cpp
#include "lcd.hpp"

// GPIO port references
GPIO_TypeDef* portData = GPIOA;
GPIO_TypeDef* portCtrlRW = GPIOB;
GPIO_TypeDef* portCtrlEN = GPIOC;
GPIO_TypeDef* portCtrlRS = GPIOD;

int main() {
    // Create an instance of the LCD class
    LCD lcd(portData, portCtrlRW, portCtrlEN, portCtrlRS);

    // Initialize the LCD control and data pins
    lcd.initCtrlPins(0, 1, 2); // Example pin numbers
    lcd.initDataPins(3, 4, 5, 6); // Example pin numbers

    // Set up the LCD display parameters
    lcd.Begin(16, 2); // 16 columns, 2 rows

    // Print a message on the LCD
    lcd.printLCD("Hello, World!");

    // Set the cursor position
    lcd.setCursor(0, 1); // Second row, first column

    // Print another message
    lcd.printLCD("LCD Library");

    while (1) {
        // Your main program logic here
    }
}
