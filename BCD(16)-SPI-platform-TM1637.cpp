#include <SPI.h>// Инициализация библиотеки SPI
#include "TM1637.h"// Инициализация библиотеки TM1637
#define CLK 3 // Обозначение вывода CLK TM1637
#define DIO 2 //Обозначение вывода DIO TM1637
TM1637 tm1637(CLK, DIO); // Создание TM1637
#define ssin_165 9 // пин SS 74HC165
#define datain_165 6 // пин DS 74HC165
#define clk_165 7 // пин CLK 74HC165
byte v = 0;// переменная для текущей битовой маски
byte str1 = 0;// первый бит от BCD
byte str2 = 0;// второй бит от BCD
void setup()
{
  SPI.begin();// начало работы SPI
  pinMode(datain_165, INPUT); // конфигурация выводов 74HC165
  pinMode(clk_165, OUTPUT);
  pinMode(ssin_165, OUTPUT);
  digitalWrite(ssin_165, HIGH);
  tm1637.init();//Инициализация модуля TM1637
  tm1637.set(BRIGHT_TYPICAL);//Стандартная яркость TM1637
}
void loop()
{
delay(10);
digitalWrite(ssin_165, LOW); // Защелку вход вниз
digitalWrite(ssin_165, HIGH); // Защелку вход вверх
str1=shiftIn(datain_165, clk_165, LSBFIRST); // получаем маску строки
str2=shiftIn(datain_165,clk_165,LSBFIRST);
for (int j=3; j<=6; j++){ //1
if (j==3)bitWrite(v, 0, !bitRead(str2, j)); else bitWrite(v, j-3, !bitRead(str2, j));  
}
LED(1, v);
for (int j=0; j<=3; j++){ //2
if (j==0)bitWrite(v, 0, !bitRead(str1, 7)); else bitWrite(v, j, !bitRead(str2, j-1));  
}
LED(2, v);
for (int j=0; j<=3; j++){ //3
if (j==3)bitWrite(v, 0, !bitRead(str1, 3)); else bitWrite(v, j+1, !bitRead(str1, j));    
}
LED(3, v);
}

void LED(int num, byte mask) { //Функция для перевода из двоичной битовой маски в шетнадцатиричное значение на TM1637
int BCD_Value[4] = {8, 4, 2, 1}; // Массив значений четырёхбитного двоичного кода
int val; // Переменная для хранения текущего шестнадцатиричного значения 
val=0;
for (int i = 0; i <= 3; i++) if (bitRead(mask, i) == 1) val = val + BCD_Value[i];//цикл по маске разряда. Если элемент маски под текущим индексом цикла равен 1, то прибавим перменной val  элемент массива под текущим индексом цикла
tm1637.display(num, val); // выводим значение одного разряда на индикатор
}
