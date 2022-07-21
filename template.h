#ifndef TEMPLATE_H

#define TEMPLATE_H

#define SYSCTL_RCC            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCGC2          (*((volatile unsigned long *)0x400FE108)) //p.464
//Port E
#define GPIO_PORTE_DATA       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_AFSEL      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL      (*((volatile unsigned long *)0x40024528))

//Port F
#define GPIO_PORTF_DATA    (*((volatile unsigned long *)0x400253FC)) // p.662
#define GPIO_PORTF_DIR     (*((volatile unsigned long *)0x40025400)) // p.663
#define GPIO_PORTF_AFSEL   (*((volatile unsigned long *)0x40025420)) // p.671
#define GPIO_PORTF_DEN     (*((volatile unsigned long *)0x4002551C)) // p.682
#define GPIO_PORTF_PUR     (*((volatile unsigned long *)0x40025510)) // p.677
#define GPIO_PORTF_PDR        (*((volatile unsigned long *)0x40025514))
#define GPIO_PORTF_PCTL       (*((volatile unsigned long *)0x4002552C))
// Unlocking SW2
#define GPIO_PORTF_LOCK     (*((volatile unsigned long *)0x40025520)) // p.684
#define GPIO_PORTF_CR       (*((volatile unsigned long *)0x40025524)) //p.685
// Port F Interrupts
#define GPIO_PORTF_IM         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_MIS        (*((volatile unsigned long *)0x40025418))
#define GPIO_PORTF_ICR        (*((volatile unsigned long *)0x4002541C))
#define GPIO_PORTF_IS         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV        (*((volatile unsigned long *)0x4002540C))

// Timer0
#define RCGCTIMER                  (*((volatile unsigned long *)0x400FE604)) //GPTMT Run mode clock gating control
#define TIMER0_CTL             (*((volatile unsigned long *)0x4003000C)) //GPTM Control
#define TIMER0_CFG             (*((volatile unsigned long *)0x40030000)) //GPTM Configuration
#define TIMER0_TBMR           (*((volatile unsigned long *)0x40030008))
#define TIMER0_TBILR          (*((volatile unsigned long *)0x4003002C))
#define TIMER0_TBMATCHR       (*((volatile unsigned long *)0x40030034))
#define TIMER0_TBPR           (*((volatile unsigned long *)0x4003003C))
#define TIMER0_TBV            (*((volatile unsigned long *)0x40030054))
// Timer1
#define TIMER1_CTL            (*((volatile unsigned long *)0x4003100C))
#define TIMER1_CFG            (*((volatile unsigned long *)0x40031000))
#define TIMER1_TAMR           (*((volatile unsigned long *)0x40031004))
#define TIMER1_TAILR          (*((volatile unsigned long *)0x40031028))
#define TIMER1_TAMATCHR       (*((volatile unsigned long *)0x40031030))
#define TIMER1_TAPR           (*((volatile unsigned long *)0x40031038))
#define TIMER1_TAV            (*((volatile unsigned long *)0x40031050))

// WD Timer 0
#define SYSCTL_RCGCWD         (*((volatile unsigned long *)0x400FE600))
#define WATCHDOG0_LOAD        (*((volatile unsigned long *)0x40000000))
#define WATCHDOG0_CTL         (*((volatile unsigned long *)0x40000008))
#define WATCHDOG0_LOCK        (*((volatile unsigned long *)0x40000C00))

// ADC0
#define SYSCTL_RCGCADC        (*((volatile unsigned long *)0x400FE638))
#define ADC0_PC               (*((volatile unsigned long *)0x40038FC4))
#define ADC0_ACTSS            (*((volatile unsigned long *)0x40038000))
#define ADC0_EMUX             (*((volatile unsigned long *)0x40038014))
#define ADC0_SSMUX3           (*((volatile unsigned long *)0x400380A0))
#define ADC0_SSCTL3           (*((volatile unsigned long *)0x400380A4))
#define ADC0_PSSI             (*((volatile unsigned long *)0x40038028))
#define ADC0_SSPRI            (*((volatile unsigned long *)0x40038020))
// ADC0 Output
#define ADC0_SSFIFO3          (*((volatile unsigned long *)0x400380A8))
#define ADC0_RIS              (*((volatile unsigned long *)0x40038004))
#define ADC0_ISC              (*((volatile unsigned long *)0x4003800C))

// ADC1
#define ADC1_PC               (*((volatile unsigned long *)0x40039FC4))
#define ADC1_ACTSS            (*((volatile unsigned long *)0x40039000))
#define ADC1_EMUX             (*((volatile unsigned long *)0x40039014))
#define ADC1_SSMUX3           (*((volatile unsigned long *)0x400390A0))
#define ADC1_SSCTL3           (*((volatile unsigned long *)0x400390A4))
#define ADC1_PSSI             (*((volatile unsigned long *)0x40039028))
#define ADC1_SSPRI            (*((volatile unsigned long *)0x40039020))
// ADC1 Output
#define ADC1_SSFIFO3          (*((volatile unsigned long *)0x400390A8))
#define ADC1_RIS              (*((volatile unsigned long *)0x40039004))
#define ADC1_ISC              (*((volatile unsigned long *)0x4003900C))

/* Interrupts Definitions */
#define NVIC_EN0                   (*((volatile unsigned long *)0xE000E100)) // NVIC Enable 0
#define NVIC_PRI7                  (*((volatile unsigned long *)0xE000E41C))

void change_clk(void);
void init_gpio(void);
void init_gptm(void);
void init_watchdog(void);
void init_adc(void);
void init_interrupts(void);
void lock_mcu (void);
void red_led_on(void);
void blue_led_on(void);
void green_led_on(void);
void clear_led(void);
void red_led_off(void);
void blue_led_off(void);
void green_led_off(void);
int toggle_led(int led_num,int led_on);




#endif
