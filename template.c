#include "template.h"

void init_gpio(void){
    volatile unsigned long delay_clk;
    SYSCTL_RCGC2 |= 0x30;
    delay_clk = SYSCTL_RCGC2;
    // Unlocking Sw2
    GPIO_PORTF_LOCK = 0x4C4F434B;
    GPIO_PORTF_CR |= 0x1;

    // Set up Port F (SW1 and Leds)
    GPIO_PORTF_DIR |= 0xE;
    GPIO_PORTF_DIR &=~ 0x10;
    GPIO_PORTF_AFSEL &=~ 0xF;
    GPIO_PORTF_AFSEL |= 0x6;
    GPIO_PORTF_PCTL &=~0X00000FF0;
    GPIO_PORTF_PCTL |= 0x00000770;
    GPIO_PORTF_DEN |= 0x1F;
    GPIO_PORTF_PUR |= 0x11;
    GPIO_PORTF_PDR |= 0xE;

    // Set up PE4 as analog input
    GPIO_PORTE_AFSEL |= 0x30;
    GPIO_PORTE_DEN &=~ 0x30;
    GPIO_PORTE_AMSEL |= 0x30;
}

void lock_mcu(void){
    GPIO_PORTF_LOCK = 0x1;
}

void init_adc(void){
    // Instructions for ACD initialization: p.817
    SYSCTL_RCGCADC |= 0x3;
    volatile unsigned long delay_clk;
    delay_clk = SYSCTL_RCGCADC;
    // Disable ASEN0 bit in ACTSS reg
    ADC0_ACTSS &=~ 0xF;
    ADC1_ACTSS &=~ 0xF;
    // set sample rate to 250ksps in ADCPC
    ADC0_PC |= 0x3;
    ADC1_PC |= 0x3;
    // configure trigger event for sample sequencer in ADCEMUX (use continous)
    ADC0_EMUX |= 0xF000;
    ADC1_EMUX |= 0xF000;
    // select ADC input channel (channel 9/PE4) through ADCSSMUX3
    ADC0_SSMUX3 |=0x9;
    // Select ADC input channel (channel 8/pe5) through ADCSSMUX3
    ADC1_SSMUX3 |=0x8;
    // configure sequencer control - disable TS0 & D0
    ADC0_SSCTL3 &=~ 0x9;
    ADC1_SSCTL3 &=~ 0x9;
    // enable IE0 & END0
    ADC0_SSCTL3 |= 0x6;
    ADC1_SSCTL3 |= 0x6;
    //enables SS3 in ADCACTSS
    ADC0_ACTSS |= 0x8;
    ADC1_ACTSS |= 0x8;

}

void init_interrupts(void){
    NVIC_EN0 |= 0x40000000; // Enable PortF interrupts
    NVIC_PRI7 = (NVIC_PRI7 & 0xFF00FFFF) | 0x00A00000; //Port F priority

    GPIO_PORTF_IM |= 0x10; // Enable masking of SW1 bit
    GPIO_PORTF_IS &= ~0x10; //Clear bit to enable edge-detection
    GPIO_PORTF_IBE &= ~0x10; // Clear bit to only detect one edge
    GPIO_PORTF_IEV &= ~0x10; // Clear bit to allow for negative edge sensing

    GPIO_PORTF_ICR |= 0xFF; // Clear interrupts at beginning
}

void init_gptm(void){
    volatile unsigned long delay_clk;
    // Enable Timer0 bit (p. 338/357
    RCGCTIMER |= 0x3;
    delay_clk = RCGCTIMER;

    // Disable timer
    TIMER0_CTL &=~ 0x100;
    TIMER1_CTL &=~ 0x1;
    // Write GPTMCFG w/ 0x4
    TIMER0_CFG |= 0x04;
    TIMER1_CFG |= 0X04;
    //set TnAMS to 0x1,TnCMR to 0x0,TnMR to 0x2
    TIMER0_TBMR |= 0xA;
    TIMER0_TBMR &=~ 0x4;
    TIMER1_TAMR |= 0xA;
    TIMER1_TAMR &=~ 0X4;
    // Configure TnPWML filed on GPTMCTL
    TIMER0_CTL |= 0x4000;
    TIMER1_CTL |= 0x40;
    // Write the prescale value in GPTMTnPR (optional)
    // Enable interrupts TnEVENT field in GPTMCTL (optional)
    // Load Timer start value into GPTMTnILR
    TIMER0_TBILR |= 0xFFF;
    TIMER1_TAILR |= 0xFFF;
    // Load match value into GPTMTnMATCHR
    TIMER0_TBMATCHR = 0xFFE;
    TIMER1_TAMATCHR = 0XFFE;

   //Enable timer through GPTMCTL
    TIMER0_CTL |= 0x100;
    TIMER1_CTL |= 0X1;
}

void init_watchdog(void){
    volatile unsigned long delay_clk;
    SYSCTL_RCGCWD |= 0x1;
    delay_clk = SYSCTL_RCGCWD;
    WATCHDOG0_LOCK = 0x5;
    WATCHDOG0_LOCK = 0x1ACCE551;
    WATCHDOG0_LOAD = 0x00F42400;
    WATCHDOG0_CTL |= 0x2;
    WATCHDOG0_CTL |= 0x1;
}

void change_clk(void){
    SYSCTL_RCC |= 0x1E0000;
}

void red_led_on(void){
    GPIO_PORTF_DATA |= 0x2;
}

void blue_led_on(void){
    GPIO_PORTF_DATA |= 0x4;
}

void green_led_on(void){
    GPIO_PORTF_DATA |= 0x8;
}

void red_led_off(void){
    GPIO_PORTF_DATA &=~ 0x2;
}

void blue_led_off(void){
    GPIO_PORTF_DATA &=~ 0x4;
}

void green_led_off(void){
    GPIO_PORTF_DATA &=~ 0x8;
}

void clear_led(void){
    GPIO_PORTF_DATA &=~ 0xE;
}

int toggle_led(int led_num,int led_on){
    if (led_on == 0){
        switch(led_num){
        case 1:
            red_led_on();
            break;
        case 2:
            blue_led_on();
            break;
        case 3:
            green_led_on();
            break;
        }
        return 1;
    } else {
        switch(led_num){
        case 1:
            red_led_off();
            break;
        case 2:
            blue_led_off();
            break;
        case 3:
            green_led_off();
            break;
        }
        return 0;
    }
}
