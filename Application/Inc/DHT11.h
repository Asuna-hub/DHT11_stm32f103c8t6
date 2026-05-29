#ifndef DHT11_H
#define DHT11_H

#include "main.h"

extern uint8_t temp, hum;

void DHT11_SetOutput(void);
void DHT11_SetInput(void);
void DHT11_Start(void);
uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum);

#endif