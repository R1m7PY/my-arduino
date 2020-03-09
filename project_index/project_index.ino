#include <Servo.h> // библиотека для серво
#include <NewPing.h> // библиотека для echo

//--создаем объекты--//
Servo servo1; // первый сервопривод
Servo servo2; // второй сервопривод
Servo last_r; // серво для правого ласта
Servo last_l; // серво для левого ласта
//-------------------//

#define TRIGGER_PIN  2  // пин trig датчика
#define ECHO_PIN     5  // пин echo датчика
#define MAX_DISTANCE 400 // максимальная дистанция echo
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int angle_last; // угол поворота ласт
int p_last = 0; // начальное положение ласт
unsigned long del_last = 0; // переменная для хранения времени от начала работы платы для ласт
//byte flag_last = 1; // флаг о положении ласт

//--переменные для хвоста--//
int p = -50; // начальное положение хвоста
int i_1 = 0; // переменная для цикла вращения 1 ч. хвоста
int i_2 = 0; // переменная для цикла вращения 2 ч. хвоста
unsigned long del_hvost1 = 0; // переменная для хранения времени от начала работы платы для хвоста
unsigned long del_hvost2 = 0;
byte flag_d = 1; // флаг о движении хвоста
byte flag_n = 1; // флаг о направлении движения хвоста
//-------------------------//

void setup() {
  servo1.attach(7); // серво1 подключен к пину 7
  servo2.attach(8); // серво2 подключен к пину 8
  last_r.attach(12); // правый ласт подключен к 9 пину
  last_l.attach(4); // левый ласт подключен к 6 пину
  /* питание от внешнего блока питания */
  Serial.begin(9600); // монитор порта
  servo1.write(i_1 + p);
  servo2.write(i_2 + p);
  last_r.write(0 + p_last);
  last_l.write(0 + p_last);
}

void loop() {
//--движение хвостом--//
  if (flag_d == 1 && flag_n == 1 && millis() - del_hvost1 >= 30){
    del_hvost1 = millis();
    servo1.write(i_1 + p);
    i_1++;
    if (i_1 == 30) {
      flag_d = 0;
      flag_n = 0;
    }
  }

  if (flag_d == 1 && flag_n == 0 && millis() - del_hvost1 >= 30){
    del_hvost1 = millis();
    servo1.write(i_1 + p);
    i_1--;
    if (i_1 == 0) {
      flag_d = 0;
      flag_n = 1;
    }
  }

  if (flag_d == 1 && flag_n == 0 && millis() - del_hvost2 >= 30){
    del_hvost2 = millis();
    servo2.write(i_2 + p);
    i_2++;
    if (i_2 == 30){
      flag_d = 1;
    }
  }

  if (flag_d == 1 && flag_n == 1 && millis() - del_hvost2 >= 30){
    del_hvost2 = millis();
    servo2.write(i_2 + p);
    i_2--;
    if (i_2 == 0){
      flag_d = 1;
    }
  }
//---------------------//

//--движение ластами--//
  if (Serial.available() > 0 && flag_last == 1) { // проверяем буфер порта и положение флажка
    //flag_last = 2; // поднимаем флажок
    angle_last = Serial.parseInt();
    last_r.write(angle_last + p_last); // наклоняем ласты на нужный угол
    last_l.write(angle_last + p_last);
    last_r.write(0 + p_last);
    last_l.write(0 + p_last);
    //del_last = millis();
  }
  if (flag_last == 2 && millis() - del_last >= 1000) { // проверяем положения флажка и время задержки
    last_r.write(0 + p_last); // возвращаем ласты в исходное положение
    last_l.write(0 + p_last);
    flag_last = 1; // опускаем флажок
    Serial.flush(); // очищаем буфер порта
  }
//-------------------//
}

//--функции, используемые в коде--//

int rost() { // функция, возращающая нужную задержку для серво
  int a; // возвращаемая переменная
  unsigned int distance = sonar.ping_cm(); // сохраняем в переменную дистанцию
  
  Serial.print("disttance "); 
  Serial.println(distance);   // выводим дистанцию в порт

  if (distance < 100) { // изменяем задержку в зависимости от растояния
    a = 10;
  } else if (distance < 150) {
    a = 15;
  } else if (distance < 200) {
    a = 20;
  } else if (distance < 250) {
    a = 25;
  } else if (distance < 300) {
    a = 30;
  } else {
    a = 40;
  }
  return a;
}
