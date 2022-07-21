#include "template.h"
#include "Systick_16.h"

int sw1,sw2,green_led = 0;

void PortFHandler(void){
    sw1++;
    GPIO_PORTF_ICR |= 0xFF;
}

int main(void)
{
    init_gpio();
    init_adc();
    init_interrupts();
    init_gptm();
    SysTick_Init();
    init_watchdog();
    lock_mcu();

    while(1){
        if (sw1){
            green_led = toggle_led(3,green_led);
            sw1 = 0;
        }

        if(GPIO_PORTF_DATA & 0x1) WATCHDOG0_LOAD = 0x00F42400;;


        if (ADC0_SSFIFO3 > 0xDDD || ADC0_SSFIFO3 <0xB00)
            TIMER0_TBMATCHR = 0xFFE;
        else if (ADC0_SSFIFO3 > 0xE00 || ADC0_SSFIFO3 <0xA00)
            TIMER0_TBMATCHR = 0xAAA;
        else if (ADC0_SSFIFO3 > 0xF00 || ADC0_SSFIFO3 <0x900)
            TIMER0_TBMATCHR = 0x555;
        else
            TIMER0_TBMATCHR = 0x000;

        if (ADC1_SSFIFO3 > 0xDFF || ADC1_SSFIFO3 <0xA90)
            TIMER1_TAMATCHR = 0xFFE;
        else if (ADC1_SSFIFO3 > 0xE00 || ADC1_SSFIFO3 <0xA00)
            TIMER1_TAMATCHR = 0xAAA;
        else if (ADC1_SSFIFO3 > 0xF00 || ADC1_SSFIFO3 <0x900)
            TIMER1_TAMATCHR = 0x555;
        else
            TIMER1_TAMATCHR = 0x000;
    }
}
