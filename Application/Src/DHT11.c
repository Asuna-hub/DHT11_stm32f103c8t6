#include "DHT11.h"

uint8_t temp = 0;
uint8_t hum = 0;

void DHT11_SetOutput(void){
    GPIOB->CRH |= GPIO_CRH_MODE9;
    GPIOB->CRH &= ~GPIO_CRH_CNF9;
    GPIOB->CRH |= GPIO_CRH_CNF9_0;
}

void DHT11_SetInput(void){
    GPIOB->CRH &= ~GPIO_CRH_MODE9;
    GPIOB->CRH &= ~GPIO_CRH_CNF9;
    GPIOB->CRH |= GPIO_CRH_CNF9_1;
    GPIOB->BSRR = GPIO_BSRR_BS9;
}

void DHT11_Start(void){
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    DHT11_SetOutput();
    GPIOB->BSRR = GPIO_BSRR_BR9;
    delay_ms(18);
    GPIOB->BSRR = GPIO_BSRR_BS9;
    delay_us(30);
    DHT11_SetInput();
}

uint8_t DHT11_Read(uint8_t *temp, uint8_t *hum){
    uint8_t data[5] = {0};

    DHT11_Start();

    uint32_t timeout = 10000;
    while (GPIOB->IDR & GPIO_IDR_IDR9)    if (!timeout--) return 0;
    while (!(GPIOB->IDR & GPIO_IDR_IDR9)) if (!timeout--) return 0;
    while (GPIOB->IDR & GPIO_IDR_IDR9)    if (!timeout--) return 0;

    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 8; j++){
            timeout = 10000;
            while (!(GPIOB->IDR & GPIO_IDR_IDR9)) if (!timeout--) return 0;
            delay_us(40);
            if (GPIOB->IDR & GPIO_IDR_IDR9)
                data[i] |= (1 << (7 - j));
            timeout = 10000;
            while (GPIOB->IDR & GPIO_IDR_IDR9) if (!timeout--) return 0;
        }
    }
    if (data[4] != (uint8_t)(data[0] + data[1] + data[2] + data[3]))
        return 0;

    *hum = data[0];
    *temp = data[2];
    return 1;
}