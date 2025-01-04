Data converter BCD-I2C-platform-4*7 (74HC595)
=

  According to the technical specifications, it is necessary to organize information transfer from the BCD switch through two PCF8574 I2C bus expanders to the Arduino Uno platform, process the information and output it via the SPI interface in dynamic indication mode to the 5461-AS segment indicator.
  The BCD switch has four digits, on each of which you can set a digit from 0 to 9. Information about the set value is output from the switch as a sequence of four bits. 
  Polling of all switch digits is organized through two PCF8574 expanders.
  If we take into account that the first bit in the "true" value corresponds to the decimal number "1", the second "2", the third "4", and the fourth "8", then we can implement a cycle with a condition, upon execution of which each bit of the switch digit will be read and compared. If the bit is "true", then its binary value is summed up into a certain temporary variable corresponding to the current decimal value on the switch digit. In this way, all four BCD digits of the switch can be sequentially processed.
  After receiving the decimal value of the current switch digit, it is necessary to organize a dynamic indication by feeding the first shift register a bit mask with the binary value "0" in place of the current digit and the remaining values ​​"1". Then it is necessary to convert the decimal number to the form of a bit mask corresponding to this number, lit on the anodes of the indicator and transfer it to the second shift register. This algorithm must be carried out with a delay of 1 millisecond, which is necessary for the complete "lighting up" of the indicator diodes.

Circuit components:

-BCD GTF511221

-Arduino platform

-PCF8574*2

-74HC595*2

-LED GNQ-5641AS-21

-Resistor SR1206FR-07220RL*8

![2021-04-03_00h27_16](https://user-images.githubusercontent.com/52381258/153914291-359007f3-c134-4d1f-8ae2-a43b1b2ee6ea.png)
