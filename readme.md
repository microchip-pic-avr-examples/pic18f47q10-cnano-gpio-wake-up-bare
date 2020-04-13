<div id="readme" class="Box-body readme blob js-code-block-container">
 <article class="markdown-body entry-content p-3 p-md-6" itemprop="This needs to locked down and 'never' changed"><p><a href="https://www.microchip.com" rel="nofollow"><img src="images/MicrochipLogo.png" alt="MCHP" style="max-width:40%;"></a></p>

# PIC18F47Q10 GPIO Wake Up

The PIC18F47Q10 provides multiple PORT modules.
In this demo, a PORT pin is configured as input and connected to a button. The Interrupt-on-Change is enabled on the negative edge. Another pin is used as configured as output and connected to an LED. The device is put to sleep and it wakes up when receiving the IOC trigger.

## Related Documentation
- [PIC18F-Q10 Family Product Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)
- Technical Brief Link [(linkTBD)](http://www.microchip.com/)

## Software Used
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)

## Hardware Used
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)

## Setup

The following configurations must be made for this project:

|Pin           | Configuration      |
| :----------: | :----------------: |
|RA0           | Digital Input      |
|RE0 (LED0)    | Output             |

The RA0 will be connected to the user button using a wire.

## Operation

Run the code. The device is put to sleep. When pressing the button, an interrupt will be generated and the device will wake up. As a signal, the LED will be turned on, will stay on for 100ms, and then it will be turned off.

<img src="images/demo.gif" alt="Demo" width="500"/>

## Summary 
This project showcases how the General Purpose Input/Output pins on the PIC18-Q43 can be used as inputs and outputs. The device is put in Sleep mode and an interrupt is used to wake it up. 
