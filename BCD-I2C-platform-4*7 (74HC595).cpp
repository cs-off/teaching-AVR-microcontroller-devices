#include <Wire.h> // Библиотека для работы через интерфейс I2C
byte address1 = 0x21; // Адрес первого расширителя PCF8574
byte address2 = 0x20; // Адрес второго расширителя PCF8574
int ss_Pin = 10;//Пин «защелки» регистра подключен к ST_CP (SS) входу
int clk_Pin = 13; //Пин подключен к SH_CP (CLK) входу 74HC595
int ds_Pin = 12; //Пин подключен к DS входу 74HC595

void setup() {
  Wire.begin(); // Инициализация библиотеки Wire
  pinMode(clk_Pin, OUTPUT); // Обозначение всех пинов как выходы
  pinMode(ds_Pin, OUTPUT);
  pinMode(ss_Pin, OUTPUT);
}

void loop() {
  BCD(ExpBoardPolling(address1), ExpBoardPolling(address2));
}

byte ExpBoardPolling (int address) // Функция для опроса платы расширения
{
  Wire.beginTransmission(address); //Начинаем процедуру передачи данных по интерфейсу I2C
  Wire.write(B11111111); //Подтяжка
  Wire.endTransmission(); // Завершаем процедуру передачи данных
  Wire.requestFrom(address, 1); // Получаем 1 байт
  byte mask = Wire.read(); // Получаем маску строки
  return mask; // Возвращяем маску строки
}

void BCD(byte mask1, byte mask2) //Функция для перевода двоичного кода в десятичное число
{
  int BCD_Value[4] = {1, 2, 4, 8}; // Массив значений четырёхбитного двоичного кода
  int val; // Переменная для хранения текущего десятичного значения
  for (int i = 0; i <= 3; i++) if (bitRead(mask1, i) == 0) val = val + BCD_Value[i];
  Dynamic_LED(val, 0);
  val = 0;
  for (int i = 4; i <= 7; i++) if (bitRead(mask1, i) == 0) val = val + BCD_Value[i - 4];
  Dynamic_LED(val, 1);
  val = 0;
  for (int i = 0; i <= 3; i++) if (bitRead(mask2, i) == 0) val = val + BCD_Value[i];
  Dynamic_LED(val, 2);
  val = 0;
  for (int i = 4; i <= 7; i++) if (bitRead(mask2, i) == 0) val = val + BCD_Value[i - 4];
  Dynamic_LED(val, 3);
}

void Dynamic_LED (int val, int digit) // Процедура для динамической индикации
{
  byte g_num[10] = {
    B00111111, B00000110, // 0 1
    B01011011, B01001111, // 2 3
    B01100110, B01101101, // 4 5
    B01111101, B00000111, // 6 7
    B01111111, B01101111, // 8 9
  }; //Битовые маски для анодов индикатора
  byte g_digit[4] = {B01111111, B10111111, B11011111, B11101111}; //Битовые маски для катодов индикатора
  digitalWrite(ss_Pin, LOW); // Защелку вниз
  shiftOut(ds_Pin, clk_Pin, LSBFIRST, g_digit[digit]); // Вывод в IIC текущего разряда (катода) индикатора, старший значащий бит первым
  shiftOut(ds_Pin, clk_Pin, MSBFIRST, g_num[val]); // Вывод в IIC текущего значения индикатора (анода), младший значащий бит первым
  digitalWrite(ss_Pin, HIGH); // Защелку вверх
  delay(1); // Время на "разжигание" светодиодов
}
