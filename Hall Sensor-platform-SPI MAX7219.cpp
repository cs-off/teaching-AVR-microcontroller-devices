#include <LedControl.h>
LedControl LC = LedControl(12, 11, 10, 3); // dataPin, clkPin, csPin, кол. разрядов
int GaussPin= A0; //Обозначение вывода DIO TM1637
float vot;
int value;// Значение датчика Холла
void setup()
{
Serial.begin(9600);
pinMode(GaussPin, INPUT); // конфигурация вывод
LC.shutdown(0, false);
LC.setIntensity(0, 8);
LC.clearDisplay(0);
}
void loop()
{
delay(100);// задержка 100 мс
float analogValue = analogRead(GaussPin);
vot=(analogValue*5)/1023;
value=round(((vot-2.6)*1000)/1.4); // считываем аналоговое значение и переводим в Гауссы
if (value<0){
 if (value>-10){
  LC.setChar(0, 2, '-', false);
  LC.setDigit(0, 3, abs(value), false);
  }
 else if (value>-100){
  LC.setChar(0, 1, '-', false);
  LC.setDigit(0, 2, (abs(value)%100)/10, false);
  LC.setDigit(0, 3, abs(value)%10, false);
  } 
 else if (value>-1000){
  LC.setChar(0, 0, '-', false);
  LC.setDigit(0, 1, (abs(value)%1000)/100, false);
  LC.setDigit(0, 2, (abs(value)%100)/10, false);
  LC.setDigit(0, 3, abs(value)%10, false);
  }
 else if (value>-10000){
  LC.setChar(0, 0, '-', false);
  LC.setDigit(0, 1, (abs(value)%10000)/1000, false);
  LC.setDigit(0, 2, (abs(value)%1000)/100, false);
  LC.setDigit(0, 3, (abs(value)%100)/10, false);
  }
}
else
{
if (value <10)
{
  LC.setDigit(0, 3, (value), false);
} 
else if (value<100)
{
  LC.setDigit(0, 2, (value%100)/10, false);
  LC.setDigit(0, 3, (value%10), false);
} 
else if (value<1000)
{
  LC.setDigit(0, 1, (value%1000)/100, false);
  LC.setDigit(0, 2, (value%100)/10, false);
  LC.setDigit(0, 3, (value%10), false);
}
else if (value<10000)
{
  LC.setDigit(0, 0, (value%10000)/1000, false);
  LC.setDigit(0, 1, (value%1000)/100, false);
  LC.setDigit(0, 2, (value%100)/10, false);
  LC.setDigit(0, 3, (value%10), false);
}
}
}
