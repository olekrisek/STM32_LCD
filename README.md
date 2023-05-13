# LCD Library for STM32 Microcontrollers

This library provides a high-level interface for driving LCD text displays using STM32 microcontrollers. It is based on the existing C code from the LiquidCrystal library, with additional features and modifications specific to STM32 microcontrollers.

This library is based on the works found in the [STM32LiquidCrystal](https://github.com/SayidHosseini/STM32LiquidCrystal) repository. We would like to acknowledge and express our gratitude to the original author for their contributions and inspiration.

The code is tested on a STM32L552 controller on a NUKLEO-STM32L552 board. 

## Features

- Supports multiple ports for digital lines, allowing flexible pin assignment for data and control signals.
- Supports multiple LCD displays connected to the same microcontroller.
- changed the "print" override, to make it possible to direct output to selected display. 
- Both C++ class code, and a C-compatible wrapper implementation to allow calls both from C++ source and C source. 
- a printFormatted method to use for printf style printing, accepting the same parameters as printf. 

## Usage

1. Include the necessary library files (`lcd.hpp` and `lcd.cpp`, `LCD_wrapper.cpp`, `LCD_wrapper.h` ) in your STM32 project. The wrapper files is only neccessary for "C" projects, in addition to the lcd.cpp and lcd.hpp. for C++ projectes, it's only neccessarey with the lcd.cpp and lcd.hpp files. 

2. Initialize the LCD display using the appropriate constructor, providing the GPIO port references for data and control signals.

3. Use the available methods to interact with the LCD display, such as writing text, setting the cursor position, creating custom characters, and controlling display settings.

4. Build and flash your STM32 project, ensuring that the LCD library is properly linked.
5. Detailed doc is found in the project's Doc/html folder. Gen from Doxygen. 

## Example for C++ project

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

    // Print another message, printf style parameters...
    lcd.printFormatted("The answer is: %d", 42);

    while (1) {
        // Your main program logic here
    }
}
```
## Example for C project
```c
#include "LCD_wrapper.h"

// GPIO port references - those are usually located in main.h when using STM32CubeMX. 
#define DSP_D4_Pin GPIO_PIN_8
#define DSP_D4_GPIO_Port GPIOC
#define DSP_D5_Pin GPIO_PIN_9
#define DSP_D6_Pin GPIO_PIN_10
#define DSP_D7_Pin GPIO_PIN_11
#define DSP_RS_Pin GPIO_PIN_3
#define DSP_RS_GPIO_Port GPIOF
#define DSP_EN_Pin GPIO_PIN_12
#define DSP_EN_GPIO_Port GPIOC
#define DSP_RW_Pin GPIO_PIN_2
#define DSP_RW_GPIO_Port GPIOD

int main() {
    // Create an instance of the LCD class
    LCD *lcd;
    lcd = LCD_create(DSP_D4_GPIO_Port, DSP_RW_GPIO_Port, DSP_EN_GPIO_Port, DSP_RS_GPIO_Port);
 
    // Initialize the LCD control and data pins
    LCD_initCtrlPins(lcd, DSP_RW_Pin, DSP_EN_Pin, DSP_RS_Pin);
    LCD_initDataPins(lcd, DSP_D4_Pin,  DSP_D5_Pin, DSP_D6_Pin, DSP_D7_Pin);

    // Set up the LCD display parameters
    LCD_Begin(lcd, 20, 4); // 20 columns and 4 lines. 
     
    // Print a message on the LCD
    LCD_print( lcd, "Hello World !");
     
    // Set the cursor position
    LCD_setCursor( lcd, 0, 2);
     
    // Print another message as formatted text
    LCD_printFormatted(lcd, "The answer is: %d", 42);

    while (1) {
        // Your main program logic here
    }
}
```
## Notes 

The C++ constructor or LCD_Create method accepts four port parameters: data port, RW port, EN port, and RS port. These ports can either be the same for all or different from each other. This change was made to enhance flexibility, considering that the microcontroller has numerous peripherals reserved for specific ports. By allowing different ports, it becomes easier to connect the display without disabling other essential peripherals. Finding seven IO pins on a single port without disabling other peripherals can be challenging. Moreover, when utilizing a NUKLEO board, it is preferable to have the LCD pins positioned close to each other on the board connectors, facilitating the connection process.

Furthermore, this library enables the connection of multiple displays to the same microcontroller. You can create and initialize two LCD objects, configuring each of them separately. Assign the names "lcd1" and "lcd2" to the objects, enabling independent printing on both displays.

![IMG_2835](https://github.com/olekrisek/STM32_LCD/assets/3278226/85caf874-7ccc-4aae-9915-3bd373223f9e)
