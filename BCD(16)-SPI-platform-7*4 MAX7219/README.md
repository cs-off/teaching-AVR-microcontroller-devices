Data converter BCD(16)-SPI-platform-7*4 MAX7219
=

According to the technical specifications, it is necessary to organize the transfer of information from the BCD switch to the Arduino Uno platform, process the information and output the current hexadecimal values ​​​​set on the switch via the SPI interface in the dynamic indication mode to the seven-segment indicator based on the MAX7219 driver.
The BCD switch has three digits, on each of which you can set a hexadecimal value (a number from 0 to 9 or a letter from A to F). Information about the set value is output from the switch as a sequence of four bits. Polling of all switch bits is organized through two 74HC165 shift registers.

Circuit components:

-BCD(16) PP10-3MV OYu0.360.061TU

-Arduino platform

-74HC165*2

-LED GNQ-5641AS-21

-MAX7219 *1

![image](https://github.com/user-attachments/assets/dc7ae951-88be-4192-bdb7-7be3f0e6bb20)
