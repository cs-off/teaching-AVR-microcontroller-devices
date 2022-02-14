#include <Wire.h> // Библиотека для работы через интерфейс I2C
int shet_pin1=12; // Цифровой выход для счетчика 
int shet_pin2=13; // Цифровой выход для счетчика 
byte address1 = 0x20; // Адрес расширителя PCF8574
int val=0; // Счетчик срабатываний фоторезистора
unsigned long timer2; // Тайамер
unsigned long prev_time = 0; // Время с момента прошлой проверки
unsigned long curr_time = 0; // Текущее время
int fall=0; // счетчик количества шагов на переключение первого разряда
bool s_pin=0; // счетчик текущей комбинации HIGH-LOW на shet_pin
boolean current = false; // Текущщее состояние фоторезистора
boolean previous = false; // Предыдущее состояние фоторезистора
void setup() {
Wire.begin(); // Инициализация библиотеки Wire 
pinMode(shet_pin1, OUTPUT); // Устанавливаем цифровые выходы для счетчика
pinMode(shet_pin2, OUTPUT);
}
void loop() {
prev_time = millis(); // Считать значение текущего времени
do{ // Подсчёт срабатываний фоторезистора
Wire.beginTransmission(address1); //Начинаем процедуру передачи данных по интерфейсу I2C
Wire.write(B11111111); //Подтяжка
Wire.endTransmission(); // Завершаем процедуру передачи данных
Wire.requestFrom(address1, 1); // Получаем 1 байт
byte mask =Wire.read(); // Получаем маску строки
current=bitRead(mask,0);
if(current && !previous){ // Если текущее состояние - 0 и прошлое - 1, то  
do { // выполнить шаги счетчиком
if (millis() - timer2 > 50){ // таймер паузы между шагами
timer2 = millis(); // обнулить таймер
fall++; //счетчик шагов +1
if (s_pin==0){
digitalWrite(shet_pin2, HIGH);
digitalWrite(shet_pin1, LOW);
s_pin=1;
}
else{
digitalWrite(shet_pin2, LOW);
digitalWrite(shet_pin1, HIGH);
s_pin=0;
}
}
} while (fall<=19);
curr_time = millis(); // Считать текущее время      
} else fall=0;
previous = current; // Записать в ячейку прошлого состояния текущее
}
while (curr_time - prev_time == 10); //Таймер. Каждые 10 мс сравнивать текущее и предидущее цифр. значение с фоторезистора
}
