/*
 * Buzzer.h
 *
 *  Created on: Nov 12, 2025
 *      Author: Richard Harrison
 */

#ifndef HAL_BUZZER_H_
#define HAL_BUZZER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include "HAL/pitches.h"

// Buzzer hardware configuration - based on working HW11 P3 implementation
#define BUZZER_PORT                 GPIO_PORT_P2
#define BUZZER_PIN                  GPIO_PIN7  // Changed from P2.4 to P2.7
#define BUZZER_TIMER_BASE           TIMER_A0_BASE
#define BUZZER_TIMER_COMPARE_REG    TIMER_A_CAPTURECOMPARE_REGISTER_4  // Changed from CCR1 to CCR4

// PWM configuration - matches working HW11 P3 implementation
#define PWM_CLKSOURCE               TIMER_A_CLOCKSOURCE_SMCLK
#define PWM_CLKSOURCE_DIVIDER       TIMER_A_CLOCKSOURCE_DIVIDER_24  // Changed from divider 1 to 24
#define PWM_COMPARE_OUTPUT_MODE     TIMER_A_OUTPUTMODE_SET_RESET  // Changed from TOGGLE_RESET
#define PWM_DUTY_CYCLE              0.5

typedef struct {
    float frequency_hz;
    uint32_t duration_ms;
    float duty_cycle;

    uint16_t period_counts;
    uint16_t compare_counts;
} note_t;

note_t Note_Construct(float frequency_hz, uint32_t duration_ms, float duty_cycle);

void Buzzer_Init();

void Buzzer_Play(note_t* note);

void Buzzer_Stop();

#endif /* HAL_BUZZER_H_ */
