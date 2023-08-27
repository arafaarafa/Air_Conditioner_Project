
# Air Conditioner System 

This repository contains the code and documentation for a temperature control system implemented using a microcontroller, LCD display, and buttons. The system allows users to set, adjust, and display temperature values within a specific range.

## System Testing Video
Watch the system testing video : [System Testing Video](https://drive.google.com/file/d/1Sh-qz9QNFMPFvHqkTucbr-UMshyghAHh/view?usp=sharing)

## Description

The temperature control system comprises a microcontroller, LCD display, and buttons. It provides the following functionality:

- Displaying a welcome message and default temperature on startup.
- Setting an initial temperature using buttons.
- Displaying temperature range limits.
- Incrementing and decrementing temperature using buttons.
- Setting a temperature threshold and activating a buzzer if exceeded.
- Returning to the initial temperature setting mode.
- Resetting the temperature to its default value.
- Displaying error messages during certain operations.

## Modules
The temperature control system comprises several modules that work together to achieve its functionality:

- **ATmega32 Microcontroller**: The heart of the system that processes user input, controls the display, manages temperature settings, and triggers the buzzer.

- **LCD Display**: A 16x2 character LCD display that provides visual feedback, showing temperature values, messages, and prompts.

- **Keypad**: A set of buttons that enable user interaction with the system. Button presses are used to set the temperature, adjust values, and trigger specific actions.

- **Buzzer**: An audible alarm that alerts the user when the temperature threshold is exceeded.

- **LM35**: sensor's temperature to the appropriate analog input pin on the microcontroller.

## Usage

1. Clone this repository to your microcontroller development environment.
2. Configure your microcontroller, LCD, and buttons according to the pin mappings in the code.
3. Build and upload the code to your microcontroller.
4. Power on the system.
5. Follow the on-screen instructions and button actions to interact with the system.

## Folder Structure

- `Code/` - Contains the source code files for the Air Conditioner system.
- `Simulation/` - Contains header files.
- `Doc/` - Documentation files and images.
- `README.md` - This file.

## Contributing

Feel free to contribute to this project by creating issues or pull requests. Your input is valuable!

## Author

[Ararfa Arafa Abd Elmawgod]

For questions or support, contact [Mail connection](arafa.prog.98@gmail.com).
