int digitalGerkon = 7; // Цифровой вход геркона
int val=0; // Счетчик срабатываний геркона
unsigned long timer; // Тайамер
unsigned long prev_time = 0; // Время с момента прошлой проверки
unsigned long curr_time = 0; // Текущее время
int latchPin = 9;// Пин «защелки» регистра подключен к ST_CP (SS) входу
int clockPin = 8; //Пин подключен к SH_CP (CLK) входу 74HC595
int dataPin = 11; //Пин подключен к DS входу 74HC595
int Time=10; // Время, в течение которого будет производится подсчёт срабатываний геркона
boolean gerk = false; // Текущщее состояние геркона
boolean previous = false; // Предыдущее состояние геркона
int g_registerArray[2]={12,13}; // Пины разрядов цифр (Аноды LED)
byte g_digits[12]={
B11000000, B11111001, // 0 1
B10100100, B10110000, // 2 3
B10011001, B10010010, // 4 5
B10000010, B11111000, // 6 7
B10000000, B10010000, // 8 9
};
byte g_digits_dp[12]={
B01000000, B01111001, // 0 1
B00100100, B00110000, // 2 3
B00011001, B00010010, // 4 5
B00000010, B01111000, // 6 7
B00000000, B00010000, // 8 9
};
void setup() {
pinMode(digitalGerkon, INPUT);  // Устанавливаем цифровой контакт геркона
pinMode(latchPin, OUTPUT); // Устанавливаем контакты регистра
pinMode(clockPin, OUTPUT);
pinMode(dataPin, OUTPUT);
for(int i=0; i<=1; i++) // Устанавливаем Аноды
{
pinMode (g_registerArray[i],OUTPUT);
digitalWrite(g_registerArray[i], 1);
}
}
void loop() {
prev_time = millis(); // Считать значение текущего времени
do 
{ // Подсчёт срабатываний геркона
boolean current = digitalRead(digitalGerkon); // Считывание текущего состояния геркона
if(current && !previous) // Если текущее состояние - 1 и прошлое - 0, то  
{
gerk = !gerk; // Переключить геркон в противоположное состояние
if (val>199) val=0; else val++; // Увеличить счётчик срабатываний на 1 или обнулить
curr_time = millis(); // Считать текущее время      
}
previous = current; // Записать в ячейку прошлого состояния текущее
}
while (curr_time - prev_time == Time); // Если прошло заданное время
if (val <10) { // Разбиение выводимого числа
Indication(B11111111, 0);
Indication(g_digits[val],1);
} else if (val<100){
Indication(g_digits[(val%100)/10], 0);
Indication(g_digits[val%10],1);
} else if (val<200)
{
Indication(g_digits_dp[(val%100)/10], 0);
Indication(g_digits[val%10],1);
}
}
void Indication(byte Mask, int Anode) // Динамическая индикация заданной маски на указанном разряде (аноде)
{
digitalWrite(latchPin, LOW); // Устанавливаем синхронизацию «защелки» на LOW
shiftOut(dataPin, clockPin, MSBFIRST, Mask); // Записываем информацию для регистра
digitalWrite(latchPin, HIGH); // «Защелкиваем» регистр, тем самым устанавливая значения на выходах
digitalWrite (g_registerArray[Anode],0); // Включаем цифру в заданном разряде
delay(1); // Пауза, чтобы сегменты «разгорелись»
digitalWrite (g_registerArray[Anode],1); // Гасим цифру  
}
