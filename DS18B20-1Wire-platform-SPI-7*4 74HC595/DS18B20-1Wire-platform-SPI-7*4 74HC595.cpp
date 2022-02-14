#include <SPI.h>
#include <OneWire.h>
OneWire ds(7); // Объект OneWire
int temperature = 0; // Значение датчика температуры
int val= 0;// Значение датчика температуры
long lastUpdateTime = 0; // Переменная для хранения времени последнего считывания с датчика
const int TEMP_UPDATE_TIME = 100; // Определяем периодичность проверок
unsigned long timing; // Таймер опроса датчика температуры
int ss_Pin = 10; // Пин «защелки» регистра подключен к ST_CP (SS) входу
int clk_Pin = 13; // Пин подключен к SH_CP (CLK) входу 74HC595
int ds_Pin = 12; // Пин подключен к DS входу 74HC595
byte g_digits[12]={
B00111111, B00000110, // 0 1
B01011011, B01001111, // 2 3
B01100110, B01101101, // 4 5
B01111101, B00000111, // 6 7
B01111111, B01101111, // 8 9
B00000000, B01000000}; // _ -
byte g_pin[4]={B01111111, B10111111, B11011111, B11101111}; // Катоды индикатора
void setup() {
pinMode(clk_Pin, OUTPUT);
pinMode(ds_Pin, OUTPUT);   
pinMode(ss_Pin, OUTPUT);
} 
void loop(){
detectTemperature();
val=temperature;
if (val<0)
{
if (val>-10)
{
LCD(11,2);  
LCD(val,3);
// Serial.println((String)analogValue);
}
else if (val>-100)
{
LCD(11,1);    
LCD((val%100)/10,2);
LCD(val%10,3);
} 
else if (val>-1000)
{
LCD(11,0);    
LCD((val%1000)/100, 1);
LCD((val%100)/10,2);
LCD(val%10,3);
}
} 
else
{
if (val <10)
{
LCD(val,3);
} 
else if (val<100)
{
LCD(val%10,3);
LCD((val%100)/10,2);
} 
else if (val<1000)
{
LCD((val%1000)/100, 1);
LCD((val%100)/10,2);
LCD(val%10,3);
}
}
}

void LCD(int val1, int val2)
{
digitalWrite(ss_Pin, LOW);
shiftOut(ds_Pin, clk_Pin, LSBFIRST, g_pin[val2]); 
shiftOut(ds_Pin, clk_Pin, MSBFIRST, g_digits[val1]); 
digitalWrite(ss_Pin, HIGH);
delay(1);  
}

int detectTemperature(){ // Функуция: Определяем температуру от датчика DS18b20
  byte data[2];// Место для значения температуры
  ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  if (millis() - lastUpdateTime > TEMP_UPDATE_TIME)
  {
    lastUpdateTime = millis();
 ds.reset(); // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC); 
  ds.write(0xBE); // Просим передать нам значение регистров со значением температуры
  // Получаем и считываем ответ
  data[0] = ds.read(); // Читаем младший байт значения температуры
  data[1] = ds.read(); // А теперь старший
  // Формируем итоговое значение: 
  //    - сперва "склеиваем" значение, 
  //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
 temperature = (data[1] << 8) + data[0]; temperature = temperature >> 4;
  }
}
