/*
 * button.c
 *
 *  Created on: Apr 6, 2021
 *      Author: leyla
 */

#include "HAL/Button.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "HAL/LED.h"
#include "HAL/Timer.h"

// Button tap flags - using static volatile for ISR communication
volatile static bool LB1modified;
volatile static bool LB2modified;
volatile static bool BB1modified;
volatile static bool BB2modified;
volatile static bool JSBmodified;

// An internal function that initializes a button and enables the high-to-low
// transition
void initButton(uint_fast8_t selectedPort, uint_fast16_t selectedPins) {
    // This sets up an input with pull-up resistor. If the input does not need the
    // pull-up resistor, the extra added resistor is harmless.
    GPIO_setAsInputPinWithPullUpResistor(selectedPort, selectedPins);

    // clear interrupt on port selectedPort, pin selectedPins
    // If we fail to this, we "might" get an interrupt as soon we enable interrupt
    GPIO_clearInterruptFlag(selectedPort, selectedPins);

    // enable interrupt on port selectedPort, pin selectedPins
    GPIO_enableInterrupt(selectedPort, selectedPins);

    // the interrupt is triggered on high to low transition (tapping)
    GPIO_interruptEdgeSelect(selectedPort, selectedPins,
                             GPIO_HIGH_TO_LOW_TRANSITION);
}

// Button pin definitions - based on Proj2 working configuration
#define LB1_PORT GPIO_PORT_P1
#define LB1_PIN GPIO_PIN1
#define LB2_PORT GPIO_PORT_P1
#define LB2_PIN GPIO_PIN4
#define BB1_PORT GPIO_PORT_P5
#define BB1_PIN GPIO_PIN1
#define BB2_PORT GPIO_PORT_P3
#define BB2_PIN GPIO_PIN5  // Proj2: BOOSTERPACK_S2 = P3.5
#define JSB_PORT GPIO_PORT_P4
#define JSB_PIN GPIO_PIN1  // Proj2: BOOSTERPACK_JS = P4.1

void initButtons() {
    // Initialize all buttons
    initButton(LB1_PORT, LB1_PIN);
    initButton(LB2_PORT, LB2_PIN);
    initButton(BB1_PORT, BB1_PIN);
    initButton(BB2_PORT, BB2_PIN);
    initButton(JSB_PORT, JSB_PIN);

    // Enable interrupts for all ports used
    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableInterrupt(INT_PORT3);
    Interrupt_enableInterrupt(INT_PORT4);
    Interrupt_enableInterrupt(INT_PORT5);

    // Initialize all flags
    LB1modified = false;
    LB2modified = false;
    BB1modified = false;
    BB2modified = false;
    JSBmodified = false;
}

// PORT1 interrupt handler for LB1 and LB2
void PORT1_IRQHandler() {
    if (GPIO_getInterruptStatus(LB1_PORT, LB1_PIN)) {
        LB1modified = true;
        GPIO_clearInterruptFlag(LB1_PORT, LB1_PIN);
    }
    if (GPIO_getInterruptStatus(LB2_PORT, LB2_PIN)) {
        LB2modified = true;
        GPIO_clearInterruptFlag(LB2_PORT, LB2_PIN);
    }
}

// PORT3 interrupt handler for BB2
void PORT3_IRQHandler() {
    if (GPIO_getInterruptStatus(BB2_PORT, BB2_PIN)) {
        BB2modified = true;
        GPIO_clearInterruptFlag(BB2_PORT, BB2_PIN);
    }
}

// PORT4 interrupt handler for JSB
void PORT4_IRQHandler() {
    if (GPIO_getInterruptStatus(JSB_PORT, JSB_PIN)) {
        JSBmodified = true;
        GPIO_clearInterruptFlag(JSB_PORT, JSB_PIN);
    }
}

// PORT5 interrupt handler for BB1
void PORT5_IRQHandler() {
    if (GPIO_getInterruptStatus(BB1_PORT, BB1_PIN)) {
        BB1modified = true;
        GPIO_clearInterruptFlag(BB1_PORT, BB1_PIN);
    }
}

// Button tapped functions
bool LB1tapped() {
    bool tapped = LB1modified;
    LB1modified = false;
    return tapped;
}

bool LB2tapped() {
    bool tapped = LB2modified;
    LB2modified = false;
    return tapped;
}

bool BB1tapped() {
    bool tapped = BB1modified;
    BB1modified = false;
    return tapped;
}

bool BB2tapped() {
    bool tapped = BB2modified;
    BB2modified = false;
    return tapped;
}

bool JSBtapped() {
    bool tapped = JSBmodified;
    JSBmodified = false;
    return tapped;
}


// This function calls all the functions that check button status and stores
// them in one structure This will allow the user to reliably get the latest
// button status. If we choose not to use this method, the user has to be
// careful to call JSBtapped() or any similar function only once in the main
// loop.
buttons_t updateButtons() {
    buttons_t buttons;
    buttons.LB1tapped = LB1tapped();
    buttons.LB2tapped = LB2tapped();
    buttons.BB1tapped = BB1tapped();
    buttons.BB2tapped = BB2tapped();
    buttons.JSBtapped = JSBtapped();
    return (buttons);
}
