#include <Servo.h> // библиотека для серво
#include <NewPing.h> // библиотека для echo

//--создаем объекты--//
Servo hvost_d; // первый сервопривод
Servo hvost_b; // второй сервопривод
Servo last_r; // серво для правого ласта
Servo last_l; // серво для левого ласта
//-------------------//

//--подключаем echo--//
#define TRIGGER_PIN  2  // пин trig датчика
#define ECHO_PIN     3  // пин echo датчика
#define MAX_DISTANCE 400 // максимальная дистанция echo
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//-------------------//

int i; // переменная для вращения хвоста

void setup() {
//--подключение серво к пинам--//
  hvost_d.attach(7);
  hvost_b.attach(8);
  last_r.attach(12);
  last_l.attach(4);
//-----------------------------//
  /* питание от внешнего блока питания */
  Serial.begin(9600); // монитор порта

  hvost_d.write(90 + 15);
  hvost_b.write(90 - 15);
  last_r.write(90);
  last_l.write(90);
  
}

void loop() {
  for (i = -15; i <= 15; i++) {
    delay(rost());
    hvost_b.write(90 + i);
    last_r.write(90 - i);
    last_l.write(90 + i);
  }
  
   for (i = 15; i >= -15; i--) {
    delay(rost());
    hvost_d.write(90 + i);
    last_r.write(90 - i);
    last_l.write(90 + i);
  }
  
   for (i = -15; i <= 15; i++) {
    delay(rost());
    hvost_b.write(90 - i);
    last_r.write(90 - i);
    last_l.write(90 + i);
  }
  
   for (i = 15; i >= -15; i--) {
    delay(rost());
    hvost_d.write(90 - i);
    last_r.write(90 - i);
    last_l.write(90 + i);
  }
}

//--функции, используемые в коде--//

int rost() { // функция, возращающая нужную задержку для серво
  unsigned int a; // возвращаемая переменная
  unsigned int distance = sonar.ping_cm(); // сохраняем в переменную дистанцию
  
  Serial.print("disttance "); 
  Serial.print(distance);   // выводим дистанцию в порт

  if (distance < 100 && distance > 0) { // изменяем задержку в зависимости от растояния
    a = 10;
  } else if (distance < 150 && distance > 0) {
    a = 15;
  } else if (distance < 200 && distance > 0) {
    a = 20;
  } else if (distance < 250 && distance > 0) {
    a = 25;
  } else {
    a = 30;
  }
  return a;
}
