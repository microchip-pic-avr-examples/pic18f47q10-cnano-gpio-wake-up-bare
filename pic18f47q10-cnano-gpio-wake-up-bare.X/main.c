/**
 * \file main.c
 *
 * \brief Main source file.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.
    Subject to your compliance with these terms, you may use this software and
    any derivatives exclusively with Microchip products. It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

#pragma config WDTE = OFF   /* WDT operating mode->WDT Disabled */
#pragma config LVP = ON     /* Low voltage programming enabled, RE3 pin is MCLR */

#include <xc.h>

#define _XTAL_FREQ  1000000UL
#define DELAY_MS    100

static void CLK_init(void);
static void PORT_init(void);
static void IOC_init(void);
static void INTERRUPT_init(void);

/* Clock initialization function */
static void CLK_init(void)
{
    OSCCON1 = _OSCCON1_NOSC2_MASK 
            | _OSCCON1_NOSC1_MASK;     /* HFINTOSC Oscillator */
    
    OSCFRQ = ~_OSCFREQ_HFFRQ_MASK;     /* Set HFFRQ to 1 MHz */
}

/* PORT initialization function */
static void PORT_init(void)
{
    TRISE   &= ~_TRISE_TRISE0_MASK;         /* Set RE0 pin as output (LED) */
    TRISA   |= _TRISA_TRISA0_MASK;          /* Set RA0 pin as input */
    
    ANSELA  &= ~_ANSELA_ANSELA0_MASK;       /* Enable Digital Input buffers for RA0 */
    
    WPUA    |= _WPUA_WPUA0_MASK;            /* Enable weak pull-up for RA0 */
}

/* IOC initialization function */
static void IOC_init(void)
{
    IOCAF   &= ~_IOCAF_IOCAF0_MASK;         /* Clear interrupt flag */
    
    IOCAN   |= _IOCAN_IOCAN0_MASK;          /* Enable IOC on negative change */
    
    PIE0    |= _PIE0_IOCIE_MASK;            /* Enable IOC interrupt */
}

/* Interrupt initialization function */
static void INTERRUPT_init(void)
{
    INTCON = _INTCON_GIE_MASK;
}

/* IOC0 ISR function */
static void IOC0_ISR (void)
{
    IOCAF &= ~_IOCAF_IOCAF0_MASK;       /* Clear the interrupt flag */
}

/* Interrupt handler function */
void __interrupt() INTERRUPT_InterruptManager (void)
{
    if(IOCAF & _IOCAF_IOCAF0_MASK)          /* Check the interrupt flag */
    {
        IOC0_ISR();
    }
}

void main(void) 
{
    CLK_init();
    PORT_init();
    IOC_init();
    INTERRUPT_init();
    
    while(1)
    {
        /* Turn the LED on*/
        LATE &= ~_LATE_LATE0_MASK;
        __delay_ms(DELAY_MS);
        /* Turn the LED off*/
        LATE |= _LATE_LATE0_MASK;
        
        SLEEP();
    }
}
