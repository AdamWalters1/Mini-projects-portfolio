/*
 * Timer.c
 *
 *  Created on: Dec 29, 2019
 *      Author: Matthew Zhong
 */

#include <HAL/LED.h>
#include <HAL/Timer.h>
#include <stdbool.h>

// System time counter in milliseconds
volatile static uint32_t system_time_ms = 0;

// Timer flags
volatile static bool timer1_expired = false;
volatile static bool timer2_expired = false;

/**
 * Initializes the global system timing. This function should be called
 * immediately after the Watchdog timer is reset, so that the system clock is
 * set appropriately.
 *
 * To change the system clock to different frequencies, use the #define on the
 * SYSTEM_CLOCK in Timer.h. DO NOT MODIFY THIS FUNCTION UNLESS YOU KNOW WHAT YOU
 * ARE DOING. You can potentially brick your board, which requires a factory
 * reset to fix.
 */
void InitSystemTiming() {
    // Before initializing anything else, disable all interrupts
    Interrupt_disableMaster();

    // Before changing the clock frequency, we need to change the flash control to
    // use 2 wait states (2 delayed cycles per flash read). IF YOU DO NOT CHANGE
    // YOUR FLASH CONTROL BEFORE CALLING CS_setDCOFrequency(), YOU WILL BRICK YOUR
    // BOARD AND WILL NEED TO PERFORM A FACTORY RESET.
    //
    // The reason why we need to change the Flash Control settings is because
    // although calling CS_setDCOFrequency() may change the system clock frequency
    // itself, the flash memory has NOT been configured for instruction fetches at
    // a higher frequency. Omitting these two lines WILL cause your board to
    // attempt to fetch instructions before flash memory has properly fetched
    // them, meaning your board will begin to read garbage instructions and will
    // no longer be flashable without a factory reset.
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);

    // Set the system clock frequency to user-specified frequency
    CS_setDCOFrequency(SYSTEM_CLOCK);

    // After DCO is set, configure all other clock signals to use a source from
    // DCO. DO NOT CHANGE THIS
    CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
    CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_2); // TODO: Calculate new frequency for SMCLK
    CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);


    Timer32_initModule(TIMER32_0_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);
    
    // Initialize Timer32_1 for periodic 1ms interrupts (system time)
    Timer32_initModule(TIMER32_1_BASE, TIMER32_PRESCALER_1, TIMER32_32BIT,
                       TIMER32_PERIODIC_MODE);
    
    // Clear interrupts before enabling
    Timer32_clearInterruptFlag(TIMER32_0_BASE);
    Timer32_clearInterruptFlag(TIMER32_1_BASE);
    
    // Enable interrupts on the timers
    Timer32_enableInterrupt(TIMER32_0_BASE);
    Timer32_enableInterrupt(TIMER32_1_BASE);
    
    // Enable NVIC for Timer32 interrupts
    Interrupt_enableInterrupt(INT_T32_INT1);
    Interrupt_enableInterrupt(INT_T32_INT2);

    // Enable interrupts again, after all system timing has been set up properly
    Interrupt_enableMaster();
    
    // Start Timer32_1 for system time (1ms period)
    Timer32_setCount(TIMER32_1_BASE, CLOCK_CYCLES_IN_MS);
    Timer32_startTimer(TIMER32_1_BASE, false);
}

// Timer32_0 ISR - for hardware timer 1 expiration
void T32_INT1_IRQHandler() {
    Timer32_clearInterruptFlag(TIMER32_0_BASE);
    timer1_expired = true;
}

// Timer32_1 ISR - increments system time every millisecond
// Timer32_1 is used for system time tracking with 1ms period
void T32_INT2_IRQHandler() {
    Timer32_clearInterruptFlag(TIMER32_1_BASE);
    system_time_ms++;
    
    // Timer32 in periodic mode automatically reloads and continues
    // The timer will automatically reload the count value and continue
}

void StartHWTimer1(uint32_t waitTime_ms) {
    timer1_expired = false;
    uint32_t count = CLOCK_CYCLES_IN_MS * waitTime_ms;
    Timer32_setCount(TIMER32_0_BASE, count);
    Timer32_startTimer(TIMER32_0_BASE, false);
}

void StartHWTimer2(uint32_t waitTime_ms) {
    timer2_expired = false;
    // Timer32_1 is used for system time, so we could use a different timer if needed
    // For now, timer2 is not implemented
}

bool HWTimer1Expired() {
    bool expired = timer1_expired;
    if (expired) {
        timer1_expired = false;
    }
    return expired;
}

bool HWTimer2Expired() {
    bool expired = timer2_expired;
    if (expired) {
        timer2_expired = false;
    }
    return expired;
}

// Get current system time in milliseconds
uint32_t GetSystemTimeMs() {
    return system_time_ms;
}
