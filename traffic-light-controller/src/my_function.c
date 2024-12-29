#include <stdint.h>
#include "msp.h"

// Global Variables
volatile uint32_t fallingEdges = 0;
const uint8_t GREEN = 0x02;
const uint8_t RED = 0x01;
const uint8_t YELLOW = 0x03;
int32_t timeRemaining = 10;
uint8_t currentColor;

void EdgeCounterInitialization(void) {
    __ASM("CPSID I");
	
    fallingEdges = 0;
    // Configure P1.4 and P1.1 as GPIO with pull-up resistors and falling edge interrupts
    // initializing counter
    P1SEL0 &= ~0x12;
    P1SEL1 &= ~0x12;
    // configuring P1.4 and P1.1 as GPIO
    P1DIR &= ~0x12;
    //  P1.4 and P1.1 in 
    P1REN |= 0x12;
    // enabling pull resistors on P1.4 and P1.1
    P1OUT |= 0x12;
    // P1.4 and P1.1 are pull-up
    P1IES |= 0x12;
    // P1.4 and P1.1 are falling edge event
    P1IFG &= ~0x12;
    // clear flag4 and flag1 
    P1IE |= 0x12;
    // arm interrupt on P1.4 and P1.1
    __ASM("CPSIE I"); // Globally enable interrupts
}

// Interrupt Service Routine for Port 1
void PORT1_IRQHandler(void) {
    fallingEdges++;

    if (P1IFG & 0x02) { // Button on P1.1
        P1IFG &= ~0x02; // Clear interrupt flag
        if (currentColor == GREEN) {
            timeRemaining = 0;
        }
    }

    if (P1IFG & 0x10) { // Button on P1.4
        P1IFG &= ~0x10; // Clear interrupt flag
        if (currentColor == RED) {
            timeRemaining += 2; // Extend red light duration
        }
    }
}

// Delay Function (approximate ms delay)
void delayMs(int ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 900; j++);
    }
}

// Set RGB LED Color
void setColor(uint8_t color) {
    P2OUT &= ~0x07;  // Turn off all LEDs
    P2OUT |= color;  // Turn on selected color
}


void handleGreenState(void) {
    currentColor = GREEN;
    setColor(GREEN);
    timeRemaining = 10;

    while (timeRemaining > 0) {
        delayMs(500); // 500 ms = 0.5 seconds
        timeRemaining--;
    }
}


void handleYellowState(void) {
    currentColor = YELLOW;
    setColor(YELLOW);
    timeRemaining = 5;

    while (timeRemaining > 0) {
        delayMs(100); // 100 ms = 0.1 seconds
        timeRemaining--;
    }
}

// Handle Red State
void handleRedState(void) {
    currentColor = RED;
    setColor(RED);
    timeRemaining = 5;

    while (timeRemaining > 0) {
        delayMs(300); // 300 ms = 0.3 seconds
        timeRemaining--;
    }
}

int main(void) {
    // Initialize Edge Counter and RGB LED GPIO
    EdgeCounterInitialization();
    P2SEL0 &= ~0x07;
    P2SEL1 &= ~0x07;
    P2DS |= 0x07;   // High drive strength
    P2DIR |= 0x07;  // Outputs
    P2OUT &= ~0x07; // Turn off all LEDs

    // Main Loop
    while (1) {
        handleGreenState();
        handleYellowState();
        handleRedState();
    }
}








