#include <Stepper_28BYJ.h> // изменить количество шагов для вашего мотора
#define STEPS 4078
Stepper_28BYJ stepper(STEPS, 8, 9, 10, 11);
int noisePin = 7;// пин датчика шума
int Timer=10000; // Время работы шагового двигателя после выявления первого шума
unsigned long prev_time = 0; // Время с момента прошлой проверки
unsigned long curr_time = 0; // Текущее время
boolean current = false; // Текущщее состояние датчика шума
boolean previous = false; // Предыдущее состояние датчика шума
boolean current2 = false; // Текущщее состояние датчика шума в случае повторного срабатывания
boolean previous2 = false; // Предыдущее состояние датчика шума в случае повторного срабатывания
void setup(){
stepper.setSpeed(5); // Скорость вращения
pinMode (noisePin, INPUT);
}
void loop(){
do{ // Опрос датчика шума
current=!digitalRead(noisePin); // Выявление шума
if(!current && previous){ // Если появился шум 
do{ // Вращение шагового двигателя и опрос датчика шума
curr_time = millis(); // Считать значение текущего времени
current2=!digitalRead(noisePin); // Выявление повторного шума
if(!current2 && previous2){ prev_time=millis(); } // Если шум выявлен, считать значение текущего времени (обнулить таймер)
stepper.step(1);// Совершать шаги
previous2 = current2; // Записать в ячейку для прошлого состояния датчика шума при повторном срабатывании текущее
}
while (curr_time - prev_time <= Timer);// На время Timer вращять шаговый двигатель и выявлять повторный шум
}
previous = current; // Записать в ячейку прошлого состояния датчика шума текущее
}
while (curr_time - prev_time == 10); // Каждые 10 мс сравнивать текущее и предидущее цифр. значение с датчика шума
prev_time = millis(); // Считать значение предыдущего времени
}
