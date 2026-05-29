#include "main.h"


int main(void)
{
    rcc_init();
    SysTick_Init();
    while (1)
    {
        if (DHT11_Read(&temp, &hum)){}
        delay_s(2);
    }
}
