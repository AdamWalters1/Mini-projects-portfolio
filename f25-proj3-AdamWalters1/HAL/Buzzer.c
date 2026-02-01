/*
 * Buzzer.c
 *
 *  Created on: Nov 12, 2025
 *      Author: Richard Harrison
 */

#include "HAL/Buzzer.h"
#include "HAL/Timer.h"

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <stdbool.h>

// Clock source for PWM - matches HW11 P3 implementation approach
// Our system: SYSTEM_CLOCK = 48MHz, SMCLK = 48MHz / 2 = 24MHz
// Effective clock = SMCLK / divider = 24MHz / 24 = 1,000,000 Hz
// Note: HW11 uses 3MHz system clock, but approach is the same
#define PWM_CLOCK_DIVIDER      24  // Matches HW11 P3 divider
// We calculate effective frequency dynamically based on actual SMCLK
// For calculation purposes, assuming SMCLK = 24MHz (our actual config)
// Actual TimerA will use whatever SMCLK is configured in Timer.c
#define PWM_EFFECTIVE_FREQ_HZ  1000000  // 24MHz / 24 = 1MHz (for our system)

// Duration timer flag
volatile static bool buzzer_duration_expired = false;

note_t Note_Construct(float frequency_hz, uint32_t duration_ms, float duty_cycle)
{
    note_t note;
    
    // Set basic values
    note.frequency_hz = frequency_hz;
    note.duration_ms = duration_ms;
    note.duty_cycle = duty_cycle;
    
    // Calculate period and compare counts for PWM
    // Based on HW11 P3: period = effective_clock / frequency
    float effective_clock = (float)PWM_EFFECTIVE_FREQ_HZ;
    float period = effective_clock / frequency_hz;
    note.period_counts = (uint16_t)period;
    
    // For SET_RESET mode, duty cycle determines the compare value
    // OFF cycles = (1 - duty_cycle) * period
    // Compare value should be the OFF cycles to achieve desired duty cycle
    note.compare_counts = (uint16_t)(period * (1.0f - duty_cycle));
    
    return note;
}

void Buzzer_Init()
{
    // Configure buzzer pin - initialize as output first, then set as peripheral

    GPIO_setAsOutputPin(BUZZER_PORT, BUZZER_PIN);
    GPIO_setOutputLowOnPin(BUZZER_PORT, BUZZER_PIN);
    
    // Configure buzzer pin as TimerA output
    GPIO_setAsPeripheralModuleFunctionOutputPin(BUZZER_PORT, BUZZER_PIN,
                                                 GPIO_PRIMARY_MODULE_FUNCTION);
    
    // TimerA configuration happens in Buzzer_Play()
}

void Buzzer_Play(note_t* note)
{
    // Configure TimerA for PWM generation
    Timer_A_PWMConfig pwmConfig;
    pwmConfig.clockSource = PWM_CLKSOURCE;
    pwmConfig.clockSourceDivider = PWM_CLKSOURCE_DIVIDER;
    pwmConfig.timerPeriod = note->period_counts;
    pwmConfig.compareRegister = BUZZER_TIMER_COMPARE_REG;
    pwmConfig.compareOutputMode = PWM_COMPARE_OUTPUT_MODE;
    pwmConfig.dutyCycle = note->compare_counts;
    
    // Generate PWM on TimerA
    Timer_A_generatePWM(BUZZER_TIMER_BASE, &pwmConfig);
    
    // Set up duration timer (using Timer32_0)
    buzzer_duration_expired = false;
    StartHWTimer1(note->duration_ms);
}

void Buzzer_Stop()
{

    Timer_A_stopTimer(BUZZER_TIMER_BASE);
}
