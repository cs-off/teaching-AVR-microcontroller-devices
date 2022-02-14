#include <Stepper_28BYJ.h>
#define STEPS 4078
Stepper_28BYJ stepper(STEPS, 8, 9, 10, 11);
int switch_pin=12; // пин кнопки
#include <max6675.h> // Подключаем библиотеку max6675 для работы с датчиком температуры
unsigned long timing; // Переменная для хранения времени. Таймер опроса термопары
int MAX_TEMP=300;// Предельная температура. Для регулировки макс. угла шагового двигателя
int CS = 5; // Пин подключен к CS выходу MAX6675
int SO=6; // Пин подключен к MISO входу MAX6675
int CLK=7; // Пин подключен к CLK выходу MAX6675
MAX6675 thermocouple(CLK, CS, SO); // Создаём объект MAX6675
int val; // текущее значение температуры
int exval=0;
bool set=1;
void setup()
{
Serial.begin(9600);

pinMode(SO, INPUT);  // устанавливаем режим работы SPI контактов MAX6675
pinMode(CLK, OUTPUT);
pinMode(CS, OUTPUT);
digitalWrite(CS, HIGH);
stepper.setSpeed(4);
pinMode(switch_pin, INPUT);// Сконфигурировать контакт кнопки как
digitalWrite(switch_pin, HIGH);// Включаем подтягивающий резистор
}
void loop()// бесконечный цикл
{
if ((digitalRead (switch_pin)==LOW)) set=false;
Serial.println(set);

if (set==true)stepper.step(-1);
else {
if (millis() - timing > 500){ // таймер на каждые 250 мс снимать значение температуры с MAX6675
timing = millis(); //обнулить тайммер
val=round(thermocouple.readCelsius());//счиатьт температуру в гр. Цельсия
val=constrain(val,0,MAX_TEMP);// Ограничить переменную в интрвал
val=map(val,0,MAX_TEMP,0,2039);
}
Serial.println(val);
if (val<exval) stepper.step(-(exval-val)); 
else stepper.step(val-exval);
exval=val;
}
}
