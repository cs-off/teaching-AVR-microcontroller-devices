unsigned long timing; // Таймер опроса термопары
int latchPin = 9;// Пин «защелки» регистра подключен к ST_CP (SS) входу
int clockPin = 8; // Пин подключен к SH_CP (CLK) входу 74HC595
int dataPin = 11; // Пин подключен к DS входу 74HC595
int CS = 5; // Пин подключен к CS выходу MAX6675
int SO=6; // Пин подключен к MISO входу MAX6675
int CLK=7; // Пин подключен к CLK выходу MAX6675
int val; // Текущее значение температуры
int g_registerArray[2]={12,13}; // Пины разрядов цифр (Аноды LED)
byte g_digits[10]={ // Массив единицы 
B11000000, B11111001, // 0 1
B10100100, B10110000, // 2 3
B10011001, B10010010, // 4 5
B10000010, B11111000, // 6 7
B10000000, B10010000, // 8 9
};
byte g_digits_dp[10]={ // Массив с точкой (сотые, десятые)
B01000000, B01111001, // 0 1
B00100100, B00110000, // 2 3
B00011001, B00010010, // 4 5
B00000010, B01111000, // 6 7
B00000000, B00010000, // 8 9
};
void setup() {
pinMode(latchPin, OUTPUT); // Устанавливаем режим работы SPI контактов регистра 74HC595
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
pinMode(SO, INPUT);  // Устанавливаем режим работы SPI контактов MAX6675
pinMode(CLK, OUTPUT);
pinMode(CS, OUTPUT);
digitalWrite(CS, HIGH);
for(int i=0; i<=1; i++) // Устанавливаем Аноды индикатора
{
pinMode (g_registerArray[i],OUTPUT);
digitalWrite(g_registerArray[i], 1);
}
}

void loop() {
if (millis() - timing > 250){ // Таймер. Каждые 250 мс снимать значение температуры с MAX6675
timing = millis(); 
val=Celsius();
}
if (val <10) { // Разбиение выводимого числа
Indicat(g_digits[val],1);
} else if (val<100){
Indicat(g_digits[(val%100)/10], 0);
Indicat(g_digits[val%10],1);
} else if (val<200)
{
Indicat(g_digits_dp[(val%100)/10], 0);
Indicat(g_digits[val%10],1);
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

void Indicat(byte Mask, int Anode) // Динамическая индикация заданной маски на указанном разряде (аноде)
{
digitalWrite(latchPin, LOW); // Устанавливаем синхронизацию «защелки» на LOW
shiftOut(dataPin, clockPin, MSBFIRST, Mask); // Записываем информацию для регистра
digitalWrite(latchPin, HIGH); // «Защелкиваем» регистр, тем самым устанавливая значения на выходах
digitalWrite (g_registerArray[Anode],0); // Включаем цифру в заданном разряде
delay(8); // Пауза, чтобы сегменты «разгорелись»
digitalWrite (g_registerArray[Anode],1); // Гасим цифру  
}
