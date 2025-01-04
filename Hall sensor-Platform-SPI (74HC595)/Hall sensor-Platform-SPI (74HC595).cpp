#include <SPI.h>
int analogPin = A0; // Аналоговый выход датчика Холла
int value=0; // Значение датчика Холла
unsigned long timing; // Таймер опроса датчика Холла
int ss_Pin = 10; // Пин «защелки» регистра подключен к ST_CP (SS) входу
int clk_Pin = 13; // Пин подключен к SH_CP (CLK) входу 74HC595
int ds_Pin = 12; // Пин подключен к DS входу 74HC595
float vot;
float gaus;
byte g_digits[12]={
B00111111, B00000110, // 0 1
B01011011, B01001111, // 2 3
B01100110, B01101101, // 4 5
B01111101, B00000111, // 6 7
B01111111, B01101111, // 8 9
B00000000, B01000000}; // _ -
byte g_pin[4]={B01111111, B10111111, B11011111, B11101111}; // Катоды индикатора
void setup() {
SPI.begin();
pinMode(clk_Pin, OUTPUT);
pinMode(ds_Pin, OUTPUT);
pinMode(ss_Pin, OUTPUT);
pinMode(analogPin, INPUT);
}
void loop(){
if (millis() - timing > 250)
{
timing = millis();
float analogValue = analogRead(analogPin);
vot=(analogValue*5)/1023;
gaus=round(((vot-2.6)*1000)/1.4);
value = gaus;// считываем аналоговое значение и переводим в Гауссы
}
//Работа с условиями
if (value<0){
if (value>-10){
LCD(11,2);
LCD(value,3);
}
else if (value>-100){
LCD(11,1);
LCD((value%100)/10,2);
LCD(value%10,3);
}
else if (value>-1000){
LCD(11,0);
LCD((value%1000)/100, 1);
LCD((value%100)/10,2);
LCD(value%10,3);
}
}
else
{
if (value <10)
{
LCD(value,3);
}
else if (value<100)
{
LCD((value%100)/10,2);
LCD(value%10,3);
}
else if (value<1000)
{
LCD((value%1000)/100, 1);
LCD((value%100)/10,2);
LCD(value%10,3);
}
}
}
void LCD(int val1, int val2)
{
digitalWrite(ss_Pin, LOW);
shiftOut(ds_Pin, clk_Pin, LSBFIRST, g_pin[val2]);
shiftOut(ds_Pin, clk_Pin, MSBFIRST, g_digits[abs(val1)]);
digitalWrite(ss_Pin, HIGH);
delay(1);
}
