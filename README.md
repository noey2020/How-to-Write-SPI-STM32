# How-to-Write-SPI-STM32

SPI, Synchronous Serial Communications       July 20, 2020

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Electronic circuits contain chips which communicate with each other so it can work in 
tandem to accomplish tasks. There was a time when chips only had 4 pins and parallel mode
would completely use up those precious pins so serial was a good idea. Chips have grown 
in size, complexity, and packaging thus giving us more pins. Nevertheless, even with more
pins available, the appetite is insatiable.

By sending bits one at a time, that is called serial. Using a clock signal to synchronize
events is call synchronous. SPI or Serial Peripheral Interface is a classic example of 
synchronous serial communications. It uses 4-wires and can do full-duplex.

The interface was developed by Motorola in 1979 and a de facto standard. Typical
applications include digital cameras, cards, and liquid crystal displays. SPI devices 
communicate in full duplex mode using a master-slave architecture with a single master.

SPI is simple, low power requirement, and supports high throughput. Single master
initiates and controls all communications. An SPI interface consists of four lines:
master-in-slave-out line (MISO), master-out-slave-in line (MOSI), serial clock line
(SCLK), and an active-low slave select line (SS).

i2c, usart, usb, external character lcd hd44780, ST7735r spi graphic lcd, kentec lcd



I included some posts for reference.

https://github.com/noey2020/How-to-Write-Multitasking-STM32

https://github.com/noey2020/How-to-Generate-Triangular-Wave-STM32-DAC

https://github.com/noey2020/How-to-Generate-Sine-Table-LUT

https://github.com/noey2020/How-to-Illustrate-Multiple-Exceptions-

https://github.com/noey2020/How-to-Blink-LED-using-Standard-Peripheral-Library

I appreciate comments. Shoot me an email at noel_s_cruz@yahoo.com!

Hire me!

Have fun and happy coding!
