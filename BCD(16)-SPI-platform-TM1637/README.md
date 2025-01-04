Data converter BCD(16)-SPI-Platform-TM1637
=

According to the technical specifications for the course project, it is necessary to organize the transfer of information from the BCD switch to the Arduino Uno platform, process the information and output the current hexadecimal values ​​​​set on the switch via the I2C interface in the dynamic indication mode to a seven-segment indicator based on the TM1637 driver.
The BCD switch has three digits, on each of which you can set a hexadecimal value (a number from 0 to 9 or a letter from A to F). Information about the set value is output from the switch as a sequence of four bits.

Polling of all switch bits is organized through two 74HC165 shift registers. If we consider that the first bit in the "true" value corresponds to the decimal number "1", the second "2", the third "4", and the fourth "8", then we can implement a cycle with a condition, upon execution of which each bit of the switch bit will be read and compared. If the bit is "true", then its binary value is summed up into a temporary variable corresponding to the current hexadecimal value on the switch bit. In this way, all three BCD bits of the switch can be processed sequentially.

Circuit components:

-BCD(16) Switch PP10-3MV OYu0.360.061TU

-Arduino platform

-74HC165*2

-LED 7-segment I2C TM1637

![image](https://github.com/user-attachments/assets/468d5162-22ec-4bfc-977f-475af3fa3e08)
