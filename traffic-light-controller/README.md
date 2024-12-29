# MSP432 Traffic Light Controller

This project controls a traffic light simulation using RGB LEDs on the MSP432 microcontroller. It uses GPIO for LED control and interrupts for button inputs.

## Features
- **LED States**: Green (10s), Yellow (5s), Red (5s).
- **Button 1 (P1.1)**: Skip the green light.
- **Button 2 (P1.4)**: Extend the red light by 2 seconds.
- **Interrupts**: Used for button presses to adjust the light timings.

## Key Components

### GPIO Configuration
- **Buttons**:
  - **P1.1** and **P1.4** are configured as inputs with pull-up resistors.
  - Falling edge detection is enabled for both buttons.

- **RGB LEDs**:
  - **P2.0 (Red)**, **P2.1 (Green)**, and **P2.2 (Yellow)** are configured as outputs to control the RGB LEDs.

### Interrupt Service Routine (ISR)
- The **PORT1_IRQHandler()** function handles button press interrupts.
  - Modifies the LED state based on the button pressed.
  - Updates the falling edge counter (`fallingEdges`) when a button is pressed.

## Setup
1. Connect the RGB LED to pins **P2.0**, **P2.1**, and **P2.2**.
2. Connect the buttons to pins **P1.1** and **P1.4** with pull-up resistors.

## Code Overview
- **EdgeCounterInitialization()**: Configures GPIO and sets up interrupts for buttons.
- **PORT1_IRQHandler()**: Handles button presses to modify light timing and updates the falling edge counter.
- **setColor(color)**: Sets the RGB LED color based on the current state.
- **handleGreenState()**, **handleYellowState()**, **handleRedState()**: Controls the timing and transition for each light state.
- **delayMs(ms)**: Provides a software-based delay for controlling the state duration.

## Notes
- Timing in `delayMs()` is approximate and may vary depending on the system clock.
- Ensure proper pull-up resistors are used for button inputs to avoid floating pin issues.

## License
This project is for educational use.

