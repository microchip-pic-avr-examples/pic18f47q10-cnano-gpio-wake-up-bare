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

static void CLK_Initialize(void);
static void PORT_Initialize(void);
static void IOC_Initialize(void);
static void INTERRUPT_Initialize(void);

/* Clock initialization function */
static void CLK_Initialize(void)
{
    /* set HFINTOSC Oscillator */
    OSCCON1bits.NOSC = 6;
    /* set HFFRQ to 1 MHz */
    OSCFRQbits.HFFRQ = 0;
}

/* PORT initialization function */
static void PORT_Initialize(void)
{
    TRISEbits.TRISE0 = 0;   /* Set RE0 pin as output (LED) */
    TRISAbits.TRISA0 = 1;   /* Set RA0 pin as input */
    
    ANSELAbits.ANSELA0 = 0; /* Enable Digital Input buffers for RA0 */
    
    WPUAbits.WPUA0 = 1;     /* Enable weak pull-up for RA0 */
}

/* IOC initialization function */
static void IOC_Initialize(void)
{
    IOCAFbits.IOCAF0 = 0;   /* Clear interrupt flag */
    
    IOCANbits.IOCAN0 = 1;   /* Enable IOC on negative change */
    
    PIE0bits.IOCIE = 1;     /* Enable IOC interrupt */
}

/* Interrupt initialization function */
static void INTERRUPT_Initialize(void)
{
    INTCONbits.GIE = 1;     /* Enable global interrupts */
}

/* IOC0 ISR function */
static void IOC0_ISR (void)
{
    IOCAFbits.IOCAF0 = 0;   /* Clear the interrupt flag */
}

/* Interrupt handler function */
void __interrupt() INTERRUPT_InterruptManager (void)
{
    if(IOCAFbits.IOCAF0)    /* Check the interrupt flag */
    {
        IOC0_ISR();
    }
}

void main(void) 
{
    CLK_Initialize();
    PORT_Initialize();
    IOC_Initialize();
    INTERRUPT_Initialize();
    
    while(1)
    {
        /* Turn the LED on*/
        LATEbits.LATE0 = 0;
        __delay_ms(DELAY_MS);
        /* Turn the LED off*/
        LATEbits.LATE0 = 1;
        
        SLEEP();
    }
}
