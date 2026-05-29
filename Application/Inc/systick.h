#ifndef SYSTICK_H
#define SYSTICK_H

#include "main.h"

#define SYSCLOCK 72000000

void SysTick_Init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);
void delay_s(uint32_t s);

#endif