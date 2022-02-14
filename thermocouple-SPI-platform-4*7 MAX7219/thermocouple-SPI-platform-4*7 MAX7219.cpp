#include <LedControl.h>
LedControl LC = LedControl(12, 11, 10, 3); // dataPin, clkPin, csPin, кол. разрядов индикатора
unsigned long timing; // Таймер опроса термопары
int CS = 5; // Пин подключен к CS выходу MAX7219 
int SO=6; // Пин подключен к MISO входу MAX7219 
int CLK=7; // Пин подключен к CLK выходу MAX7219 
int value; // Текущее значение температуры

void setup() {
pinMode(SO, INPUT);  // Устанавливаем режим работы SPI контактов MAX7219 
pinMode(CLK, OUTPUT);
pinMode(CS, OUTPUT);
digitalWrite(CS, HIGH);
LC.shutdown(0, false); // разбудить MAX7219 
LC.setIntensity(0, 8); // средняя яркость
LC.clearDisplay(0); // очистка дисплея
}

void loop() {
if (millis() - timing > 250){ // Таймер. Каждые 250 мс снимать значение температуры с MAX7219 
timing = millis(); //Обнулить таймер
value=Celsius(); //Считать текущее значение температуры
value=constrain(value, 0, 800); // ограничить значения температуры
if (value <10) // выведение температуры на дисплей
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
}
}

int Celsius(void) { // Функция для вывода температуры термопары в Гр. Цельсия
uint16_t v; // Переменная в 2 байта 
digitalWrite(CS, LOW); // Защелку вниз
delayMicroseconds(10); 
v = SPI_Read(); // Вызов функции на считывание двух бит
v <<= 8; // Сдвиг на 8 битов влево (для записи второго бита в одну перемнную)
v |= SPI_Read(); // Объеденить (логич И) v с следующим выданным функцией чилом
digitalWrite(CS, HIGH); // Защелку вверх
if (v & 0x4) return 0; // Если нет термопары возвращает значение 0. 0x4==01000000
v >>= 3; // Сдвиг на 3 бита вправо
return round(v*0.25); // Сдвиг на 3 бита вправо
}

byte SPI_Read (void){ // Функция для работы с SPI без использования библиотек
int i; // Счетчик
byte d = 0; // значение в 2 бита
for (i = 7; i >= 0; i--) { // Обратный цикл
digitalWrite(CLK, LOW); // Такт вниз
delayMicroseconds(10); // Эмуляция работы тактового сигнала
if (digitalRead(SO)) { // Установит бит в 0
d |= (1 << i); // Объеденить (логич И) d со сдвигом единицы на i бит влево 
}
digitalWrite(CLK, HIGH); // Такт вверх
delayMicroseconds(10); // Эмуляция работы тактового сигнала
}
return d; // Возвращает значение в 2 бита
}
