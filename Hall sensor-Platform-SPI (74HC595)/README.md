Data converter Hall sensor-Platform-SPI (74HC595)
=

The following modules are specified in the technical specifications: a four-digit seven-segment indicator 5461AS, two output shift registers 74HC595, a KY-024 module with a Hall sensor.

It is necessary to receive an input analog value from the Hall sensor, convert it into a unit of magnetic induction - in Gauss, output the obtained result to a four-digit seven-segment indicator connected to two shift registers using the SPI interface. The device operates in real time.

The principle of operation of the ignition sensor is based on the Hall effect - this is a special case of the Lorentz force, i.e. the effect of a magnetic field on a charged particle. The module with the Hall sensor contains the following components: a trimmer resistor, a two-channel comparator, several matching resistors, a pair of LEDs and, in fact, the Hall sensor SS49E itself. In this case, it will be necessary to display numbers consisting of more than one digit. The output of the value to the four-digit seven-segment indicator is controlled by two shift registers. Thus, using a cascade of shift registers, it is possible to reduce the number of contacts used for the indicator.

Circuit components:

-Hall sensor SS49E *1

-Arduino platform

-74HC595*2

-LED GNQ-5641AS-21 *1

-Resistor SR1206FR-07220RL*8

![image](https://github.com/user-attachments/assets/9ce738c8-a7fa-4328-9e70-65f0a092a64b)
