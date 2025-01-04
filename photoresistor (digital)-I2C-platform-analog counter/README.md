Data converter Photoresistor(digital) G5516-I2C-Platform-Analog counter
=

  According to the technical specifications, it is necessary to organize the transfer of a digital value from the photoresistor through the PCF8574 expander via the I2C protocol to the Arduino Uno platform, process the information, and count the number of photoresistor operations using the LY200 electromechanical counter.
  The technical specifications describe the operating principle of the component counter, so it should be taken into account that one change in the digital value of the photoresistor should be counted once, and not as multiple operations, i.e. expressed in the continuous rotation of the counter.
  
  ![image](https://github.com/user-attachments/assets/5019caf7-54ae-406d-9619-5234bdcb156b)

Circuit components:

-Photoresistor(digital) G5516(VT83N1) *1

-Arduino platform

-PCF8574*1

-Analog counter LY200-51L5/5V *1

-Resistor SR1206FR-07220RL*8

![image](https://github.com/user-attachments/assets/587cbb7a-6e27-4560-a701-7d46ad7d97d5)

![image](https://github.com/user-attachments/assets/93cd110d-23ee-4af2-b3c6-d48dff3adb55)
